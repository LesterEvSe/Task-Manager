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

private slots:
    void on_delButton_clicked();
    void on_backButton_clicked();

public:
    explicit ConcreteProject(const QString &project_name, QWidget *parent = nullptr);
    ~ConcreteProject();

    QListWidget *get_list_widget() const;
};

#endif // CONCRETEPROJECT_HPP
