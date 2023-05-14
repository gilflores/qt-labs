#include "MainWindow.h"
#include <QApplication>
#include "WidgetPrincipal.h"
#include <SiteRepository.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font ("DejaVu Sans");


    WidgetPrincipal w;
    w.setWindowTitle("Demo server");

    w.show();

    return a.exec();
}
