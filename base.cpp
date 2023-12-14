#include "base.hpp"
#include "./ui_base.h"

#include "task_item_widget.hpp"
#include <QMessageBox> // for debug output

Base::Base(QWidget *parent):
    QWidget(parent), ui(new Ui::Base)
{
    QLocale::setDefault(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
    ui->setupUi(this);
    m_today     = ui->stackedWidget->findChild<QListWidget*>("todayListWidget");
    m_all_tasks = ui->stackedWidget->findChild<QListWidget*>("allTasksListWidget");
    m_projects  = ui->stackedWidget->findChild<QListWidget*>("projectsListWidget");

    QListWidgetItem *expired = new QListWidgetItem("Прострочено");
    m_today->addItem(expired);
    // here download expired data from db

    QListWidgetItem *today   = new QListWidgetItem(
        QDate::currentDate().toString("dd MMM ddd")
    );
    m_today->addItem(today);

    // here download today data from db
}

Base::~Base() {
    delete ui;
}

Task *Base::create_custom_dialog(const TaskData *data) {
    Task *taskDialog = new Task(this, data);
    taskDialog->resize(width(), taskDialog->height());

    QPoint currBottom = mapToGlobal(QPoint(0, height()));
    QSize dialogSize = taskDialog->size();
    taskDialog->move(0, currBottom.y() - dialogSize.height());
    return taskDialog;
}

void Base::create_task(TaskData data) {
    QListWidgetItem *item = new QListWidgetItem();
    TaskItemWidget *taskItem = new TaskItemWidget(data, m_today, this);
    connect(taskItem, &TaskItemWidget::sendNewData, this, &Base::create_task);

    item->setSizeHint(taskItem->sizeHint());
    m_today->addItem(item);
    m_today->setItemWidget(item, taskItem);
}

void Base::on_pushButton_clicked()
{
    Task *taskDialog = create_custom_dialog();
    connect(taskDialog, &Task::sendData, this, &Base::create_task);
    taskDialog->exec();
}
