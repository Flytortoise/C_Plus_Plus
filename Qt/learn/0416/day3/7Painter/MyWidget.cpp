#include "MyWidget.h"
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include "MyButton.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    MyButton *button = new MyButton("MyButton", this);
    connect(button,SIGNAL(clicked()),this, SLOT(slotClicked()));

}
void MyWidget::slotClicked()
{
    qDebug() << "MyButton clicked";
}

void MyWidget::paintEvent(QPaintEvent *ev)
{
    QPixmap pixmap(size());
    QPainter p(&pixmap);
    p.fillRect(0,0,size().width(), size().height(), Qt::white);
//    p.drawLine(QPoint(0,0), QPoint(100, 100));
    for(int i=0; i < _lines.count(); i++)
    {
        const QVector<QPoint> &line = _lines.at(i);
        for (int j = 0; j < line.count()-1; j++)
        {
             p.drawLine(line.at(j), line.at(j+1));
        }
    }
    p.end();
    p.begin(this);
    p.drawPixmap(0,0,pixmap);
}

void MyWidget::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton)
    {
        // 去掉最后一条线
        if (_lines.count() > 0)
        {
            _lines.removeLast();
            update();
        }
    }
    else
    {
        QVector<QPoint> line;
        line.append(ev->pos());
        _lines.append(line);
    }
}
void MyWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton)
    {

    }
    else
    {
        if (_lines.count() > 0)
        {
            QVector<QPoint> &line = _lines.last();
            line.append(ev->pos());
        }
    }
}
void MyWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() == Qt::RightButton)
    {
    }
    else
    {
        if (_lines.count() > 0)
        {
            QVector<QPoint> &line = _lines.last();
            line.append(ev->pos());
            update();
        }
    }
}
