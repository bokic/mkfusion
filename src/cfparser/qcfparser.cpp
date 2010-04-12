#include "qcfparser.h"
#include "qcf8.h"

#include <QtCore/QString>
#include <QtCore/QChar>
#ifdef QT_DEBUG
#include <QDebug>
#endif
/*
  (0) comment inside cftags.
  (0) cfscript
    * End of cfscript: </cf
  (5) cftagarguments
    * End of cfarguments: > or />
  (3) cftagargument
    * End of cfargument:
  (0) expression
  (0) object member function
  (0) function
    * End of function name chars are: tab, space, newline, (
   ** Ilegal characters inside brackets <, /, >
  (3) variable
    * End of variable name chars are: tab, space, newline, [
  (2) operator
  (3) string
  (5) numerical
  (0) parametars
  (0) parametar
  */

QCFParser::QCFParser(): QObject()
{
	this->m_CFTagsDef = QCF8::generateCFTags();
	this->m_CFFunctionsDef = QCF8::generateCFFunctions();
}

quint32 GetLineNumberFromPosition(const QString &p_FileContent, const qint32 p_FileOffset)
{
	quint32 ret = 1;

	for(qint32 offset = p_FileContent.indexOf('\n', 0, Qt::CaseInsensitive); offset != -1; offset = p_FileContent.indexOf('\n', offset + 1, Qt::CaseInsensitive))
	{
		if (offset > p_FileOffset)
		{
			break;
		}

		ret++;
	}

	return ret;
}

quint32 GetColumnNumberFromPosition(const QString &p_FileContent, const qint32 p_FileOffset)
{
	qint32 offset = 0;

	for(offset = p_FileContent.indexOf('\n', 0, Qt::CaseInsensitive); offset != -1; offset = p_FileContent.indexOf('\n', offset + 1, Qt::CaseInsensitive))
	{
		if (offset > p_FileOffset)
		{
			break;
		}
	}

	return p_FileOffset - offset + 1;
}

bool QCFParser::TrimCFCode(const QString& p_Text, int& p_Offset)
{
	int l_Len = p_Text.length();
	QChar l_ch;
	for(; ; )
	{
		if (p_Offset >= l_Len)
		{
			return true;
		}

		l_ch = p_Text.at(p_Offset);
		if ((l_ch == ' ')||(l_ch == '\t')||(l_ch == '\r')||(l_ch == '\n'))
		{
			p_Offset++;
			continue;
		}
		break;
	}

	return false;
}

QCFParserElement QCFParser::ParseCFCode(const QString& p_Text, const qint32 p_Offset, const QCFParserElementType p_ElementType)
{
	QCFParserElement ret;
	QCFParserElement child;
	QString str;
	QChar ch, ch2;
	ret.m_Type = p_ElementType;
	int l_Offset = p_Offset;

	if (TrimCFCode(p_Text, l_Offset))
	{
		ret.m_Type = Error;
		ret.m_Position = l_Offset - 1;
		ret.m_Text = tr("End of file found.");
		return ret;
	}

	ret.m_Position = l_Offset;

	switch(p_ElementType)
	{
		case CFTagExpression:
			ch = p_Text.at(l_Offset);

			if (ch == '>')
			{
				ret.m_Position = p_Offset;
				ret.m_Size = l_Offset - p_Offset;
				return ret;
			}

			if (ch == '/')
			{
				if (l_Offset + 1 >= p_Text.length())
				{
					ret.m_Type = Error;
					ret.m_Text = tr("'>' Missing.");
					return ret;
				}

				ch2 = p_Text.at(l_Offset + 1);
				if (ch2 == '>')
				{
					ret.m_Position = p_Offset;
					ret.m_Size = l_Offset - p_Offset;
					return ret;
				}
				else
				{
					ret.m_Type = Error;
					ret.m_Text = tr("'>' Missing, and something else found.");
					return ret;
				}
			}

			child = ParseCFCode(p_Text, l_Offset, Expression);
			if (child.m_Type == Error)
			{
				return child;
			}
			ret.m_ChildElements.append(child);
			ret.m_Size = child.m_Size;
			l_Offset = child.m_Position + child.m_Size;
			break;
		case CFTagArguments:
			for (l_Offset = l_Offset; l_Offset < p_Text.length(); )
			{
				if (TrimCFCode(p_Text, l_Offset))
				{
					ret.m_Type = Error;
					ret.m_Position = l_Offset - 1;
					ret.m_Text = tr("cftag not closed.");
					return ret;
				}
				ch = p_Text.at(l_Offset);

				if (ch == '>')
				{
					ret.m_Position = p_Offset;
					ret.m_Size = l_Offset - p_Offset;
					return ret;
				}

				if (ch == '/')
				{
					if (l_Offset + 1 >= p_Text.length())
					{
						ret.m_Type = Error;
						ret.m_Text = tr("'>' Missing.");
						return ret;
					}

					ch2 = p_Text.at(l_Offset + 1);
					if (ch2 == '>')
					{
						ret.m_Position = p_Offset;
						ret.m_Size = l_Offset - p_Offset;
						return ret;
					}
					else
					{
						ret.m_Type = Error;
						ret.m_Text = tr("'>' Missing, something else found.");
						return ret;
					}
				}

				child = ParseCFCode(p_Text, l_Offset, CFTagArgument);
				if (child.m_Type == Error)
				{
					return child;
				}
				ret.m_ChildElements.append(child);
				l_Offset = child.m_Position + child.m_Size;
			}

			ret.m_Type = Error;
			ret.m_Position = p_Text.length();
			ret.m_Text = tr("cftag not closed.");
			break;
		case CFTagArgument:
			int l_NotOperatorFirst;
			int lastElementFound;
			int index;

			index = 0;
			l_NotOperatorFirst = 0;
			lastElementFound = l_Offset;

			for (int c = l_Offset; c < p_Text.length(); )
			{
				if (TrimCFCode(p_Text, c))
				{
					ret.m_Type = Error;
					ret.m_Position = l_Offset - 1;
					ret.m_Text = tr("End of file found.");
					return ret;
				}
				ch = p_Text.at(c);

				if (ch == '>')
				{
					ret.m_Size = lastElementFound - ret.m_Position;
					return ret;
				}

				if (ch == '/')
				{
					if (c + 1 >= p_Text.length())
					{
						ret.m_Type = Error;
						ret.m_Size = c + 1;
						ret.m_Text = tr("'>' Missing.");
						return ret;
					}

					ch2 = p_Text.at(c + 1);
					if (ch2 == '>')
					{
						ret.m_Size = lastElementFound - ret.m_Position;
						return ret;
					}
					else
					{
						ret.m_Type = Error;
						ret.m_Size = c + 1;
						ret.m_Text = tr("'>' Missing.");
						return ret;
					}
				}

				if (ch == '<')
				{
					child = ParseCFCode(p_Text, c, CFComment);
					if (child.m_Type == Error)
					{
						return child;
					}
					ret.m_ChildElements.append(child);
					lastElementFound = child.m_Position + child.m_Size;
					c = child.m_Position + child.m_Size;
					continue;
				}

				if ((index + l_NotOperatorFirst) % 2 == 0)
				{
					if ((ch == '\"')||(ch == '\"'))
						child = ParseCFCode(p_Text, c, String);
					else if (((ch >= '0')&&(ch <= '9'))||(ch == '-')||(ch == '+'))
						child = ParseCFCode(p_Text, c, Number);
					else if (ch == '#')
						child = ParseCFCode(p_Text, c, SharpExpression);
					else
						child = ParseCFCode(p_Text, c, Variable);
				}
				else
				{
					child = ParseCFCode(p_Text, c, Operator);
					if (child.m_Type == Error)
					{
						ret.m_Size = lastElementFound - ret.m_Position;
						return ret;
					}
				}

				if ((index == 0)&&(child.m_Type == Operator)&&(child.m_Text == "NOT"))
				{
					l_NotOperatorFirst = 1;
				}

				if (child.m_Type == Error)
				{
					return child;
				}

				if (((index+l_NotOperatorFirst) % 2 == 1)&&(child.m_Type != Operator))
				{
					child = ret.m_ChildElements.last();
					ret.m_Size = (child.m_Position + child.m_Size) - ret.m_Position;
					break;
				}
				ret.m_ChildElements.append(child);
				lastElementFound = child.m_Position + child.m_Size;
				c = child.m_Position + child.m_Size;
				index++;
			}

			ret.m_Type = Error;
			ret.m_Position = p_Text.length();
			ret.m_Text = tr("cftag not closed.");
			break;
		case Variable:
			for (int c = l_Offset; c < p_Text.length(); c++)
			{
				ch = p_Text.at(c);

				if ((l_Offset == c)&&(((ch >= '0')&&(ch <= '9'))||(ch == '-')||(ch == '+')))
				{
					return ParseCFCode(p_Text, l_Offset, Number);
				}

				if ((l_Offset == c)&&((ch == '*')||(ch == '/')||(ch == '&')||(ch == '=')))
				{
					return ParseCFCode(p_Text, l_Offset, Operator);
				}

				if (ch =='(')
				{
					return ParseCFCode(p_Text, l_Offset, Function);
				}

				if ((l_Offset == c)&&((ch =='\'')||(ch =='\"')))
				{
					return ParseCFCode(p_Text, l_Offset, String);
				}

				if (ch == '[')
				{
					child = ParseCFCode(p_Text, c, VariableIndex);

					if (child.m_Type == Error)
					{
						return child;
					}

					ret.m_Text = p_Text.mid(l_Offset, c - l_Offset);
					ret.m_Size = child.m_Position + child.m_Size - ret.m_Position;
					ret.m_ChildElements.append(child);
					return ret;
				}

				if ((ch == ' ')||(ch == '\'')||(ch == '\"')||(ch == '=')||(ch == '&')||(ch == '#')||(ch == '>')||(ch == '/')||(ch == ')')||(ch == ']')||(ch == ',')) // TODO: Add other operators
				{
					if (c - l_Offset == 0)
					{
						ret.m_Type = Error;
						ret.m_Position = c;
						ret.m_Size = 1;
						ret.m_Text = tr("Invalid variable name.");
						return ret;
					}
					ret.m_Position = l_Offset;
					ret.m_Size = c - l_Offset;
					ret.m_Text = p_Text.mid(l_Offset, c - l_Offset);
					if (
							(ret.m_Text.compare("eq", Qt::CaseInsensitive) == 0)||
							(ret.m_Text.compare("neq", Qt::CaseInsensitive) == 0)||
							(ret.m_Text.compare("gt", Qt::CaseInsensitive) == 0)||
							(ret.m_Text.compare("gte", Qt::CaseInsensitive) == 0)||
							(ret.m_Text.compare("lt", Qt::CaseInsensitive) == 0)||
							(ret.m_Text.compare("lte", Qt::CaseInsensitive) == 0)||
							(ret.m_Text.compare("not", Qt::CaseInsensitive) == 0)
						)
					{
						ret.m_Type = Operator;
					}
					return ret;
				}
			}
			ret.m_Type = Error;
			ret.m_Size = 1;
			ret.m_Text = tr("Variable name not set.");
			break;
		case Number:
			bool comma;
			int signOffset;

			ch = p_Text.at(l_Offset);
			if (((ch < '0')||(ch > '9'))&&(ch !='-')&&(ch !='+'))
			{
				ret.m_Type = Error;
				ret.m_Position = l_Offset;
				ret.m_Text = tr("Element not number.");
				return ret;
			}

			comma = false;
			signOffset = l_Offset;

			for (int c = l_Offset; c < p_Text.length(); c++)
			{
				ch = p_Text.at(c);

				if ((c == signOffset)&&((ch == '-')||(ch == '+')))
				{
					continue;
				}

				if ((ch == '.')&&(comma == false))
				{
					comma = true;
					continue;
				}

				if ((ch < '0')||(ch > '9'))
				{
					ret.m_Size = c - l_Offset;
					ret.m_Text = p_Text.mid(l_Offset, c - l_Offset);
					if ((ret.m_Text == "-")||(ret.m_Text == "+"))
					{
						ret.m_Type = Operator;
					}
					return ret;
				}
			}
			ret.m_Type = Error;
			break;
		case String:
			char stringType;
			stringType = 0;

			for (int c = l_Offset; c < p_Text.length(); c++)
			{
				ch = p_Text.at(c);

				if (c == l_Offset)
				{
					stringType = ch.toLatin1();

					if ((ch != '\'')&&(ch != '\"'))
					{
						ret.m_Type = Error;
						ret.m_Text = tr("String not start with ['] or [\"].");
						return ret;
					}
				}
				else
				{
					if (ch == '#')
					{
						if (p_Text.length() <= c)
						{
							ret.m_Type = Error;
							ret.m_Position = c;
							ret.m_Size = 1;
							ret.m_Text = tr("# not closed.");
							return ret;
						}

						if (p_Text.at(c + 1) == '#')
						{
							str.append(ch);
							c++;
							continue;
						}
						else
						{
							if (!str.isEmpty())
							{
								child = QCFParserElement();
								child.m_Type = String;
								child.m_Text = str;
								ret.m_ChildElements.append(child);
								str.clear();
							}
							child = ParseCFCode(p_Text, c, SharpExpression);
							ret.m_ChildElements.append(child);
							c = child.m_Position + child.m_Size - 1;
						}
					}
					else
					{
						if (ch == stringType)
						{
							ret.m_Size = c - l_Offset + 1;

							if (ret.m_ChildElements.count() == 0)
							{
								ret.m_Text = str;
							}
							else
							{
								ret.m_Text = "";
								if (!str.isEmpty())
								{
									child = QCFParserElement();
									child.m_Type = String;
									child.m_Text = str;
									ret.m_ChildElements.append(child);
								}
							}

							if (ret.m_Text != "")
							{
								bool l_bool;
								ret.m_Text.toDouble(&l_bool);
								if (l_bool)
								{
									ret.m_Type = Number;
								}
							}

							return ret;
						}
						str.append(ch);
					}
				}
			}
			ret.m_Type = Error;
			ret.m_Size = 1;
			ret.m_Text = tr("String not finished.");
			break;
		case Operator:
			ch = p_Text.at(l_Offset);

			if ((ch == '=')||(ch == '&')||(ch == '*')||(ch == '/')||(ch == '+')||(ch == '-')||(ch == '.')) // TODO: Add more operator strings.
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 1;
				ret.m_Text = ch;
				break;
			}

			if (p_Text.mid(l_Offset, 2).compare("eq", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 2;
				ret.m_Text = p_Text.mid(l_Offset, 2).toUpper();
				break;
			}

			if (p_Text.mid(l_Offset, 3).compare("neq", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 3;
				ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
				break;
			}

			if (p_Text.mid(l_Offset, 3).compare("and", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 3;
				ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
				break;
			}

			if (p_Text.mid(l_Offset, 2).compare("or", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 2;
				ret.m_Text = p_Text.mid(l_Offset, 2).toUpper();
				break;
			}

			if (p_Text.mid(l_Offset, 2).compare("is", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 2;
				ret.m_Text = p_Text.mid(l_Offset, 2).toUpper();
				break;
			}

			if (p_Text.mid(l_Offset, 6).compare("is not", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 6;
				ret.m_Text = p_Text.mid(l_Offset, 6).toUpper();
				break;
			}

			if (p_Text.mid(l_Offset, 8).compare("contains", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 8;
				ret.m_Text = p_Text.mid(l_Offset, 8).toUpper();
				break;
			}

			if (p_Text.mid(l_Offset, 16).compare("does not contain", Qt::CaseInsensitive) == 0)
			{
				ret.m_Position = l_Offset;
				ret.m_Size = 16;
				ret.m_Text = p_Text.mid(l_Offset, 16).toUpper();
				break;
			}

			ret.m_Type = Error;
			break;
		case SharpExpression:
			if (p_Text.at(l_Offset) != '#')
			{
				ret.m_Type = Error;
				ret.m_Position = l_Offset;
				ret.m_Text = tr("SharpExpression doesn't start with '#'.");
				break;
			}

			child = ParseCFCode(p_Text, l_Offset + 1, Expression);
			if (child.m_Type == Error)
			{
				ret = child;
				break;
			}

			if (p_Text.at(l_Offset + child.m_Size + 1) != '#')
			{
				ret.m_Type = Error;
				ret.m_Position = l_Offset;
				ret.m_Text = tr("SharpExpression doesn't end with '#'.");
				break;
			}

			ret.m_Size = child.m_Size + 2;
			ret.m_ChildElements.append(child);
			break;
		case Expression:
			int c;
			char nextch;

			ret.m_Position = p_Offset;
			c = l_Offset;

			ret.m_Size = 0;

			while( c < p_Text.length())
			{
				if (TrimCFCode(p_Text, c))
				{
					ret.m_Type = Error;
					ret.m_Position = l_Offset - 1;
					ret.m_Text = tr("End of file found.");
					return ret;
				}

				ch = p_Text.at(c);
				if(c + 1 < p_Text.length())
				{
					nextch = p_Text.at(c + 1).toLatin1();
				}
				else
				{
					nextch = 0;
				}

				if ((ch == ']'))
				{
					ret.m_Size = c - p_Offset;
					break;
				} else if (ch == ',') {
					ret.m_Size = c - p_Offset;
					break;
				} else if (ch == ')') {
					ret.m_Size = c - p_Offset;
					break;
				} else if (ch == '#') {
					ret.m_Size = c - p_Offset;
					break;
				} else if (((ch == '/')&&(nextch == '>'))||(ch == '>')) {
					ret.m_Size = c - p_Offset;
					break;
				} else if (ch == '(') {
					child = ParseCFCode(p_Text, c, SubExpression);
					if (child.m_Type == Error)
					{
						return child;
					}
					ret.m_ChildElements.append(child);
					c = child.m_Position + child.m_Size;
				}
				else
				{
					child = ParseCFCode(p_Text, c, Variable);
					if (child.m_Type == Error)
					{
						return child;
					}
					ret.m_ChildElements.append(child);
					c = child.m_Position + child.m_Size;
				}
            }
	    break;
	case SubExpression:
		if (p_Text.at(l_Offset) != '(')
		{
			ret.m_Type = Error;
			ret.m_Position = l_Offset;
			ret.m_Text = tr("SubExpression doesn\'t start with '('.");
			break;
		}

		child = ParseCFCode(p_Text, l_Offset + 1, Expression);
		if (child.m_Type == Error)
		{
			ret = child;
			break;
		}

		if (p_Text.at(l_Offset + child.m_Size + 1) != ')')
		{
			ret.m_Type = Error;
			ret.m_Position = l_Offset;
			ret.m_Text = tr("SubExpression doesn\'t end with ')'.");
			break;
		}

		ret.m_Size = child.m_Size + 2;
		ret.m_ChildElements.append(child);
		break;
	case Function:
		c = p_Text.indexOf('(', l_Offset);
		if (c == -1)
		{
			ret.m_Type = Error;
			ret.m_Text = tr("Can\'t find '(' in function.");
			ret.m_Position = p_Text.length();
			ret.m_Size = 1;
			return ret;
		}
		if (c + 1 >= p_Text.length())
		{
			ret.m_Type = Error;
			ret.m_Text = tr("Unfinished function.");
			ret.m_Position = p_Text.length();
			ret.m_Size = 1;
			return ret;
		}

		child = ParseCFCode(p_Text, c, Parameters);
		if (child.m_Type == Error)
		{
			return child;
		}

		ret.m_ChildElements.append(child);
		ret.m_Text = p_Text.mid(l_Offset, c - l_Offset);
		ret.m_Position = l_Offset;
		ret.m_Size = c - l_Offset + child.m_Size;
		break;
	case Parameters:
		c = l_Offset;
		for(;;)
		{
			ch = p_Text.at(c);

			if (ch == ')')
			{
				ret.m_Size = c - ret.m_Position + 1;
				break;
			}

			c++;

			if (p_Text.length() <= c)
			{
				ret.m_Type = Error;
				ret.m_Position = p_Text.length();
				ret.m_Text = tr("Parametar not finished.");
				return ret;
			}


			child = ParseCFCode(p_Text, c, Parameter);

			if (child.m_Type == Error)
			{
				ret = child;
				break;
			}

			c = child.m_Position + child.m_Size;

			if (p_Text.length() <= c)
			{
				ret.m_Type = Error;
				ret.m_Position = p_Text.length();
				ret.m_Text = tr("Parametar not finished.");
				return ret;
			}

			ret.m_ChildElements.append(child);
		}
		break;
	case Parameter:
		child = ParseCFCode(p_Text, l_Offset, Expression);
		if (child.m_Type == Error)
		{
			return child;
		}
		ret.m_Size = child.m_Size;
		ret.m_ChildElements.append(child);
		break;
	case VariableIndex:
		ch = p_Text.at(l_Offset);
		if (ch != '[')
		{
			ret.m_Size = 1;
			ret.m_Text = tr("Element not variableIndex(Does\'t begin with '[').");
			ret.m_Type = Error;
			return ret;
		}

		child = ParseCFCode(p_Text, l_Offset + 1, Expression);
		if (child.m_Type == Error)
		{
			return child;
		}

		if (p_Text.at(child.m_Position + child.m_Size) != ']') // TODO: Check for end.
		{
			ret.m_Position = child.m_Position + child.m_Size;
			ret.m_Size = 1;
			ret.m_Text = tr("Element not variableIndex(Doesn\'t end with ']').");
			ret.m_Type = Error;
			return ret;
		}

		ret.m_ChildElements.append(child);
		ret.m_Size = child.m_Size + 2;
		break;
	case CFComment:
		ret.m_Size = FindCFCommentSize(p_Text, l_Offset);
		if (ret.m_Size <= 0)
		{
			ret.m_Type = Error;
			ret.m_Text = tr("ColdFusion comment not closed.");
		}
		break;
	default:
		ret.m_Type = Error;
		ret.m_Position = l_Offset;
		ret.m_Text = tr("Not implemented.");
		break;
	}

#ifdef QT_DEBUG
	if ((ret.m_Position > p_Text.length())||(ret.m_Position < l_Offset))
	{
		qDebug() << tr("Bad position %1.").arg(ret.m_Position);
	}
#endif

	return ret;
}

QString QCFParser::getError()
{
	return m_Error;
}

const QString& QCFParser::getText()
{
	return m_Text;
}

quint32 QCFParser::getErrorPosition()
{
	return m_ErrorPosition;
}

quint32 QCFParser::FindCFCommentSize(QString p_Text, const quint32 p_Position) /* Done */
{
	quint32 begCFComment, endCFComment, pos, reqPos;

	pos = p_Position;

	if (p_Text.mid(pos, 5) != "<!---")
		return 0;

	pos += 5;

	for (; ; )
    {
		begCFComment = p_Text.indexOf("<!---", pos, Qt::CaseInsensitive);
		endCFComment = p_Text.indexOf("--->", pos, Qt::CaseInsensitive);

		if ((begCFComment == 0xFFFFFFFF)&&(endCFComment == 0xFFFFFFFF))
			return begCFComment;

		if (endCFComment < begCFComment)
			return endCFComment + 4 - p_Position;

		reqPos = FindCFCommentSize(p_Text, begCFComment);

		if (reqPos == 0xFFFFFFFF)
			return reqPos;

		pos = begCFComment + reqPos;
	}
}

QCFParserErrorType QCFParser::Parse(const QString& p_Text, bool* p_Terminate)
{
	m_Text = p_Text;
	m_Tags.clear();
	m_Error.clear();
	m_ErrorPosition = 0;	

	qint32 l_CodeInside = 0;
	quint32 pos = 0, cf_pos = 0, cf_epos = 0, cf_comment = 0, cf_expression = 0;

	for (; ; )
	{
		// For multithread applications. Set p_Terminate to true to stop parsing.
		if ((p_Terminate != NULL)&&(*p_Terminate == true))
			return ForcedTerminationError;

		if (cf_pos <= pos)
			cf_pos = p_Text.indexOf("<cf", pos, Qt::CaseInsensitive);
		if (cf_epos <= pos)
			cf_epos = p_Text.indexOf("</cf", pos, Qt::CaseInsensitive);
		if (cf_comment <= pos)
			cf_comment = p_Text.indexOf("<!---", pos, Qt::CaseSensitive);
		if ((l_CodeInside > 0)&&(cf_expression <= pos))
			cf_expression = p_Text.indexOf("#", pos, Qt::CaseSensitive);


		if ((cf_pos == 0xFFFFFFFF) && (cf_epos == 0xFFFFFFFF) && (cf_comment == 0xFFFFFFFF) && ((cf_expression == 0xFFFFFFFF)||(l_CodeInside <= 0)))
			break; // No more ColdFusion tags remaining.

		if ((l_CodeInside > 0)&&(cf_expression < cf_pos)&&(cf_expression < cf_epos)&&(cf_expression < cf_comment))
		{
			QCFParserElement el = ParseCFCode(p_Text, cf_expression, SharpExpression);

			if (el.m_Type == Error)
			{
				this->m_Error = el.m_Text;
				this->m_ErrorPosition = el.m_Position;

				return ParsingError;
			}

			if (el.m_Size > 2)
			{
				QCFParserTag l_codeTag;
				l_codeTag.m_TagType = ExpressionTagType;
				l_codeTag.m_Arguments = el;
				l_codeTag.m_Start = el.m_Position;
				l_codeTag.m_Length = el.m_Size;

				m_Tags.append(l_codeTag);
			}

			pos = el.m_Position + el.m_Size;
			continue;
		}

		if ((cf_pos < cf_epos)&&(cf_pos < cf_comment)) // If <cf tag is the closes one.
		{

			quint32 endName, endNameTemp;

			endName = p_Text.indexOf(' ', cf_pos + 3, Qt::CaseInsensitive);

			endNameTemp = p_Text.indexOf('\r', cf_pos + 3, Qt::CaseInsensitive);
			if (endNameTemp < endName)
				endName = endNameTemp;

			endNameTemp = p_Text.indexOf('\n', cf_pos + 3, Qt::CaseInsensitive);
			if (endNameTemp < endName)
				endName = endNameTemp;

			endNameTemp = p_Text.indexOf('\t', cf_pos + 3, Qt::CaseInsensitive);
			if (endNameTemp < endName)
				endName = endNameTemp;

			endNameTemp = p_Text.indexOf('/', cf_pos + 3, Qt::CaseInsensitive);
			if (endNameTemp < endName)
				endName = endNameTemp;

			endNameTemp = p_Text.indexOf('>', cf_pos + 3, Qt::CaseInsensitive);
			if (endNameTemp < endName)
				endName = endNameTemp;

			if (endName == 0xFFFFFFFF)
			{
				m_Error = tr("ColdFusion tag not closed.");
				m_ErrorPosition = cf_pos;
				return ParsingError;
			}
			QCFParserTag openTag;
			openTag.m_TagType = CFTagType;
			openTag.m_Start = cf_pos;
			//openTag.m_StartLine = linesCount;
			//openTag.m_StartColumn = cf_pos - currentLineIndex;
			openTag.m_Name = p_Text.mid(cf_pos + 1, endName - cf_pos - 1).toLower();
			openTag.m_EndTag = 0;
			if ((m_CFTagsDef.contains(openTag.m_Name))&&(m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeExpression))
			{
				openTag.m_Arguments = ParseCFCode(p_Text, endName, CFTagExpression);
			} else {
				openTag.m_Arguments = ParseCFCode(p_Text, endName, CFTagArguments);
			}

			if (openTag.m_Arguments.m_Type == Error)
			{
				this->m_Error = openTag.m_Arguments.m_Text;
				this->m_ErrorPosition = openTag.m_Arguments.m_Position;

				return ParsingError;
			}
			openTag.m_Length = (openTag.m_Arguments.m_Position + openTag.m_Arguments.m_Size) - cf_pos;

			int c;
			for(c = 0; openTag.m_Start + openTag.m_Length + c < p_Text.length(); c++)
			{
				if (p_Text.at(openTag.m_Start + openTag.m_Length + c) != ' ')
				{
					break;
				}
			}

			if (openTag.m_Start + openTag.m_Length + c < p_Text.length())
			{
				if (p_Text[openTag.m_Start + openTag.m_Length + c] == '/')
				{
					openTag.m_InlineClosedTag = true;
					openTag.m_Length = openTag.m_Length + c + 2;
				} else {
					openTag.m_InlineClosedTag = false;
					openTag.m_Length = openTag.m_Length + c + 1;
				}
			} else {
			}

			if ((openTag.m_Name.left(3).compare("cf_", Qt::CaseInsensitive))&&(openTag.m_Name.left(4).compare("cfx_", Qt::CaseInsensitive)))
			{
				if (!m_CFTagsDef.contains(openTag.m_Name))
				{
					m_Error = tr("Unknown cftag '%1'.").arg(openTag.m_Name);
					m_ErrorPosition = cf_pos;
					return ParsingError;
				}

				// TODO: Add parameters check.
				if (openTag.m_Arguments.m_Size > 0)
				{
					if ((m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeArguments)&&(openTag.m_Arguments.m_Type != CFTagArguments))
					{
						m_Error = tr("Arguments for cftag '%1' must be key/value pair.").arg(openTag.m_Name);
						m_ErrorPosition = cf_pos;
						return ParsingError;
					}

					if ((m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeExpression)&&(openTag.m_Arguments.m_ChildElements.size() > 1))
					{
						m_Error = tr("cftag '%1' can't have more than one expression inside.").arg(openTag.m_Name);
						m_ErrorPosition = cf_pos;
						return ParsingError;
					}

					if ((m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeExpression)&&(openTag.m_Arguments.m_ChildElements.size() == 1))
					{
						QCFParserElement temp = openTag.m_Arguments.m_ChildElements[0];
						temp.m_Type = Expression;
						openTag.m_Arguments = temp;
					}
				}
			}

			m_Tags.append(openTag);

			if ((openTag.m_Name.left(3).compare("cf_", Qt::CaseInsensitive))&&(openTag.m_Name.left(4).compare("cfx_", Qt::CaseInsensitive)))
			{
				if (this->m_CFTagsDef.contains(openTag.m_Name))
				{
					if (this->m_CFTagsDef[openTag.m_Name].m_ExpressionInside == QCFTag::WithExpressionInside)
					{
						l_CodeInside++;
					}
				}
				else
				{
					m_Error = tr("Unknown cftag '%1'.").arg(openTag.m_Name);
					m_ErrorPosition = cf_pos;
					return ParsingError;
				}
			}

			pos = endName + openTag.m_Arguments.m_Size;

		}
		else if ((cf_epos < cf_pos)&&(cf_epos < cf_comment)) // If </cf tag is the closes one.
		{
			qint32 cf_endtag = p_Text.indexOf('>', cf_epos, Qt::CaseSensitive);
			if (cf_endtag == -1)
			{
				m_Error = tr("Tag not closed. Missing '>'");
				m_ErrorPosition = cf_epos + 1;
				return ParsingError;
			}

			QCFParserTag closeTag;

			closeTag.m_Start = cf_epos;
			closeTag.m_Length = cf_endtag - cf_epos + 1;
			closeTag.m_TagType = EndCFTagType;
			closeTag.m_Name = p_Text.mid(cf_epos + 2, cf_endtag - cf_epos - 2).toLower();
			closeTag.m_Arguments = ParseCFCode(p_Text, cf_endtag, CFTagArguments);
			closeTag.m_InlineClosedTag = false;
			closeTag.m_EndTag = -1;

			m_Tags.append(closeTag);

			if ((closeTag.m_Name.left(3).compare("cf_", Qt::CaseInsensitive))&&(closeTag.m_Name.left(4).compare("cfx_", Qt::CaseInsensitive)))
			{
				if (this->m_CFTagsDef.contains(closeTag.m_Name))
				{
					if (this->m_CFTagsDef[closeTag.m_Name].m_ExpressionInside == QCFTag::WithExpressionInside)
					{
						l_CodeInside--;
					}
				}
				else
				{
					m_Error = tr("Unknown cftag '%1'.").arg(closeTag.m_Name);
					m_ErrorPosition = cf_pos;
					return ParsingError;
				}
			}

			pos = cf_endtag + 1;

		}
		else if ((cf_comment < cf_pos)&&(cf_comment < cf_epos)) // If <!--- tag is the closes one.
		{
			QCFParserTag commentTag;

			commentTag.m_Start = cf_comment;
			commentTag.m_Length = FindCFCommentSize(p_Text, cf_comment);
			if (commentTag.m_Length == -1)
			{
				m_Error = tr("The closing tag for the CFML comment is missing. Comment begins on line %1.").arg(GetLineNumberFromPosition(p_Text, cf_comment));
				m_ErrorPosition = p_Text.size();
				return ParsingError;
			}
			commentTag.m_TagType = CommentTagType;
			commentTag.m_Name = p_Text.mid(cf_comment + 5, commentTag.m_Length - 9).trimmed();
			commentTag.m_Arguments = QCFParserElement();
			commentTag.m_Arguments.m_Position = 0;
			commentTag.m_Arguments.m_Size = 0;
			commentTag.m_Arguments.m_Text = "";
			commentTag.m_Arguments.m_Type = Error;
			commentTag.m_InlineClosedTag = false;
			commentTag.m_EndTag = -1;

			m_Tags.append(commentTag);

			pos = commentTag.m_Start + commentTag.m_Length + 1;
		}
	}

	return BuildTagTree();
}

QCFParserErrorType QCFParser::BuildTagTree()
{
	QList<quint32> nestedList;
	bool Found;

	for (qint32 c = 0; c < m_Tags.size(); c++)
	{
		switch(m_Tags[c].m_TagType)
		{
		case CFTagType:
			if (m_Tags[c].m_InlineClosedTag == false)
				nestedList.append(c);
			break;
		case EndCFTagType:
			Found = false;

			while(nestedList.size() > 0)
			{
				quint32 last = nestedList.takeLast();
				if (m_Tags[c].m_Name == m_Tags[last].m_Name)
				{
					m_Tags[last].m_EndTag = c;
					Found = true;
					break;
				}
			}

			if (Found == false)
			{
				m_Error = tr("Invalid closetag '%1'.").arg(m_Tags[c].m_Name);
				m_ErrorPosition = m_Tags[c].m_Start;
				return InvalidCloseTagError;
			}

			break;
		default:
			break;
		}
	}
	return NoError;
}

QList<QCFParserTag> QCFParser::getTags()
{
	return m_Tags;
}
