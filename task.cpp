#include "task.hpp"
#include "ui_task.h"

Task::Task(QWidget *parent) :
    QDialog(parent), ui(new Ui::Task)
{
    ui->setupUi(this);

    ui->priorityBox->addItem("Пріоритет 1");
    ui->priorityBox->addItem("Пріоритет 2");
    ui->priorityBox->addItem("Пріоритет 3");
    ui->priorityBox->addItem("Пріоритет 4");
    ui->priorityBox->addItem("Пріоритет 5");

    // Other will be add in process
    ui->containerBox->addItem("Усі");
}

Task::~Task() {
    delete ui;
}

