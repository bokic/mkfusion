#include "qcodeeditwidget.h"
#include <QPainter>
#include <QFontMetrics>
#include <QTimerEvent>
#include <QScrollBar>
#include <QKeyEvent>
#include <QPalette>

#include <math.h>

const quint32 KBD_BACKSPACE = 8;
const quint32 KBD_ENTER = 13;
const quint32 KBD_DELETE = 127;

#ifdef Q_WS_WIN
const quint32 KBD_LCTRL = 29;
const quint32 KBD_RCTRL = 285;
const quint32 KBD_HOME = 327;
const quint32 KBD_END = 335;
const quint32 KBD_UP = 328;
const quint32 KBD_DOWN = 336;
const quint32 KBD_LEFT = 331;
const quint32 KBD_RIGHT = 333;
#elif defined Q_WS_X11
const quint32 KBD_LCTRL = 37;
const quint32 KBD_RCTRL = 105;
const quint32 KBD_HOME = 110;
const quint32 KBD_END = 115;
const quint32 KBD_UP = 111;
const quint32 KBD_DOWN = 116;
const quint32 KBD_LEFT = 113;
const quint32 KBD_RIGHT = 114;
#else
	#error Unsupported OS.
#endif

QCodeEditWidget::QCodeEditWidget(QWidget *parent) :
	QAbstractScrollArea(parent),
	m_LineNumbersNormal(QPen(QColor(172, 168, 153))),
	m_LineNumbersCurrent(QPen(QColor(128, 128, 128))),
	m_LineModifiedAndNotSavedBackground(QColor(128, 0, 0)),
	m_LineModifiedAndSavedBackground(QColor(0, 128, 0)),
	m_CurrentLineBackground(QColor(224, 233, 247)),
#ifdef Q_WS_WIN
	m_TextFont(QFont("Courier", 10, 0, false)),
#elif defined Q_WS_X11
	m_TextFont(QFont("Monospace", 9, 0, false)),
#else
	#error Unsupported OS.
#endif
	m_ScrollXPixelPos(0),
	m_ScrollYLinePos(0),
	m_LineNumbersPanelWidth(3),
	m_currentlyBlinkCursorShowen(1)
{
	m_CarretPosition.m_Row = 1;
	m_CarretPosition.m_Column = 1;

	QPalette l_Palette;
	m_LineNumbersBackground = QBrush(l_Palette.color(QPalette::Window), Qt::SolidPattern);
	setAutoFillBackground(false);

	m_CursorHeight = QFontMetrics(m_TextFont).height();

	m_TextFont.setStyleHint(QFont::Courier, QFont::PreferAntialias);

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	verticalScrollBar()->setRange(1, 1);
	horizontalScrollBar()->setRange(1, 30);

	setText("");

	m_CursorTimerID = startTimer(500);
}

QCodeEditWidget::~QCodeEditWidget()
{
	killTimer(m_CursorTimerID);
}

void QCodeEditWidget::timerEvent(QTimerEvent *event)
{
	if (event->timerId() ==  m_CursorTimerID)
	{
		m_currentlyBlinkCursorShowen ^= 1;

		//viewport()->update(0, 0, ceil(m_CursorHeight * 0.05) + 1, m_CursorHeight + 1);
		viewport()->update(); // TODO: optimize this call, by updating the affected region only!!
	}
}

void QCodeEditWidget::keyPressEvent(QKeyEvent *event)
{
	quint32 l_ScanCode = event->nativeScanCode();
	Qt::KeyboardModifiers l_Modifiers = event->modifiers();

	if ((l_ScanCode == KBD_LCTRL)||(l_ScanCode == KBD_RCTRL))
	{
		return;
	}

	switch(l_ScanCode)
	{
	case KBD_HOME:
		if (l_Modifiers == Qt::NoModifier)
		{
			m_CarretPosition.m_Column = 1;
		}
		else if (l_Modifiers == Qt::ControlModifier)
		{
			m_CarretPosition.m_Column = 1;
			m_CarretPosition.m_Row = 1;
		}
		break;
	case KBD_END:
		if (l_Modifiers == Qt::NoModifier)
		{
			m_CarretPosition.m_Column = (quint32)m_Lines.at(m_CarretPosition.m_Row - 1).Content.length() + 1;
		}
		else if (l_Modifiers == Qt::ControlModifier)
		{
			m_CarretPosition.m_Row = (quint32)m_Lines.count();
			m_CarretPosition.m_Column = (quint32)m_Lines.at(m_CarretPosition.m_Row - 1).Content.length() + 1;
		}
		break;

	case KBD_UP:
		if (m_CarretPosition.m_Row <= 1)
		{
			return;
		}

		m_CarretPosition.m_Row--;
		break;

	case KBD_DOWN:
		if (m_CarretPosition.m_Row < (quint32)m_Lines.count())
		{
			m_CarretPosition.m_Row++;
		}
		break;

	case KBD_LEFT:
		if (m_CarretPosition.m_Column <= 1)
		{
			return;
		}

		m_CarretPosition.m_Column--;
		break;

	case KBD_RIGHT:
		if (m_CarretPosition.m_Column <= (quint32)m_Lines.at(m_CarretPosition.m_Row - 1).Content.length())
		{
			m_CarretPosition.m_Column++;
		}
		break;

	}

	QString l_EventText = event->text();

	if (!l_EventText.isEmpty())
	{
		for(int c = 0; c < l_EventText.count(); c++)
		{
			QChar l_Char = l_EventText.at(c);

			switch(l_Char.unicode())
			{
			case KBD_BACKSPACE:
				{
					if ((m_CarretPosition.m_Row == 1)&&(m_CarretPosition.m_Column == 1))
					{
						break;
					}

					if (m_CarretPosition.m_Column > 1)
					{
						QCodeEditWidgetLine line = m_Lines.takeAt(m_CarretPosition.m_Row - 1);

						line.Content = line.Content.left(m_CarretPosition.m_Column - 2) + line.Content.right(line.Content.length() - m_CarretPosition.m_Column + 1);

						m_Lines.insert(m_CarretPosition.m_Row - 1, line);

						m_CarretPosition.m_Column--;
					}
					else
					{
						QCodeEditWidgetLine line = m_Lines.takeAt(m_CarretPosition.m_Row - 1);
						QCodeEditWidgetLine line2 = m_Lines.takeAt(m_CarretPosition.m_Row - 2);

						int l_oldPos = line2.Content.length();

						line2.Content.append(line.Content);

						m_Lines.insert(m_CarretPosition.m_Row - 2, line2);

						m_CarretPosition.m_Row--;
						m_CarretPosition.m_Column = l_oldPos + 1;
					}
				}
				break;

			case KBD_ENTER:
				{
					QCodeEditWidgetLine line = m_Lines.takeAt(m_CarretPosition.m_Row - 1);
					QString l_NewLineText = line.Content.right(line.Content.length() - m_CarretPosition.m_Column + 1);
					line.Content.remove(m_CarretPosition.m_Column - 1, line.Content.length() - m_CarretPosition.m_Column + 1);

					QCodeEditWidgetLine line2;
					line2.Content = l_NewLineText;
					line2.EndLine = line.EndLine;
					line2.LineStatus = LineStatusTypeLineModified;

					m_Lines.insert(m_CarretPosition.m_Row - 1, line);
					m_Lines.insert(m_CarretPosition.m_Row, line2);

					m_CarretPosition.m_Row++;
					m_CarretPosition.m_Column = 1;
				}
				break;

			case KBD_DELETE:
				{
					QCodeEditWidgetLine line = m_Lines.at(m_CarretPosition.m_Row - 1);

					if (m_CarretPosition.m_Column - 1 == (quint32)line.Content.length())
					{
						if ((quint32)m_Lines.length() > m_CarretPosition.m_Row)
						{
							QCodeEditWidgetLine line2 = m_Lines.takeAt(m_CarretPosition.m_Row);

							line.Content.append(line2.Content);
						}
					}
					else
					{
						line.Content.remove(m_CarretPosition.m_Column - 1, 1);
					}

					m_Lines.replace(m_CarretPosition.m_Row - 1, line);
				}
				break;

			default:
				{
					QCodeEditWidgetLine line = m_Lines.at(m_CarretPosition.m_Row - 1);

					line.Content.insert(m_CarretPosition.m_Column - 1, l_EventText);

					m_Lines.replace(m_CarretPosition.m_Row - 1, line);
					m_CarretPosition.m_Column += l_EventText.size();
				}
			}
		}
	}

	m_currentlyBlinkCursorShowen = 1;

	killTimer(m_CursorTimerID);
	m_CursorTimerID = startTimer(500);

	viewport()->update(); // TODO: optimize this call, by updating the affected region only!!
}

void QCodeEditWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

	QPainter painter(viewport());

	QFontMetrics l_fm(m_TextFont);
	int l_fontHeight = l_fm.height();
	int l_fontWidth = l_fm.width(' ');
	quint32 l_LinesToDraw = (viewport()->height() / l_fontHeight) + 1;
	int l_LineNumbersPanelWidth = l_fm.width(" ") * m_LineNumbersPanelWidth;

	painter.fillRect(QRect(0, 0, l_LineNumbersPanelWidth, viewport()->height()), m_LineNumbersBackground);

	for(quint32 c = 0; c < l_LinesToDraw; c++)
	{
		if (m_ScrollYLinePos + c >= (quint32)m_Lines.count())
		{
			break;
		}

		//painter.set

		if ((m_ScrollYLinePos + c + 1) == m_CarretPosition.m_Row)
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

		painter.drawText(QRect(0, c * l_fontHeight, l_LineNumbersPanelWidth - 5, l_fontHeight), Qt::AlignRight, QString::number(m_ScrollYLinePos + c + 1));

		if ((m_ScrollYLinePos + c + 1) == m_CarretPosition.m_Row)
		{
			painter.setFont(m_TextFont);
		}

		painter.setPen(QColor(0, 0, 0));

		if ((m_ScrollYLinePos + c + 1) == m_CarretPosition.m_Row)
		{
			painter.fillRect(l_LineNumbersPanelWidth, c * l_fontHeight, viewport()->width() - l_LineNumbersPanelWidth, l_fontHeight, m_CurrentLineBackground);
		}

		painter.drawText(l_LineNumbersPanelWidth, (c * l_fontHeight) + 12, m_Lines.at(m_ScrollYLinePos + c).Content); // TODO: 12 is hardcoded
	}

	setFont(m_TextFont);

	if (m_currentlyBlinkCursorShowen == 1)
	{
		const QBrush oldBrush = painter.brush();
		painter.setBrush(QColor(Qt::black));
		painter.drawRect(l_LineNumbersPanelWidth + ((m_CarretPosition.m_Column - 1) * l_fontWidth), ((m_CarretPosition.m_Row - 1) * l_fontHeight), ceil(m_CursorHeight * 0.05), l_fontHeight - 1);
		painter.setBrush(oldBrush);
	}
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

void QCodeEditWidget::clearFormatting()
{
	m_ColorItems.clear();
	update();
}

void QCodeEditWidget::addFormat(const QCodeEditWidgetColorItem &p_item)
{
	if ((p_item.index < 0)||(p_item.length <= 0))
	{
		return;
	}

	int l_beginPoint = 0; // TODO: Optimize me to start from right position.
	int l_endPoint = p_item.index + p_item.length;

	for(int c = l_beginPoint; c < m_ColorItems.count(); c++)
	{
		const QCodeEditWidgetColorItem & item = m_ColorItems.at(c);
		if(item.index > l_endPoint)
		{
			return;
		}

		if (item.index > p_item.index)
		{
			m_ColorItems.insert(c, p_item);
			return;
		}
	}

	m_ColorItems.append(p_item);
}
