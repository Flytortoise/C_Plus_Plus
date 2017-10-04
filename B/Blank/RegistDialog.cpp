#include "RegistDialog.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>  //标准对话框
#include <QDebug>

#include <unistd.h>

#include "mark.h"


RegistDialog::RegistDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Regist");

    QVBoxLayout *vbox = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout();
    QLabel *label = new QLabel("username",this);
    _username = new QLineEdit(this);
    hbox->addWidget(label);
    hbox->addWidget(_username);

    QHBoxLayout *hbox1 = new QHBoxLayout();
    QLabel *label1 = new QLabel("password",this);
    _passwd = new QLineEdit(this);
    //_passwd->setEchoMode(QLineEdit::Password);
    hbox1->addWidget(label1);
    hbox1->addWidget(_passwd);

    QHBoxLayout *hbox2 = new QHBoxLayout();
    QLabel *label2 = new QLabel("password again",this);
    _passwd2 = new QLineEdit(this);
    //_passwd2->setEchoMode(QLineEdit::Password);
    hbox2->addWidget(label2);
    hbox2->addWidget(_passwd2);


    QHBoxLayout *hbox3 = new QHBoxLayout();
    QPushButton *button1 = new QPushButton("confirm",this);
    QPushButton *button2 = new QPushButton("cancel",this);

    connect(button1,SIGNAL(clicked(bool)),this,SLOT(confirm()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(cancel()));

    hbox3->addWidget(button1);
    hbox3->addWidget(button2);

   // vbox->addStretch(1);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    //vbox->addStretch(1);
}


void RegistDialog::confirm()
{
    if(Warning())
    {
        return ;
    }
    else
    {
        accept();
    }

}

void RegistDialog::cancel()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        //strcpy(_flag,CANCEL);
        //write(_m_sock,&_flag,sizeof(_flag));  //发送取消操作

        reject();
    }
}

QString RegistDialog::GetUserName()
{
    return _username->text();
}

QString RegistDialog::GetPassWd()
{
    return _passwd->text();
}

int RegistDialog::Warning()
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

    if(_passwd->text().compare(_passwd2->text()))
    {
        QMessageBox::warning(this,"warning","the two passwords are not the same");
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
