#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Func/Save.h"

class SaveDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SaveDialog(int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_passbook_id;   //存折ID
    QLineEdit *_money;      //存款金额

    Save *_save;    //开户操作

    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};

#endif // SAVEDIALOG_H
