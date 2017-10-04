// 应用程序抽象，抽象的是一个应用程序
#include <QApplication>
#include "MyWidget.h"
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyWidget w;
    w.show();
   // QPushButton butto;
    return app.exec();
}
