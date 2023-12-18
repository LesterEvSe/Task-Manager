#ifndef TASKDATA_H
#define TASKDATA_H

#include <QString>
#include <QDate>
#include <QTime>

struct TaskData {
    int id = -1; // DB id
    QString task_describe;
    QDate date;
    QTime time;
    int priority;
    QString group;
};

#endif // TASKDATA_H
