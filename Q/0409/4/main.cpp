#include <QApplication>
#include "MyWidget.h"
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    MyWidget m;
    m.show();


    return app.exec();
}
