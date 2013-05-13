#include <QApplication>
#include "qappmaindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QAppMainDialog w;
    w.show();
    return a.exec();
}
