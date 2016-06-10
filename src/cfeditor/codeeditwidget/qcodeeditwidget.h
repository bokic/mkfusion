#pragma once

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
    Q_PROPERTY(QString Text READ text WRITE setText DESIGNABLE false)
    Q_PROPERTY(int TabSize READ tabSize WRITE setTabSize DESIGNABLE true)
public:
    enum QLineStatusType {QLineStatusTypeLineNotModified, QLineStatusTypeLineSaved, QLineStatusTypeLineModified};
    enum QBreakpointType {QBreakpointTypeNoBreakpoint, QBreakpointTypeBreakpoint, QBreakpointTypeBreakpointPending, QBreakpointTypeDisabled};

    struct QTextParserColorItem
    {
        int index = -1;
        int length = -1;
        QColor foregroundColor;
    };

    struct QCodeEditWidgetLine : QTextParserLine
    {
        QBreakpointType breakpointType = QBreakpointTypeNoBreakpoint;
        QLineStatusType lineStatus = QLineStatusTypeLineNotModified;
        QList<QTextParserColorItem> colors;
    };

    explicit QCodeEditWidget(QWidget *parent = 0);
    virtual ~QCodeEditWidget() override;
    QString text() const;
    int tabSize() const;
    void setFileExtension(const QString &extension);
    void clearFormatting();
    void addFormat(int p_line, const QTextParserColorItem &p_item);
    void setBreakpoint(int line, QBreakpointType type);
    QBreakpointType breakpoint(int line) const;

signals:
    void on_key_press(QKeyEvent *event);
    void on_text_change();
    void on_breakpoint_change(int line);

public slots:
    void setText(QString text);
    void setTabSize(int size);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void scrollContentsBy(int dx , int dy) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void updatePanelWidth();
    void ensureCaretIsVisible();

    typedef struct {
        int m_Row = 1;
        int m_Column = 1;
    } QCodeEditWidgetTextPosition;

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

    int m_ScrollXCharPos = 0;
    int m_ScrollYLinePos = 0;
    int m_LineNumbersPanelWidth = 3;
    int m_currentlyBlinkCursorShowen = 1;
    int m_CursorTimerID = 0;
    int m_FontHeight = 0;
    int m_LineHeight = 0;
    int m_LineYOffset = 0;
    bool m_SelectMouseDown = false;
    int m_tabSize = 4;

    QCodeEditWidgetTextPosition m_CarretPosition;
    QCodeEditWidgetTextPosition m_SelectionPosition;
};
