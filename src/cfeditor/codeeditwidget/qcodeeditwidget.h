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
        QCodeEditWidgetLine() : QTextParserLine(), Breakpoint(BreakpointTypeNoBreakpoint), LineStatus(LineStatusTypeLineNotModified) {}
    };

    explicit QCodeEditWidget(QWidget *parent = 0);
    virtual ~QCodeEditWidget();
	QString getText();
    void setFileExtension(const QString &Extension);
	void clearFormatting();
    //void addFormat(int p_line, const QTextParser::QTextParserColorItem &p_item);
    void setBreakpoint(int line, BreakpointType newBreakpoint);
    BreakpointType breakpoint(int line);

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
	void updatePanelWidth();
	void ensureCaretIsVisible();
    void scrollContentsBy(int dx , int dy);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

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
    int m_FontHeight;
    int m_LineHeight;
    int m_LineYOffset;
	bool m_SelectMouseDown;

    struct CarretPosition {
		int m_Row;
		int m_Column;
        CarretPosition() : m_Row(1), m_Column(1) {}
	} m_CarretPosition;

    struct SelectionPosition{
		int m_Row;
		int m_Column;
        SelectionPosition() : m_Row(1), m_Column(1) {}
	} m_SelectionPosition;

signals:
	void on_key_press(QKeyEvent *);
	void on_text_change();
	void on_breakpoint_change(int);

public slots:
	void setText(const QString &text);
};

#endif // QCODEEDITWIDGET_H
