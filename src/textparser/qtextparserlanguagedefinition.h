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

#include <QStringList>
#include <QString>
#include <QVector>


class QTextParserLanguageDefinition
{
public:
    QTextParserLanguageDefinition() = default;
    QTextParserLanguageDefinition(const QTextParserLanguageDefinition &other) = default;

    inline QTextParserLanguageDefinition &operator=(QTextParserLanguageDefinition &&other) = default;
    inline QTextParserLanguageDefinition &operator=(const QTextParserLanguageDefinition &other) = default;

    QString languageName;
    Qt::CaseSensitivity caseSensitivity;
    QStringList defaultExtensions;
    QVector<QTextParserLanguageDefinitionToken> tokens;
    QVector<int> startsWith;
};
