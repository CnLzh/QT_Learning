#include"iconeditor.h"

iconEditor::iconEditor(QWidget *parent)
    :QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents;
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    curColor = Qt::black;
    zoom = 8;

    image = QImage(16,16,QImage::Format_ARGB32);
    image.fill(qRgba(0,0,0,0));
}

QSize iconEditor::sizeHint() const
{
    QSize size = zoom * image.size();
    if(zoom >= 3)
        size += QSize(1,1);
    return size;
}

void iconEditor::setPenColor(const QColor &newColor)
{
    cureColor = newColor;
}

void iconEditor::setIconImage(const QImage &newImage)
{
    if(newImage != image){
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update();
        updateGeometry();
    }
}

void iconEditor::setZoomFactor(int newZoom)
{
    if(newZoom < 1)
        newZoom = 1;
    if(newZoom != zoom){
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

void iconEditor::paintEvent(QPaintEvent *event)
{

}
