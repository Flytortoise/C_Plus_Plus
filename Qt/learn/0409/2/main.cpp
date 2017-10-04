#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QCompleter>
#include <QTextCodec>  
#include <QDebug>



int main(int argc, char* argv[])
{
	QApplication app(argc,argv);

	QWidget w1;
	QLineEdit Edit;
	Edit.setParent(&w1);

	Edit.setEchoMode(QLineEdit::Normal);	//设置输入模式
	//Edit.text();	//获取文本


	Edit.setPlaceholderText("密码");	//设置提示

	QCompleter cmp(QStringList() << "你好" << "321");	//创建补全对象，并且初始化
	cmp.setFilterMode(Qt::MatchContains);	//设置补齐方式，以任意字母补齐
	Edit.setCompleter(&cmp);	//自动补全，默认以第一个匹配

	w1.show();
	qDebug() << "您好,333";
    return app.exec();
}

