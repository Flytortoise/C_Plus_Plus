#include "MyButton.h"
#include <QPainter>

MyButton::MyButton(const QString & text,QWidget*parent):
    QWidget(parent),_text(text),_rect(0,0,100,30)
{
    this->setGeometry(30,30,100,50);
    _pressed=false;
}

void MyButton::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    if(_pressed)
    {
        p.setBrush(Qt::red);
    }
    else
    {
        p.setBrush(Qt::lightGray);

    }
    p.drawRect(_rect);
    p.drawText(_rect,_text,QTextOption(Qt::AlignCenter));
}

void MyButton::mousePressEvent(QMouseEvent*)
{
    _pressed =true;
    update();
   // emit clicked();
    clicked();

}

void MyButton::mouseReleaseEvent(QMouseEvent * ev)
{
    _pressed = false;
    update();
}
