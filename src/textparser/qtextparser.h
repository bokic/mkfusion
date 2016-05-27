/****************************************************************************
**
** Author: Boris Barbulovski(bbarbulovski@gmail.com)
**
** This file is part of the MKFusion(http://mkfusion.bokicsoft.com/ or
** https://github.com/bokic/mkfusion/) project.
**
** $QT_BEGIN_LICENSE:LGPL$
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#pragma once

#include "qtextparserlanguagedefinitiontoken.h"
#include "qtextparserlanguagedefinition.h"
#include "qtextparserelement.h"
#include "qtextparserline.h"

#include <QStringList>
#include <QString>
#include <QVector>
#include <QList>


class QTextParser
{
public:
    QTextParser();
    static void loadParserDefinitionsFromDir(const QString &dir);
    void setTextTypeByFileExtension(const QString &fileExt);
    void setTextTypeByLanguageName(const QString &langName);
    QTextParserElements parseFile(const QString &fileName);
    QTextParserElements parseText(const QString &text, const QString &fileExt);
    QTextParserElements parseTextLines(const QTextParserLines &lines);
    QTextParserLanguageDefinition getLanguage() const;

protected:
    QTextParserElement parseElement(const QTextParserLines &lines, const QVector<int> &tokens, int &start_line, int &start_column, int end_line, int end_column, int end_token = -1);
    bool findFirstElement(const QTextParserLines &lines, int &cur_line, int &cur_column, const QVector<int> &tokens, int end_token);
    bool findFirstElement(const QString &line, int &cur_column, const QVector<int> &tokens, int end_token);
    QTextParserLanguageDefinition language;
    QTextParserLines lines;
};
