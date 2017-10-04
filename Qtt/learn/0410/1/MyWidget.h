#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class MyWidget : public QWidget
{
public:
    MyWidget();
    void mousePressEvent(QMouseEvent *);

};

#endif // MYWIDGET_H
