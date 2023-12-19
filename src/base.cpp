#include "base.hpp"
#include "./ui_base.h"

#include "task_item_widget.hpp"
#include "task_enum.hpp"
#include "addproject.hpp"
#include "concreteproject.hpp"

#include <QMessageBox>
#include <QInputDialog>
#include <QSqlError> // for exceptions
#include <exception>

Database *Base::s_database = Database::get_instance();
int Base::s_beg_ind = 1; // After "Overdue" text


Base::Base(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Base)
{
    // For usual data and time view
    QLocale::setDefault(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
    ui->setupUi(this);

    m_today     = ui->stackedWidget->findChild<QListWidget*>("todayListWidget");
    m_all_tasks = ui->stackedWidget->findChild<QListWidget*>("allTasksListWidget");
    m_projects  = ui->stackedWidget->findChild<QListWidget*>("projectsListWidget");
    m_projects->setWordWrap(true);

    m_today->addItem(new QListWidgetItem("Overdue"));
    m_all_tasks->addItem(new QListWidgetItem("Overdue"));

    try {
    // Download overdue data
    for (const TaskData &data : s_database->get_task(TaskEnum::OVERDUE))
        create_task(data);

    m_today->addItem(new QListWidgetItem(
        QDate::currentDate().toString("dd MMM ddd")
    ));

    m_all_tasks->addItem(new QListWidgetItem("Current"));

    // ORDER IS IMPORTANT!!!
    /* Let's say there is data in a project, we fill the 'All' window,
    then when we create a task in 'All' we will want to add the task to a specific project,
    but the point is that the projects have not been create yet!
    The application will crash, that's all */

    // CREATE PROJECT
    for (const QString &project_name : s_database->get_projects()) {
        m_projects->addItem(new QListWidgetItem(project_name));
        create_project(project_name);
    }

    // CREATE TASK
    for (const TaskData &data : s_database->get_task(TaskEnum::ALL_ACTIVE))
        create_task(data);

    } catch (const QSqlError &error) {
        show_error_and_exit("Caught SQL error in func " + error.text());
    } catch (const std::exception& error) {
        show_error_and_exit("Caught exception: " + QString(error.what()));
    } catch(...) {
        show_error_and_exit("Caught unknown exception");
    }
}

Base::~Base() {
    delete ui;
}

std::vector<QString> Base::get_project_names() const {
    std::vector<QString> names;
    names.reserve(memo.size());

    for (auto it : memo)
        names.emplace_back(it.first);
    return names;
}

QString Base::get_curr_label_text() const {
    return ui->currPageLabel->text();
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
    auto create = [this](QListWidget *listWidget, const TaskData &new_data) {
        QListWidgetItem *item = new QListWidgetItem();
        TaskItemWidget *taskItem = new TaskItemWidget(new_data, listWidget, this);
        connect(taskItem, &TaskItemWidget::sendNewData, this, &Base::create_task);

        item->setSizeHint(taskItem->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, taskItem);
        return taskItem;
    };

    std::vector<TaskItemWidget*> tasks;
    tasks.emplace_back(create(m_all_tasks, data));
    const TaskData &temp = tasks[0]->get_data();

    if (temp.date == QDate::currentDate())
        tasks.emplace_back(create(m_today, temp));
    if (temp.group != "All")
        tasks.emplace_back(create(memo[temp.group].second, temp));

    for (TaskItemWidget *item : tasks)
        item->set_other_items(tasks);
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

void Base::set_project_widget() {
    Base::on_projectsButton_clicked();
}

void Base::on_addProjectButton_clicked()
{
    AddProject *project = new AddProject(this);
    project->resize(width(), project->height());

    QPoint currBottom = mapToGlobal(QPoint(0, height()));
    QSize dialogSize = project->size();
    project->move(0, currBottom.y() - dialogSize.height());

    connect(project, &AddProject::textEntered, this, [this](QString text){
        if (!s_database->add_project(text)) {
            QMessageBox::critical(this, "Error", "You can not add a project, which name already exist.");
            return;
        }
        QListWidgetItem *item = new QListWidgetItem(text);
        m_projects->addItem(item);
        create_project(text);
    });
    project->exec();
}

void Base::create_project(const QString &project_name) {
    ConcreteProject *project = new ConcreteProject(project_name, this);

    // need to do it, otherwise not displayed
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(project);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    int ind = ui->stackedWidget->addWidget(widget);
    memo[project_name] = {ind, project->get_list_widget()};
}

// It does not work properly
void Base::delete_project(const QString &project_name) {
    set_project_widget();
    try {
    s_database->del_project_and_tasks(project_name);
    } catch (const QSqlError &error) {
        show_error_and_exit("Caught SQL error in func " + error.text());
    }

    QListWidget *listWidget = memo[project_name].second;
    while (listWidget->count()) {
        QWidget *widget = listWidget->itemWidget(listWidget->item(0));
        TaskItemWidget *taskWidget = qobject_cast<TaskItemWidget*>(widget);
        taskWidget->delete_item();
    }

    for (int i = 0; i < m_projects->count(); ++i) {
        QListWidgetItem *item = m_projects->item(i);
        if (item->text() != project_name) continue;

        m_projects->takeItem(i);
        break;
    }
}

void Base::on_projectsListWidget_itemClicked(QListWidgetItem *item)
{
    QString project_name = item->text();
    ui->currPageLabel->setText(project_name);
    ui->stackedWidget->setCurrentIndex(memo[project_name].first);
}

