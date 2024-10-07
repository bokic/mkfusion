#include "qtextparser.h"


int main(int argc, char *argv[])
{
    printf("start\n");
    QTextParser parser;

    if (argc != 2)
    {
        printf("Usage textparser <file to parse>\n");
        return 1;
    }

    QTextParser::loadParserDefinitionsFromDir("../src/textparser");
    QTextParserElements elements = parser.parseFile(argv[1]);

    printf("Found tokens: %lld\n", elements.count());

    return 0;
}
