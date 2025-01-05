#include "mainwindow.h"

#include <QApplication>
#include <QtGlobal>

int main(int argc, char *argv[])
{    
    qDebug() << qVersion();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
