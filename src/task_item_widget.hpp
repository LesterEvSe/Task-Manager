#ifndef TASKITEMWIDGET_HPP
#define TASKITEMWIDGET_HPP

#include "base.hpp"
#include "task_data.hpp"
#include "database.hpp"

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
    static Database *m_database;
    QListWidget *m_parent;
    Base *m_base;
    TaskData m_data; // for restore data in window

    QPushButton *m_button;
    QLabel *m_task_label, *m_date_label, *m_time_label;
    QSize m_size;

    std::vector<TaskItemWidget*> m_other_items;

    void set_styles();
    void delete_item();

public:
    TaskItemWidget(const TaskData &data, QWidget *parent, Base *base);
    void change_view(const TaskData &data);
    QSize sizeHint() const override;

    void set_other_items(const std::vector<TaskItemWidget*> &other_items);
    void delete_item_from_widget();

    const TaskData &get_data() const;
    ~TaskItemWidget();

// Own signals
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void sendNewData(TaskData data);
};

#endif // TASKITEMWIDGET_HPP
