#ifndef TASK_HPP
#define TASK_HPP

#include "task_data.hpp"

#include <QDialog>

class Base;

namespace Ui { class Task; }

class Task : public QDialog
{
    Q_OBJECT

private:
    Ui::Task *ui;
    Base *m_base;
    QDate m_date;
    QTime m_time;

// Own signals
    void on_cancelButton_clicked();
    void on_okButton_clicked();

public:
    static QDateTime EDGE;

    // TODO Think about Array of groups as parameter
    explicit Task(Base *parent = nullptr, const TaskData *data = nullptr);
    ~Task();

signals:
    void sendData(TaskData data);
};

#endif // TASK_HPP
