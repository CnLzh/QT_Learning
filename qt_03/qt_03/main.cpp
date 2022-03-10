#include "mainwindow.h"
#include"hexspinbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    HexSpinBox hex;
    hex.show();
    return a.exec();
}
