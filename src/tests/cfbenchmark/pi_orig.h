#include "qmkfusionexception.h"
#include "qcfworkerthread.h"
#include "qcftemplate.h"
#include "cffunctions.h"
#include "qcfvariant.h"


#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

class QCFGeneratedWorkerThreadOrig : public QCFWorkerThread
{
public:
    QCFGeneratedWorkerThreadOrig()
	{
        //m_isModified.m_Filename = QString::fromWCharArray(L"/var/www/pi.cfm");
        //m_isModified.m_Size = 2081;
        //m_isModified.m_Modified = 1374408058;
	}
	
    virtual ~QCFGeneratedWorkerThreadOrig()
	{
	}
	
    virtual void executePage() override
    {
// Line 85.
        m_VARIABLES[L"FINAL"] = cf_ArrayNew(QCFVariant(1));

// Line 115.
        m_VARIABLES[L"TMP"] = cf_ArrayNew(QCFVariant(1));

// Line 144.
        m_VARIABLES[L"PRECISION"] = QCFVariant(6);

// Line 169.
        for (m_VARIABLES[L"I"] = (QCFVariant(1)).toNumber(); (m_VARIABLES[L"I"]).toNumber()  <=  (m_VARIABLES[L"PRECISION"]).toNumber(); m_VARIABLES[L"I"] = (m_VARIABLES[L"I"]).toNumber() + 1) {

// Line 218.
        m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] = QCFVariant(0);

// Line 245.
        m_VARIABLES[L"TMP"][m_VARIABLES[L"I"]] = QCFVariant(0);

// Line 266.
		}

// Line 277.
        m_VARIABLES[L"KEEPLOOPING"] = QCFVariant(true);

// Line 306.
        m_VARIABLES[L"DIVIDER"] = QCFVariant(1);

// Line 328.
        m_VARIABLES[L"POSITIVESIGN"] = QCFVariant(true);

// Line 358.
        m_VARIABLES[L"COUNTER"] = QCFVariant(0);

// Line 381.
        while(m_VARIABLES[L"KEEPLOOPING"] == QCFVariant(true)) {

// Line 426.
        m_VARIABLES[L"KEEPLOOPING"] = QCFVariant(false);

// Line 465.
        m_VARIABLES[L"VALUE"] = QCFVariant(1);

// Line 489.
        m_VARIABLES[L"REMAINING"] = QCFVariant(0);

// Line 517.
        for (m_VARIABLES[L"I"] = (QCFVariant(1)).toNumber(); (m_VARIABLES[L"I"]).toNumber()  <=  (m_VARIABLES[L"PRECISION"]).toNumber(); m_VARIABLES[L"I"] = (m_VARIABLES[L"I"]).toNumber() + 1) {

// Line 563.
        m_VARIABLES[L"TMP"][m_VARIABLES[L"I"]] = cf_Fix(m_VARIABLES[L"VALUE"] / m_VARIABLES[L"DIVIDER"]);

// Line 604.
        if (( m_VARIABLES[L"TMP"][m_VARIABLES[L"I"]] != QCFVariant(0) ) && ( m_VARIABLES[L"KEEPLOOPING"] == QCFVariant(false) )) {

// Line 658.
        m_VARIABLES[L"KEEPLOOPING"] = QCFVariant(true);

// Line 688.
		}

// Line 697.
        m_VARIABLES[L"VALUE"] = cf_Fix(( m_VARIABLES[L"VALUE"]%m_VARIABLES[L"DIVIDER"] ) * QCFVariant(10));

// Line 749.
		}

// Line 768.
        if (m_VARIABLES[L"KEEPLOOPING"] == QCFVariant(true)) {

// Line 797.
        if (m_VARIABLES[L"POSITIVESIGN"] == QCFVariant(true)) {

// Line 828.
        m_VARIABLES[L"TRANSFER"] = QCFVariant(0);

// Line 854.
        for (m_VARIABLES[L"I"] = (m_VARIABLES[L"PRECISION"]).toNumber(); (m_VARIABLES[L"I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_VARIABLES[L"I"] = (m_VARIABLES[L"I"]).toNumber() + QCFVariant(-1)) {

// Line 913.
        m_VARIABLES[L"TMP_VAL"] = m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] + m_VARIABLES[L"TMP"][m_VARIABLES[L"I"]] + m_VARIABLES[L"TRANSFER"];

// Line 966.
        if (m_VARIABLES[L"TMP_VAL"] > QCFVariant(9)) {

// Line 991.
        m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] = m_VARIABLES[L"TMP_VAL"] - QCFVariant(10);

// Line 1030.
        m_VARIABLES[L"TRANSFER"] = QCFVariant(1);

// Line 1057.
		} else {

// Line 1071.
        m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] = m_VARIABLES[L"TMP_VAL"];

// Line 1105.
        m_VARIABLES[L"TRANSFER"] = QCFVariant(0);

// Line 1132.
		}

// Line 1143.
		}

// Line 1155.
		} else {

// Line 1167.
        m_VARIABLES[L"TRANSFER"] = QCFVariant(0);

// Line 1193.
        for (m_VARIABLES[L"I"] = (m_VARIABLES[L"PRECISION"]).toNumber(); (m_VARIABLES[L"I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_VARIABLES[L"I"] = (m_VARIABLES[L"I"]).toNumber() + QCFVariant(-1)) {

// Line 1252.
        m_VARIABLES[L"TMP_VAL"] = m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] - m_VARIABLES[L"TMP"][m_VARIABLES[L"I"]] - m_VARIABLES[L"TRANSFER"];

// Line 1305.
        if (m_VARIABLES[L"TMP_VAL"] < QCFVariant(0)) {

// Line 1330.
        m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] = m_VARIABLES[L"TMP_VAL"] + QCFVariant(10);

// Line 1369.
        m_VARIABLES[L"TRANSFER"] = QCFVariant(1);

// Line 1396.
		} else {

// Line 1410.
        m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] = m_VARIABLES[L"TMP_VAL"];

// Line 1444.
        m_VARIABLES[L"TRANSFER"] = QCFVariant(0);

// Line 1471.
		}

// Line 1482.
		}

// Line 1494.
		}

// Line 1507.
        m_VARIABLES[L"DIVIDER"] = m_VARIABLES[L"DIVIDER"] + QCFVariant(2);

// Line 1541.
        m_VARIABLES[L"POSITIVESIGN"] =  !m_VARIABLES[L"POSITIVESIGN"];

// Line 1587.
		}

// Line 1596.
        m_VARIABLES[L"COUNTER"] = m_VARIABLES[L"COUNTER"] + QCFVariant(1);

// Line 1628.
		}

// Line 1639.
        m_VARIABLES[L"TRANSFER"] = QCFVariant(0);

// Line 1662.
        for (m_VARIABLES[L"I"] = (m_VARIABLES[L"PRECISION"]).toNumber(); (m_VARIABLES[L"I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_VARIABLES[L"I"] = (m_VARIABLES[L"I"]).toNumber() + QCFVariant(-1)) {

// Line 1718.
        m_VARIABLES[L"TMP_VAL"] = ( m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] * QCFVariant(4) ) + m_VARIABLES[L"TRANSFER"];

// Line 1765.
        m_VARIABLES[L"TRANSFER"] = cf_Fix(m_VARIABLES[L"TMP_VAL"] / QCFVariant(10));

// Line 1805.
        m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]] = m_VARIABLES[L"TMP_VAL"]%QCFVariant(10);

// Line 1841.
		}

// Line 1852.
        m_VARIABLES[L"PI"] = QString("");

// Line 1870.
        for (m_VARIABLES[L"I"] = (QCFVariant(1)).toNumber(); (m_VARIABLES[L"I"]).toNumber()  <=  (m_VARIABLES[L"PRECISION"]).toNumber(); m_VARIABLES[L"I"] = (m_VARIABLES[L"I"]).toNumber() + 1) {

// Line 1916.
        m_VARIABLES[L"PI"] = m_VARIABLES[L"PI"] & cf_Chr(QCFVariant(48) + m_VARIABLES[L"FINAL"][m_VARIABLES[L"I"]]);

// Line 1956.
        if (m_VARIABLES[L"I"] == QCFVariant(1)) {

// Line 1972.
        m_VARIABLES[L"PI"] = m_VARIABLES[L"PI"] & QString(".");

// Line 1997.
		}

// Line 2005.
		}

// Line 2016.
        m_CFOutput++;

// Line 2026.
        f_WriteOutput(m_VARIABLES[L"PI"]);

// Line 2030.
        m_CFOutput--;
	}
};

/*extern "C" MY_EXPORT QCFTemplate* createCFMTemplate()
{
	return new QCFGeneratedTemplate();
};*/
