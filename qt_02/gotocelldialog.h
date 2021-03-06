#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

#include"ui_gotocelldialog.h"

class GoToCellDialog : public QDialog
{
    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = nullptr);
    ~GoToCellDialog();
    QString getCellLocation();

private slots:
    void on_lineEdit_textChanged();

private:
    Ui::GoToCellDialog *ui;
};

#endif // GOTOCELLDIALOG_H
