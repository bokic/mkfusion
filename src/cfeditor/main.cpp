#include "qappmainwindow.h"
#include "qcfparser.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
	try {
		QCFParser l_parser;
		QCFParserErrorType l_ret;
		QList<QCFParserTag> l_tags;

		l_ret = l_parser.Parse("<cfset returnTime = DateAdd(\"h\",useOpperator&session.hourajustment,useTime)>");
		if (l_ret == NoError)
		{
			l_tags = l_parser.getTags();
			qDebug(QString("Number of elements is %1").arg(l_tags.size()).toAscii());
		} else {
			qDebug(QString("Parsing Error.\nError description: " + l_parser.getError() + " at position: " + QString::number(l_parser.getErrorPosition())).toAscii());
		}
		//return 0;
	} catch(...) {
	}

	QApplication a(argc, argv);
	QAppMainWindow main;
	main.show();

	return a.exec();
}
