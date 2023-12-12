#include "task.hpp"
#include "ui_task.h"

#include <QPalette>

Task::Task(QWidget *parent) :
    QDialog(parent), ui(new Ui::Task)
{
    ui->setupUi(this);
    ui->taskLineEdit->setStyleSheet("color: gray;");
    ui->taskLineEdit->setPlaceholderText("Назва");

    ui->descriptionTextEdit->setStyleSheet("color: gray;");
    ui->descriptionTextEdit->setPlaceholderText("Опис");

//    ui->taskLineEdit->setFocus();
    qApp->inputMethod()->show();

    ui->priorityBox->addItem("Пріоритет 1");
    ui->priorityBox->addItem("Пріоритет 2");
    ui->priorityBox->addItem("Пріоритет 3");
    ui->priorityBox->addItem("Пріоритет 4");
    ui->priorityBox->addItem("Пріоритет 5");

    // Other will be add in process
    ui->containerBox->addItem("Усі");
    return;

    // Клавиатура видна, изменяем размер или положение диалогового окна
//    int keyboardHeight = qApp->inputMethod()->keyboardRectangle().height();
//    QRect dialogGeometry = geometry();
//    dialogGeometry.moveBottom(qApp->inputMethod()->keyboardRectangle().top());
//    setGeometry(dialogGeometry);
}

Task::~Task() {
    // Maybe do not need
//    qApp->inputMethod()->hide();
    delete ui;
}

