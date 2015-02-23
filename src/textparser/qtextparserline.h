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

#ifndef QTEXTPARSERLINE_H
#define QTEXTPARSERLINE_H

#include <QString>
#include <QList>


class QTextParserLine
{
public:
    enum QTextParserLineType
    {
        QTextParserLineTypeNoEndLine,
        QTextParserLineTypeCREndLine,
        QTextParserLineTypeLFEndLine,
        QTextParserLineTypeCRLFEndLine,
        QTextParserLineTypeLFCREndLine
    };

    QTextParserLine();
    QTextParserLine(const QTextParserLine &other);

#ifdef Q_COMPILER_RVALUE_REFS
    inline QTextParserLine &operator=(QTextParserLine &&other)
    {
        qSwap(text, other.text);
        qSwap(type, other.type);

        return *this;
    }
#endif
    QTextParserLine operator=(const QTextParserLine &other);

    QString text;
    QTextParserLineType type;
};

typedef QList<QTextParserLine> QTextParserLines;

#endif // QTEXTPARSERLINE_H
