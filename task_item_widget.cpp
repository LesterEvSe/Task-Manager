#include "task_item_widget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>

TaskItemWidget::TaskItemWidget(const TaskData &data, QWidget *parent):
    QWidget(parent),
    m_task_label(new QLabel(this)),
    m_date_label(new QLabel(this)),
    m_time_label(new QLabel(this)),
    m_button(new QPushButton(this))
{
    // task
    // date
    // time
    // prior
    // group
    m_button->setFixedSize(20, 20);
    set_styles();
    change_view(data);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(m_task_label);
    vlayout->addWidget(m_time_label);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(m_button);
    hlayout->addSpacing(5);
    hlayout->addLayout(vlayout);

    hlayout->setAlignment(Qt::AlignVCenter);
    setLayout(hlayout);
    m_size = hlayout->sizeHint();

    connect(m_button, &QPushButton::clicked, this, [this, parent](){
        QListWidget *list = qobject_cast<QListWidget*>(parent);
        if (!list) return;

        // return the widget item located at the coord of the parent widget
        QListWidgetItem *item = list->itemAt(mapToParent(QPoint(0, 0)));
        if (!item) return;

        list->removeItemWidget(item);

        // Maybe bad idea
        delete item;
    });
}

QSize TaskItemWidget::sizeHint() const {
    return m_size;
}

void TaskItemWidget::set_styles() {
    // font-weight: bold;
    m_task_label->setStyleSheet("font-size: 18px;");
    m_time_label->setStyleSheet("font-size: 18px;");

    m_task_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_task_label->setWordWrap(true);
}

void TaskItemWidget::change_view(const TaskData &data) {
    m_task_label = new QLabel(data.task_describe, this);
    m_date_label = new QLabel(data.date.toString(), this);
    m_time_label = new QLabel(data.time.toString(), this);

    m_priority = data.priority.at(data.priority.length()-1).digitValue();
    m_group = data.group;
}
