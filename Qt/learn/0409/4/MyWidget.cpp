#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    Init();
    connect(_label,SIGNAL(linkActivated(QString)),this,SLOT(LabelOpen(QString)));
}

void  MyWidget::Init()
{
    _vBox = new QVBoxLayout(this);
    _label = new QLabel("<a href=www.baidu.com>baidu</a>");
    _lineEdit = new QLineEdit(this);
    _textEdit = new QTextEdit(this);
    _button = new QPushButton("button", this);
    _radio = new QRadioButton("RadioButton", this);
    _checkbox = new QCheckBox("checkBox", this);
    _groupBox = new QGroupBox("group", this);
    _combo = new QComboBox(this);
    _slider = new QSlider(this);
    _spinBox = new QSpinBox(this);
    _dateEdit = new QDateEdit(this);
    _timeEdit = new QTimeEdit(this);
    _DTEdit = new QDateTimeEdit(this);
    _lcd = new QLCDNumber(this);

    _vBox->addWidget(_label);
    _vBox->addWidget(_lineEdit);;
    _vBox->addWidget(_textEdit);
    _vBox->addWidget(_button);
    _vBox->addWidget(_radio);
    _vBox->addWidget(_checkbox);
    _vBox->addWidget(_groupBox);
    _vBox->addWidget(_combo);
    _vBox->addWidget(_slider);
    _vBox->addWidget(_spinBox);
    _vBox->addWidget(_dateEdit);
    _vBox->addWidget(_timeEdit);
    _vBox->addWidget(_DTEdit);
    _vBox->addWidget(_lcd);

}

MyWidget::~MyWidget()
{
    delete _vBox;
    delete _label;
    delete _lineEdit;
    delete _textEdit;
    delete _button;
    delete _radio;
    delete _checkbox;
    delete _groupBox;
    delete _combo;
    delete _slider;
    delete _spinBox;
    delete _dateEdit;
    delete _timeEdit;
    delete _DTEdit;
    delete _lcd;
}


void MyWidget::LabelOpen(QString str)
{
    QDesktopServices::openUrl(str);
}
