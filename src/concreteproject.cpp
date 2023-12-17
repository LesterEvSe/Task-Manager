#include "concreteproject.hpp"
#include "ui_concreteproject.h"

Database *ConcreteProject::m_database = Database::get_instance();


ConcreteProject::ConcreteProject(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConcreteProject),
    m_id(id)
{
    ui->setupUi(this);
}

ConcreteProject::~ConcreteProject()
{
    delete ui;
}
