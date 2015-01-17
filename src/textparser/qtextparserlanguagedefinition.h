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

#ifndef QTEXTPARSERLANGUAGEDEFINITION_H
#define QTEXTPARSERLANGUAGEDEFINITION_H

#include "qtextparserlanguagedefinitiontoken.h"

#include <QStringList>
#include <QString>
#include <QVector>
#include <QHash>


class QTextParserLanguageDefinition
{
public:
    QTextParserLanguageDefinition();
    QTextParserLanguageDefinition(const QTextParserLanguageDefinition &other);

#ifdef Q_COMPILER_RVALUE_REFS
    QTextParserLanguageDefinition &operator=(QTextParserLanguageDefinition &&other);
#endif
    QTextParserLanguageDefinition operator=(const QTextParserLanguageDefinition &other);

    QString languageName;
    Qt::CaseSensitivity caseSensitivity;
    QStringList defaultExtensions;
    QVector<int> startsWith;
    QHash<QString, QTextParserLanguageDefinitionToken> tokens;
};

#endif // QTEXTPARSERLANGUAGEDEFINITION_H
