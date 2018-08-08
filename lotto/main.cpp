#include "widget.h"
#include "main_widget.h"
#include <QApplication>
#include <QWidget>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList b;
    main_widget w(1,b);
    w.show();

    return a.exec();
}
