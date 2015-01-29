#include "qdetail.h"
#include "ui_qdetail.h"
#include "qcfparser.h"

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
    QString fileContent;

    // Read file from file
    {
        QFile f(file);
        f.open(QIODevice::ReadOnly);
        fileContent = f.readAll();
        f.close();
    }

    ui->textEdit->setPlainText(fileContent);

    QCFParser oldParser;

    if (oldParser.parse(fileContent) == NoError)
    {
        oldParser.prioritizeOperators();
    }

    ui->status_label->setText(oldParser.error());

    m_ParserTags = oldParser.getTags();

    ushort c = 0;

    for(const QCFParserTag &tag: m_ParserTags)
    {
        QString name;

        switch(tag.m_TagType)
        {
        case UnknownTagType:
            name = "UnknownTag";
            break;
        case CFTagType:
            name = "CFTag(" + tag.m_Name + ")";
            break;
        case EndCFTagType:
            name = "EndCFTag(" + tag.m_Name + ")";
            break;
        case CommentTagType:
            name = "CommentTag";
            break;
        case ExpressionTagType:
            name = "ExpressionTag";
            break;
        }

        QTreeWidgetItem *widgetItem = new QTreeWidgetItem();

        widgetItem->setText(0, name);
        widgetItem->setText(1, QChar(c));

        addSubTrees(tag.m_Arguments, widgetItem);

        ui->parser_treeWidget->addTopLevelItem(widgetItem);

        c++;
    }

    ui->parser_treeWidget->expandAll();

    recolor();

    // Set focus to old_parser tree widget
    ui->parser_treeWidget->setFocus();
}

void QDetail::addSubTrees(const QCFParserElement &element, QTreeWidgetItem *widgetItem)
{
    ushort c = 0;

    for(const QCFParserElement &child: element.m_ChildElements)
    {
        QString name;

        //enum QCFParserElementType {Boolean, Number, String, Variable, Function, Operator, SharpExpression
        //Expression, SubExpression, Parameters, Parameter, CFScript, CFComment, CFTagExpression, CFTagArguments, CFTagArgument, ObjectFunction, VariableMember, Error};

        switch(child.m_Type)
        {
        case Boolean:
            name = "Boolean(" + child.m_Text + ")";
            break;
        case Number:
            name = "Number(" + child.m_Text + ")";
            break;
        case String:
            name = "String(" + child.m_Text + ")";
            break;
        case Variable:
            name = "Variable(" + child.m_Text + ")";
            break;
        case Function:
            name = "Function(" + child.m_Text + ")";
            break;
        case Operator:
            name = "Operator(" + child.m_Text + ")";
            break;
        case SharpExpression:
            name = "SharpExpression";
            break;
        case CodeBlock:
            name = "CodeBlock";
            break;
        case Expression:
            name = "Expression";
            break;
        case SubExpression:
            name = "SubExpression";
            break;
        case Parameters:
            name = "Parameters";
            break;
        case Parameter:
            name = "Parameter";
            break;
        case CFScript:
            name = "CFScript";
            break;
        case CFComment:
            name = "CFComment";
            break;
        case CFTagExpression:
            name = "CFTagExpression";
            break;
        case CFTagArguments:
            name = "CFTagArguments";
            break;
        case CFTagArgument:
            name = "CFTagArgument";
            break;
        case ObjectFunction:
            name = "ObjectFunction(" + child.m_Text + ")";
            break;
        case VariableMember:
            name = "VariableMember(" + child.m_Text + ")";
            break;
        case Keyword:
            name = "Keyword(" + child.m_Text + ")";
            break;
        case Error:
            name = "Error(" + child.m_Text + ")";
            break;
        default:
            name = "[Unknown](" + child.m_Text + ")";
            break;
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem();

        childItem->setText(0, name);
        childItem->setText(1, childItem->text(1) + QChar(c));

        addSubTrees(child, childItem);

        widgetItem->addChild(childItem);

        c++;
    }
}

void QDetail::recolor()
{
    QTextCursor cursor = ui->textEdit->textCursor();

    ushort c = 0;

    for(const QCFParserTag &tag: m_ParserTags)
    {
        QString TagString = QChar(c);

        if ((!m_CurrentTextSegment.isEmpty())&&(m_CurrentTextSegment.left(1) != TagString))
        {
            c++;

            continue;
        }

        cursor.setPosition(tag.m_Start, QTextCursor::MoveAnchor);
        ui->textEdit->setTextCursor(cursor);
        cursor.setPosition(tag.m_Start + tag.m_Length, QTextCursor::KeepAnchor);
        ui->textEdit->setTextCursor(cursor);

        if ((TagString == m_CurrentTextSegment))
        {
            if (m_IsCurrentSelect)
            {
                ui->textEdit->setTextBackgroundColor(QColor(255, 128, 128));
            }
            else
            {
                ui->textEdit->setTextBackgroundColor(QColor(255, 255, 255));
            }

            cursor.setPosition(tag.m_Start, QTextCursor::MoveAnchor);
            ui->textEdit->setTextCursor(cursor);

            break;
        }

        if (tag.m_TagType == CommentTagType)
        {
            ui->textEdit->setTextColor(QColor(128, 128, 128));
        }
        else
        {
            ui->textEdit->setTextColor(QColor(128, 0, 0));
        }

        colorElement(tag.m_Arguments, TagString);

        cursor.setPosition(tag.m_Start, QTextCursor::MoveAnchor);
        ui->textEdit->setTextCursor(cursor);

        c++;
    }
}

void QDetail::colorElement(const QCFParserElement &element, const QString &idString)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    cursor.setPosition(element.m_Position, QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(cursor);
    cursor.setPosition(element.m_Position + element.m_Size, QTextCursor::KeepAnchor);
    ui->textEdit->setTextCursor(cursor);

    if (!m_CurrentTextSegment.isEmpty())
    {
        if ((idString.left(m_CurrentTextSegment.length()) == m_CurrentTextSegment))
        {
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

    switch (element.m_Type)
    {
    case CFTagArguments:
        //ui->textEdit->setTextColor(QColor(255, 128, 0));
        break;
    case CFTagArgument:
        ui->textEdit->setTextColor(QColor(255, 255, 0));
        break;
    case Variable:
        ui->textEdit->setTextColor(QColor(128, 128, 0));
        break;
    case Operator:
        ui->textEdit->setTextColor(QColor(0, 0, 0));
        break;
    case Number:
        ui->textEdit->setTextColor(QColor(0, 255, 0));
        break;
    case String:
        ui->textEdit->setTextColor(QColor(0, 0, 255));
        break;
    case SharpExpression:
        ui->textEdit->setTextColor(QColor(72, 72, 0));
        break;
    case Expression:
        ui->textEdit->setTextColor(QColor(92, 92, 0));
        break;
    case CFComment:
        ui->textEdit->setTextColor(QColor(128, 128, 128));
        break;
    default:
        break;
    }

    ushort c = 0;

    for(const QCFParserElement &child: element.m_ChildElements)
    {
        colorElement(child, idString + QChar(c));

        c++;
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
