#ifndef TASKITEMWIDGET_HPP
#define TASKITEMWIDGET_HPP

#include "base.hpp"
#include "task_data.hpp"

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QMouseEvent>

class TaskItemWidget : public QWidget
{
    Q_OBJECT
private:
    Base *m_base;
    TaskData m_data; // for restore data in window
    QListWidgetItem *m_item;

    QPushButton *m_button;
    QLabel *m_task_label, *m_date_label, *m_time_label;
    QChar m_priority; // number
    QString m_group;
    QSize m_size;

    void set_styles();

public:
    TaskItemWidget(const TaskData &data, QWidget *parent, Base *base, QListWidgetItem *item);
    void change_view(const TaskData &data, bool from_db = false);
    QSize sizeHint() const override;

// Own signals
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // TASKITEMWIDGET_HPP
