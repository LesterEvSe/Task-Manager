#include "addproject.hpp"
#include "ui_addproject.h"

#include <QMessageBox>


AddProject::AddProject(QWidget *parent):
    QDialog(parent),
    ui(new Ui::AddProject)
{
    ui->setupUi(this);
    set_styles();
}

AddProject::~AddProject() {
    delete ui;
}

void AddProject::set_styles() {
    auto set_icon = [](QPushButton *button, const QString &path){
        QIcon icon(path);
        int min = std::min(button->size().width(), button->size().height());

        button->setText("");
        button->setIcon(icon);
        button->setIconSize(QSize(min, min));
    };
    set_icon(ui->okButton, ":/res/ok.png");
    set_icon(ui->cancelButton, ":/res/cancel.png");
}

void AddProject::on_cancelButton_clicked() {
    QMessageBox dualChoose;
    dualChoose.setText("Delete changes?");
    dualChoose.setInformativeText("The changes you make will not be saved.");
    dualChoose.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if (dualChoose.exec() == QMessageBox::Ok)
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
