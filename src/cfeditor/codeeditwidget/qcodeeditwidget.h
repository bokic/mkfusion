#ifndef QCODEEDITWIDGET_H
#define QCODEEDITWIDGET_H

#include <QAbstractScrollArea>
#include <QColor>
#include <QFont>
#include <QList>
#include <QPen>

class QCodeEditWidget : public QAbstractScrollArea
{
Q_OBJECT
Q_PROPERTY(QString Text READ getText WRITE setText DESIGNABLE false)
public:

	enum LineStatusType {LineStatusTypeLineNotModified, LineStatusTypeLineSaved, LineStatusTypeLineModified};
	enum EndLineType {EndLineTypeNoEndLine, EndLineTypeCREndLine, EndLineTypeLFEndLine, EndLineTypeCRLFEndLine, EndLineTypeLFCREndLine};
	enum UnderlineType {UnderlineTypeNoUnderline, UnderlineTypeLine, UnderlineTypeWave};

	struct QCodeEditWidgetColorItem {
		int index;
		int length;
		QColor foregroundColor;
		QColor backgroundColor;
		QColor underlineColor;
		UnderlineType underline;

	};

	struct QCodeEditWidgetLine {
		LineStatusType LineStatus;
		QString Content;
		EndLineType EndLine;
	};

	explicit QCodeEditWidget(QWidget* = 0);
	QString getText();
	void clearFormatting();
	void addFormat(const QCodeEditWidgetColorItem&);

protected:
	void paintEvent(QPaintEvent*);

private:
	QBrush m_LineNumbersBackground;
	QPen m_LineNumbersNormal;
	QPen m_LineNumbersCurrent;
	QBrush m_LineModifiedAndNotSavedBackground;
	QBrush m_LineModifiedAndSavedBackground;
	QBrush m_CurrentLineBackground;
	QFont m_TextFont;
	QList<QCodeEditWidgetLine> m_Lines;
	QList<QCodeEditWidgetColorItem> m_ColorItems;

	int m_ScrollXPixelPos;
	int m_ScrollYLinePos;
	int m_CaretXPos;
	int m_CaretYPos;

signals:

public slots:
	void setText(const QString &text);
};

#endif // QCODEEDITWIDGET_H
