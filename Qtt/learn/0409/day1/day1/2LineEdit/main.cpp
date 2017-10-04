// 应用程序抽象，抽象的是一个应用程序
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QCompleter>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget w;
    QLineEdit lineEdit;
    lineEdit.setParent(&w);

    QPushButton button("Button");
    button.setParent(&w);

    button.setGeometry(200, 100, 100, 50);
    lineEdit.setGeometry(200, 160, 100, 20);

    // 设置输入模式
    //enum EchoMode { Normal, NoEcho, Password, PasswordEchoOnEdit };
    lineEdit.setEchoMode(QLineEdit::Normal);

    // 获取文本
    lineEdit.text();

    // 设置提示
    lineEdit.setPlaceholderText("密码");

    // 自动补全
    QCompleter cmpl(QStringList() << "123" << "213" << "abc" << "zhao" << "qian" << "sun" << "li");
    cmpl.setFilterMode(Qt::MatchContains);

    lineEdit.setCompleter(&cmpl);

    w.show();

    return app.exec();
}
