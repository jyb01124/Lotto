#include "open_number.h"

open_number::open_number(const int &max_num,QWidget *parent) : QDialog(parent)
{
    QListWidget* count = new QListWidget;
    QTableWidget *lotto_table = new QTableWidget;
    QHBoxLayout* main_Lay = new QHBoxLayout;

    int M_num = max_num;

    bool col_num[M_num]={0};

    for(int i=0;i<M_num;i++)
    {
        QString count = QString::number(i);
        QString ApplicationPath = QApplication::applicationDirPath();
        QString name = ApplicationPath+"/"+count;

        QFile f(name);
        if (!f.open(QIODevice::ReadOnly))
        {
            if(!f.exists())
            {
                col_num[i]=0;
                continue;
            }
        }
        else
        {
            col_num[i]=1;
        }
    }



    main_Lay->addWidget(count);
    main_Lay->addWidget(lotto_table);
    setLayout(main_Lay);
}
