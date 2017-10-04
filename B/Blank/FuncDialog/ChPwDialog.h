#ifndef CHPWDIALOG_H
#define CHPWDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Func/ChPw.h"

class ChPwDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChPwDialog( int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_passbook_id;   //存折ID
    QLineEdit *_passwd;     //密码
    QLineEdit *_new_passwd;      //转账金额
    QLineEdit *_new_passwd2;   //对方ID

    ChPw *_chpw;    //开户操作

    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};



#endif // CHPWDIALOG_H
