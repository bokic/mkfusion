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

#ifndef QTEXTPARSERELEMENT_H
#define QTEXTPARSERELEMENT_H

#include <QString>
#include <QList>


class QTextParserElement
{
public:
    QTextParserElement();
    QTextParserElement(const QTextParserElement &other);

#ifdef Q_COMPILER_RVALUE_REFS
    inline QTextParserElement &operator=(QTextParserElement &&other)
    {
        qSwap(m_Type, other.m_Type);
 #ifdef DEBUG_QTEXTPARSER
        qSwap(m_TypeDebug, other.m_TypeDebug);
 #endif
        qSwap(m_Text, other.m_Text);
        qSwap(m_StartLine, other.m_StartLine);
        qSwap(m_StartColumn, other.m_StartColumn);
        qSwap(m_EndLine, other.m_EndLine);
        qSwap(m_EndColumn, other.m_EndColumn);
        qSwap(m_ChildElements, other.m_ChildElements);

        return *this;
    }
#endif
    QTextParserElement operator=(const QTextParserElement &other);

    int m_Type;
#ifdef DEBUG_QTEXTPARSER
    QString m_TypeDebug;
#endif
    QString m_Text;
    int m_StartLine;
    int m_StartColumn;
    int m_EndLine;
    int m_EndColumn;
    QList<QTextParserElement> m_ChildElements;
};

typedef QList<QTextParserElement> QTextParserElements;

#endif // QTEXTPARSERELEMENT_H
