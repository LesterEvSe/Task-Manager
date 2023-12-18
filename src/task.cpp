#include "task.hpp"
#include "ui_task.h"
#include "base.hpp"

#include <QMessageBox>
#include "database.hpp"

QDateTime Task::EDGE = QDateTime(QDate(3000, 1, 1), QTime(23, 59, 59));


Task::Task(Base *parent, const TaskData *data) :
    QDialog(parent),
    ui(new Ui::Task),
    m_base(parent)
{
    ui->setupUi(this);

    ui->priorityBox->addItem("Priority 1");
    ui->priorityBox->addItem("Priority 2");
    ui->priorityBox->addItem("Priority 3");
    ui->priorityBox->addItem("Priority 4");
    ui->priorityBox->addItem("Priority 5");

    // TODO, think about this. first item (if we not called from projects)
    int curr_ind = 0;
    ui->groupBox->addItem("All");
    std::vector<QString> project_names = m_base->get_project_names();
    for (int i = 0; i < project_names.size(); ++i) {
        ui->groupBox->addItem(project_names[i]);
        if (project_names[i] == m_base->get_curr_label())
            curr_ind = i+1;
    }
    ui->groupBox->setCurrentIndex(curr_ind);

    if (data) {
        ui->mainTextEdit->setText(data->task_describe);
        m_date = data->date >= EDGE.date() ? QDate::currentDate() : data->date;
        m_time = data->time >= EDGE.time() ? QTime() : data->time;
        ui->dateEdit->setDate(m_date);
        ui->timeEdit->setTime(m_time);

        ui->priorityBox->setCurrentIndex(data->priority - 1);
        int ind = ui->groupBox->findText(data->group);
        ui->groupBox->setCurrentIndex(ind);
    }
    else {
        m_date = QDate::currentDate();
        ui->dateEdit->setDate(m_date);
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
    QDate after_ten_years = QDate::currentDate().addYears(100);
    if (ui->dateEdit->date() > after_ten_years) {
        QMessageBox::critical(this, "Problem", "You can't put a deadline that far away.");
        return;
    }

    TaskData task_data;
    task_data.task_describe = ui->mainTextEdit->toPlainText();

    task_data.date = ui->dateEdit->date() < m_date ? EDGE.date() : ui->dateEdit->date();
    if (task_data.date == EDGE.date())
        task_data.time = EDGE.time();
    else if (task_data.date == QDate::currentDate()) {
        task_data.time = ui->timeEdit->time() <= QTime::currentTime() ? EDGE.time() : ui->timeEdit->time();
        task_data.date = task_data.time == EDGE.time() ? EDGE.date() : task_data.date;
    }
    else
        task_data.time = ui->timeEdit->time() <= QTime(1, 0, 0) ? EDGE.time() : ui->timeEdit->time();

    task_data.priority = (*(ui->priorityBox->currentText().toStdString().end() - 1))-'0';
    task_data.time = task_data.time.addMSecs(task_data.priority); // for sorting by priority too
    task_data.group = ui->groupBox->currentText();

    emit sendData(task_data);
    accept();
}
