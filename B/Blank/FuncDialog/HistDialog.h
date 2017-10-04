#ifndef HISTDIALOG_H
#define HISTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Func/Hist.h"

class HistDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HistDialog( int client_sock = 0);

signals :

public slots:
    void Yes();   //确认
    void Exit();    //取消

private:
    QLineEdit *_passbook_id;
    QLineEdit *_passwd;
    QLineEdit *_year_;   //起始年
    QLineEdit *_month_;     //起始月
    QLineEdit *_day_;      //起始日
    QLineEdit *_year_next;
    QLineEdit *_month_next;
    QLineEdit *_day_next;

    Hist *_hist;    //开户操作

    int _my_sock;      //链接服务器的套结字

    void Result(int action);
    int Warning();

};



#endif // HISTDIALOG_H
