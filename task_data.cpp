#include "task_data.hpp"

void TaskData::set_task_describe(const QString &task_describe) {
    m_task_describe = task_describe;
}
void TaskData::set_date(const QDate &date) {
    m_date = date;
}
void TaskData::set_time(const QTime &time) {
    m_time = time;
}
void TaskData::set_priority(const QString &priority) {
    m_priority = priority;
}
void TaskData::set_group(const QString &group) {
    m_group = group;
}

QString TaskData::get_task_describe() const { return m_task_describe; }
QDate TaskData::get_date() const { return m_date; }
QTime TaskData::get_time() const { return m_time; }
QString TaskData::get_priority() const { return m_priority; }
QString TaskData::get_group() const { return m_group; }
