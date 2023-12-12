#ifndef TASK_HPP
#define TASK_HPP

#include <QDialog>

namespace Ui { class Task; }

class Task : public QDialog
{
    Q_OBJECT

private:
    Ui::Task *ui;

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();
};

#endif // TASK_HPP
