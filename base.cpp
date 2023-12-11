#include "base.hpp"
#include "./ui_base.h"
#include "task_item_widget.hpp"
#include <QString>

Base::Base(QWidget *parent):
    QWidget(parent), ui(new Ui::Base)
{
    ui->setupUi(this);
    m_today     = ui->stackedWidget->findChild<QListWidget*>("todayListWidget");
    m_all_tasks = ui->stackedWidget->findChild<QListWidget*>("allTasksWidget");
    m_projects  = ui->stackedWidget->findChild<QListWidget*>("projectsWidget");
}

Base::~Base()
{
    delete ui;
}


void Base::on_pushButton_clicked()
{
    TaskItemWidget *taskItem = new TaskItemWidget("Тут буде якийсь текст", "12:00", m_today);

    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(taskItem->sizeHint());

    m_today->addItem(item);
    m_today->setItemWidget(item, taskItem);
}

