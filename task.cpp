#include "task.hpp"
#include "ui_task.h"

#include <QMessageBox>

Task::Task(QWidget *parent) :
    QDialog(parent), ui(new Ui::Task)
{
    ui->setupUi(this);

    ui->priorityBox->addItem("Пріоритет 1");
    ui->priorityBox->addItem("Пріоритет 2");
    ui->priorityBox->addItem("Пріоритет 3");
    ui->priorityBox->addItem("Пріоритет 4");
    ui->priorityBox->addItem("Пріоритет 5");

    ui->priorityBox->setCurrentIndex(4);

    // Other will be add in process
    ui->groupBox->addItem("Усі");

    connect(ui->cancelButton, &QPushButton::clicked, this, &Task::on_cancelButton_clicked);
    connect(ui->okButton, &QPushButton::clicked, this, &Task::on_okButton_clicked);
}

Task::~Task() {
    delete ui;
}

void Task::on_cancelButton_clicked() {
    QMessageBox dualChoose;
    dualChoose.setText("Видалити зміни?");
    dualChoose.setInformativeText("Внесені зміни не будуть збережені.");
    dualChoose.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if (dualChoose.exec() == QMessageBox::Ok)
        reject();
}

void Task::on_okButton_clicked() {
    TaskData task_data;
    task_data.task_describe = ui->mainTextEdit->toPlainText();
    task_data.date = ui->dateEdit->date();
    task_data.time = ui->timeEdit->time();
    task_data.priority = ui->priorityBox->currentText();
    task_data.group = ui->groupBox->currentText();

    emit sendData(task_data);
    accept();
}
