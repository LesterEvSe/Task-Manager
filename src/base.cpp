#include "base.hpp"
#include "./ui_base.h"

#include "task_item_widget.hpp"
#include "task_enum.hpp"

#include <QMessageBox>
#include <QSqlError> // for exceptions


Base::Base(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Base),
    m_database(Database::get_instance())
{
    // For usual data and time view
    QLocale::setDefault(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
    ui->setupUi(this);

    m_today     = ui->stackedWidget->findChild<QListWidget*>("todayListWidget");
    m_all_tasks = ui->stackedWidget->findChild<QListWidget*>("allTasksListWidget");
    m_projects  = ui->stackedWidget->findChild<QListWidget*>("projectsListWidget");

    m_today->addItem(new QListWidgetItem("Overdue"));
    m_all_tasks->addItem(new QListWidgetItem("Overdue"));

    // Download overdue data
    for (const TaskData &data : m_database->get_task(TaskEnum::OVERDUE))
        create_task(data);

    m_today->addItem(new QListWidgetItem(
        QDate::currentDate().toString("dd MMM ddd")
    ));
    m_all_tasks->addItem(new QListWidgetItem("Current"));

    for (const TaskData &data : m_database->get_task(TaskEnum::ALL_ACTIVE))
        create_task(data);
}

Base::~Base() {
    delete ui;
}

void Base::show_error_and_exit(const QString &error) {
    QMessageBox::critical(this, "Error", error);
    exit(1);
}

Task *Base::create_custom_dialog(const TaskData *data) {
    Task *taskDialog = new Task(this, data);
    taskDialog->resize(width(), taskDialog->height());

    QPoint currBottom = mapToGlobal(QPoint(0, height()));
    QSize dialogSize = taskDialog->size();
    taskDialog->move(0, currBottom.y() - dialogSize.height());
    return taskDialog;
}

void Base::create_task(const TaskData &data) {
    QListWidgetItem *item = new QListWidgetItem();
    TaskItemWidget *taskItem = new TaskItemWidget(data, m_all_tasks, this);
    connect(taskItem, &TaskItemWidget::sendNewData, this, &Base::create_task);

    item->setSizeHint(taskItem->sizeHint());
    m_all_tasks->addItem(item);
    m_all_tasks->setItemWidget(item, taskItem);
    // and tasks for projects and today if need
}

void Base::on_pushButton_clicked()
{
    Task *taskDialog = create_custom_dialog();
    connect(taskDialog, &Task::sendData, this, &Base::create_task);
    taskDialog->exec();
}

void Base::on_allButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ALL_TASKS);
    ui->currPageLabel->setText("All Tasks");
}

void Base::on_todayButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(TODAY);
    ui->currPageLabel->setText("Today");
}

void Base::on_projectsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROJECTS);
    ui->currPageLabel->setText("Projects");
}

