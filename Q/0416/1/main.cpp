#include <QApplication>
#include <QWidget>
#include "MyWidge.h"
#include "MyButton.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    MyWidge w;

    w.show();

    return  app.exec();
}
