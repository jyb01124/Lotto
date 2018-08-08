#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QProcess>
#include <QLabel>
#include <QVBoxLayout>
#include "widget.h"

class main_widget : public QDialog
{
    Q_OBJECT
public:
    explicit main_widget(const int &su, const QStringList &a, QWidget *parent = nullptr);

    Widget* w;

signals:
    void sig();

public slots:
    void start_1();
    void start_2();
    void error_();
};

#endif // MAIN_WIDGET_H
