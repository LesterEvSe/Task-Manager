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

void Base::on_pushButton_clicked()
{
    Task *taskDialog = create_custom_dialog();
    connect(taskDialog, &Task::sendData, this, [=](TaskData data) {

        QListWidgetItem *item = new QListWidgetItem();
        TaskItemWidget *taskItem = new TaskItemWidget(data, m_today, this, item);

        item->setSizeHint(taskItem->sizeHint());
        m_today->addItem(item);
        m_today->setItemWidget(item, taskItem);
    });
    taskDialog->exec();
}

/*
void Base::mousePressEvent(QMouseEvent *event) {
    // Get the widget we clicked on
    QWidget *curr_widget = qApp->widgetAt(event->globalPos());

    QMessageBox::information(this, "layer 0", "");
    QListWidget *listWidget = qobject_cast<QListWidget*>(curr_widget);
    if (!listWidget) {
        // Basic implementation here
        QWidget::mousePressEvent(event);
        return;
    }

    QMessageBox::information(this, "layer 1", "get listWidget");

    QListWidgetItem *item = listWidget->itemAt(event->pos());
    if (!item) {
        QWidget::mousePressEvent(event);
        return;
    }
    QMessageBox::information(this, "layer 2", "get item");
    item->setText("новый текст");
    listWidget->repaint();
    return;


    TaskItemWidget *customItem = qobject_cast<TaskItemWidget*>(listWidget->itemWidget(item));
    if (!customItem) {
        QWidget::mousePressEvent(event);
        return;
    }

    Task *taskDialog = create_custom_dialog();
    connect(taskDialog, &Task::sendData, this, [=](TaskData data) {

        customItem->change_view(data);
        //        int ind = parentList->row(qobject_cast<QListWidgetItem*>(this));
        //        parentList->update(parentList->visualItemRect(parentList->item(ind)));
    });
    taskDialog->exec();
}
*/
