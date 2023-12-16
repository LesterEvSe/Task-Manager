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
    QListWidget *m_parent;
    Base *m_base;
    TaskData m_data; // for restore data in window

    QPushButton *m_button;
    QLabel *m_task_label, *m_date_label, *m_time_label;
    QSize m_size;

    void set_styles();
    void delete_item();

public:
    TaskItemWidget(const TaskData &data, QWidget *parent, Base *base);
    void change_view(const TaskData &data, bool from_db = false);
    QSize sizeHint() const override;

    const TaskData &get_data() const;
    ~TaskItemWidget();

// Own signals
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void sendNewData(TaskData data);
};

#endif // TASKITEMWIDGET_HPP
