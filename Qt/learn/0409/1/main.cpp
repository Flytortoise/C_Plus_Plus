#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QObject>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QWidget w1;
	QWidget w2;

	QPushButton button("close");
	button.setParent(&w1);
	QObject::connect(&button,SIGNAL(clicked()),&w2,SLOT(close()));


    w1.show();
	w2.show();

	w1.setWindowTitle("Text1");
	w2.setWindowTitle("Text2");

    return app.exec();
}
