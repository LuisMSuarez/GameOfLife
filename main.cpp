#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{    
    qDebug() << qVersion();
    srand(time(0));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
