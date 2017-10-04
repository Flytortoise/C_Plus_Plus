#ifndef OPENDIALOG_H
#define OPENDIALOG_H

#include <QDialog>
#include <QLineEdit>

#include "Func/Open.h"

class OpenDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OpenDialog(int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_username;   //用户名
    QLineEdit *_passwd;     //密码
    QLineEdit *_passagin;   //重复密码
    QLineEdit *_ID; //身份证号
    QLineEdit *_money;      //开户金额

    Open *_open;    //开户操作


    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};

#endif // OPENDIALOG_H
