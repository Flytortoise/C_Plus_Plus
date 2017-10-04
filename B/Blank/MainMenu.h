#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0,int client_sock = 0);

signals:

public slots:
    int Open(); //开户
    int Save(); //存款
    int Draw(); //取款
    int Tran(); //转账
    int Inqu(); //余额查询
    int ChPw(); //密码修改
    int Hist(); //显示全部历史信息
    int Dest(); //销户
    int Exit(); //退出登录

private:
    QPushButton *_open;
    QPushButton *_save;
    QPushButton *_draw;
    QPushButton *_tran;
    QPushButton *_inqu;
    QPushButton *_chpw;
    QPushButton *_hist;
    QPushButton *_dest;
    QPushButton *_exit;
    QLabel *_temp;

    int _my_sock;

};

#endif // MAINMENU_H
