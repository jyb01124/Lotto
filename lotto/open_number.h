#ifndef OPEN_NUMBER_H
#define OPEN_NUMBER_H

#include <QWidget>
#include <QtWidgets>
#include <QListWidget>
#include <QHBoxLayout>

class open_number : public QDialog
{

    Q_OBJECT
public:
    explicit open_number(const int &max_num, QWidget *parent = nullptr);
};

#endif // OPEN_NUMBER_H
