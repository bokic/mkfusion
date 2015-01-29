#ifndef QDETAIL_H
#define QDETAIL_H

#include "qcfparser.h"

#include <QTreeWidgetItem>
#include <QDialog>
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

    void addSubTrees(const QCFParserElement &element, QTreeWidgetItem *widgetItem);
    void recolor();
    void colorElement(const QCFParserElement &element, const QString &idString);

    QString m_CurrentTextSegment;
    QList<QCFParserTag> m_ParserTags;
    bool m_IsCurrentSelect;

};

#endif // QDETAIL_H
