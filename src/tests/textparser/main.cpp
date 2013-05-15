#include "qtextparser.h"


int main()
{
	QTextParser parser;

    parser.setTextTypeByFileExtension("cfm");
    parser.parseFile("site/pi.cfm");

	return 0;
}
