#include "qdetail.h"
#include "ui_qdetail.h"

#include "qtextparser.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QFont>

QDetail::QDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDetail)
{
    ui->setupUi(this);

	setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);

#ifdef Q_OS_WIN
    QFont l_Font = QFont("Courier", 10, 0, false);
#else
    QFont l_Font = QFont("Monospace", 9, 0, false);
#endif
    ui->textEdit->setFont(l_Font);
}

QDetail::~QDetail()
{
    delete ui;
	ui = 0;
}

void QDetail::setFileForParsing(const QString &p_File)
{
    m_Parser = QTextParser();

    elements = m_Parser.parseFile(p_File);

    m_ElementTextColors.clear();
    m_ElementBackgroundColors.clear();

    for(const QTextParser::QTextParserLanguageDefinitionToken &token: m_Parser.getLanguage().tokens)
    {
        if ((token.name == "CFTag")||(token.name == "CFEndTag")||(token.name == "CFScript")||(token.name == "CFOutput"))
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if ((token.name == "CFComment")||(token.name == "ScriptComment"))
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor(Qt::lightGray));
        }
        else if (token.name == "ScriptExpression")
        {
            m_ElementTextColors.append(Qt::black);
            m_ElementBackgroundColors.append(QColor(224, 224, 255));
        }
        else if (token.name == "OutputExpression")
        {
            m_ElementTextColors.append(Qt::black);
            m_ElementBackgroundColors.append(Qt::white);
        }
        else if ((token.name == "SingleString")||(token.name == "DoubleString"))
        {
            m_ElementTextColors.append(QColor(Qt::black));
            m_ElementBackgroundColors.append(QColor(192, 192, 255));
        }
        else if ((token.name == "SingleChar")||(token.name == "DoubleChar")||(token.name == "SharpChar"))
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor(128, 128, 255));
        }
        else if (token.name == "SharpExpression")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor(192, 192, 0));
        }
        else if (token.name == "Expression")
        {
            m_ElementTextColors.append(QColor(92, 92, 0));
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "ExpressionEnd")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Number")
        {
            m_ElementTextColors.append(QColor(Qt::green));
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Boolean")
        {
            m_ElementTextColors.append(QColor(Qt::darkYellow));
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "ObjectMember")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Function")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Separator")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Variable")
        {
            m_ElementTextColors.append(QColor(128, 128, 0));
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Object")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Assigment")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Operator")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "SubExpression")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "VariableIndex")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "CodeBlock")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if (token.name == "Keyword")
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else
        {
            qDebug() << "Unknown token.";
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
    }

    QFile file(p_File);
    file.open(QIODevice::ReadOnly);
    QString fileContent = file.readAll();
    fileContent = fileContent.replace("\r\n", "\n");
    m_FileLines = fileContent.split('\n');
    file.close();

    ui->textEdit->setPlainText(fileContent);


    for(int c = 0; c < elements.count(); c++)
    {
        const QTextParser::QTextParserElement &element = elements.at(c);

        QTreeWidgetItem *widgetItem = new QTreeWidgetItem();

        widgetItem->setText(0, element.m_Debug);
        widgetItem->setText(1, QChar(c));

        addSubTrees(element, widgetItem);

        ui->treeWidget->addTopLevelItem(widgetItem);
    }

    ui->treeWidget->expandAll();

    recolor();

    ui->treeWidget->setFocus();
}

void QDetail::addSubTrees(const QTextParser::QTextParserElement &p_ParserElement, QTreeWidgetItem *p_WidgetItem)
{
    for(int c = 0; c < p_ParserElement.m_ChildElements.count(); c++)
    {
        const QTextParser::QTextParserElement &child = p_ParserElement.m_ChildElements.at(c);

        QTreeWidgetItem *widgetItem = new QTreeWidgetItem();

        widgetItem->setText(0, child.m_Debug);
        widgetItem->setText(1, p_WidgetItem->text(1) + QChar(c));

        addSubTrees(child, widgetItem);

        p_WidgetItem->addChild(widgetItem);
    }
}

void QDetail::recolor()
{
    ui->textEdit->selectAll();
    ui->textEdit->setTextBackgroundColor(Qt::white);
    ui->textEdit->setTextColor(Qt::black);

    for(int c = 0; c < elements.count(); c++)
    {
        QTextParser::QTextParserElement element = elements.at(c);

        colorElement(element, QChar(c));
    }
}

int QDetail::getTextPos(int line, int column)
{
    int pos = 0;

    for(int c = 0; c < line; c++)
    {
        pos += m_FileLines.at(c).count() + 1;
    }

    return pos + column;
}

void QDetail::colorElement(const QTextParser::QTextParserElement &p_Element, const QString &p_ElementIDString)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.setPosition(getTextPos(p_Element.m_StartLine, p_Element.m_StartColumn), QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(cursor);
    cursor.setPosition(getTextPos(p_Element.m_EndLine, p_Element.m_EndColumn), QTextCursor::KeepAnchor);
    ui->textEdit->setTextCursor(cursor);

    if (m_ElementTextColors.at(p_Element.m_Type).isValid())
    {
        ui->textEdit->setTextColor(m_ElementTextColors.at(p_Element.m_Type));
    }
    if(m_ElementBackgroundColors.at(p_Element.m_Type).isValid())
    {
        ui->textEdit->setTextBackgroundColor(m_ElementBackgroundColors.at(p_Element.m_Type));
    }

    if (!m_CurrentTextSegment.isEmpty())
    {
        if ((p_ElementIDString.left(m_CurrentTextSegment.length()) == m_CurrentTextSegment))
        {
            QTextCursor cursor = ui->textEdit->textCursor();
            cursor.setPosition(getTextPos(p_Element.m_StartLine, p_Element.m_StartColumn), QTextCursor::MoveAnchor);
            ui->textEdit->setTextCursor(cursor);
            cursor.setPosition(getTextPos(p_Element.m_EndLine, p_Element.m_EndColumn), QTextCursor::KeepAnchor);
            ui->textEdit->setTextCursor(cursor);

            if (m_IsCurrentSelect)
            {
                ui->textEdit->setTextBackgroundColor(QColor(255, 128, 128));
            }
            else
            {
                ui->textEdit->setTextBackgroundColor(QColor(255, 255, 255));
            }
        }
    }

    cursor.setPosition(getTextPos(p_Element.m_StartLine, p_Element.m_StartColumn), QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(cursor);

    for(int c = 0; c < p_Element.m_ChildElements.count(); c++)
    {
        const QTextParser::QTextParserElement &child = p_Element.m_ChildElements.at(c);

        colorElement(child, p_ElementIDString + QChar(c));
    }
}

void QDetail::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (previous)
    {
        m_CurrentTextSegment = previous->text(1);
        m_IsCurrentSelect = false;

        recolor();
    }

    if (current)
    {
        m_CurrentTextSegment = current->text(1);
        m_IsCurrentSelect = true;

        recolor();
    }
}
