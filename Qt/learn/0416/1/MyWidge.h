#ifndef MYWIDGE_H
#define MYWIDGE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>

class MyWidge : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidge(QWidget *parent = 0);
    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

public slots:
    void slotClicked();

private :
    QVector<QVector<QPoint>> _lines;
};

#endif // MYWIDGE_H
