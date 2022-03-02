/**  Hello QT  **/
/*
#include <QApplication>
#include<QLabel>

int main(int argc ,char *argv[])
{
    QApplication app(argc,argv );
    QLabel *label = new QLabel("Hello QT!");
    label->show();
    return app.exec();
}
*/


/**  点击事件与信号槽  **/
/*
#include<QApplication>
#include<QPushButton>

int main(int argc ,char *argv[])
{
    QApplication app(argc,argv);
    QPushButton *button = new QPushButton("quit");
    QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
    button->show();
    return app.exec();
}
*/


/**  窗口部件及布局 使用信号槽同步  **/
/*
#include<QApplication>
#include<QHBoxLayout>
#include<QSlider>
#include<QSpinBox>

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("Enter Your Age");

    QSpinBox * spinBox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0,130);
    slider->setRange(0,130);

    QObject::connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
    spinBox->setValue(35);

    //布局管理器 QHBoxLayout:水平排列  QVBoxLayout:垂直排列  QGirdLayout:网格排列
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    window->setLayout(layout);

    window->show();
    return app.exec();
}
*/


/**  查找对话框  **/
#include<QApplication>

#include"finddialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    FindDialog *dialog = new FindDialog;
    dialog->show();
    return app.exec();
}




/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
*/
