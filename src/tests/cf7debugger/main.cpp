#include <QApplication>
#include "qappmainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QAppMainWindow main;
    main.show();

    return app.exec();
}
