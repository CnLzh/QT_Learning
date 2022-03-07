#include <QApplication>
#include<QDialog>
#include<QSplashScreen>
#include"mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QSplashScreen *splash = new QSplashScreen;
//    splash->setPixmap(QPixmap("./images/splash.png"));
//    splash->show();

//    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
//    splash->showMessage(QObject::tr("Setting up the main window..."),
//                        topRight,Qt::white);

//    MainWindow mainWin;
//    splash->showMessage(QObject::tr("Loading modules..."),
//                        topRight,Qt::white);

//    splash->showMessage(QObject::tr("Establishing connections..."),
//                        topRight,Qt::white);

//    mainWin.show();
//    splash->finish(&mainWin);
//    delete splash;

    MainWindow w;
    w.show();

    return app.exec();
}
