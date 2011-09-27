#ifndef QCODEEDITWIDGET_H
#define QCODEEDITWIDGET_H

#include "qtextparser.h"

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
    enum BreakpointType {BreakpointTypeNoBreakpoint, BreakpointTypeBreakpoint, BreakpointTypeBreakpointPending, BreakpointTypeDisabled};

    struct QCodeEditWidgetLine : QTextParser::QTextParserLine
    {
        BreakpointType Breakpoint;
        LineStatusType LineStatus;
    };

    explicit QCodeEditWidget(QWidget* = 0);
	~QCodeEditWidget();
	QString getText();
    void setFileExtension(const QString &);
	void clearFormatting();
    void addFormat(int p_line, const QTextParser::QTextParserColorItem &p_item);
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
    QTextParser m_Parser;

	int m_ScrollXCharPos;
	int m_ScrollYLinePos;
	int m_LineNumbersPanelWidth;
	int m_currentlyBlinkCursorShowen;
	int m_CursorTimerID;
	int m_CursorHeight;
	bool m_SelectMouseDown;

	struct {
		int m_Row;
		int m_Column;
	} m_CarretPosition;

	struct {
		int m_Row;
		int m_Column;
	} m_SelectionPosition;

signals:
	void on_key_press(QKeyEvent *);
	void on_text_change();
	void on_breakpoint_change(int);

public slots:
	void setText(const QString &text);
};

#endif // QCODEEDITWIDGET_H
