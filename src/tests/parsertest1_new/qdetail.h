#ifndef QDETAIL_H
#define QDETAIL_H

#include "qtextparserelement.h"
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

    void setFileForParsing(const QString &file);

private slots:
    void on_parser_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::QDetail *ui;

    void addSubTrees(const QTextParserElement &element, QTreeWidgetItem *widgetItem);
    void recolor();
    int getTextPos(int line, int column);
    void colorElement(const QTextParserElement &element, const QString &idString);
	
    QTextParser m_Parser;
    QStringList m_FileLines;
    QString m_CurrentTextSegment;
    bool m_IsCurrentSelect;

    QTextParserElements elements;
    QList<QColor> m_ElementTextColors;
    QList<QColor> m_ElementBackgroundColors;
};

#endif // QDETAIL_H
