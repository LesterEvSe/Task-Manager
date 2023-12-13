#include "base.hpp"
#include "./ui_base.h"

#include "task_item_widget.hpp"
#include <QString>
#include "task.hpp"

Base::Base(QWidget *parent):
    QWidget(parent), ui(new Ui::Base)
{
    ui->setupUi(this);
    m_today     = ui->stackedWidget->findChild<QListWidget*>("todayListWidget");
    m_all_tasks = ui->stackedWidget->findChild<QListWidget*>("allTasksListWidget");
    m_projects  = ui->stackedWidget->findChild<QListWidget*>("projectsListWidget");
}

Base::~Base()
{
    delete ui;
}

void Base::on_pushButton_clicked()
{
    Task *taskDialog = new Task(this);
    taskDialog->resize(width(), taskDialog->height());

    QPoint currBottom = mapToGlobal(QPoint(0, height()));
    QSize dialogSize = taskDialog->size();
    taskDialog->move(0, currBottom.y() - dialogSize.height());

    if (taskDialog->exec() != QDialog::Accepted) return;
    TaskItemWidget *taskItem = new TaskItemWidget("Тут буде якийсь текст", "12:00", m_today);

    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(taskItem->sizeHint());
    m_today->addItem(item);
    m_today->setItemWidget(item, taskItem);
}

