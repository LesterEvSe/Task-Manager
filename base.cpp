#include "base.hpp"
#include "./ui_base.h"

Base::Base(QWidget *parent):
    QWidget(parent), ui(new Ui::Base)
{
    ui->setupUi(this);
}

Base::~Base()
{
    delete ui;
}

