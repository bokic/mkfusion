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

#ifndef QTEXTPARSERLANGUAGEDEFINITIONTOKEN_H
#define QTEXTPARSERLANGUAGEDEFINITIONTOKEN_H

#include <QString>
#include <QVector>
#include <QRegExp>


class QTextParserLanguageDefinitionToken
{
public:
    QTextParserLanguageDefinitionToken();
    QTextParserLanguageDefinitionToken(const QTextParserLanguageDefinitionToken &other);

#ifdef Q_COMPILER_RVALUE_REFS
    QTextParserLanguageDefinitionToken &operator=(QTextParserLanguageDefinitionToken &&other);
#endif
    QTextParserLanguageDefinitionToken operator=(const QTextParserLanguageDefinitionToken &other);

    QString name;
    QRegExp startString;
    QRegExp endString;
    QRegExp tokenString;
    bool searchEndStringLast; // TODO: Unimplemented yet(greedy/lazy??)
    bool immediateStartString;
    QVector<int> nestedTokens;
};

#endif // QTEXTPARSERLANGUAGEDEFINITIONTOKEN_H
