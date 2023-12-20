#ifndef BASE_HPP
#define BASE_HPP

#include "task.hpp"
#include "database.hpp"
#include "concreteproject.hpp"
#include "settings.hpp"

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
    friend class ConcreteProject;

private:
    enum Ind {
        TODAY,
        PROJECTS,
        ALL_TASKS
    };

    Ui::Base *ui;
    static Database *s_database;
    static int s_beg_ind;
    QListWidget *m_today, *m_all_tasks, *m_projects;
    QListWidgetItem *m_curr_item;

    // Concrete project name. Value - index in ui->stackedWidget (0 - is not created), it's QListWidget
    std::unordered_map<QString, std::pair<int, QListWidget*>> memo;

    // index in ui->stackedWidget and it's QListWidget
    std::unordered_map<int, QListWidget*> ind_widget;

    void create_project(const QString &project_name);
    void delete_project(const QString &project_name);
    void create_task(const TaskData &data);

    void set_styles();

private slots:
    void on_pushButton_clicked();
    void on_allButton_clicked();
    void on_todayButton_clicked();
    void on_projectsButton_clicked();
    void on_addProjectButton_clicked();
    void on_projectsListWidget_itemClicked(QListWidgetItem *item);

    void on_upButton_clicked();
    void on_downButton_clicked();

    void on_settingsButton_clicked();

public:
    Base(QWidget *parent = nullptr);
    void show_error_and_exit(const QString &error);
    ~Base();

    void set_project_widget();
    std::vector<QString> get_project_names() const;
    QString get_curr_label_text() const;

    Task *create_custom_dialog(const TaskData *data = nullptr);
    void save_tasks();
};
#endif // BASE_HPP
