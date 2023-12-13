#ifndef TASKITEMWIDGET_HPP
#define TASKITEMWIDGET_HPP

#include "task_data.hpp"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>

class TaskItemWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *m_button;
    QLabel *m_task_label, *m_date_label, *m_time_label;
    int m_priority;
    QString m_group;
    QSize m_size;

    void set_styles();

public:
    TaskItemWidget(const TaskData &data, QWidget *parent);
    void change_view(const TaskData &data);

    QSize sizeHint() const override;
};

#endif // TASKITEMWIDGET_HPP
