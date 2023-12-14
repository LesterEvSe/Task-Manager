#ifndef BASE_HPP
#define BASE_HPP

#include "task.hpp"

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QWidget
{
    Q_OBJECT

private:
    Ui::Base *ui;
    QListWidget *m_today, *m_all_tasks, *m_projects;

private slots:
    void on_pushButton_clicked();

public:
    Task *create_custom_dialog(const TaskData *data = nullptr);
    Base(QWidget *parent = nullptr);
    ~Base();

// Own signals
//    void mousePressEvent(QMouseEvent *event) override;
};
#endif // BASE_HPP
