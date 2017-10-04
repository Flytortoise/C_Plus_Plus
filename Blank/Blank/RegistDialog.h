//注册窗口

#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H


#include <QLineEdit>
#include <QDialog>
#include <QString>
#include "MyDialog.h"

class RegistDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RegistDialog(QWidget *parent = 0);
    QString GetUserName();
    QString GetPassWd();
signals :

public slots:
    void confirm();
    void cancel();

private:
    QLineEdit *_username;
    QLineEdit *_passwd;
    QLineEdit *_passwd2;     //再次输入密码

   // int _m_sock;
   // char _flag[5];

    int Warning();
};

#endif // REGISTDIALOG_H
