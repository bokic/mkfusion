#include <QApplication>
#include "parsertest1_new.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CFTest1 mainWindow;
    mainWindow.show();
    return a.exec();
}
