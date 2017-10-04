#ifndef INQUDIALOG_H
#define INQUDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Func/Inqu.h"

class InquDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InquDialog(int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_passbook_id;   //存折ID
    QLineEdit *_passwd;     //密码

    Inqu *_inqu;    //开户操作

    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};




#endif // INQUDIALOG_H
