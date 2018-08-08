#include "sql.h"
#include <QDebug>
#include <windows.h>

SQL::SQL(const int &ja, const int &su, const QString &no, const QString &con, QWidget *parent) : QDialog(parent)
{
    setGeometry(100,100,340,300);

    QString count = con;
    co_unt = count.toInt(nullptr,10);

    setWindowTitle("lotto - "+count+"회차");

    lotto_table = new QTableWidget;

    Save = new QPushButton("Save");
    QPushButton* Cancle = new QPushButton("Cancle");
    gbox = new QGridLayout;

    QHBoxLayout* MainBox = new QHBoxLayout;

    gbox->addWidget(Cancle,0,2);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(lotto_table);
    vbox->addLayout(gbox);

    MainBox->addLayout(vbox);
    setLayout(MainBox);

    connect(Cancle,SIGNAL(clicked(bool)),this,SLOT(close()));

    static const QStringList lotto_sel_num(
                QStringList() << tr("1번") << tr("2번") << tr("3번") << tr("4번")
                              << tr("5번") << tr("6번"));

    lotto_table->setColumnCount(6); // 세로줄 수 설정
    lotto_table->setRowCount(co_unt);// 가로줄 수 설정

    for (int i = 0; i < 6; ++i)
    {
        // 테이블 아이템 생성
        QTableWidgetItem *item = new QTableWidgetItem;
        // 아이템 텍스트 요일로 설정
        item->setText(lotto_sel_num.at(i));
        // 가로 헤더 아이템 설정
        lotto_table->setHorizontalHeaderItem(i, item);
        lotto_table->setColumnWidth(i,50);
    }

    for (int i = 0; i < co_unt; ++i)
    {
        // 테이블 아이템 생성
        QTableWidgetItem *item = new QTableWidgetItem;
        // 아이템 텍스트 시간으로 설정
        item->setText(QString::number(i + 1));
        // 세로 헤더 아이템 설정
        lotto_table->setVerticalHeaderItem(i, item);
    }

    if((ja == 1) && (su == 0))
    {
        QStringList num_list_str[co_unt];
        gbox->addWidget(Save,0,1);

        int cou_nt = 0;
        for(cou_nt = 0; cou_nt<co_unt; cou_nt++)
        {
            num_list_str[cou_nt] = jadong();
        }

        // 테이블 셀 초기화
        for (int i = 0; i < co_unt; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                // 빈 아이템으로 설정
                lotto_table->setItem(i, j, new QTableWidgetItem(QString(num_list_str[i].at(j))));
                lotto_table->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }

    }
    else if((ja == 0) && (su == 1))
    {
        QPushButton* Apply = new QPushButton("Apply");
        gbox->addWidget(Apply,0,1);

        for (int i = 0; i < co_unt; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                // 빈 아이템으로 설정
                lotto_table->setItem(i, j, new QTableWidgetItem(QString()));
                lotto_table->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }

        connect(Apply,SIGNAL(clicked(bool)),this,SLOT(Apply()));
        connect(lotto_table,SIGNAL(cellChanged(int,int)),this,SLOT(check_in(int,int)));
        connect(Save,SIGNAL(clicked(bool)),this,SLOT(Save_f()));
    }

    qDebug() << no;
}

void SQL::Load_f()
{
    QString count = QString::number(co_unt);

    QString ApplicationPath=QApplication::applicationDirPath();
    QString name = ApplicationPath+"/"+count;

    QFile f(name);

    // 읽기 전용으로 파일 열기
    if (f.open(QIODevice::ReadOnly))
    {
        lotto_table->clear();    // 테이블 초기화

        int a = 8;

        QTextStream in(&f);     // 파일을 텍스트 스트림으로 처리

        in >> a >> co_unt; // 세로줄 수와 가로줄 수 읽기
        in.readLine();                  // 줄바꿈 문자 읽기

        lotto_table->setColumnCount(co_unt); // 가로줄 수 설정
        lotto_table->setRowCount(8);    // 세로줄 수 설정

        // 세로 헤더 아이템 읽어 설정
        for (int i = 0; i < co_unt; ++i)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(in.readLine());
            lotto_table->setHorizontalHeaderItem(i, item);
        }
        lotto_table->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

        // 가로 헤더 아이템 읽어 설정
        for (int i = 0; i < 8; ++i)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(in.readLine());
            lotto_table->setVerticalHeaderItem(i, item);
        }
        lotto_table->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

        // 테이블 셀 설정
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < co_unt; ++j)
            {
                lotto_table->setItem(i, j,
                                    new QTableWidgetItem(in.readLine()));
            }
        }

        f.close();  // 파일 닫음
    }
}

void SQL::Save_f()
{    
    QString logPath = "Save_Data";
    QDir dir(logPath);
    dir.mkpath(logPath);

    QString count = QString::number(co_unt);

    QString ApplicationPath=QApplication::applicationDirPath();
    QString name = ApplicationPath+"/"+count;

    QFile f(name);

    // 쓰기 모드로 파일 열기

    if(!f.open(QIODevice::Append)) // 읽기 전용, 텍스트로 파일 열기
    {
         if(!f.exists()) // 파일이 존재하지 않으면...
        {
             // 파일이 존재하지 않으면...여기에 동작 적용
             f.open(QIODevice::WriteOnly);
        }
        else
        {
            // 파일을 열수 없거나 파일 손상 등 여러 요인작용...
        }
    }

    QTextStream out(&f);    // 텍스트 스트림으로 처리

        // 세로줄 수 및 가로줄 수 저장
    out << co_unt << " " << 8 << "\n";

        // 가로 헤더 아이템 저장
    for (int i = 0; i < 8; ++i)
        out << lotto_table->horizontalHeaderItem(i)->text() << "\n";

        // 세로 헤더 아이템 저장
    for (int i =  0; i < co_unt; ++i)
        out << lotto_table->verticalHeaderItem(i)->text() << "\n";

        // 테이블 셀 저장
    for (int i = 0; i < co_unt; ++i)
    {
        for (int j = 0; j < 8; ++j)
            out << lotto_table->item(i, j)->text() << "\n";
    }

    f.close();  // 파일 닫기
}

bool SQL::check()
{
    QString i_s;
    QString j_s;
    QString k_s;
    QString o_s;

    for(int i=0;i<co_unt;i++) // 값이 들어있는지 확인
    {
        i_s = QString::number(i);
        for(int j=0;j<6;j++)
        {
            if(array[i][j]==0)
            {
                j_s = QString::number(j);
                QMessageBox::information(this, tr("cell error"),"값이 들어 있지 않습니다.\n"
                                                                "cell ("+i_s+","+j_s+")에 값을 넣어주세요");
                return false;
            }
        }

        int jungbok_ck[6];    // 값을 문자로 긁어와서 숫자로 변환
        QString jungbok_ck_s;
        for(int m=0;m<6;m++)
        {
            jungbok_ck_s = lotto_table->item(i,m)->text();
            jungbok_ck[m] = jungbok_ck_s.toInt(nullptr,10);
        }

        for(int o=0;o<6;o++)  // 숫자 범위값 확인
        {
            if((1>jungbok_ck[o]) || (jungbok_ck[o]>45))
            {
                o_s = QString::number(o);
                QMessageBox::information(this, tr("cell error"),"범위를 초과한 값이 들어있습니다.\n"
                                                                "cell ("+i_s+","+o_s+")의 값을 수정해주세요.");
                return false;
            }
        }

        for(int k=0;k<6;k++)  // 숫자 중복 확인
        {
            for(int l=k+1;l<7;l++)
            {
                if(jungbok_ck[k] == jungbok_ck[l])
                {
                    k_s = QString::number(k);
                    QMessageBox::information(this, tr("cell error"),"중복된 값이 들어있습니다.\n"
                                                                    "cell ("+i_s+","+k_s+")의 값을 수정해주세요.");
                    return false;
                }
            }
        }

        int* number_p = jungbok_ck;
        quick_sort(number_p, 0, 5);  // 숫자 오름차순 퀵정렬

        for(int n=0;n<6;n++)  // 셀에 다시 집어 넣는 과정
        {
            jungbok_ck_s = QString::number(jungbok_ck[n]);
            lotto_table->setItem(i, n, new QTableWidgetItem(jungbok_ck_s));
            lotto_table->item(i,n)->setTextAlignment(Qt::AlignCenter);
        }

    }
    return true;
}

void SQL::check_in(int row, int column)
{
    QString check;
    check = lotto_table->item(row,column)->text();

    if(check == "")
    {
        array[row][column] = 0;
    }
    else
    {
        array[row][column] = 1;
    }
}

void SQL::Apply()
{
    setGeometry(100,100,490,300);

    if(check() == true)
    {
        gbox->addWidget(Save,0,0);

        QLayoutItem *item = gbox->takeAt(1);

        if(item == 0)
        {
            return;
        }

        gbox->removeWidget(item->widget());

        delete item->widget();

        static const QStringList lotto_sel_num(
                    QStringList() << tr("1번") << tr("2번") << tr("3번") << tr("4번")
                                  << tr("5번") << tr("6번") << tr("등수") << tr("당첨금"));
        qDebug() << "asdf";
        lotto_table->setColumnCount(8); // 세로줄 수 설정

        for (int i = 6; i < 8; ++i)
        {
            // 테이블 아이템 생성
            QTableWidgetItem *item = new QTableWidgetItem;
            // 아이템 텍스트 요일로 설정
            item->setText(lotto_sel_num.at(i));
            // 가로 헤더 아이템 설정
            lotto_table->setHorizontalHeaderItem(i, item);
            lotto_table->setColumnWidth(i,50);
        }

        lotto_table->setColumnWidth(7,100);

        //fileopen

        QString ApplicationPath = QApplication::applicationDirPath() + "/lotto_db.w";
        QFile File(ApplicationPath);

        File.open(QFile::ReadOnly|QFile::Text);

        QTextStream OpenFile(&File);

        for(int i=0;i<6;i++)
        {
            imformation[i] = OpenFile.readLine(); // 한라인씩 읽어서 변수에 적용
        }

        File.close(); // 파일닫기

        //QFile::remove(ApplicationPath);
        ck_rank();

    }
    else
    {
        return;
    }

}

void SQL::ck_rank()
{
    QString sel_num_s;
    QStringList rank_num_sl= imformation[1].split(",");
    QStringList victory_money= imformation[5].split("원");
    QString rank_num_s;

    victory_money.removeAt(5);
    victory_money << ",0";
    victory_money << ",0";
    victory_money << ",0";

    int sel_num[6];
    int rank_num[6];
    int bonus_rank_num;

    int rank = 8;

    for(int i=0;i<co_unt;i++)
    {
        for(int j=0;j<6;j++)
        {
            sel_num_s=lotto_table->item(i,j)->text();
            sel_num[j]=sel_num_s.toInt(nullptr,10);

            rank_num_s=rank_num_sl[j];
            rank_num[j]=rank_num_s.toInt(nullptr,10);
        }
        rank_num_s=rank_num_sl[6];
        bonus_rank_num = rank_num_s.toInt(nullptr,10);

        for(int k=0;k<6;k++)
        {
            for(int l=0;l<6;l++)
            {
                if(sel_num[k] == rank_num[l])
                {
                    rank--;
                    break;
                }
            }
        }
        if(rank == 2)
        {
            rank =1;
        }
        else if(rank == 3)
        {
            for(int m=0;m<6;m++)
            {
                if(sel_num[m] == bonus_rank_num)
                {
                    rank--;
                    break;
                }
            }
        }

        QString money = victory_money[rank-1] + "원";
        QString rank_s = QString::number(rank) + "등";
        money.replace(",","");

        lotto_table->setItem(i, 6, new QTableWidgetItem(rank_s));
        lotto_table->setItem(i, 7, new QTableWidgetItem(money));

        for (int n = 6; n < 8; n++)
        {
            lotto_table->item(i,n)->setTextAlignment(Qt::AlignCenter);
        }

        rank = 8;
    }
}

QStringList SQL::jadong()
{
    int count, count_1, count_2;
    int flag = 0;

    qsrand(QTime::currentTime().msecsSinceStartOfDay()+delay);
    for(count=0;count<6;count++)
    {
        number[count] = (qrand()%45)+1;
    }

    for(count_1=0;count_1<5;count_1++)
    {
        for(count_2=count_1+1;count_2<6;count_2++)
        {
            if(number[count_1]==number[count_2])
            {
                number[count_2] = qrand()%(qrand()%45)+1;
                flag = 1;
                break;
            }
        }
        if(flag == 1)
        {
            flag = 0;
            count_1 = 0;
            continue;
        }
    }

    int* number_p = number;

    quick_sort(number_p, 0, 5);

    QStringList list;
    for(count = 0; count<6; count++)
    {
        list << QString::number(number[count]);
    }

    delay++;
    return list;
}

void SQL::swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void SQL::quick_sort(int* array, int start, int end)
{
    if(start>=end) return;
    int mid = (start+end)/2;
    int pivot = array[mid];

    swap(&array[start],&array[mid]);

    int left = start+1, right = end;
    while(1)
    {
        while(array[left]<=pivot)
        {
            left++;
        }
        while(array[right]>pivot)
        {
            right--;
        }
        if(left>right)
        {
            break;
        }
        swap(&array[left],&array[right]);
    }
    swap(&array[start],&array[right]);

    quick_sort(array,start,right-1);
    quick_sort(array,right+1,end);
}
