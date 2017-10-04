#ifndef MYMIANWINDOW_H
#define MYMIANWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class MyMianWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyMianWindow(QWidget *parent = 0);

signals:

public slots:

private :
    QMenuBar * pMenuBar;
};

#endif // MYMIANWINDOW_H
