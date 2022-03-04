#include <QApplication>
#include<QDialog>

#include"gotocelldialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GoToCellDialog *ui = new GoToCellDialog;
    ui->show();

    return app.exec();
}
