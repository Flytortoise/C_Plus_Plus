#include "MyWidge.h"
#include "MyButton.h"
#include <QPixmap>
#include <QDebug>

MyWidge::MyWidge(QWidget *parent) : QWidget(parent)
{
    MyButton *button = new MyButton("MyButton", this);

    connect(button,SIGNAL(clicked()),this, SLOT(slotClicked()));

}

void MyWidge::slotClicked()
{
    qDebug() << "MyButton clicked";
}

void MyWidge::paintEvent(QPaintEvent *ev)
{
    QPixmap pixmap(size());
    QPainter p(&pixmap);
    p.fillRect(0,0,size().width(),size().height(),Qt::white);

    for(int i = 0; i < _lines.count(); i++)
    {
        for(int j = 0; j < _lines.at(i).count() - 1; j++)
        {
            p.drawLine(_lines.at(i).at(j),_lines.at(i).at(j + 1));
        }

    }

    p.end();
    p.begin(this);
    p.drawPixmap(0,0,pixmap);
}

void MyWidge::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {
        if(_lines.size() > 0)
        {
            _lines.removeLast();
            update();
        }
    }
    else
    {
        QVector<QPoint> &line = _lines.last();
        line.append(event->pos());
        update();
    }

}

void MyWidge::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        if(_lines.size() > 0)
        {
            _lines.removeLast();
            update();
        }
    }
    else
    {
        QVector<QPoint> line;
        line.append(event->pos());
        _lines.append(line);
    }
}

void MyWidge::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {

    }
    else
    {
        QVector<QPoint> &line = _lines.last();
        line.append(event->pos());
    }

}
