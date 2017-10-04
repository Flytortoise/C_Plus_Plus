
#include "HistDialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QIntValidator>
#include <stdio.h>
#include <QDebug>
#include "mark.h"


HistDialog::HistDialog( int client_sock) : _my_sock(client_sock)
{
    this->setWindowTitle("Hist");

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
    QLabel *label2 = new QLabel("Begin year",this);
    _year_ = new QLineEdit(this);
    _year_->setText("0");
    hbox2->addWidget(label2);
    hbox2->addWidget(_year_);

    QHBoxLayout *hbox3 = new QHBoxLayout();
    QLabel *label3 = new QLabel("Begin month",this);
    _month_ = new QLineEdit(this);
    _month_->setText("0");
    hbox3->addWidget(label3);
    hbox3->addWidget(_month_);

    QHBoxLayout *hbox4 = new QHBoxLayout();
    QLabel *label4 = new QLabel("Begin day",this);
    _day_ = new QLineEdit(this);
    _day_->setText("0");
    hbox4->addWidget(label4);
    hbox4->addWidget(_day_);

    QHBoxLayout *hbox5 = new QHBoxLayout();
    QLabel *label5 = new QLabel("End year",this);
    _year_next = new QLineEdit(this);
    _year_next->setText("0");
    hbox5->addWidget(label5);
    hbox5->addWidget(_year_next);

    QHBoxLayout *hbox6 = new QHBoxLayout();
    QLabel *label6 = new QLabel("End month",this);
    _month_next = new QLineEdit(this);
    _month_next->setText("0");
    hbox6->addWidget(label6);
    hbox6->addWidget(_month_next);

    QHBoxLayout *hbox7 = new QHBoxLayout();
    QLabel *label7 = new QLabel("End day",this);
    _day_next = new QLineEdit(this);
    _day_next->setText("0");
    hbox7->addWidget(label7);
    hbox7->addWidget(_day_next);


    QHBoxLayout *hbox8 = new QHBoxLayout();
    QPushButton *button1 = new QPushButton("Yes",this);
    QPushButton *button2 = new QPushButton("Exit",this);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(Yes()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(Exit()));
    hbox8->addWidget(button1);
    hbox8->addWidget(button2);

   // vbox->addStretch(1);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    vbox->addLayout(hbox4);
    vbox->addLayout(hbox5);
    vbox->addLayout(hbox6);
    vbox->addLayout(hbox7);
    vbox->addLayout(hbox8);
    //vbox->addStretch(1);
}

void HistDialog::Yes()
{
    if(Warning())
    {
        return ;
    }

    QByteArray passbook = _passbook_id->text().toLatin1();
    QByteArray passwd = _passwd->text().toLatin1();
    QByteArray year = _year_->text().toLatin1();
    QByteArray month = _month_->text().toLatin1();
    QByteArray day = _day_->text().toLatin1();
    QByteArray year2 = _year_next->text().toLatin1();
    QByteArray month2 = _month_next->text().toLatin1();
    QByteArray day2 = _day_next->text().toLatin1();

    int len1 = year.size() + month.size() + day.size() ;
    int len2 = year2.size() + month2.size() + day2.size();

    char *str1 = new char[len1 + 3];
    char *str2 = new char[len2 + 3];

    snprintf(str1,len1+3,"%s-%s-%s",year.data(),month.data(),day.data());
    snprintf(str2,len2+3,"%s-%s-%s",year2.data(),month2.data(),day2.data());
   // qDebug() <<str1;
   // qDebug() << str2;

    _hist = Hist::GetHist();
    this->Result(_hist->Function(_my_sock,passbook.data(),passwd.data(),
                                 str1,str2));
    delete []str1;
    delete []str2;
}

void HistDialog::Exit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        reject();
    }
}

void HistDialog::Result(int action)
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

        case HIST_SUCCESS: //查询成功
        {

            QMessageBox::about(this,"success",_hist->GetInformation().c_str());
        }break;

        case NO_HISTORY: //无记录
        {
            QMessageBox::about(this,"NULL","History is empty !!");
        }break;

    }
}


int HistDialog::Warning()
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

