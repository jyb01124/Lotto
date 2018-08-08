#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QProcess>
#include <QApplication>
#include <QtWidgets>
#include "sql.h"
#include "open_number.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    int su = 0;
    int ja = 0;
    int Max_num = 0;

    QSpinBox* no_QSpin;
    QSpinBox* count_QSpin;

public slots:
    void sudong_f(bool);
    void jadong_f(bool);
    void chul_f();
    void bul_f(int Max_num);
    void start_();
    void error_();
};

#endif // WIDGET_H
