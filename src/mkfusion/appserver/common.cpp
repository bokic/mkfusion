#include "common.h"
#include "qwddx.h"
#include <QString>
#include <QFile>


void log(const QString &p_filename, const QString &p_Line)
{
	QFile l_Log(p_filename);
	l_Log.open(QIODevice::WriteOnly	| QIODevice::Append);
#ifdef Q_OS_WIN
	l_Log.write(p_Line.toUtf8() + "\r\n");
#elif defined Q_OS_LINUX
	l_Log.write(p_Line.toUtf8() + "\n");
#else
#error Windows and Linux OSs are currently supported.
#endif
	l_Log.close();
}

QString cfdump_var(const QWDDX& p_Variable)
{
	QString ret;

	QWDDX l_temp = p_Variable;
	switch(l_temp.getType())
	{
		case QWDDX::Boolean:
		case QWDDX::DateTime:
		case QWDDX::Number:
		case QWDDX::String:
			ret = l_temp.toString();
			break;
		case QWDDX::Struct:
			ret = "<table class=\"cfdump_struct\"><tr><th class=\"struct\" colspan=\"2\" onClick=\"cfdump_toggleTable(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">struct</th></tr>\n";

			foreach(QString l_key, l_temp.m_Struct.keys())
			{
				ret += "<tr><td class=\"struct\" onClick=\"cfdump_toggleRow(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">" + l_key + "</td><td>" + cfdump_var(l_temp.m_Struct[l_key]) + "</td></tr>\n";
			}

			ret += "</table>\n";
			break;
		case QWDDX::Array:
			ret = "<table class=\"cfdump_array\"><tr><th class=\"array\" colspan=\"2\" onClick=\"cfdump_toggleTable(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">array</th></tr>\n";

			for(int i = 0; i < p_Variable.m_Array.size(); i++)
			{
				ret += "<tr><td class=\"array\" onClick=\"cfdump_toggleRow(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">" + QString::number(i + 1) + "</td><td>" + cfdump_var(l_temp.m_Array[i]) + "</td></tr>\n";
			}

			ret += "</table>\n";
			break;
		default:
			return "";
	}

	return ret;
}

QString mk_cfdump(const QWDDX& p_Variable)
{
	QString ret;

	ret = "<style type=\"text/css\">\n" \
		  "	table.cfdump_wddx,\n" \
		  "	table.cfdump_xml,\n" \
		  "	table.cfdump_struct,\n" \
		  "	table.cfdump_array,\n" \
		  "	table.cfdump_query,\n" \
		  "	table.cfdump_cfc,\n" \
		  "	table.cfdump_object,\n" \
		  "	table.cfdump_binary,\n" \
		  "	table.cfdump_udf,\n" \
		  "	table.cfdump_udfbody,\n" \
		  "	table.cfdump_udfarguments {\n" \
		  "		font-size: xx-small;\n" \
		  "		font-family: verdana, arial, helvetica, sans-serif;\n" \
		  "		cell-spacing: 2px;\n" \
		  "	}\n" \
		  "	table.cfdump_wddx th,\n" \
		  "	table.cfdump_xml th,\n" \
		  "	table.cfdump_struct th,\n" \
		  "	table.cfdump_array th,\n" \
		  "	table.cfdump_query th,\n" \
		  "	table.cfdump_cfc th,\n" \
		  "	table.cfdump_object th,\n" \
		  "	table.cfdump_binary th,\n" \
		  "	table.cfdump_udf th,\n" \
		  "	table.cfdump_udfbody th,\n" \
		  "	table.cfdump_udfarguments th {\n" \
		  "		text-align: left;\n" \
		  "		color: white;\n" \
		  "		padding: 5px;\n" \
		  "	} \n" \
		  "	table.cfdump_wddx td,\n" \
		  "	table.cfdump_xml td,\n" \
		  "	table.cfdump_struct td,\n" \
		  "	table.cfdump_array td,\n" \
		  "	table.cfdump_query td,\n" \
		  "	table.cfdump_cfc td,\n" \
		  "	table.cfdump_object td,\n" \
		  "	table.cfdump_binary td,\n" \
		  "	table.cfdump_udf td,\n" \
		  "	table.cfdump_udfbody td,\n" \
		  "	table.cfdump_udfarguments td {\n" \
		  "		padding: 3px;\n" \
		  "		background-color: #ffffff;\n" \
		  "		vertical-align : top;\n" \
		  "	} \n" \
		  "	table.cfdump_wddx {\n" \
		  "		background-color: #000000;\n" \
		  "	}\n" \
		  "	table.cfdump_wddx th.wddx {\n" \
		  "		background-color: #444444;\n" \
		  "	}  \n" \
		  "	table.cfdump_xml {\n" \
		  "		background-color: #888888;\n" \
		  "	}\n" \
		  "	table.cfdump_xml th.xml {\n" \
		  "		background-color: #aaaaaa;\n" \
		  "	}\n" \
		  "	table.cfdump_xml td.xml {\n" \
		  "		background-color: #dddddd;\n" \
		  "	} \n" \
		  "	table.cfdump_struct {\n" \
		  "		background-color: #0000cc ;\n" \
		  "	}\n" \
		  "	table.cfdump_struct th.struct {\n" \
		  "		background-color: #4444cc ;\n" \
		  "	}\n" \
		  "	table.cfdump_struct td.struct {\n" \
		  "		background-color: #ccddff;\n" \
		  "	} \n" \
		  "	table.cfdump_array {\n" \
		  "		background-color: #006600 ;\n" \
		  "	}\n" \
		  "	table.cfdump_array th.array {\n" \
		  "		background-color: #009900 ;\n" \
		  "	}\n" \
		  "	table.cfdump_array td.array {\n" \
		  "		background-color: #ccffcc ;\n" \
		  "	} \n" \
		  "	table.cfdump_query {\n" \
		  "		background-color: #884488 ;\n" \
		  "	}\n" \
		  "	table.cfdump_query th.query {\n" \
		  "		background-color: #aa66aa ;\n" \
		  "	}\n" \
		  "	table.cfdump_query td.query {\n" \
		  "		background-color: #ffddff ;\n" \
		  "	}\n" \
		  "	table.cfdump_cfc {\n" \
		  "		background-color: #ff0000;\n" \
		  "	}\n" \
		  "	table.cfdump_cfc th.cfc{\n" \
		  "		background-color: #ff4444;\n" \
		  "	}\n" \
		  "	table.cfdump_cfc td.cfc {\n" \
		  "		background-color: #ffcccc;\n" \
		  "	}\n" \
		  "	table.cfdump_object {\n" \
		  "		background-color : #ff0000;\n" \
		  "	}\n" \
		  "	table.cfdump_object th.object{\n" \
		  "		background-color: #ff4444;\n" \
		  "	}\n" \
		  "	table.cfdump_binary {\n" \
		  "		background-color : #eebb00;\n" \
		  "	}\n" \
		  "	table.cfdump_binary th.binary {\n" \
		  "		background-color: #ffcc44;\n" \
		  "	}\n" \
		  "	table.cfdump_binary td {\n" \
		  "		font-size: x-small;\n" \
		  "	}\n" \
		  "	table.cfdump_udf {\n" \
		  "		background-color: #aa4400;\n" \
		  "	}\n" \
		  "	table.cfdump_udf th.udf {\n" \
		  "		background-color: #cc6600;\n" \
		  "	}\n" \
		  "	table.cfdump_udfarguments {\n" \
		  "		background-color: #dddddd;\n" \
		  "		cell-spacing: 3;\n" \
		  "	}\n" \
		  "	table.cfdump_udfarguments th {\n" \
		  "		background-color: #eeeeee;\n" \
		  "		color: #000000;\n" \
		  "	} \n" \
		  "	</style>\n" \
		  "	<script language=\"javascript\" type=\"text/javascript\">\n" \
		  "		var expand = \"open\";\n" \
		  "	\n" \
		  "		dump = function( obj ) {\n" \
		  "			var out = \"\" ;\n" \
		  "			if ( typeof obj == \"object\" ) {\n" \
		  "				for ( key in obj ) {\n" \
		  "					if ( typeof obj[key] != \"function\" ) out += key + ': ' + obj[key] + '<br>' ;\n" \
		  "				}\n" \
		  "			}\n" \
		  "		}\n" \
		  "	\n" \
		  "		cfdump_toggleRow = function(source) {\n" \
		  "			//target is the right cell\n" \
		  "			if(document.all) target = source.parentElement.cells[1];\n" \
		  "			else {\n" \
		  "				var element = null;\n" \
		  "				var vLen = source.parentNode.childNodes.length;\n" \
		  "				for(var i=vLen-1;i>0;i--){\n" \
		  "					if(source.parentNode.childNodes[i].nodeType == 1){\n" \
		  "						element = source.parentNode.childNodes[i];\n" \
		  "						break;\n" \
		  "					}\n" \
		  "				}\n" \
		  "				if(element == null)\n" \
		  "					target = source.parentNode.lastChild;\n" \
		  "				else\n" \
		  "					target = element;\n" \
		  "			}\n" \
		  "			//target = source.parentNode.lastChild ;\n" \
		  "			cfdump_toggleTarget( target, cfdump_toggleSource( source ) ) ;\n" \
		  "		}\n" \
		  "	\n" \
		  "		cfdump_toggleXmlDoc = function(source) {\n" \
		  "	\n" \
		  "			var caption = source.innerHTML.split( ' [' ) ;\n" \
		  "	\n" \
		  "			if ( source.style.fontStyle == 'italic' ) {\n" \
		  "				source.style.fontStyle = 'normal' ;\n" \
		  "				source.innerHTML = caption[0] + ' [short version]' ;\n" \
		  "				source.title = 'click to maximize' ;\n" \
		  "				switchLongToState = 'closed' ;\n" \
		  "				switchShortToState = 'open' ;\n" \
		  "			} else if ( source.innerHTML.indexOf('[short version]') != -1 ) {\n" \
		  "				source.innerHTML = caption[0] + ' [long version]' ;\n" \
		  "				source.title = 'click to collapse' ;\n" \
		  "				switchLongToState = 'open' ;\n" \
		  "				switchShortToState = 'closed' ;\n" \
		  "			} else {\n" \
		  "				source.style.fontStyle = 'italic' ;\n" \
		  "				source.title = 'click to expand' ;\n" \
		  "				source.innerHTML = caption[0] ;\n" \
		  "				switchLongToState = 'closed' ;\n" \
		  "				switchShortToState = 'closed' ;\n" \
		  "			}\n" \
		  "	\n" \
		  "			if(document.all) {\n" \
		  "				var table = source.parentElement.parentElement ;\n" \
		  "				for ( var i = 1; i < table.rows.length; i++ ) {\n" \
		  "					target = table.rows[i] ;\n" \
		  "					if ( i < 3 ) cfdump_toggleTarget( target, switchLongToState ) ;\n" \
		  "					else cfdump_toggleTarget( target, switchShortToState ) ;\n" \
		  "				}\n" \
		  "			} else {\n" \
		  "				var table = source.parentNode.parentNode ;\n" \
		  "				var row = 1;\n" \
		  "				for ( var i = 1; i < table.childNodes.length; i++ ) {\n" \
		  "					target = table.childNodes[i] ;\n" \
		  "					if( target.style ) {\n" \
		  "						if ( row < 3 ) {\n" \
		  "							cfdump_toggleTarget( target, switchLongToState ) ;\n" \
		  "						} else {\n" \
		  "							cfdump_toggleTarget( target, switchShortToState ) ;\n" \
		  "						}\n" \
		  "						row++;\n" \
		  "					}\n" \
		  "				}\n" \
		  "			}\n" \
		  "		}\n" \
		  "	\n" \
		  "		cfdump_toggleTable = function(source) {\n" \
		  "	\n" \
		  "			var switchToState = cfdump_toggleSource( source ) ;\n" \
		  "			if(document.all) {\n" \
		  "				var table = source.parentElement.parentElement ;\n" \
		  "				for ( var i = 1; i < table.rows.length; i++ ) {\n" \
		  "					target = table.rows[i] ;\n" \
		  "					cfdump_toggleTarget( target, switchToState ) ;\n" \
		  "				}\n" \
		  "			}\n" \
		  "			else {\n" \
		  "				var table = source.parentNode.parentNode ;\n" \
		  "				for ( var i = 1; i < table.childNodes.length; i++ ) {\n" \
		  "					target = table.childNodes[i] ;\n" \
		  "					if(target.style) {\n" \
		  "						cfdump_toggleTarget( target, switchToState ) ;\n" \
		  "					}\n" \
		  "				}\n" \
		  "			}\n" \
		  "		}\n" \
		  "	\n" \
		  "		cfdump_toggleSource = function( source ) {\n" \
		  "			if ( source.style.fontStyle == 'italic' || source.style.fontStyle == null) {\n" \
		  "				source.style.fontStyle = 'normal' ;\n" \
		  "				source.title = 'click to collapse' ;\n" \
		  "				return 'open' ;\n" \
		  "			} else {\n" \
		  "				source.style.fontStyle = 'italic' ;\n" \
		  "				source.title = 'click to expand' ;\n" \
		  "				return 'closed' ;\n" \
		  "			}\n" \
		  "		}\n" \
		  "	\n" \
		  "		cfdump_toggleTarget = function( target, switchToState ) {\n" \
		  "			if ( switchToState == 'open' )	target.style.display = '' ;\n" \
		  "			else target.style.display = 'none' ;\n" \
		  "		}\n" \
		  "	\n" \
		  "		cfdump_toggleRow_qry = function(source) {\n" \
		  "			expand = (source.title == \"click to collapse\") ? \"closed\" : \"open\";\n" \
		  "			if(document.all) {\n" \
		  "				var nbrChildren = source.parentElement.cells.length;\n" \
		  "				if(nbrChildren > 1){\n" \
		  "					for(i=nbrChildren-1;i>0;i--){\n" \
		  "						target = source.parentElement.cells[i];\n" \
		  "						cfdump_toggleTarget( target,expand ) ;\n" \
		  "						cfdump_toggleSource_qry(source);\n" \
		  "					}\n" \
		  "				}\n" \
		  "				else {\n" \
		  "					//target is the right cell\n" \
		  "					target = source.parentElement.cells[1];\n" \
		  "					cfdump_toggleTarget( target, cfdump_toggleSource( source ) ) ;\n" \
		  "				}\n" \
		  "			}\n" \
		  "			else{\n" \
		  "				var target = null;\n" \
		  "				var vLen = source.parentNode.childNodes.length;\n" \
		  "				for(var i=vLen-1;i>1;i--){\n" \
		  "					if(source.parentNode.childNodes[i].nodeType == 1){\n" \
		  "						target = source.parentNode.childNodes[i];\n" \
		  "						cfdump_toggleTarget( target,expand );\n" \
		  "						cfdump_toggleSource_qry(source);\n" \
		  "					}\n" \
		  "				}\n" \
		  "				if(target == null){\n" \
		  "					//target is the last cell\n" \
		  "					target = source.parentNode.lastChild;\n" \
		  "					cfdump_toggleTarget( target, cfdump_toggleSource( source ) ) ;\n" \
		  "				}\n" \
		  "			}\n" \
		  "		}\n" \
		  "	\n" \
		  "		cfdump_toggleSource_qry = function(source) {\n" \
		  "			if(expand == \"closed\"){\n" \
		  "				source.title = \"click to expand\";\n" \
		  "				source.style.fontStyle = \"italic\";\n" \
		  "			}\n" \
		  "			else{\n" \
		  "				source.title = \"click to collapse\";\n" \
		  "				source.style.fontStyle = \"normal\";\n" \
		  "			}\n" \
		  "		}\n" \
		  "	 </script>\n";

	return ret + cfdump_var(p_Variable);
}
