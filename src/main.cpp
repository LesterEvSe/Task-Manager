#include "base.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Base base_window;
    base_window.show();

    int res = app.exec();
    base_window.save_tasks();
    return res;
}
