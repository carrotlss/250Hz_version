#include "mainwindow.h"
#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Controller C;
    C.startshow();

    return a.exec();
}
