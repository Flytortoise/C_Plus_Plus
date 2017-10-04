#include "MyWidget.h"

#include <QVBoxLayout>
#include <QDesktopServices>
#include <QDebug>
#include <QCompleter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    init();
    initLayout();

}

void MyWidget::init()
{
    _vBox = new QVBoxLayout(this);
    //_label = new QLabel("label", this);
    // 设置文本
    //_label = new QLabel("<h1>lable</h1>");
    // 设置颜色
    //_label = new QLabel("<font color=red>lable</font>");
    // 设置链接
    _label = new QLabel("<a href=www.baidu.com>baidu</a>");
    // 设置图片
    //_label = new QLabel("<img src=../photo/1.gif></img>");
    //_label->setPixmap(QPixmap("../photo/1.gif"));
    //connect(_label, SIGNAL(linkActivated(QString)), this, SLOT(LableOpenLink(QString)));
    connect(_label, &QLabel::linkActivated, [](QString str){
        qDebug() << "asdadadsad";
        QDesktopServices::openUrl(str); //设置超链接
    });

    _lineEdit = new QLineEdit(this);    //单行文本输入框
    _textEdit = new QTextEdit("第一题内容", this);   //多行文本输入框
//  connect(_textEdit, SIGNAL(textChanged()), this, SLOT(textEditChage())); 好像没啥用


    _button = new QPushButton("button", this);  //按钮
 // connect(_button, SIGNAL(clicked()),this, SLOT(clicked()));  好像也没啥用

    _radio = new QRadioButton("RadioButton", this);     //单选按钮
    connect(_radio, &QRadioButton::clicked, [](bool value){
        qDebug() << value;
    });

    _checkbox = new QCheckBox("checkBox", this);    //选择框（方框，可打勾的）
    connect(_checkbox, &QRadioButton::clicked, [](bool value){
        qDebug() << value;
    });

    _groupBox = new QGroupBox("第一题", this); //组合框
#if 0
    QVBoxLayout *vBox1 = new QVBoxLayout(this);
    vBox1->addWidget(new QRadioButton("A"));
    vBox1->addWidget(new QRadioButton("B"));
    vBox1->addWidget(new QRadioButton("C"));
    vBox1->addWidget(new QRadioButton("D"));

    QVBoxLayout *vBox2 = new QVBoxLayout(this);
    vBox2->addWidget(new QRadioButton("A"));
    vBox2->addWidget(new QRadioButton("B"));
    vBox2->addWidget(new QRadioButton("C"));
    vBox2->addWidget(new QRadioButton("D"));

    QVBoxLayout *vBox3 = new QVBoxLayout(this);
    vBox3->addWidget(new QRadioButton("A"));
    vBox3->addWidget(new QRadioButton("B"));
    vBox3->addWidget(new QRadioButton("C"));
    vBox3->addWidget(new QRadioButton("D"));

    QGroupBox * groupBox = new QGroupBox("第一题", this);
    groupBox->setLayout(vBox1);
    QGroupBox *groupBox1 = new QGroupBox("第二题", this);
    groupBox1->setLayout(vBox2);
    QGroupBox *groupBox2 = new QGroupBox("第三题", this);
    groupBox2->setLayout(vBox3);

    _vBox->addWidget(groupBox);
    _vBox->addWidget(groupBox1);
    _vBox->addWidget(groupBox2);
#endif
    _combo = new QComboBox(this);   //下拉框
    _combo->addItem("第一题");
    _combo->addItem("第二题");
    _combo->addItem("第三题");
    _combo->setEditable(true);  //下拉框内容可输入
    //_combo->setCompleter(new QCompleter(QStringList() << "123" << "abc"));
    _combo->setCompleter(new QCompleter(_combo->model()));  //自动填充
    //connect(_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboChanged(QString)));
    connect(_combo, SIGNAL(currentIndexChanged(QString)), _textEdit, SLOT(setText(QString)));
                //将下拉框的内容在文本框中显示

    _slider = new QSlider(this);    //滑动器
    _slider->setMaximum(100);   //滑动器上限
    _slider->setMinimum(0);     //滑动器下限
    _slider->setOrientation(Qt::Horizontal);    //让滑动器横放
    //connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));

    _spinBox = new QSpinBox(this);  //选值框
    _spinBox->setMaximum(100);      //选值框上限
    _spinBox->setMinimum(0);        //选值框下限
    connect(_spinBox, SIGNAL(valueChanged(int)), _slider, SLOT(setValue(int)));
    connect(_slider, SIGNAL(valueChanged(int)), _spinBox, SLOT(setValue(int)));
        //将滑动器与选值框互相关联

    _dateEdit = new QDateEdit(this);    //日期输入框
    _timeEdit = new QTimeEdit(this);    //时间输入框
    _DTEdit = new QDateTimeEdit(this);  //日期时间输入框

    _lcd = new QLCDNumber(this);        //数码显示框
    _lcd->display("16");    //输出的内容
    _lcd->setMode(QLCDNumber::Hex);     //16进制输出
    _lcd->setSegmentStyle(QLCDNumber::Flat);    //变亮，不会成为灰色
}

void MyWidget::initLayout()
{
    _vBox->addWidget(_label);
    _vBox->addWidget(_lineEdit);;
    _vBox->addWidget(_textEdit);
    _vBox->addWidget(_button);
    _vBox->addWidget(_radio);
    _vBox->addWidget(new QRadioButton("radioButton2"));
    _vBox->addWidget(new QRadioButton("radioButton3"));
    _vBox->addWidget(new QRadioButton("radioButton4"));

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

void MyWidget::LableOpenLink(QString str)
{
    qDebug() << str;
    QDesktopServices::openUrl(str);
}


void MyWidget::textEditChage()
{
    QString str = _textEdit->toPlainText();
    if (str.contains("/ku"))
    {
        str.replace("/ku", "<img src=../photo/1.gif></img>");
        _textEdit->setText(str);
    }
}

void MyWidget::comboChanged(QString str)
{
    qDebug() << str;
    if (str == "第一题")
    {
        _textEdit->setText("第一题内容");
    }
    else if (str == "第二题")
    {
        _textEdit->setText("第二题内容");
    }
    else if (str == "第三题")
    {
        _textEdit->setText("第三题内容");
    }
}

void MyWidget::sliderValueChanged(int value)
{
    qDebug() << value;
}

void MyWidget::clicked()
{

}
