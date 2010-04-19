#include "qcodeeditwidget.h"
#include <QPainter>
#include <QFontMetrics>

QCodeEditWidget::QCodeEditWidget(QWidget *parent) :
	QAbstractScrollArea(parent)
{
	m_ScrollXPixelPos = 0;
	m_ScrollYLinePos = 0;
	m_CaretXPos = 0;
	m_CaretYPos = 0;

	m_LineNumbersBackground = QBrush(QColor(236, 233, 216), Qt::SolidPattern);
	m_LineNumbersNormal = QPen(QColor(172, 168, 153));
	m_LineNumbersCurrent = QPen(QColor(128, 128, 128));
	m_LineModifiedAndNotSavedBackground = QColor(128, 0, 0);
	m_LineModifiedAndSavedBackground = QColor(0, 128, 0);
	m_CurrentLineBackground = QColor(224, 233, 247);
	m_TextFont = QFont("Courier", 10, 0, false);
	m_TextFont.setStyleHint(QFont::Courier, QFont::PreferAntialias);

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	setText("");
}

void QCodeEditWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(viewport());

	QFontMetrics l_fm(m_TextFont);
	int l_fontHeight = l_fm.height();
	int l_LinesToDraw = (viewport()->height() / l_fontHeight) + 1;

	painter.fillRect(QRect(0, 0, 100, viewport()->height()), m_LineNumbersBackground); // TODO: 100 is hardcoded

	for(int c = 0; c < l_LinesToDraw; c++)
	{
		if (m_ScrollYLinePos + c >= m_Lines.count())
		{
			break;
		}

		//painter.set

		if (c == m_CaretYPos)
		{
			QFont l_tmpFont = m_TextFont;
			l_tmpFont.setBold(true);
			//l_tmpFont.C
			painter.setFont(l_tmpFont);
			painter.setPen(m_LineNumbersCurrent);
		}
		else
		{
			painter.setPen(m_LineNumbersNormal);
		}

		painter.drawText(QRect(0, c * l_fontHeight, 100 - 5, l_fontHeight), Qt::AlignRight, QString::number(m_ScrollYLinePos + c + 1)); // TODO: 100 is hardcoded

		if (c == m_CaretYPos)
		{
			painter.setFont(m_TextFont);
		}

		painter.setPen(QColor(0, 0, 0));

		if (c == m_CaretYPos)
		{
			painter.fillRect(100, c * l_fontHeight, viewport()->width() - 100, l_fontHeight, m_CurrentLineBackground);
		}

		painter.drawText(100, (c * l_fontHeight) + 12, m_Lines.at(m_ScrollYLinePos + c).Content); // TODO: 100, 12 is hardcoded
	}

	setFont(m_TextFont);
}

QString QCodeEditWidget::getText()
{
	QString ret;

	foreach(QCodeEditWidgetLine l_Line, m_Lines)
	{
		ret.append(l_Line.Content);
		switch(l_Line.EndLine)
		{
			case QCodeEditWidget::EndLineTypeCREndLine:
				ret.append('\r');
				break;
			case QCodeEditWidget::EndLineTypeLFEndLine:
				ret.append('\n');
				break;
			case QCodeEditWidget::EndLineTypeCRLFEndLine:
				ret.append("\r\n");
				break;
			case QCodeEditWidget::EndLineTypeLFCREndLine:
				ret.append("\n\r");
				break;
			default:
				break;
		}
	}

	return ret;
}

void QCodeEditWidget::setText(const QString &text)
{
	QCodeEditWidgetLine l_Line;

	m_Lines.clear();
	m_ScrollXPixelPos = 0;
	m_ScrollYLinePos = 0;

	int pos = 0;

	l_Line.LineStatus = QCodeEditWidget::LineStatusTypeLineNotModified;

	forever
	{
		int crindex = text.indexOf('\r', pos);
		int lfindex = text.indexOf('\n', pos);

		if ((crindex == -1)&&(lfindex == -1))
		{
			if(pos < text.length() - 1)
			{
				l_Line.Content = text.right(text.length() - pos);
				l_Line.EndLine = QCodeEditWidget::EndLineTypeNoEndLine;

				m_Lines.push_back(l_Line);
			}

			break;
		}

		if ((crindex < lfindex)&&(crindex > -1))
		{
			l_Line.Content = text.mid(pos, crindex - pos);
			l_Line.EndLine = QCodeEditWidget::EndLineTypeCREndLine;
			pos = crindex + 1;

			if((text.length() > pos)&&(text.at(pos) == '\n'))
			{
				l_Line.EndLine = QCodeEditWidget::EndLineTypeCRLFEndLine;
				pos++;
			}
		}
		else
		{
			l_Line.Content = text.mid(pos, lfindex - pos);
			l_Line.EndLine = QCodeEditWidget::EndLineTypeLFEndLine;
			pos = lfindex + 1;

			if((text.length() > pos)&&(text.at(pos) == '\t'))
			{
				l_Line.EndLine = QCodeEditWidget::EndLineTypeLFCREndLine;
				pos++;
			}
		}

		m_Lines.push_back(l_Line);
	}

	if (m_Lines.isEmpty())
	{
		l_Line.Content = "";
		l_Line.EndLine = QCodeEditWidget::EndLineTypeNoEndLine;
		m_Lines.push_back(l_Line);
	}

	update();
}
