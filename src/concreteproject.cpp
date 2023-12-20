#include "concreteproject.hpp"
#include "ui_concreteproject.h"

#include <QMessageBox>

Database *ConcreteProject::s_database = Database::get_instance();


ConcreteProject::ConcreteProject(const QString &project_name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConcreteProject),
    m_base(dynamic_cast<Base*>(parent)),
    m_project_name(project_name)
{
    ui->setupUi(this);
    set_styles();
}

ConcreteProject::~ConcreteProject() {
    delete ui;
}

void ConcreteProject::set_styles() {
    setStyleSheet(QString("font-size: %1pt;").arg(Settings::get_font_size()));
    auto set_icon = [](QPushButton *button, const QString &path){
        QIcon icon(path);
        int min = std::min(button->size().width(), button->size().height());

        button->setText("");
        button->setIcon(icon);
        button->setIconSize(QSize(min, min));
    };
    set_icon(ui->backButton, ":/res/return.png");
    set_icon(ui->delButton, ":/res/bin.png");
}

void ConcreteProject::on_delButton_clicked()
{
    QMessageBox dualChoose;
    dualChoose.setText("Are you sure?");
    dualChoose.setInformativeText("The project and all tasks in it will be deleted");
    dualChoose.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if (dualChoose.exec() == QMessageBox::Ok)
        m_base->delete_project(m_project_name);
}

void ConcreteProject::on_backButton_clicked() {
    m_base->set_project_widget();
}

QListWidget *ConcreteProject::get_list_widget() const {
    return ui->listWidget;
}
