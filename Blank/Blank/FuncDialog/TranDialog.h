#ifndef TRANDIALOG_H
#define TRANDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Func/Tran.h"

class TranDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TranDialog(int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_passbook_id;   //存折ID
    QLineEdit *_passwd;     //密码
    QLineEdit *_money;      //转账金额
    QLineEdit *_other_id;   //对方ID

    Tran *_tran;    //开户操作

    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};



#endif // TRANDIALOG_H
