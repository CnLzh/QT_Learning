#include "gotocelldialog.h"

#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include<QLineEdit>

GoToCellDialog::GoToCellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToCellDialog)
{
    ui->setupUi(this);

    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");
    ui->lineEdit->setValidator(new QRegularExpressionValidator(regExp,this));

    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));

}

GoToCellDialog::~GoToCellDialog()
{
    delete ui;
}

void GoToCellDialog::on_lineEdit_textChanged()
{
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}

QString GoToCellDialog::getCellLocation()
{
    return ui->lineEdit->text();
}
