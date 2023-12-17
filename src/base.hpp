#ifndef BASE_HPP
#define BASE_HPP

#include "task.hpp"
#include "database.hpp"

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QWidget
{
    Q_OBJECT

private:
    enum Ind {
        TODAY,
        PROJECTS,
        ALL_TASKS
    };

    Ui::Base *ui;
    static Database *m_database;
    QListWidget *m_today, *m_all_tasks, *m_projects;

    // concrete item in project. Value - index in ui->stackedWidget, id in database
    std::unordered_map<QListWidgetItem*, std::pair<int, int>> memo;

    void create_task(const TaskData &data);
    void show_error_and_exit(const QString &error);

private slots:
    void on_pushButton_clicked();
    void on_allButton_clicked();
    void on_todayButton_clicked();
    void on_projectsButton_clicked();
    void on_addProjectButton_clicked();
    void on_projectsListWidget_itemClicked(QListWidgetItem *item);

public:
    Base(QWidget *parent = nullptr);
    ~Base();

    Task *create_custom_dialog(const TaskData *data = nullptr);
    void save_tasks();
};
#endif // BASE_HPP
