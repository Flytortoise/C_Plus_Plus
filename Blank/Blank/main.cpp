#include <QApplication>
#include <QDialog>
#include <QDebug>
#include "MyDialog.h"
#include "MainMenu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    MyDialog dia;
    if(dia.exec() == QDialog::Accepted)
    {
       // qDebug() << dia.GetSock();
        MainMenu w(0,dia.GetSock());
        w.show();
        return app.exec();
    }
    else
    {
        return 0;
    }
}
