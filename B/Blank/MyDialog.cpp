#include "MyDialog.h"
#include "RegistDialog.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>  //标准对话框
#include <QDebug>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Sock.h"
#include "Pass.h"
#include "mark.h"   //自定义宏

MyDialog::MyDialog(QWidget *parent) : QDialog(parent),_count(false)
{
    //this->setMaximumSize(429,330);
    //this->setMinimumSize(429,330);
    this->setWindowTitle("Log");
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
    QPushButton *button1 = new QPushButton("log",this);
    QPushButton *button2 = new QPushButton("exit",this);
    QPushButton *button3 = new QPushButton("regist",this);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(login()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(slotExit()));
    connect(button3,SIGNAL(clicked(bool)),this,SLOT(regist()));
    hbox2->addWidget(button1);
    hbox2->addWidget(button2);
    hbox2->addWidget(button3);

   // vbox->addStretch(1);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    //vbox->addStretch(1);
}


void MyDialog::login()
{
    if(Warning())
    {
        return ;
    }
    //qDebug()<< "log!";
    if(!_count) //未链接
    {
        //qDebug()<< "connect!";
        Client_Sock *my_client = Client_Sock::GetSock();
        _m_sock = my_client->Action();
        _count = true;
    }

    //进行登录操作
    QByteArray username = _username->text().toLatin1();
    QByteArray passwd = _passwd->text().toLatin1();
    _pass = new Pass(_m_sock,username.data(),passwd.data());
    //strcpy(_flag,LOG);
    //send(_m_sock,_flag,sizeof(_flag),0);   //发送登录操作

    this->Result(_pass->Action(1));
    delete _pass;
}

void MyDialog::regist()
{
   // int sock = _m_sock;
    RegistDialog reg;
    if(reg.exec() == QDialog::Accepted)
    {
        _passwd->setText(reg.GetPassWd());
       // qDebug() << _passwd->text();
        if(!_count) //未链接
        {
            Client_Sock *my_client = Client_Sock::GetSock();
            _m_sock = my_client->Action();
            _count = true;
        }

        //进行注册操作
        QByteArray name = reg.GetUserName().toLatin1();
        QByteArray passwd = _passwd->text().toLatin1();
        //qDebug()<<name.data();
        _pass = new Pass(_m_sock,name.data(),passwd.data());
       // strcpy(_flag,REGIST);
       // write(_m_sock,_flag,sizeof(_flag));  //发送注册操作
       // send(_m_sock,_flag,sizeof(_flag),0);

        this->Result(_pass->Action(0));
        delete _pass;
    }
}


void MyDialog::slotExit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        //strcpy(_flag,CANCEL);
        //send(_m_sock,_flag,sizeof(_flag),0);  //发送取消操作

        reject();
    }
}

void MyDialog::Result(int action)
{
    switch(action)
    {
        case LOG_SUCCESS: //登录成功
        {
            accept();
        }break;
        case PASSWD_ERROR: //密码错误
        {
            QMessageBox::critical(this,"error","Passwd error!");
        }break;

        case NO_ACCOUNT: //帐号未注册
        {
            QMessageBox::critical(this,"error","Account is not registed");
        }break;

        case HAS_ACCOUNT: //帐号已注册
        {
            QMessageBox::critical(this,"error","Account already exists");
        }break;

        case REGIST_SUCCESS: //注册成功，显示ID号
        {
            QMessageBox::about(this,"success","Account Success!!");
        }break;

        case DOUBLE_LOG: //请勿重复登录
        {
            QMessageBox::critical(this,"error","Don't log again");
        }break;
    }
}


int MyDialog::Warning()
{
    if(_username->text().length() < 3)
    {
        QMessageBox::warning(this,"warning","usename is too short");
        return 1;
    }

    if(_username->text().length() > 10)
    {
        QMessageBox::warning(this,"warning","usename is too long");
        return 1;
    }

    if(_passwd->text().length() < 6 )
    {
        QMessageBox::warning(this,"warning","passwd is too short");
        return 1;
    }

    if(_passwd->text().length() > 8 )
    {
        QMessageBox::warning(this,"warning","passwd is too long");
        return 1;
    }

    QByteArray name = _username->text().toLatin1();
    char *str = name.data();
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

int MyDialog::GetSock()
{
    //qDebug() << _m_sock;
    return _m_sock;
}

