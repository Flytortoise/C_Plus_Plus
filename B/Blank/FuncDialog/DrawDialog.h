#ifndef DRAWDIALOG_H
#define DRAWDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Func/Draw.h"

class DrawDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DrawDialog(int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_passbook_id;   //存折ID
    QLineEdit *_passwd;     //密码
    QLineEdit *_money;      //取款金额

    Draw *_draw;    //开户操作

    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};



#endif // DRAWDIALOG_H
