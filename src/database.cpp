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

    // Delete Later
//    QSqlQuery clear_query("DELETE FROM TaskData");
//    if (!clear_query.exec())
//        throw QSqlError(clear_query.lastError().text(),
//                        QString("'save'. Failed to delete table."));
}

Database *Database::get_instance() {
    static Database TaskManager = Database();
    return &TaskManager;
}

int Database::add(const TaskData &data) {
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

void Database::del(int id) {
    QSqlQuery delete_query;
    delete_query.prepare("DELETE FROM TaskData WHERE task_id = :task_id");
    delete_query.bindValue(":id", id);

    if (!delete_query.exec())
        throw QSqlError(delete_query.lastError().text(),
                        QString("Failed to delete the data."));
}

/*
void Database::save(const std::vector<TaskData> &data) {
    QSqlQuery clear_query("DELETE FROM TaskData");
    if (!clear_query.exec())
        throw QSqlError(clear_query.lastError().text(),
                        QString("'save'. Failed to delete table."));

    QSqlQuery insert_query;
    insert_query.prepare("INSERT INTO TaskData (task_describe, date_time, priority, task_group)"
                         "VALUES (:task_describe, :date_time, :priority, :task_group)");

    for (int i = 0; i < data.size(); ++i) {
        insert_query.bindValue(":task_describe", data[i].task_describe);
        insert_query.bindValue(":date_time", QDateTime(data[i].date, data[i].time));
        insert_query.bindValue(":priority", data[i].priority);
        insert_query.bindValue(":task_group", data[i].group);

        if (!insert_query.exec())
            throw QSqlError(insert_query.lastError().text(),
                            QString("'save'. Failed to insert data."));
    }
}
*/

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
        query.prepare("SELECT * FROM TaskData WHere date_time >= :current_date_time");
        query.bindValue(":current_date_time", QDateTime::currentDateTime());
        break;
    default:
        throw QString("'get task'. Invalid value in TaskEnum");
    }

    if (!query.exec())
        throw QSqlError(query.lastError().text(),
                        QString("'get task error'. Task flag is: ") + taskEnumStr(task));

    std::vector<TaskData> data;
    while (query.next()) {
        TaskData temp;
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
//std::vector<QString>  Database::get_projects() const;
//std::vector<TaskData> Database::get_project_data(const QString &project);
