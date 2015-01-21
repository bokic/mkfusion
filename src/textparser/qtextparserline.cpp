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

#include "qtextparserline.h"


QTextParserLine::QTextParserLine()
    : type(QTextParserLineTypeNoEndLine)
{
}

QTextParserLine::QTextParserLine(const QTextParserLine &other)
{
    text = other.text;
    type = other.type;
}

QTextParserLine QTextParserLine::operator=(const QTextParserLine &other)
{
    text = other.text;
    type = other.type;

    return *this;
}
