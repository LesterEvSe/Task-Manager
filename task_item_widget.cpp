#include "task_item_widget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>

TaskItemWidget::TaskItemWidget(const QString &task, const QString &time, QWidget *parent):
    QWidget(parent),
    m_button(new QPushButton(this)),
    m_task_label(new QLabel(task, this)),
    m_time_label(new QLabel(time, this))
{
    m_button->setFixedSize(20, 20);

    // CSS
    // font-weight: bold;
    m_task_label->setStyleSheet("font-size: 14px;");
    m_time_label->setStyleSheet("font-size: 14px;");

    m_task_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_task_label->setWordWrap(true);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(m_task_label);
    vlayout->addWidget(m_time_label);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(m_button);
    hlayout->addSpacing(5);
    hlayout->addLayout(vlayout);

    hlayout->setAlignment(Qt::AlignVCenter);
    setLayout(hlayout);
    m_size = QSize(hlayout->sizeHint().width()-20, hlayout->sizeHint().height() - 20);

    connect(m_button, &QPushButton::clicked, this, [this, parent](){
        QListWidget *list = qobject_cast<QListWidget*>(parent);
        if (!list) return;

        // return the widget item located at the coord of the parent widget
        QListWidgetItem *item = list->itemAt(mapToParent(QPoint(0, 0)));
        if (!item) return;

        list->removeItemWidget(item);
        delete item;
    });
}

QSize TaskItemWidget::sizeHint() const {
    return m_size;
}

void TaskItemWidget::set_styles() {
    // Not implemented yet
}
