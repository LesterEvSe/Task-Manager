#ifndef CONCRETEPROJECT_HPP
#define CONCRETEPROJECT_HPP

#include "database.hpp"
#include "base.hpp"

#include <QWidget>


namespace Ui {
class ConcreteProject;
}

class ConcreteProject : public QWidget
{
    Q_OBJECT

private:
    Ui::ConcreteProject *ui;
    Base *m_base;
    static Database *m_database;
    QString m_project_name;

public:
    explicit ConcreteProject(const QString &project_name, QWidget *parent = nullptr);
    ~ConcreteProject();
private slots:
    void on_delButton_clicked();
    void on_backButton_clicked();
};

#endif // CONCRETEPROJECT_HPP
