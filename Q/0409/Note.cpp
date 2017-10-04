
#include <QWidget>
#include <QLabel>         // 标签页
#include <QLineEdit>      // 单行文本输入框
#include <QVBoxLayout>
#include <QTextEdit>      // 多行文本输入框
#include <QPushButton>    // 按钮
#include <QRadioButton>   // 单选按钮
#include <QCheckBox>      // 选择框
#include <QGroupBox>      // 组合框
#include <QComboBox>      // 下拉框
#include <QSlider>        // 滑动器
#include <QSpinBox>       // 选值框
#include <QDateEdit>      // 日期输入框
#include <QTimeEdit>      // 时间输入框
#include <QDateTimeEdit>  // 日期时间输入框
#include <QLCDNumber>     // 数码显示器

QVBoxLayout *_vBox;
QLabel *_label;
QLineEdit *_lineEdit;
QTextEdit *_textEdit;
QPushButton *_button;
QRadioButton *_radio;
QCheckBox *_checkbox;
QGroupBox *_groupBox;
QComboBox *_combo;
QSlider *_slider;
QSpinBox *_spinBox;
QDateEdit *_dateEdit;
QTimeEdit *_timeEdit;
QDateTimeEdit *_DTEdit;
QLCDNumber *_lcd;

_vBox = new QVBoxLayout(this);
_label = new QLabel("label", this);
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

"<h1>lable</h1>"

"<font color=red>lable</font>"

"<a href=www.baidu.com>baidu</a>"

"<img src=../photo/1.gif></img>"

connect(_label, SIGNAL(linkActivated(QString)), this, SLOT(LableOpenLink(QString)));

connect(_label, &QLabel::linkActivated, [](QString str){
    });

SLOT
