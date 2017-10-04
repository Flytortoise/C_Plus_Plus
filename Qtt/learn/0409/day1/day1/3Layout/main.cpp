// 应用程序抽象，抽象的是一个应用程序
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextBrowser>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget w;
#if 0
    QLineEdit lineEdit;
    lineEdit.setParent(&w);

    QPushButton button("Button");
    button.setParent(&w);

    QPushButton button1("Button1");
    button1.setParent(&w);

    QPushButton button2("Button2");
    button2.setParent(&w);

    QLabel label("label");
    label.setParent(&w);
    tb.setParent(&w);

    QVBoxLayout vBox;
    vBox.addStretch(1);
    vBox.addWidget(&button);
    vBox.addWidget(&button1);
   // vBox.addStretch(1);
    vBox.addWidget(&button2);
    vBox.addWidget(&lineEdit);
    vBox.addStretch(1);
    QHBoxLayout hBox;
    hBox.addStretch(1);
    hBox.addLayout(&vBox);
    hBox.addStretch(1);

//    hBox.addStretch(1);
//    hBox.addWidget(&button);
//    hBox.addWidget(&button1);
//    hBox.addStretch(1);
//    hBox.addWidget(&button2);
//    hBox.addWidget(&lineEdit);
//    hBox.addStretch(1);


    QGridLayout glayout;
    glayout.addWidget(&button, 1, 1);
    glayout.addWidget(&button1, 1, 2);
    glayout.addWidget(&button2, 2, 1);
    glayout.addWidget(&label, 2, 2);
    glayout.addWidget(&lineEdit, 3, 1, 1, 2);


    glayout.setColumnStretch(0, 1);
    glayout.setColumnStretch(3, 1);
    glayout.setRowStretch(0, 1);
    glayout.setRowStretch(4, 1);
#endif
    QLabel username("<img src=../photo/1.gif></img>");
    QLabel password("password");

    QLineEdit userEdit;
    userEdit.setPlaceholderText("用户名");
    QLineEdit passwdEdit;
    passwdEdit.setPlaceholderText("密码");
    passwdEdit.setEchoMode(QLineEdit::Password);

    QPushButton button("登陆");
    QGridLayout glayout;
    QHBoxLayout hBox;
    glayout.addWidget(&username, 1, 1);
    glayout.addWidget(&userEdit, 1, 2);
    glayout.addWidget(&password, 2, 1);
    glayout.addWidget(&passwdEdit, 2, 2);

    hBox.addStretch(1);
    hBox.addWidget(&button);
    glayout.addLayout(&hBox, 3, 2);

    glayout.setColumnStretch(0, 1);
    glayout.setColumnStretch(3, 1);
    glayout.setRowStretch(0, 1);
    glayout.setRowStretch(4, 1);

    w.setLayout(&glayout);
    w.show();

    return app.exec();
}
