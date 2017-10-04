#include "MyWidget.h"
#include <QFont>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    _scene = new QGraphicsScene();
    _view = new QGraphicsView(this);
    _view->setScene(_scene);

    QGraphicsTextItem *text = new QGraphicsTextItem("你好");
  //  QGraphicsPixmapItem *Pix = new QGraphicsPixmapItem("写路径");

    _scene->addItem(new QGraphicsLineItem(QLineF(QPoint(0,0),QPoint(100,100))));
    _scene->addItem(text);
    text->setPos(100,100);
    text->setFont(QFont("黑体"));

}

void MyWidget::resizeEvent(QResizeEvent *ev)
{
    _view->setGeometry(0,0,size().width(),size().height());
}
