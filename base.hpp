#ifndef BASE_HPP
#define BASE_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QWidget
{
    Q_OBJECT

public:
    Base(QWidget *parent = nullptr);
    ~Base();

private:
    Ui::Base *ui;
};
#endif // BASE_HPP
