#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <sys/types.h>
#include <sys/socket.h>
#include "MainMenu.h"
#include "Func/Func.h"
#include "FuncDialog/AllDialog.h"
#include "mark.h"


MainMenu::MainMenu(QWidget *parent,int client_sock) : QWidget(parent),_my_sock(client_sock)
{
    this->setWindowTitle("MainMenu");
    this->setMaximumSize(306,220);
    this->setMinimumSize(306,220);

    _open = new QPushButton("Open",this);
    _save = new QPushButton("Save",this);
    _draw = new QPushButton("Draw",this);
    _tran = new QPushButton("Tran",this);
    _inqu = new QPushButton("Inqu",this);
    _chpw = new QPushButton("ChPw",this);
    _hist = new QPushButton("Hist",this);
    _dest = new QPushButton("Dest",this);
    _exit = new QPushButton("Exit",this);
    _temp = new QLabel("",this);

    connect(_open,SIGNAL(clicked(bool)),this,SLOT(Open()));
    connect(_save,SIGNAL(clicked(bool)),this,SLOT(Save()));
    connect(_draw,SIGNAL(clicked(bool)),this,SLOT(Draw()));
    connect(_tran,SIGNAL(clicked(bool)),this,SLOT(Tran()));
    connect(_inqu,SIGNAL(clicked(bool)),this,SLOT(Inqu()));
    connect(_chpw,SIGNAL(clicked(bool)),this,SLOT(ChPw()));
    connect(_hist,SIGNAL(clicked(bool)),this,SLOT(Hist()));
    connect(_dest,SIGNAL(clicked(bool)),this,SLOT(Dest()));
    connect(_exit,SIGNAL(clicked(bool)),this,SLOT(Exit()));


    QVBoxLayout *vbox1 = new QVBoxLayout();
    vbox1->addWidget(_open);
    vbox1->addWidget(_draw);
    vbox1->addWidget(_inqu);
    vbox1->addWidget(_hist);
    vbox1->addWidget(_temp);

    QVBoxLayout *vbox2 = new QVBoxLayout();
    vbox2->addWidget(_save);
    vbox2->addWidget(_tran);
    vbox2->addWidget(_chpw);
    vbox2->addWidget(_dest);
    vbox2->addWidget(_exit);
    vbox2->addStretch(1);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    //hbox->addStretch(1);
    hbox->addLayout(vbox1);
    hbox->addLayout(vbox2);

}

int MainMenu::Open()
{
    OpenDialog OpenDia(_my_sock);
    OpenDia.exec();
    return 0;
}

int MainMenu::Save() //存款
{
    SaveDialog SaveDia(_my_sock);
    SaveDia.exec();

    return 0;
}

int MainMenu::Draw() //取款
{
   DrawDialog DrawDia(_my_sock);
   DrawDia.exec();

   return 0;
}

int MainMenu::Tran() //转账
{
    TranDialog TranDia(_my_sock);
    TranDia.exec();
    return 0;
}

int MainMenu::Inqu() //余额查询
{
     InquDialog Inqu(_my_sock);
     Inqu.exec();
     return 0;
}

int MainMenu::ChPw() //密码修改
{
    ChPwDialog ChPw(_my_sock);
    ChPw.exec();
    return 0;
}



int MainMenu::Hist() //显示全部历史信息
{
    HistDialog Hist(_my_sock);
    Hist.exec();
    return 0;
}

int MainMenu::Dest() //销户
{
    DestDialog Dest(_my_sock);
    Dest.exec();
    return 0;
}

int MainMenu::Exit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        close();
    }

    return 0;
}

