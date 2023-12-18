#include "database.hpp"

#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

Database::Database():
    m_task_manager(QSqlDatabase::addDatabase("QSQLITE"))
{

    QString dataFolder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // Chesk if folder wiht data exist
    if (!QDir(dataFolder).exists())
        QDir().mkpath(dataFolder);

    QString DBName = dataFolder + "/TaskManager.sqlite";

//    QString DBName = "TaskManager.sqlite";
    m_task_manager.setDatabaseName(DBName);

    // Delete all database
//    QFile::remove(DBName);
//    exit(1);

    if (!m_task_manager.open())
        QMessageBox::critical(nullptr, "Failed to connect to DataBase", m_task_manager.lastError().text());

    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='TaskData';");
    if (!query.next() &&
        !query.exec("CREATE TABLE TaskData ("
                    "task_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "task_describe TEXT, "
                    "date_time DATETIME, "
                    "priority INTEGER, "
                    "task_group TEXT)")) {
        QMessageBox::information(nullptr, "Failed to create TaskData table", query.lastError().text());
    }

    QSqlQuery query2("SELECT name FROM sqlite_master WHERE type='table' AND name='Projects';");
    if (!query2.next() &&
        !query2.exec("CREATE TABLE Projects ("
                    "project TEXT PRIMARY KEY UNIQUE)")) {
        QMessageBox::information(nullptr, "Failed to create Group table", query.lastError().text());
    }

    // Clear Tables
//    QSqlQuery clear_query;
//    if (!clear_query.exec("DELETE FROM TaskData"))
//        QMessageBox::information(nullptr, "Failed to delete TaskData table.", query.lastError().text());
//    if (!clear_query.exec("DELETE FROM Projects"))
//        QMessageBox::information(nullptr, "Failed to delete Projects table.", query.lastError().text());
}

Database *Database::get_instance() {
    static Database TaskManager = Database();
    return &TaskManager;
}

int Database::add_task(const TaskData &data) {
    QSqlQuery insert_query;
    insert_query.prepare("INSERT INTO TaskData (task_describe, date_time, priority, task_group)"
                         "VALUES (:task_describe, :date_time, :priority, :task_group)");
    insert_query.bindValue(":task_describe", data.task_describe);
    insert_query.bindValue(":date_time", QDateTime(data.date, data.time));
    insert_query.bindValue(":priority", data.priority);
    insert_query.bindValue(":task_group", data.group);

    if (!insert_query.exec())
        throw QSqlError(insert_query.lastError().text(),
                        QString("Failed to add the data."));
    return insert_query.lastInsertId().toInt();
}

bool Database::add_project(const QString &project) {
    QSqlQuery check_query;
    check_query.prepare("SELECT COUNT(*) FROM Projects WHERE project = :project");
    check_query.bindValue(":project", project);

    if (!check_query.exec())
        throw QSqlError(check_query.lastError().text(), "Failed to check project existence.");
    check_query.next();

    // project already exist
    if (check_query.value(0).toInt() > 0)
        return false;

    QSqlQuery insert_query;
    insert_query.prepare("INSERT INTO Projects (project) VALUES (:project)");
    insert_query.bindValue(":project", project);

    if (!insert_query.exec())
        throw QSqlError(insert_query.lastError().text(),
                        QString("Failed to add the project."));
    return true;
}

void Database::del_task(int id) {
    QSqlQuery delete_query;
    delete_query.prepare("DELETE FROM TaskData WHERE task_id = :task_id");
    delete_query.bindValue(":task_id", id);

    if (!delete_query.exec())
        throw QSqlError(delete_query.lastError().text(),
                        QString("Failed to delete the data."));
}

void Database::del_project(const QString &project) {
    QSqlQuery delete_query;
    delete_query.prepare("DELETE FROM Projects WHERE project = :project");
    delete_query.bindValue(":project", project);

    if (!delete_query.exec())
        throw QSqlError(delete_query.lastError().text(),
                        QString("Failed to delete the project."));
}

std::vector<TaskData> Database::get_task(TaskEnum task) const {
    QSqlQuery query;
    switch (task) {
    case OVERDUE:
        query.prepare("SELECT * FROM TaskData WHERE date_time < :current_date_time");
        query.bindValue(":current_date_time", QDateTime::currentDateTime());
        break;

    case TODAY:
        break;

    case ALL_ACTIVE:
        query.prepare("SELECT * FROM TaskData WHERE date_time >= :current_date_time");
        query.bindValue(":current_date_time", QDateTime::currentDateTime());
        break;

    default:
        throw QString("'get task'. Invalid value in TaskEnum");
    }

    if (!query.exec())
        throw QSqlError(query.lastError().text(),
                        QString("'get task'. Task flag is: ") + taskEnumStr(task));

    std::vector<TaskData> data;
    while (query.next()) {
        TaskData temp;
        temp.id = query.value(ID).toInt();
        temp.task_describe = query.value(TASK_DESCRIPTION).toString();

        QDateTime data_time = query.value(DATA_TIME).toDateTime();
        temp.date = data_time.date();
        temp.time = data_time.time();

        temp.priority = query.value(PRIORITY).toInt();
        temp.group = query.value(GROUP).toString();
        data.emplace_back(temp);
    }
    return data;
}

std::vector<QString> Database::get_projects() const {
    QSqlQuery query("SELECT * FROM Projects");
    if (!query.exec())
        throw QSqlError(query.lastError().text(), QString("'get projects'."));

    std::vector<QString> projects;
    while (query.next())
        projects.emplace_back(query.value(0).toString());
    return projects;
}

std::vector<TaskData> Database::get_project_data(const QString &project) const {
    QSqlQuery query;
    query.prepare("SELECT * FROM TaskData WHERE task_group = :project");
    query.bindValue(":project", project);

    if (!query.exec())
        throw QSqlError(query.lastError().text(), QString("Failed to get data from ") + project);

    std::vector<TaskData> data;
    while (query.next()) {
        TaskData temp;
        temp.id = query.value(ID).toInt();
        temp.task_describe = query.value(TASK_DESCRIPTION).toString();

        QDateTime data_time = query.value(DATA_TIME).toDateTime();
        temp.date = data_time.date();
        temp.time = data_time.time();

        temp.priority = query.value(PRIORITY).toInt();
        temp.group = query.value(GROUP).toString();
        data.emplace_back(temp);
    }
    return data;
}
