#include <QtCore/QCoreApplication>
#include <QtXml/QDomDocument>
#include <QtCore/QFile>

#include "qtextparser.h"

QTextParser::QTextParserLines& loadTextFromFile(const QString fileName)
{
	QTextParser::QTextParserLines* lines = new QTextParser::QTextParserLines();

	QFile file(fileName);
	file.open(QFile::ReadOnly);
	QByteArray buffer = file.readAll();
	file.close();

	QString text = QString::fromUtf8(buffer.constData(), buffer.length());

	//lines

	return *lines;
}

int main()
{

	QTextParser::loadParserDefinitionsFromDir(".");

	QTextParser parser;

	//parser.parseTextLines(loadTextFromFile("html\\index.htm"));

	return 0;
}
