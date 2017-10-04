#include "DrawDialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <stdio.h>
#include "mark.h"


DrawDialog::DrawDialog(int client_sock) : _my_sock(client_sock)
{
    this->setWindowTitle("Draw");

    QVBoxLayout *vbox = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout();
    QLabel *label = new QLabel("Passbook Id",this);
    _passbook_id = new QLineEdit(this);
    hbox->addWidget(label);
    hbox->addWidget(_passbook_id);

    QHBoxLayout *hbox1 = new QHBoxLayout();
    QLabel *label1 = new QLabel("Passwd",this);
    _passwd = new QLineEdit(this);
    _passwd->setEchoMode(QLineEdit::Password);
    hbox1->addWidget(label1);
    hbox1->addWidget(_passwd);

    QHBoxLayout *hbox2 = new QHBoxLayout();
    QLabel *label2 = new QLabel("Draw Money",this);
    _money = new QLineEdit(this);
    hbox2->addWidget(label2);
    hbox2->addWidget(_money);


    QHBoxLayout *hbox3 = new QHBoxLayout();
    QPushButton *button1 = new QPushButton("Yes",this);
    QPushButton *button2 = new QPushButton("Exit",this);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(Yes()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(Exit()));
    hbox3->addWidget(button1);
    hbox3->addWidget(button2);

   // vbox->addStretch(1);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    //vbox->addStretch(1);
}

void DrawDialog::Yes()
{
    if(Warning())
    {
        return ;
    }

    QByteArray passbook = _passbook_id->text().toLatin1();
    QByteArray passwd = _passwd->text().toLatin1();
    QByteArray money = _money->text().toLatin1();

    _draw = Draw::GetDraw();
    this->Result(_draw->Function(_my_sock,passbook.data(),passwd.data(),money.data()));

}

void DrawDialog::Exit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        reject();
    }
}

void DrawDialog::Result(int action)
{
    switch(action)
    {
        case NO_ACCOUNT: //无帐号
        {
            QMessageBox::critical(this,"error","No Account !!");
        }break;

        case NO_MONEY: //无余额
        {
            QMessageBox::critical(this,"error","No Money !!");
        }break;

        case PASSWD_ERROR: //密码错误
        {
            QMessageBox::critical(this,"error","PassWord ERROR !!");
        }break;

        case DRAW_SUCCESS: //存款成功
        {
            QMessageBox::about(this,"success","Draw successfully");
        }break;

    }
}


int DrawDialog::Warning()
{
    if(_passbook_id->text().length() == 0)  //无ID
    {
        QMessageBox::warning(this,"warning","Please input ID !");
        return 1;
    }

    if(_passwd->text().length() < 6 )   //密码过短
    {
        QMessageBox::warning(this,"warning","passwd is too short");
        return 1;
    }

    if(_passwd->text().length() > 8 )   //密码过长
    {
        QMessageBox::warning(this,"warning","passwd is too long");
        return 1;
    }

    if(!(QString::compare(_money->text(),"0"))) //初始金额为0
    {
        QMessageBox::warning(this,"warning","No money");
        return 1;
    }

    return 0;
}
