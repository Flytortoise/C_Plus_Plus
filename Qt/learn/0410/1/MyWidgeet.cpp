#include "MyWidget.h"

MyWidget::MyWidget() : QWidget()
{

}

void MyWidget::mousePressEvent(QMouseEvent * event)
{
    qDebug() << event->type();

    return ;

}
