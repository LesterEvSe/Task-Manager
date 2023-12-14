#include "task.hpp"
#include "ui_task.h"

#include <QMessageBox>

Task::Task(QWidget *parent, const TaskData *data) :
    QDialog(parent), ui(new Ui::Task)
{
    ui->setupUi(this);

    ui->priorityBox->addItem("Пріоритет 1");
    ui->priorityBox->addItem("Пріоритет 2");
    ui->priorityBox->addItem("Пріоритет 3");
    ui->priorityBox->addItem("Пріоритет 4");
    ui->priorityBox->addItem("Пріоритет 5");

    // TODO, think about this. first item (if we not called from projects)
    ui->groupBox->addItem("Усі");
    // add another items here

    if (data) {
        ui->mainTextEdit->setText(data->task_describe);
        ui->dateEdit->setDate(data->date);
        ui->timeEdit->setTime(data->time);

        ui->priorityBox->setCurrentIndex(data->priority.toInt());
        int ind = ui->groupBox->findText(data->group);
        ui->groupBox->setCurrentIndex(ind);
    }
    else {
        ui->priorityBox->setCurrentIndex(4);
        // find and set appropriate group
    }

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
