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

#include <QString>
#include <QList>


class QTextParserElement
{
public:
    QTextParserElement() = default;
    QTextParserElement(const QTextParserElement &other) = default;

    inline QTextParserElement &operator=(QTextParserElement &&other) = default;
    inline QTextParserElement &operator=(const QTextParserElement &other) = default;

    int m_Type = -1;
#ifdef DEBUG_QTEXTPARSER
    QString m_TypeDebug;
#endif
    QString m_Text;
    int m_StartLine = -1;
    int m_StartColumn = -1;
    int m_EndLine = -1;
    int m_EndColumn = -1;
    QList<QTextParserElement> m_ChildElements;
};

typedef QList<QTextParserElement> QTextParserElements;
