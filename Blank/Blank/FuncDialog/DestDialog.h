#ifndef DESTDIALOG_H
#define DESTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Func/Dest.h"

class DestDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DestDialog( int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_passbook_id;   //存折ID
    QLineEdit *_passwd;     //密码

    Dest *_dest;    //开户操作

    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};


#endif // DESTDIALOG_H
