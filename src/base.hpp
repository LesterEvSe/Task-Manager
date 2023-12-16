#ifndef BASE_HPP
#define BASE_HPP

#include "task.hpp"

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QWidget
{
    Q_OBJECT

private:
    Ui::Base *ui;
    enum Ind {
        TODAY,
        PROJECTS,
        ALL_TASKS
    };
    QListWidget *m_today, *m_all_tasks, *m_projects;

    void create_task(TaskData data);

private slots:
    void on_pushButton_clicked();

    void on_allButton_clicked();

    void on_todayButton_clicked();

    void on_projectsButton_clicked();

public:
    Task *create_custom_dialog(const TaskData *data = nullptr);
    Base(QWidget *parent = nullptr);
    ~Base();
};
#endif // BASE_HPP
