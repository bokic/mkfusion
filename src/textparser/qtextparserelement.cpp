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

#include "qtextparserelement.h"


QTextParserElement::QTextParserElement()
{

}

QTextParserElement::QTextParserElement(const QTextParserElement &other)
{
    m_Type = other.m_Type;
#ifdef DEBUG_QTEXTPARSER
    m_TypeDebug = other.m_TypeDebug;
#endif
    m_Text = other.m_Text;
    m_StartLine = other.m_StartLine;
    m_StartColumn = other.m_StartColumn;
    m_EndLine = other.m_EndLine;
    m_EndColumn = other.m_EndColumn;
    m_ChildElements = other.m_ChildElements;
}

QTextParserElement &QTextParserElement::operator=(const QTextParserElement &other)
{
    m_Type = other.m_Type;
#ifdef DEBUG_QTEXTPARSER
    m_TypeDebug = other.m_TypeDebug;
#endif
    m_Text = other.m_Text;
    m_StartLine = other.m_StartLine;
    m_StartColumn = other.m_StartColumn;
    m_EndLine = other.m_EndLine;
    m_EndColumn = other.m_EndColumn;
    m_ChildElements = other.m_ChildElements;

    return *this;
}
