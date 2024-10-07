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

void QDetail::setFileForParsing(const QString &file)
{
    m_Parser = QTextParser();

    elements = m_Parser.parseFile(file);

    m_ElementTextColors.clear();
    m_ElementBackgroundColors.clear();

    for(const QTextParserLanguageDefinitionToken &token: m_Parser.getLanguage().tokens)
    {
        if ((token.name == "StartTag")||(token.name == "EndTag"))
        {
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
        else if ((token.name == "Comment")||(token.name == "ScriptComment")||(token.name == "BlockComment"))
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
            m_ElementTextColors.append(QColor(92, 92, 92));
            m_ElementBackgroundColors.append(QColor());
        }
        else
        {
            qDebug() << "Unknown token.";
            m_ElementTextColors.append(QColor());
            m_ElementBackgroundColors.append(QColor());
        }
    }

    QFile f(file);
    f.open(QIODevice::ReadOnly);
    QString fileContent = f.readAll();
    fileContent = fileContent.replace("\r\n", "\n");
    m_FileLines = fileContent.split('\n');
    f.close();

    ui->textEdit->setPlainText(fileContent);


    for(int c = 0; c < elements.count(); c++)
    {
        const QTextParserElement &element = elements.at(c);

        QTreeWidgetItem *widgetItem = new QTreeWidgetItem();

        if (element.m_Type >= 0)
        {
            QString text = m_Parser.getLanguage().tokens.at(element.m_Type).name;

            if (!element.m_Text.isEmpty())
            {
                text.append(QString("(%1)").arg(element.m_Text));
            }

            widgetItem->setText(0, text);
            widgetItem->setText(1, QChar(c));

            addSubTrees(element, widgetItem);

            ui->parser_treeWidget->addTopLevelItem(widgetItem);
        }
    }

    ui->parser_treeWidget->expandAll();

    recolor();

    ui->parser_treeWidget->setFocus();
}

void QDetail::addSubTrees(const QTextParserElement &element, QTreeWidgetItem *widgetItem)
{
    for(int c = 0; c < element.m_ChildElements.count(); c++)
    {
        const QTextParserElement &childElement = element.m_ChildElements.at(c);

        QTreeWidgetItem *child = new QTreeWidgetItem();

        QString text = m_Parser.getLanguage().tokens.at(childElement.m_Type).name;

        if (!childElement.m_Text.isEmpty())
        {
            text.append(QString("(%1)").arg(childElement.m_Text));
        }

        child->setText(0, text);
        child->setText(1, widgetItem->text(1) + QChar(c));

        addSubTrees(childElement, child);

        widgetItem->addChild(child);
    }
}

void QDetail::recolor()
{
    ui->textEdit->selectAll();
    ui->textEdit->setTextBackgroundColor(Qt::white);
    ui->textEdit->setTextColor(Qt::black);

    for(int c = 0; c < elements.count(); c++)
    {
        const QTextParserElement &element = elements.at(c);

        if (element.m_Type >= 0)
        {
            colorElement(element, QChar(c));
        }
    }
}

int QDetail::getTextPos(int line, int column)
{
    int pos = 0;

    for(int c = 0; c < line; c++)
    {
        pos += m_FileLines.at(c).size() + 1;
    }

    return pos + column;
}

void QDetail::colorElement(const QTextParserElement &element, const QString &idString)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.setPosition(getTextPos(element.m_StartLine, element.m_StartColumn), QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(cursor);
    cursor.setPosition(getTextPos(element.m_EndLine, element.m_EndColumn), QTextCursor::KeepAnchor);
    ui->textEdit->setTextCursor(cursor);

    if (m_ElementTextColors.at(element.m_Type).isValid())
    {
        ui->textEdit->setTextColor(m_ElementTextColors.at(element.m_Type));
    }
    if(m_ElementBackgroundColors.at(element.m_Type).isValid())
    {
        ui->textEdit->setTextBackgroundColor(m_ElementBackgroundColors.at(element.m_Type));
    }

    if (!m_CurrentTextSegment.isEmpty())
    {
        if ((idString.left(m_CurrentTextSegment.length()) == m_CurrentTextSegment))
        {
            QTextCursor cursor = ui->textEdit->textCursor();
            cursor.setPosition(getTextPos(element.m_StartLine, element.m_StartColumn), QTextCursor::MoveAnchor);
            ui->textEdit->setTextCursor(cursor);
            cursor.setPosition(getTextPos(element.m_EndLine, element.m_EndColumn), QTextCursor::KeepAnchor);
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

    cursor.setPosition(getTextPos(element.m_StartLine, element.m_StartColumn), QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(cursor);

    for(int c = 0; c < element.m_ChildElements.count(); c++)
    {
        const QTextParserElement &child = element.m_ChildElements.at(c);

        colorElement(child, idString + QChar(c));
    }
}

void QDetail::on_parser_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
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
