#include "reactor.h"
#include "net_show.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    net_show main_window;
    main_window.show();
    return a.exec();
}
