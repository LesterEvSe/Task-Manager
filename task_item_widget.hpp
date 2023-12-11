#ifndef TASKITEMWIDGET_HPP
#define TASKITEMWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>

class TaskItemWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *m_button;
    QLabel *m_task_label, *m_time_label;
    QSize m_size;

public:
    TaskItemWidget(const QString &task, const QString &time, QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void set_styles();
};

#endif // TASKITEMWIDGET_HPP
