#include "main_widget.h"
#include <QDebug>

main_widget::main_widget(const int &su, const QStringList &a, QWidget *parent) : QDialog(parent)
{
    QProcess *EProcess = new QProcess;
    QStringList list = a;

    QLabel* warn;

    if(su == 1)
    {
        EProcess->start("lotto_max.exe");

        warn = new QLabel("인터넷에 연결하고 있습니다.\n"
                          "     잠시 기다려 주십시오.");

        connect(EProcess,SIGNAL(finished(int)),this,SLOT(start_1()));
        connect(EProcess,SIGNAL(readyReadStandardError()),this,SLOT(error_()));
    }
    else if(su == 2)
    {
        EProcess->start("lotto_parser.exe",list);
        warn = new QLabel("필요한 데이터를 받고 있습니다.\n"
                          "     잠시 기다려 주십시오.");

        connect(EProcess,SIGNAL(finished(int)),this,SLOT(start_2()));
        connect(EProcess,SIGNAL(readyReadStandardError()),this,SLOT(error_()));
    }

    QVBoxLayout* main_lay = new QVBoxLayout;
    main_lay->addWidget(warn);

    setLayout(main_lay);

}
void main_widget::start_1()
{
     qDebug() << "asdf";
     w = new Widget;
     w->show();
     hide();
}

void main_widget::error_()
{
     qDebug() << "asdf";
     QMessageBox::information(this, tr("인터넷 연결 에러"),tr("인터넷에 연결되어 있지 않습니다.\n"
                                                            "인터넷 연결을 확인해 주세요."));
     exit(0);
}

void main_widget::start_2()
{
    emit sig();
    hide();
}
