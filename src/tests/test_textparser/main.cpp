#include <QtCore/QCoreApplication>
#include <QtXml/QDomDocument>
#include <QtCore/QFile>

#include "qtextparser.h"

int main()
{

    QTextParser::loadParserDefinitionsFromDir(".");

    QTextParser parser;

    parser.parseFile("html\\index.htm");

    return 0;
}
