#include "widget.h"
#include "main_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QString ApplicationPath = QApplication::applicationDirPath() + "/max_num.w";
    QFile File(ApplicationPath);

    File.open(QFile::ReadOnly|QFile::Text);

    QTextStream OpenFile(&File);
    QString Max_num_String;

    Max_num_String = OpenFile.readLine(); // 한라인씩 읽어서 변수에 적용
    Max_num = Max_num_String.toInt(nullptr,10);
    File.close(); // 파일닫기

    QFile::remove(ApplicationPath);

    setGeometry(500,500,200,90);
    setMaximumSize(200,90);
    setMinimumSize(200,90);

    QRadioButton* sudong = new QRadioButton("수동");
    QRadioButton* jadong = new QRadioButton("자동");
    sudong->setChecked(1);
    ja=0;su=1;

    QHBoxLayout* radio_btn = new QHBoxLayout;
    radio_btn->addSpacing(15);
    radio_btn->addWidget(sudong);
    radio_btn->addSpacing(30);
    radio_btn->addWidget(jadong);

    QLabel* no = new QLabel("회차");
    //no_QLine = new QLineEdit(Max_num_String);
    //no_QLine->setValidator(new QIntValidator(0, Max_num, this));

    no_QSpin = new QSpinBox;
    no_QSpin->setRange(1,815);

    QHBoxLayout* chang_one = new QHBoxLayout;
    chang_one->addWidget(no);
    chang_one->addWidget(no_QSpin);

    //spinbox
    QLabel* count = new QLabel("개수");

    count_QSpin = new QSpinBox;
    count_QSpin->setRange(1,100);
    count_QSpin->setValue(1);

    QHBoxLayout* chang_two = new QHBoxLayout;
    chang_two->addWidget(count);
    chang_two->addWidget(count_QSpin);

    QHBoxLayout* chang = new QHBoxLayout;
    chang->addLayout(chang_one);
    chang->addLayout(chang_two);

    QPushButton* chul = new QPushButton("출력");
    QPushButton* bul = new QPushButton("불러오기");

    QHBoxLayout* btn_lay = new QHBoxLayout;
    btn_lay->addWidget(chul);
    btn_lay->addWidget(bul);


    QVBoxLayout* main_lay = new QVBoxLayout;
    main_lay->addLayout(radio_btn);
    main_lay->addLayout(chang);
    main_lay->addLayout(btn_lay);

    setLayout(main_lay);

    connect(sudong,SIGNAL(toggled(bool)),this,SLOT(sudong_f(bool)));
    connect(jadong,SIGNAL(toggled(bool)),this,SLOT(jadong_f(bool)));
    connect(chul,SIGNAL(clicked()),this,SLOT(chul_f()));
    connect(bul,SIGNAL(clicked()),this,SLOT(bul_f()));
}

Widget::~Widget()
{

}

void Widget::sudong_f(bool a)
{
    if(a==1)
    {
        ja=0;
        su=1;
        no_QSpin->setEnabled(1);
        no_QSpin->setValue(814);
    }
}

void Widget::jadong_f(bool a)
{
    if(a==1)
    {
        ja=1;
        su=0;
        no_QSpin->setDisabled(1);
        no_QSpin->setValue(815);
    }
}

void Widget::chul_f()
{
    if(ja==1)
    {
        SQL* a = new SQL(ja,su,QString::number(Max_num+1),count_QSpin->text());
        a->setModal(1);
        a->show();
    }
    else if(su == 1)
    {
        QString Max_num_String = "814";
        QStringList para;
        para << Max_num_String;

        main_widget* a = new main_widget(2,para);
        connect(a,SIGNAL(sig()),this,SLOT(start_()));
        a->setModal(1);
        a->show();
    }
}

void Widget::error_()
{
     QMessageBox::information(this, tr("인터넷 연결 에러"),tr("인터넷에 연결되어 있지 않습니다.\n"
                                                            "인터넷 연결을 확인해 주세요."));
     exit(0);
}

void Widget::start_()
{
     SQL* a = new SQL(ja,su,no_QSpin->text(),count_QSpin->text());
     a->setModal(1);
     a->show();
}

void Widget::bul_f(int Max_num)
{
    open_number* a = new open_number(Max_num);
    a->setModal(1);
    a->show();
}
