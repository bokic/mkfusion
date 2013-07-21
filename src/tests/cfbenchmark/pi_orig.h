#include "qmkfusionexception.h"
#include "qcfrunningtemplate.h"
#include "qcftemplate.h"
#include "cffunctions.h"
#include "common.h"

#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

class QCFGeneratedTemplateOrig : public QCFTemplate
{
public:
    QCFGeneratedTemplateOrig()
	{
		m_isModified.m_Filename = QString::fromWCharArray(L"/var/www/pi.cfm");
		m_isModified.m_Size = 2081;
		m_isModified.m_Modified = 1374408058;
	}
	
	virtual void run(QCFRunningTemplate* p_TemplateInstance)
	{
		QCFTemplate::run(p_TemplateInstance);

// Line 85.
		m_TemplateInstance->m_VARIABLES["FINAL"] = cf_ArrayNew(QWDDX(1));

// Line 115.
		m_TemplateInstance->m_VARIABLES["TMP"] = cf_ArrayNew(QWDDX(1));

// Line 144.
		m_TemplateInstance->m_VARIABLES["PRECISION"] = QWDDX(6);

// Line 169.
		for (m_TemplateInstance->m_VARIABLES["I"] = (QWDDX(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1) {

// Line 218.
		m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = QWDDX(0);

// Line 245.
		m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] = QWDDX(0);

// Line 266.
		}

// Line 277.
		m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QWDDX(true);

// Line 306.
		m_TemplateInstance->m_VARIABLES["DIVIDER"] = QWDDX(1);

// Line 328.
		m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] = QWDDX(true);

// Line 358.
		m_TemplateInstance->m_VARIABLES["COUNTER"] = QWDDX(0);

// Line 381.
		while(m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] == QWDDX(true)) {

// Line 426.
		m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QWDDX(false);

// Line 465.
		m_TemplateInstance->m_VARIABLES["VALUE"] = QWDDX(1);

// Line 489.
		m_TemplateInstance->m_VARIABLES["REMAINING"] = QWDDX(0);

// Line 517.
		for (m_TemplateInstance->m_VARIABLES["I"] = (QWDDX(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1) {

// Line 563.
		m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] = cf_Fix(m_TemplateInstance->m_VARIABLES["VALUE"] / m_TemplateInstance->m_VARIABLES["DIVIDER"]);

// Line 604.
		if (( m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] != QWDDX(0) ) && ( m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] == QWDDX(false) )) {

// Line 658.
		m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QWDDX(true);

// Line 688.
		}

// Line 697.
		m_TemplateInstance->m_VARIABLES["VALUE"] = cf_Fix(( m_TemplateInstance->m_VARIABLES["VALUE"]%m_TemplateInstance->m_VARIABLES["DIVIDER"] ) * QWDDX(10));

// Line 749.
		}

// Line 768.
		if (m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] == QWDDX(true)) {

// Line 797.
		if (m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] == QWDDX(true)) {

// Line 828.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);

// Line 854.
		for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QWDDX(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QWDDX(-1)) {

// Line 913.
		m_TemplateInstance->m_VARIABLES["TMP_VAL"] = m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] + m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] + m_TemplateInstance->m_VARIABLES["TRANSFER"];

// Line 966.
		if (m_TemplateInstance->m_VARIABLES["TMP_VAL"] > QWDDX(9)) {

// Line 991.
		m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] - QWDDX(10);

// Line 1030.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(1);

// Line 1057.
		} else {

// Line 1071.
		m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"];

// Line 1105.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);

// Line 1132.
		}

// Line 1143.
		}

// Line 1155.
		} else {

// Line 1167.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);

// Line 1193.
		for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QWDDX(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QWDDX(-1)) {

// Line 1252.
		m_TemplateInstance->m_VARIABLES["TMP_VAL"] = m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] - m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] - m_TemplateInstance->m_VARIABLES["TRANSFER"];

// Line 1305.
		if (m_TemplateInstance->m_VARIABLES["TMP_VAL"] < QWDDX(0)) {

// Line 1330.
		m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] + QWDDX(10);

// Line 1369.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(1);

// Line 1396.
		} else {

// Line 1410.
		m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"];

// Line 1444.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);

// Line 1471.
		}

// Line 1482.
		}

// Line 1494.
		}

// Line 1507.
		m_TemplateInstance->m_VARIABLES["DIVIDER"] = m_TemplateInstance->m_VARIABLES["DIVIDER"] + QWDDX(2);

// Line 1541.
		m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] =  !m_TemplateInstance->m_VARIABLES["POSITIVESIGN"];

// Line 1587.
		}

// Line 1596.
		m_TemplateInstance->m_VARIABLES["COUNTER"] = m_TemplateInstance->m_VARIABLES["COUNTER"] + QWDDX(1);

// Line 1628.
		}

// Line 1639.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);

// Line 1662.
		for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QWDDX(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QWDDX(-1)) {

// Line 1718.
		m_TemplateInstance->m_VARIABLES["TMP_VAL"] = ( m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] * QWDDX(4) ) + m_TemplateInstance->m_VARIABLES["TRANSFER"];

// Line 1765.
		m_TemplateInstance->m_VARIABLES["TRANSFER"] = cf_Fix(m_TemplateInstance->m_VARIABLES["TMP_VAL"] / QWDDX(10));

// Line 1805.
		m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"]%QWDDX(10);

// Line 1841.
		}

// Line 1852.
		m_TemplateInstance->m_VARIABLES["PI"] = QString("");

// Line 1870.
		for (m_TemplateInstance->m_VARIABLES["I"] = (QWDDX(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1) {

// Line 1916.
		m_TemplateInstance->m_VARIABLES["PI"] = m_TemplateInstance->m_VARIABLES["PI"] & cf_Chr(QWDDX(48) + m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]]);

// Line 1956.
		if (m_TemplateInstance->m_VARIABLES["I"] == QWDDX(1)) {

// Line 1972.
		m_TemplateInstance->m_VARIABLES["PI"] = m_TemplateInstance->m_VARIABLES["PI"] & QString(".");

// Line 1997.
		}

// Line 2005.
		}

// Line 2016.
		p_TemplateInstance->m_CFOutput++;

// Line 2026.
		f_WriteOutput(m_TemplateInstance->m_VARIABLES["PI"]);

// Line 2030.
		p_TemplateInstance->m_CFOutput--;
	}
};

/*extern "C" MY_EXPORT QCFTemplate* createCFMTemplate()
{
	return new QCFGeneratedTemplate();
};*/
