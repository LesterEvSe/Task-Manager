#include "base.hpp"
#include "settings.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Settings::init();
    Base window;
    window.show();
    return app.exec();
}
