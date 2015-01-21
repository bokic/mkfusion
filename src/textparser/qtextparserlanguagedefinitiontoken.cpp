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

#include "qtextparserlanguagedefinitiontoken.h"


QTextParserLanguageDefinitionToken::QTextParserLanguageDefinitionToken()
    : searchEndStringLast(false)
    , immediateStartString(false)
    , onlyStartTag(false)
{
}

QTextParserLanguageDefinitionToken::QTextParserLanguageDefinitionToken(const QTextParserLanguageDefinitionToken &other)
{
    name = other.name;
    startString = other.startString;
    endString = other.endString;
    tokenString = other.tokenString;
    searchEndStringLast = other.searchEndStringLast;
    immediateStartString = other.immediateStartString;
    onlyStartTag = other.onlyStartTag;
    nestedTokens = other.nestedTokens;
}

#ifdef Q_COMPILER_RVALUE_REFS
QTextParserLanguageDefinitionToken &QTextParserLanguageDefinitionToken::operator=(QTextParserLanguageDefinitionToken &&other)
{
    qSwap(name, other.name);
    qSwap(startString, other.startString);
    qSwap(endString, other.endString);
    qSwap(tokenString, other.tokenString);
    qSwap(searchEndStringLast, other.searchEndStringLast);
    qSwap(immediateStartString, other.immediateStartString);
    qSwap(onlyStartTag, other.onlyStartTag);
    qSwap(nestedTokens, other.nestedTokens);

    return *this;
}

#endif
QTextParserLanguageDefinitionToken QTextParserLanguageDefinitionToken::operator=(const QTextParserLanguageDefinitionToken &other)
{
    name = other.name;
    startString = other.startString;
    endString = other.endString;
    tokenString = other.tokenString;
    searchEndStringLast = other.searchEndStringLast;
    immediateStartString = other.immediateStartString;
    onlyStartTag = other.onlyStartTag;
    nestedTokens = other.nestedTokens;

    return *this;
}
