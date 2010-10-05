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
	~QCodeEditWidget();
	QString getText();
	void clearFormatting();
	void addFormat(const QCodeEditWidgetColorItem&);

protected:
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent*);
	void keyPressEvent(QKeyEvent*);

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

	quint32 m_ScrollXPixelPos;
	quint32 m_ScrollYLinePos;
	int m_LineNumbersPanelWidth;
	int m_currentlyBlinkCursorShowen;
	int m_CursorTimerID;
	int m_CursorHeight;

	struct
	{
		quint32 m_Row;
		quint32 m_Column;
	} m_CarretPosition;

signals:

public slots:
	void setText(const QString &text);
};

#endif // QCODEEDITWIDGET_H
