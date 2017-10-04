#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

class MyButton : public QWidget
{
    Q_OBJECT
public:
    explicit MyButton(const QString &text, QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);


    QRect _rect;
    QString _text;
    bool _press;

signals:
    void clicked();

public slots:
};

#endif // MYBUTTON_H
