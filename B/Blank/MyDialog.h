//登录窗口

#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QLineEdit>
#include <QDialog>
#include <Pass.h>

class MyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialog(QWidget *parent = 0);
    int GetSock();


signals :

public slots:
    void login();   //登录
    void slotExit();    //取消
    void regist();      //注册

private:
    QLineEdit *_username;   //用户名
    QLineEdit *_passwd;     //密码

    bool _count;
    int _m_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

    Pass *_pass;    //PASS操作
//    char _flag[5];      //操作标志
};

#endif // MYDIALOG_H
