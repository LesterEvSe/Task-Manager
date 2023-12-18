#include "concreteproject.hpp"
#include "ui_concreteproject.h"

Database *ConcreteProject::m_database = Database::get_instance();


ConcreteProject::ConcreteProject(const QString &project_name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConcreteProject),
    m_project_name(project_name)
{
    ui->setupUi(this);
}

ConcreteProject::~ConcreteProject() {
    delete ui;
}
