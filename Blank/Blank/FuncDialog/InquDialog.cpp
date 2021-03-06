
#include "InquDialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <stdio.h>
#include "mark.h"


InquDialog::InquDialog( int client_sock) : _my_sock(client_sock)
{
    this->setWindowTitle("Inqu");

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
    QPushButton *button1 = new QPushButton("Yes",this);
    QPushButton *button2 = new QPushButton("Exit",this);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(Yes()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(Exit()));
    hbox2->addWidget(button1);
    hbox2->addWidget(button2);

   // vbox->addStretch(1);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    //vbox->addStretch(1);
}

void InquDialog::Yes()
{
    if(Warning())
    {
        return ;
    }

    QByteArray passbook = _passbook_id->text().toLatin1();
    QByteArray passwd = _passwd->text().toLatin1();

    _inqu = Inqu::GetInqu();
    this->Result(_inqu->Function(_my_sock,passbook.data(),passwd.data()));

}

void InquDialog::Exit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        reject();
    }
}

void InquDialog::Result(int action)
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

        case INQU_SUCCESS: //查询成功
        {
            char t[30];
            sprintf(t,"Balance : %s",_inqu->GetMoney());
            QMessageBox::about(this,"success",t);
        }break;

    }
}


int InquDialog::Warning()
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

    return 0;
}

