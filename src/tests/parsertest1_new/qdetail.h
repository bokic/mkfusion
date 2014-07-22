#ifndef QDETAIL_H
#define QDETAIL_H

#include "qtextparser.h"

#include <QTreeWidgetItem>
#include <QDialog>
#include <QColor>
#include <QList>

namespace Ui
{
class QDetail;
}

class QDetail : public QDialog
{
    Q_OBJECT

public:
    explicit QDetail(QWidget *parent = 0);
    virtual ~QDetail();

    void setFileForParsing(const QString &p_File);

private:
    Ui::QDetail *ui;

    void addSubTrees(const QTextParser::QTextParserElement &p_ParserElement, QTreeWidgetItem *p_WidgetItem);
    void recolor();
    int getTextPos(int line, int column);
    void colorElement(const QTextParser::QTextParserElement &p_Element, const QString &p_ElementIDString);
    QTextParser m_Parser;
    QStringList m_FileLines;
    QString m_CurrentTextSegment;
    bool m_IsCurrentSelect;

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    QTextParser::QTextParserElements elements;
    QList<QColor> m_ElementTextColors;
    QList<QColor> m_ElementBackgroundColors;
};

#endif // QDETAIL_H
