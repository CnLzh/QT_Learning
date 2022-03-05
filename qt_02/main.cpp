#include <QApplication>
#include<QDialog>

#include"gotocelldialog.h"
#include"sortdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //GoToCellDialog *ui = new GoToCellDialog;
    SortDialog *ui = new SortDialog;
    ui->setColumnRange('C','F');
    ui->show();

    return app.exec();
}
