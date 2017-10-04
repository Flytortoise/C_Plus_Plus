#include "SaveDialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <stdio.h>

#include "mark.h"

SaveDialog::SaveDialog( int client_sock) : _my_sock(client_sock)
{
    this->setWindowTitle("Save");

    QVBoxLayout *vbox = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout();
    QLabel *label = new QLabel("Passbook id",this);
    _passbook_id = new QLineEdit(this);
    hbox->addWidget(label);
    hbox->addWidget(_passbook_id);

    QHBoxLayout *hbox1 = new QHBoxLayout();
    QLabel *label1 = new QLabel("Save money",this);
    _money = new QLineEdit(this);
    hbox1->addWidget(label1);
    hbox1->addWidget(_money);


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

void SaveDialog::Yes()
{
    if(Warning())
    {
        return ;
    }

    QByteArray passbook = _passbook_id->text().toLatin1();
    QByteArray money = _money->text().toLatin1();

    _save = Save::GetSave();
    this->Result(_save->Function(_my_sock,passbook.data(),money.data()));

}

void SaveDialog::Exit()
{
    int ret = QMessageBox::question(this,"Exit?","yes/no",QMessageBox::No|QMessageBox::Yes,QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        reject();
    }
}

void SaveDialog::Result(int action)
{
    switch(action)
    {
        case NO_ACCOUNT: //无帐号
        {
            QMessageBox::critical(this,"error","No Account !!");
        }break;

        case SAVE_SUCCESS: //存款成功
        {
            QMessageBox::about(this,"success","Save successfully");
        }break;

    }
}


int SaveDialog::Warning()
{
    if(_passbook_id->text().length() == 0)
    {
        QMessageBox::warning(this,"warning","Please input ID!");
        return 1;
    }

    if(!(QString::compare(_money->text(),"0"))) //初始金额为0
    {
        QMessageBox::warning(this,"warning","No money");
        return 1;
    }

    return 0;
}
