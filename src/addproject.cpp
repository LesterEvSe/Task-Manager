#include "addproject.hpp"
#include "ui_addproject.h"

#include <QMessageBox>


AddProject::AddProject(QWidget *parent):
    QDialog(parent),
    ui(new Ui::AddProject)
{
    ui->setupUi(this);
}

AddProject::~AddProject() {
    delete ui;
}

void AddProject::on_cancelButton_clicked() {
    reject();
}

void AddProject::on_okButton_clicked()
{
    QString text = ui->projectNameLineEdit->text();
    if (text.isEmpty()) {
        QMessageBox::critical(this, "Empty name", "The project name can not be blank.");
        return;
    }
    emit textEntered(text);
    accept();
}
