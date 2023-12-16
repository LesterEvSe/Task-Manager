#include "base.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Base w;
    w.show();
    return a.exec();
}
