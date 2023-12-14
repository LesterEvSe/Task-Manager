#ifndef TASKITEMWIDGET_HPP
#define TASKITEMWIDGET_HPP

#include "task_data.hpp"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
//#include <QMouseEvent>
#include <QTouchEvent>

class TaskItemWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *m_button;
    QLabel *m_task_label, *m_date_label, *m_time_label;
    QChar m_priority; // number
    QString m_group;
    QSize m_size;

    void set_styles();

public:
    TaskItemWidget(const TaskData &data, QWidget *parent);
    void change_view(const TaskData &data, bool from_db = false);
    QSize sizeHint() const override;

// Own signals
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // TASKITEMWIDGET_HPP
