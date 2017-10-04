#include "OpenDialog.h"
#include "mark.h"
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <stdio.h>

OpenDialog::OpenDialog(int client_sock) : _my_sock(client_sock)
{
    this->setWindowTitle("Open");
    QVBoxLayout *vbox = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout();
    QLabel *label = new QLabel("usename",this);
    _username = new QLineEdit(this);
    hbox->addWidget(label);
    hbox->addWidget(_username);

    QHBoxLayout *hbox1 = new QHBoxLayout();
    QLabel *label1 = new QLabel("password",this);
    _passwd = new QLineEdit(this);
    _passwd->setEchoMode(QLineEdit::Password);
    hbox1->addWidget(label1);
    hbox1->addWidget(_passwd);

    QHBoxLayout *hbox2 = new QHBoxLayout();
    QLabel *label2 = new QLabel("password agagin",this);
    _passagin = new QLineEdit(this);
    _passagin->setEchoMode(QLineEdit::Password);
    hbox2->addWidget(label2);
    hbox2->addWidget(_passagin);

    QHBoxLayout *hbox3 = new QHBoxLayout();
    QLabel *label3 = new QLabel("ID",this);
    _ID = new QLineEdit(this);
    hbox3->addWidget(label3);
    hbox3->addWidget(_ID);

    QHBoxLayout *hbox4 = new QHBoxLayout();
    QLabel *label4 = new QLabel("money",this);
    _money = new QLineEdit(this);
    hbox4->addWidget(label4);
    hbox4->addWidget(_money);

    QHBoxLayout *hbox5 = new QHBoxLayout();
    QPushButton *button1 = new QPushButton("Yes",this);
    QPushButton *button2 = new QPushButton("Exit",this);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(Yes()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(Exit()));
    hbox5->addWidget(button1);
    hbox5->addWidget(button2);

   // vbox->addStretch(1);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    vbox->addLayout(hbox4);
    vbox->addLayout(hbox5);
    //vbox->addStretch(1);
}

void OpenDialog::Yes()
{
    if(Warning())
    {
        return ;
    }

    QByteArray username = _username->text().toLatin1();
    QByteArray passwd = _passwd->text().toLatin1();
    QByteArray id = _ID->text().toLatin1();
    QByteArray money = _money->text().toLatin1();

    _open = Open::GetOpen();

    this->Result(_open->Function(_my_sock,username.data(),passwd.data(),id.data(),money.data()));

}

void OpenDialog::Exit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        reject();
    }
}

void OpenDialog::Result(int action)
{
    switch(action)
    {
        case HAS_ACCOUNT: //帐号已注册
        {
            QMessageBox::critical(this,"error","Account already exists");
        }break;

        case REGIST_SUCCESS: //注册成功，显示ID号
        {
            char t[30];
            sprintf(t,"Account Success!!\nID:%s",_open->GetIdd());
            QMessageBox::about(this,"success",t);
        }break;

    }
}



int OpenDialog::Warning()
{
   // qDebug() << _username->text() ;
   // qDebug() << _passwd->text() ;
    //qDebug() << _passagin->text();
   // qDebug() << _ID->text() ;
    //qDebug() << _money->text();


    if(_username->text().length() < 3)  //用户名过短
    {
        QMessageBox::warning(this,"warning","usename is too short");
        return 1;
    }

    if(_username->text().length() > 10) //用户名过长
    {
        QMessageBox::warning(this,"warning","usename is too long");
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

    //qDebug() <<_passwd->text().compare(_passagin->text());


    if(_ID->text().length() < 18 )   //密码长度错误
    {
        QMessageBox::warning(this,"warning","ID is short");
        return 1;
    }

    if(_ID->text().length() > 18 )   //密码长度错误
    {
        QMessageBox::warning(this,"warning","ID is long");
        return 1;
    }

    if(!(QString::compare(_money->text(),"0"))) //初始金额为0
    {
        QMessageBox::warning(this,"warning","No money");
        return 1;
    }

    if(QString::compare(_passwd->text(),_passagin->text())) //两次密码不一致
    {
        QMessageBox::warning(this,"warning","the two passwords are not the same");
        return 1;
    }

    //身份证全为数字
    QByteArray ID = _ID->text().toLatin1();
    char *str = ID.data();
    while(*str != '\0')
    {
        if(!(*str >= '0' && *str <= '9'))
        {
            QMessageBox::warning(this,"warning","usename is not all letters");
            return 1;
        }
        str++;
    }



    //用户名全为字母
    QByteArray name = _username->text().toLatin1();
    str = name.data();
    while(*str != '\0')
    {
        if(!((*str >= 'a' && *str <= 'z')||(*str >= 'A' && *str <='Z')))
        {
            QMessageBox::warning(this,"warning","usename is not all letters");
            return 1;
        }
        str++;
    }

    return 0;
}
