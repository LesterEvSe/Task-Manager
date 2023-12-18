#ifndef CONCRETEPROJECT_HPP
#define CONCRETEPROJECT_HPP

#include "database.hpp"

#include <QWidget>


namespace Ui {
class ConcreteProject;
}

class ConcreteProject : public QWidget
{
    Q_OBJECT

private:
    Ui::ConcreteProject *ui;
    static Database *m_database;
    QString m_project_name;

public:
    explicit ConcreteProject(const QString &project_name, QWidget *parent = nullptr);
    ~ConcreteProject();
};

#endif // CONCRETEPROJECT_HPP
