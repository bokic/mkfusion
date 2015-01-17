#include <QApplication>
#include "parsertest1.h"
#include "qtextparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextParser::loadParserDefinitionsFromDir("../src/textparser");

    CFTest1 mainWindow;
    mainWindow.show();
    return a.exec();
}
