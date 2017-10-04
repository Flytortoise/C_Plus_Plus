#include "ChPwDialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <stdio.h>
#include "mark.h"


ChPwDialog::ChPwDialog(int client_sock) : _my_sock(client_sock)
{
    this->setWindowTitle("ChangePasswd");

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
    QLabel *label2 = new QLabel("New Passwd",this);
    _new_passwd = new QLineEdit(this);
    hbox2->addWidget(label2);
    hbox2->addWidget(_new_passwd);

    QHBoxLayout *hbox3 = new QHBoxLayout();
    QLabel *label3 = new QLabel("New Passwd agagin",this);
    _new_passwd2 = new QLineEdit(this);
    hbox3->addWidget(label3);
    hbox3->addWidget(_new_passwd2);


    QHBoxLayout *hbox4 = new QHBoxLayout();
    QPushButton *button1 = new QPushButton("Yes",this);
    QPushButton *button2 = new QPushButton("Exit",this);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(Yes()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(Exit()));
    hbox4->addWidget(button1);
    hbox4->addWidget(button2);

   // vbox->addStretch(1);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    vbox->addLayout(hbox4);
    //vbox->addStretch(1);
}

void ChPwDialog::Yes()
{
    if(Warning())
    {
        return ;
    }

    QByteArray passbook = _passbook_id->text().toLatin1();
    QByteArray passwd = _passwd->text().toLatin1();
    QByteArray newpasswd = _new_passwd->text().toLatin1();

    _chpw = ChPw::GetChPw();
    this->Result(_chpw->Function(_my_sock,passbook.data(),passwd.data(),
                                 newpasswd.data()));

}

void ChPwDialog::Exit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        reject();
    }
}

void ChPwDialog::Result(int action)
{
    switch(action)
    {
        case NO_ACCOUNT: //无帐号
        {
            QMessageBox::critical(this,"error","No Account !!");
        }break;


        case PASSWD_ERROR: //密码错误
        {
            QMessageBox::critical(this,"error","PassWord ERROR !!");
        }break;

        case CHPW_SUCCESS: //转账成功
        {
            QMessageBox::about(this,"success","Change Passwd successfully");
        }break;

    }
}


int ChPwDialog::Warning()
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

    if(_new_passwd->text().length() < 6 )   //新密码过短
    {
        QMessageBox::warning(this,"warning","new passwd is too short");
        return 1;
    }

    if(_new_passwd->text().length() > 8 )   //新密码过长
    {
        QMessageBox::warning(this,"warning","new passwd is too long");
        return 1;
    }

    if(QString::compare(_new_passwd->text(),_new_passwd2->text()))
    {
        QMessageBox::warning(this,"warning","the two passwords are not the same");
        return 1;
    }

    return 0;
}

