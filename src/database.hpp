#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <task_data.hpp>

#include <QtSql>
#include <vector>

// Singleton
class Database
{
private:
    QSqlDatabase m_task_manager;

    Database(const Database&) = delete;
    Database(Database&&)      = delete;
    Database &operator=(const Database&) = delete;
    Database &operator=(Database&&)      = delete;
    Database();

public:
    static Database *get_instance();
    void save(const std::vector<TaskData> &data); // or another data type

    std::vector<TaskData> get_overdue_task() const;
    std::vector<TaskData> get_today_task() const;
    std::vector<TaskData> get_all_active_task() const;
    std::vector<QString>  get_projects() const;
    std::vector<TaskData> get_project_data(const QString &project);
};

#endif // DATABASE_HPP
