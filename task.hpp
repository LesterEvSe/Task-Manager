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

// Own signals
    void on_cancelButton_clicked();
    void on_okButton_clicked();

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();

signals:
    void sendData(TaskData data);
};

#endif // TASK_HPP
