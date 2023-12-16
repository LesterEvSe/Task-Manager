#ifndef TASK_HPP
#define TASK_HPP

#include "task_data.hpp"

#include <QDialog>

namespace Ui { class Task; }

class Task : public QDialog
{
    Q_OBJECT

private:
    Ui::Task *ui;
    QDate m_date;
    QTime m_time;

// Own signals
    void on_cancelButton_clicked();
    void on_okButton_clicked();

public:
    // TODO Think about Array of groups as parameter
    explicit Task(QWidget *parent = nullptr, const TaskData *data = nullptr);
    ~Task();

signals:
    void sendData(TaskData data);
};

#endif // TASK_HPP
