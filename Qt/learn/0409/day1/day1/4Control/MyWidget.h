#ifndef MYWIDGET_H
#define MYWIDGET_H

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


class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

    void init();
    void initLayout();

signals:

public slots:
    void LableOpenLink(QString);

    void textEditChage();

    void comboChanged(QString);

    void sliderValueChanged(int);

    void clicked();

private:
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
};

#endif // MYWIDGET_H
