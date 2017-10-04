#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QGraphicsScene>   //场景类
#include <QGraphicsView>    //展示场景
#include <QGraphicsItem>    //场景内容
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QResizeEvent>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);   //窗口大小改变的时候发生
signals:

public slots:

private :
    QGraphicsScene *_scene;
    QGraphicsView * _view;

};

#endif // MYWIDGET_H
