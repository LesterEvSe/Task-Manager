#ifndef BASE_HPP
#define BASE_HPP

#include <QWidget>
#include <QListWidget>

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
    Base(QWidget *parent = nullptr);
    ~Base();
};
#endif // BASE_HPP
