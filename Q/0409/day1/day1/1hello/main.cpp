// 应用程序抽象，抽象的是一个应用程序
#include <QApplication>

// 窗口类抽象类
#include <QWidget>

// 按钮类
#include <QPushButton>
#include <QObject>

int main(int argc, char **argv)
{
    // 定义一个应用程序对象，代表一个应用程序
    QApplication app(argc, argv);

    // 窗口对象
    QWidget w;
    QPushButton button("Button");
    button.setText("abc");
    //button.show();

    // 将窗口设置为button的父对象
    button.setParent(&w);

    //显示窗口
    w.show();


    // 修改窗口名称
    w.setWindowTitle("126");

//    QWidget w1;
//    w1.show();

    QObject::connect(&button, SIGNAL(clicked()), &w, SLOT(close()));

    //exec里面有一个消息死循环，用来处理各种消息
    return app.exec();
}
