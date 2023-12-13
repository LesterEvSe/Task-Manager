#ifndef TASKDATA_H
#define TASKDATA_H

#include <QString>
#include <QDate>
#include <QTime>

struct TaskData {
    QString task_describe;
    QDate date;
    QTime time;
    QString priority;
    QString group;
};

#endif // TASKDATA_H
