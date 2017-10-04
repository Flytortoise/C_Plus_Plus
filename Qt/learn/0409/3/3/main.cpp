#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget w;
    QLabel L1("帐号:");
    L1.setParent(&w);
    QLabel L2("密码:");
    L2.setParent(&w);

    QPushButton button("登录");
    button.setParent(&w);

    QLineEdit userEdit;
    QLineEdit passwdEdit;
    userEdit.setParent(&w);
    passwdEdit.setParent(&w);
    userEdit.setPlaceholderText("帐号");
    passwdEdit.setPlaceholderText("密码");
    passwdEdit.setEchoMode(QLineEdit::Password);

    QGridLayout glayout;
    QHBoxLayout hbox;

    glayout.addWidget(&L1,1,1);
    glayout.addWidget(&userEdit,1,2);
    glayout.addWidget(&L2,2,1);
    glayout.addWidget(&passwdEdit,2,2);

    hbox.addStretch(1);
    hbox.addWidget(&button);
    glayout.addLayout(&hbox,3,2);

    glayout.setColumnStretch(3,1);
    glayout.setColumnStretch(0,1);
    glayout.setRowStretch(4,1);
    glayout.setRowStretch(0,1);

    w.setLayout(&glayout);
    w.show();
    return app.exec();
}
