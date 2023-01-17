#include "qwddxutils.h"
#include <QDomDocument>
#include <QDomNode>
#include <QHash>


QDomNode EncodeRecursive(QDomDocument &doc, const QWDDX &node)
{
    QDomElement ret;
    QDomText content;

    int len;

    switch(node.type())
    {
    case QWDDX::Array:
        ret = doc.createElement(QStringLiteral("array"));
        len = node.size();
        ret.setAttribute(QStringLiteral("length"), QString::number(len));

        for (int c = 0; c < len; c++)
        {
            ret.appendChild(EncodeRecursive(doc, node.at(c)));
        }
        break;

    case QWDDX::Struct:
        ret = doc.createElement(QStringLiteral("struct"));
        len = node.size();

        for (int c = 0; c < len; c++)
        {
            QDomElement var = doc.createElement(QStringLiteral("var"));
            var.setAttribute(QStringLiteral("name"), node.StructKeyAt(c));

            var.appendChild(EncodeRecursive(doc, node.at(c)));
            ret.appendChild(var);
        }
        break;

    case QWDDX::DateTime:
        ret = doc.createElement(QStringLiteral("dateTime"));
        content = doc.createTextNode(node.toDateTime().toString(QStringLiteral("yyyy-MM-dd'T'hh:mm:ss")));
        ret.appendChild(content);
        break;

    case QWDDX::String:
        ret = doc.createElement(QStringLiteral("string"));
        content = doc.createTextNode(node.toString()); // Todo: <char implementation is not done
        ret.appendChild(content);
        break;

    case QWDDX::Number:
        ret = doc.createElement(QStringLiteral("number"));
        content = doc.createTextNode(QString::number(node.toNumber()));
        ret.appendChild(content);
        break;

    case QWDDX::Boolean:
        ret = doc.createElement(QStringLiteral("boolean"));
        ret.setAttribute(QStringLiteral("value"), node.toString());
        ret.appendChild(content);
        break;

    case QWDDX::Null:
        ret = doc.createElement(QStringLiteral("null"));
        break;

    default:
        ret = doc.createElement(QStringLiteral("error"));
    }

    return ret;
}

QString QWDDXUtils::serialize(const QWDDX &node)
{
    QDomDocument doc;

    QDomElement wddxPacketNode = doc.createElement(QStringLiteral("wddxPacket"));
    QDomElement headerNode = doc.createElement(QStringLiteral("header"));
    QDomElement dataNode = doc.createElement(QStringLiteral("data"));

    dataNode.appendChild(EncodeRecursive(doc, node));

    wddxPacketNode.appendChild(headerNode);
    wddxPacketNode.appendChild(dataNode);
    wddxPacketNode.setAttribute(QStringLiteral("version"), QStringLiteral("1.0"));

    doc.appendChild(wddxPacketNode);

    return doc.toString();
}

QWDDX DecodeRecursive(const QDomNode &node)
{
    QString nodeName = node.nodeName();

    if (nodeName == QStringLiteral("struct"))
    {
        QWDDX ret(QWDDX::Struct);

        for(int c = 0; c < node.childNodes().count(); c++)
        {
            if (node.childNodes().at(c).nodeName() != QStringLiteral("var"))
                return QWDDX(QWDDX::Error);

            if (node.childNodes().at(c).attributes().contains(QStringLiteral("name")) == false)
                return QWDDX(QWDDX::Error);

            QString key = node.childNodes().at(c).attributes().namedItem(QStringLiteral("name")).nodeValue();
            ret[key] = DecodeRecursive(node.childNodes().at(c).childNodes().at(0));
        }
        return ret;
    }
    else if (nodeName == QStringLiteral("array"))
    {
        QWDDX ret(QWDDX::Array);
        int count = node.attributes().namedItem(QStringLiteral("length")).nodeValue().toInt();

        for (int c = 0; c < count; c++)
        {
            ret[c] = DecodeRecursive(node.childNodes().at(c));
        }

        return ret;
    }
    else if (nodeName == QStringLiteral("binary"))
    {
        return QWDDX(QWDDX::NotImplemented);
    }
    else if (nodeName == QStringLiteral("recordset"))
    {
        return QWDDX(QWDDX::NotImplemented);
    }
    else if (nodeName == QStringLiteral("number"))
    {
        QWDDX ret;

        ret = node.childNodes().at(0).nodeValue().toDouble(); // Todo: Reimplements with for loop
        return ret;
    }
    else if (nodeName == QStringLiteral("string"))
    {
        QWDDX ret;

        ret = node.childNodes().at(0).nodeValue(); // Todo: Reimplements with for loop, adds <char /> items
        return ret;
    }
    else if (nodeName == QStringLiteral("null"))
    {
        return QWDDX(QWDDX::Null);
    }
    else if (nodeName == QStringLiteral("dateTime"))
    {
        QWDDX ret;

        ret = QDateTime::fromString(node.childNodes().at(0).nodeValue(), QStringLiteral("yyyy-MM-dd'T'hh:mm:ss")); // Todo: Reimplements with for loop
        return ret;
    }
    else if (nodeName == QStringLiteral("boolean"))
    {
        QWDDX ret;

        if (node.childNodes().at(0).nodeValue() == QStringLiteral("false")) // Todo: Reimplements with for loop
            ret = false;
        else
            ret = true;
        return ret;
    };

    return QWDDX(QWDDX::Error);
}

QWDDX QWDDXUtils::deserialize(const QString &txt)
{
    QDomDocument domdoc;
    if (domdoc.setContent(txt, false) == true)
    {
        if (domdoc.childNodes().count() > 0)
        {
            QDomNode mainNode = domdoc.firstChild();
            if (mainNode.nodeName() == QStringLiteral("wddxPacket"))
            {
                if (mainNode.attributes().namedItem(QStringLiteral("version")).nodeValue() == QStringLiteral("1.0"))
                {
                    if (mainNode.childNodes().count() == 2)
                    {
                        //QDomNode header = mainNode.childNodes().at(0);
                        QDomNode data = mainNode.childNodes().at(1);

                        if (data.childNodes().count() == 1)
                        {
                            return DecodeRecursive(data.childNodes().at(0));
                        }
                        else
                            m_Error = QStringLiteral("Wrong number of children in data.");
                    }
                    else
                        m_Error = QStringLiteral("Wrong number of children in root.");
                }
                else
                    m_Error = QStringLiteral("Wrong version.");
            }
            else
                m_Error = QStringLiteral("wddxPacket not found");
        }
        else
            m_Error = QStringLiteral("No Nodes");
    }
    else
        m_Error = QStringLiteral("Parsing Error.");

    return QWDDX(QWDDX::Error);
}

QString QWDDXUtils::getLastError()
{
    return m_Error;
}
