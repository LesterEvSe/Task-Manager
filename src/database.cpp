#include "database.hpp"

#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

Database::Database():
    m_task_manager(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString dataFolder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // Проверка наличия папки для данных
    if (!QDir(dataFolder).exists()) {
        QDir().mkpath(dataFolder);
    }

    QString DBName = dataFolder + "/TaskManager.sqlite";

//    QString DBName = "TaskManager.sqlite";
    m_task_manager.setDatabaseName(DBName);
    QMessageBox::information(nullptr, "File location", DBName);

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
}

Database *Database::get_instance() {
    static Database TaskManager = Database();
    return &TaskManager;
}

void Database::save(const std::vector<TaskData> &data) {

}

std::vector<TaskData> Database::get_overdue_task() const {

}
//std::vector<TaskData> Database::get_today_task() const;
//std::vector<TaskData> Database::get_all_active_task() const;
//std::vector<QString>  Database::get_projects() const;
//std::vector<TaskData> Database::get_project_data(const QString &project);
