#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "task_enum.hpp"
#include "task_data.hpp"

#include <QtSql>
#include <vector>

// Singleton
class Database
{
private:
    enum Data {
        ID,
        TASK_DESCRIPTION,
        DATA_TIME,
        PRIORITY,
        GROUP
    };
    QSqlDatabase m_task_manager;

    Database(const Database&) = delete;
    Database(Database&&)      = delete;
    Database &operator=(const Database&) = delete;
    Database &operator=(Database&&)      = delete;
    Database();

public:
    static Database *get_instance();

    // return inserted value index
    int add(const TaskData &data);
    void del(int id);
//    void save(const std::vector<TaskData> &data);

    // Data, id
    std::vector<TaskData> get_task(TaskEnum task) const;
    std::vector<QString>  get_projects() const;
    std::vector<TaskData> get_project_data(const QString &project);
};

#endif // DATABASE_HPP
