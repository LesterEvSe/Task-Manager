#include "database.hpp"

#include <QDebug>

Database::Database():
    m_task_manager(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString DBName = "../TaskManager.sqlite";
    m_task_manager.setDatabaseName(DBName);

    if (!m_task_manager.open())
        qDebug() << "Failed to connect to TaskManager database" << m_task_manager.lastError().text();

    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='TaskData';");
    if (!query.next() &&
        !query.exec("CREATE TABLE users ("
                    "task_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "task_describe TEXT, "
                    "date_time DATETIME, "
                    "priority INTEGER, "
                    "group TEXT)")) {
        qDebug() << "Failed to create TaskData table" << query.lastError().text();
    }
}

Database *Database::get_instance() {
    static Database TaskManager = Database();
    return &TaskManager;
}
