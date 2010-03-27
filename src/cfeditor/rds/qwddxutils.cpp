#include "qwddxutils.h"
#include <QHash>

QWDDXUtils::QWDDXUtils()
{
	QHash<QString, QWDDX> hash;
}

QDomNode EncodeRecursive(QDomDocument doc, QWDDX node)
{
	QDomElement ret;
	QDomText content;

	int len;

	switch(node.getType())
	{
	case QWDDX::Array:
		ret = doc.createElement("array");
		len = node.size();
		ret.setAttribute("length", QString::number(len));

		for (int c = 0; c < len; c++)
			ret.appendChild(EncodeRecursive(doc, node[c]));
		break;

	case QWDDX::Struct:
		ret = doc.createElement("struct");
		len = node.size();

		for (int c = 0; c < len; c++)
		{
			QDomElement var = doc.createElement("var");
			var.setAttribute("name", node.StructKeyAt(c));

			var.appendChild(EncodeRecursive(doc, node[c]));
			ret.appendChild(var);
		}
		break;

	case QWDDX::DateTime:
		ret = doc.createElement("dateTime");
		content = doc.createTextNode(node.toDateTime().toString("yyyy-MM-dd'T'hh:mm:ss"));
		ret.appendChild(content);
		break;

	case QWDDX::String:
		ret = doc.createElement("string");
		content = doc.createTextNode(node.toString()); // Todo: <char implementation is not done
		ret.appendChild(content);
		break;

	case QWDDX::Number:
		ret = doc.createElement("number");
		content = doc.createTextNode(QString::number(node.toNumber()));
		ret.appendChild(content);
		break;

	case QWDDX::Boolean:
		ret = doc.createElement("boolean");
		ret.setAttribute("value", node.toString());
		ret.appendChild(content);
		break;
	
	case QWDDX::Null:
		ret = doc.createElement("null");
		break;

	default:
		ret = doc.createElement("error");
	}

	return ret;
}

QString QWDDXUtils::serialize(QWDDX node)
{
	QDomDocument doc;

	QDomElement wddxPacketNode = doc.createElement("wddxPacket");
	QDomElement headerNode = doc.createElement("header");
	QDomElement dataNode = doc.createElement("data");

	dataNode.appendChild(EncodeRecursive(doc, node));

	wddxPacketNode.appendChild(headerNode);
	wddxPacketNode.appendChild(dataNode);
	wddxPacketNode.setAttribute("version", "1.0");

	doc.appendChild(wddxPacketNode);

	QString tt = doc.toString();

	return doc.toString();
}

QWDDX DecodeRecursive(QDomNode node)
{
	int c;
	QString nodeName = node.nodeName();

	if (nodeName == "struct")
	{
		QWDDX ret(QWDDX::Struct);

		for(c = 0; c < node.childNodes().count(); c++)
		{
			if (node.childNodes().at(c).nodeName() != "var")
				return QWDDX(QWDDX::Error);

			if (node.childNodes().at(c).attributes().contains("name") == false)
				return QWDDX(QWDDX::Error);

			QString key = node.childNodes().at(c).attributes().namedItem("name").nodeValue();
			ret[key] = DecodeRecursive(node.childNodes().at(c).childNodes().at(0));
		}
		return ret;
	}
	else if (nodeName == "array")
	{
		QWDDX ret(QWDDX::Array);
		int count = node.attributes().namedItem("length").nodeValue().toInt();

		for (int c = 0; c < count; c++)
		{
			ret[c] = DecodeRecursive(node.childNodes().at(c));
		}

		return ret;
	}
	else if (nodeName == "binary")
	{
		return QWDDX(QWDDX::NotImplemented);
	}
	else if (nodeName == "recordset")
	{
		return QWDDX(QWDDX::NotImplemented);
	}
	else if (nodeName == "number")
	{
		QWDDX ret;

		ret = node.childNodes().at(0).nodeValue().toDouble(); // Todo: Reimplements with for loop
		return ret;
	}
	else if (nodeName == "string")
	{
		QWDDX ret;

		ret = node.childNodes().at(0).nodeValue(); // Todo: Reimplements with for loop, adds <char /> items
		return ret;
	}
	else if (nodeName == "null")
	{
		return QWDDX(QWDDX::Null);
	}
	else if (nodeName == "dateTime")
	{
		QWDDX ret;

		ret = QDateTime::fromString(node.childNodes().at(0).nodeValue(), "yyyy-MM-dd'T'hh:mm:ss"); // Todo: Reimplements with for loop
		return ret;
	}
	else if (nodeName == "boolean")
	{
		QWDDX ret;

		if (node.childNodes().at(0).nodeValue() == "false") // Todo: Reimplements with for loop
			ret = false;
		else
			ret = true;
		return ret;
	};

	return QWDDX(QWDDX::Error);
}

QWDDX QWDDXUtils::deserialize(QString txt)
{
	QString error = "";
	QDomDocument domdoc;
	if (domdoc.setContent(txt, false) == true)
	{
		if (domdoc.childNodes().count() > 0)
		{
			QDomNode mainNode = domdoc.firstChild();
			QString ttt = mainNode.nodeName();
			if (mainNode.nodeName() == "wddxPacket")
			{
				if (mainNode.attributes().namedItem("version").nodeValue() == "1.0")
				{
					if (mainNode.childNodes().count() == 2)
					{
						QDomNode header = mainNode.childNodes().at(0);
						QDomNode data = mainNode.childNodes().at(1);

						if (data.childNodes().count() == 1)
						{
							return DecodeRecursive(data.childNodes().at(0));
						}
						else
							m_Error = "Wrong number of children in data.";
					}
					else
						m_Error = "Wrong number of children in root.";
				}
				else
					m_Error = "Wrong version.";
			}
			else
				m_Error = "wddxPacket not found";
		}
		else
			m_Error = "No Nodes";
	}
	else
		m_Error = "Parsing Error.";

	return QWDDX(QWDDX::Error);
}

QString QWDDXUtils::getLastError()
{
	return m_Error;
}
