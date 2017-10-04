// 应用程序抽象，抽象的是一个应用程序
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextBrowser>
#include "MyWidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyWidget w;
    w.show();


    return app.exec();
}
