#ifndef QCODEEDITWIDGET_H
#define QCODEEDITWIDGET_H

#include <QAbstractScrollArea>
#include <QPixmap>
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
	enum BreakpointType {BreakpointTypeNoBreakpoint, BreakpointTypeBreakpoint, BreakpointTypeBreakpointPending, BreakpointTypeDisabled};

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
		BreakpointType Breakpoint;
	};

	explicit QCodeEditWidget(QWidget* = 0);
	~QCodeEditWidget();
	QString getText();
	void clearFormatting();
	void addFormat(const QCodeEditWidgetColorItem&);
	void setBreakpoint(int, BreakpointType);
	BreakpointType breakpoint(int);

protected:
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent*);
	void keyPressEvent(QKeyEvent*);
	void updatePanelWidth();
	void ensureCaretIsVisible();
	void scrollContentsBy(int, int);
	void mouseMoveEvent(QMouseEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);

private:
	QBrush m_LineNumbersBackground;
	QPen m_LineNumbersNormal;
	QPen m_LineNumbersCurrent;
	QBrush m_LineModifiedAndNotSavedBackground;
	QBrush m_LineModifiedAndSavedBackground;
	QBrush m_CurrentLineBackground;
	QFont m_TextFont;
	QPixmap m_BreakPointPixmap;
	QPixmap m_BreakPointPixmapPending;
	QPixmap m_BreakPointPixmapDisabled;
	QList<QCodeEditWidgetLine> m_Lines;
	QList<QCodeEditWidgetColorItem> m_ColorItems;

	int m_ScrollXCharPos;
	int m_ScrollYLinePos;
	int m_LineNumbersPanelWidth;
	int m_currentlyBlinkCursorShowen;
	int m_CursorTimerID;
	int m_CursorHeight;

	struct {
		int m_Row;
		int m_Column;
	} m_CarretPosition;

signals:
	void on_key_press(QKeyEvent *);
	void on_text_change();
	void on_breakpoint_change(int);

public slots:
	void setText(const QString &text);
};

#endif // QCODEEDITWIDGET_H
