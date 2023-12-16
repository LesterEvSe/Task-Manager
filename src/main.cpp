#include "base.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Base window;
    window.show();
    return app.exec();
}
