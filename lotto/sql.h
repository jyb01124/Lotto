#ifndef SQL_H
#define SQL_H

#include <QWidget>
#include <QtWidgets>
#include <QStringList>
#include <QGridLayout>
#include <QLayoutItem>

class SQL : public QDialog
{
    Q_OBJECT
public:
    explicit SQL(const int &ja, const int &su, const QString &no, const QString &con, QWidget *parent = nullptr);
    QTableWidget *lotto_table;

    QStringList jadong();

    void swap(int* a,int* b);
    void quick_sort(int* array, int start, int end);
    void setFileName(const QString &name);
    bool check();
    void ck_rank();


    QGridLayout* gbox;
    QPushButton* Save;
    QString imformation[6];
    int number[6];
    QString fileName;
    int delay = 0;
    bool array[100][6];
    bool dif_flag=0;
    int co_unt;



signals:

public slots:
    void Apply();
    void check_in(int row, int column);
    void Save_f();
    void Load_f();
};

#endif // SQL_H
