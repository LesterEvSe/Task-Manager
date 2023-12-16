#include "task_item_widget.hpp"
#include "task.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QMessageBox> // for debug output

TaskItemWidget::TaskItemWidget(const TaskData &data, QWidget *parent, Base *base):
    QWidget(parent),
    m_parent(qobject_cast<QListWidget*>(parent)),
    m_base(base),
    m_data(data),

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
    m_button->setFixedSize(30, 30);

    // change view, then set styles. Without data, we can not move them
    change_view(data);
    set_styles();

    QHBoxLayout *date_time = new QHBoxLayout();
    date_time->addWidget(m_date_label);
    date_time->addWidget(m_time_label);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(m_task_label);
    vlayout->addLayout(date_time);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(m_button);
    hlayout->addSpacing(5);
    hlayout->addLayout(vlayout);

    hlayout->setAlignment(Qt::AlignVCenter);
    setLayout(hlayout);
    m_size = hlayout->sizeHint();
    connect(m_button, &QPushButton::clicked, this, &TaskItemWidget::delete_item);
}

const TaskData &TaskItemWidget::get_data() const {
    return m_data;
}

TaskItemWidget::~TaskItemWidget() {
    delete m_button;
    delete m_task_label;
    delete m_date_label;
    delete m_time_label;
}

void TaskItemWidget::delete_item() {
    QListWidget *list = qobject_cast<QListWidget*>(m_parent);
    if (!list) return;

    // return the widget item located at the coord of the parent widget
    QListWidgetItem *item = list->itemAt(mapToParent(QPoint(0, 0)));
    if (!item) return;

    list->removeItemWidget(item);

    // Maybe bad idea
    delete item;
}

QSize TaskItemWidget::sizeHint() const {
    return m_size;
}

void TaskItemWidget::set_styles() {
    // font-weight: bold;
    m_task_label->setStyleSheet("font-size: 18px;");
    m_date_label->setStyleSheet("font-size: 18px;");
    m_time_label->setStyleSheet("font-size: 18px;");

    m_task_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_task_label->setWordWrap(true);
}

void TaskItemWidget::change_view(const TaskData &data, bool from_db) {
    m_data = data;
    m_task_label = new QLabel(data.task_describe, this);
    m_button->setText(m_data.priority == 5 ? " " : QString::number(m_data.priority));
    switch (m_data.priority) {
        case 1: m_button->setStyleSheet("background-color: green");  break;
        case 2: m_button->setStyleSheet("background-color: purple"); break;
        case 3: m_button->setStyleSheet("background-color: blue");   break;
        case 4: m_button->setStyleSheet("background-color: red");    break;
    };

    if (!from_db && (data.date < QDate::currentDate() ||
        data.date == QDate::currentDate() && data.time < QTime::currentTime())) return;

    m_date_label = new QLabel(data.date.toString("dd MMM ddd"), this);

    QString time;
    if (data.time.hour() == 0 && data.time.minute() == 0)
        time = "";
    else
        time = data.time.toString("hh:mm");
    m_time_label = new QLabel(time, this);
}

void TaskItemWidget::mousePressEvent(QMouseEvent *event) {
    // If m_button clicked (task completed)
    QWidget::mousePressEvent(event);
    Task *taskDialog = m_base->create_custom_dialog(&m_data);

    connect(taskDialog, &Task::sendData, this, [this](TaskData data) {
        emit sendNewData(data);
        delete_item();
    });
    taskDialog->exec();
}
