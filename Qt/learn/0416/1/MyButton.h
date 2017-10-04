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

    explicit MyButton(const QString& text,QWidget* parent);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void clicked();
public slots:

private :
    QRect _rect;    //大小和位置
    QString _text;  //文本显示
    bool _pressed;    // 是否被按下
};

#endif // MYBUTTON_H
