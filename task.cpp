#include "task.hpp"
#include "ui_task.h"

#include <QMessageBox>

Task::Task(QWidget *parent, const TaskData *data) :
    QDialog(parent), ui(new Ui::Task)
{
    ui->setupUi(this);

    ui->priorityBox->addItem("Priority 1");
    ui->priorityBox->addItem("Priority 2");
    ui->priorityBox->addItem("Priority 3");
    ui->priorityBox->addItem("Priority 4");
    ui->priorityBox->addItem("Priority 5");

    // TODO, think about this. first item (if we not called from projects)
    ui->groupBox->addItem("All");
    // add another items here

    if (data) {
        ui->mainTextEdit->setText(data->task_describe);
        ui->dateEdit->setDate(data->date);
        ui->timeEdit->setTime(data->time);

        ui->priorityBox->setCurrentIndex(data->priority - 1);
        int ind = ui->groupBox->findText(data->group);
        ui->groupBox->setCurrentIndex(ind);
    }
    else {
        ui->dateEdit->setDate(QDate::currentDate());
        ui->timeEdit->setTime(QTime::currentTime());
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
    dualChoose.setText("Delete changes?");
    dualChoose.setInformativeText("The changes you make will not be saved.");
    dualChoose.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if (dualChoose.exec() == QMessageBox::Ok)
        reject();
}

void Task::on_okButton_clicked() {
    TaskData task_data;
    task_data.task_describe = ui->mainTextEdit->toPlainText();
    task_data.date = ui->dateEdit->date();
    task_data.time = ui->timeEdit->time();
    task_data.priority = (*(ui->priorityBox->currentText().toStdString().end() - 1))-'0';
    task_data.group = ui->groupBox->currentText();

    emit sendData(task_data);
    accept();
}
