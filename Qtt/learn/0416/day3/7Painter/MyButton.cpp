#include "MyButton.h"
#include <QPainter>

MyButton::MyButton(const QString &text, QWidget *parent):
    QWidget(parent), _text(text), _rect(0,0,100,30)
{
    this->setGeometry(30,30,100,50);
    _press = false;
}

void MyButton::mousePressEvent(QMouseEvent *)
{
    _press =true;
    update();
   // emit clicked();
    clicked();
}
void MyButton::mouseReleaseEvent(QMouseEvent *)
{
    _press = false;
    update();
}

void MyButton::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    if (_press)
        p.setBrush(Qt::red);
    else
        p.setBrush(Qt::yellow);

    p.drawRect(_rect);
    p.drawText(_rect, _text, QTextOption(Qt::AlignCenter));
}
