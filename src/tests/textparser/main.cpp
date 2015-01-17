#include "qtextparser.h"


int main()
{
    QTextParser parser;

    parser.setTextTypeByFileExtension("cfm");
    QTextParserElements elements = parser.parseFile("site/pi.cfm");

    return 0;
}
