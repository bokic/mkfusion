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

#define QCHECK_QWDDX_VAR_CACHE(VAR, STR) \
    if (VAR == NULL) \
    { \
        if (!m_TemplateInstance->m_VARIABLES.m_Struct->contains(STR)) \
        { \
            (*m_TemplateInstance->m_VARIABLES.m_Struct)[STR] = QWDDX(); \
        } \
        VAR = &(*m_TemplateInstance->m_VARIABLES.m_Struct)[STR]; \
    }


class QCFGeneratedTemplateOpt2 : public QCFTemplate
{
public:
    QCFGeneratedTemplateOpt2()
	{
        m_isModified.m_Filename = QStringLiteral("/var/www/pi.cfm");
		m_isModified.m_Size = 2081;
		m_isModified.m_Modified = 1374408058;
	}
	
    virtual ~QCFGeneratedTemplateOpt2()
	{
	}
	
	virtual void run(QCFRunningTemplate* p_TemplateInstance)
	{
        QWDDX *c_VARIABLES_FINAL = 0;
        QWDDX *c_VARIABLES_TMP = 0;
        QWDDX *c_VARIABLES_PRECISION = 0;
        QWDDX *c_VARIABLES_I = 0;
        QWDDX *c_VARIABLES_KEEPLOOPING = 0;
        QWDDX *c_VARIABLES_DIVIDER = 0;
        QWDDX *c_VARIABLES_POSITIVESIGN = 0;
        QWDDX *c_VARIABLES_COUNTER = 0;
        QWDDX *c_VARIABLES_VALUE = 0;
        QWDDX *c_VARIABLES_REMAINING = 0;
        QWDDX *c_VARIABLES_TRANSFER = 0;
        QWDDX *c_VARIABLES_TMP_VAL = 0;
        QWDDX *c_VARIABLES_PI = 0;

		QCFTemplate::run(p_TemplateInstance);

        //m_TemplateInstance->m_VARIABLES["FINAL"] = cf_ArrayNew(QWDDX(1));
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
        (*c_VARIABLES_FINAL) = cf_ArrayNew(1);

        //m_TemplateInstance->m_VARIABLES["TMP"] = cf_ArrayNew(QWDDX(1));
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
        *c_VARIABLES_TMP = cf_ArrayNew(1);

        //m_TemplateInstance->m_VARIABLES["PRECISION"] = QWDDX(6);
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
        *c_VARIABLES_PRECISION = 6;

        //for (m_TemplateInstance->m_VARIABLES["I"] = (QWDDX(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1)
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, "I");
        for (*c_VARIABLES_I = 1; (*c_VARIABLES_I)  <=  (*c_VARIABLES_PRECISION); *c_VARIABLES_I = c_VARIABLES_I->toNumber() + 1)
        {
            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = QWDDX(0);
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            (*c_VARIABLES_FINAL)[*c_VARIABLES_I] = 0;

            //m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] = QWDDX(0);
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            (*c_VARIABLES_TMP)[*c_VARIABLES_I] = 0;
		}

        //m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QWDDX(true);
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
        *c_VARIABLES_KEEPLOOPING = true;

        //m_TemplateInstance->m_VARIABLES["DIVIDER"] = QWDDX(1);
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
        *c_VARIABLES_DIVIDER = 1;

        //m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] = QWDDX(true);
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_POSITIVESIGN, QStringLiteral("POSITIVESIGN"));
        *c_VARIABLES_POSITIVESIGN = true;

        //m_TemplateInstance->m_VARIABLES["COUNTER"] = QWDDX(0);
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_COUNTER, QStringLiteral("COUNTER"));
        *c_VARIABLES_COUNTER = 0;

        while(*c_VARIABLES_KEEPLOOPING == true)
        {
            //m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QWDDX(false);
            *c_VARIABLES_KEEPLOOPING = false;

            //m_TemplateInstance->m_VARIABLES["VALUE"] = QWDDX(1);
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_VALUE, QStringLiteral("VALUE"));
            *c_VARIABLES_VALUE = 1;

            //m_TemplateInstance->m_VARIABLES["REMAINING"] = QWDDX(0);
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_REMAINING, QStringLiteral("REMAINING"));
            *c_VARIABLES_REMAINING = 0;

            //for (m_TemplateInstance->m_VARIABLES["I"] = (QWDDX(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1)
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
            for ((*c_VARIABLES_I) = 1; (*c_VARIABLES_I) <= (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)++)
            {
                //m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] = cf_Fix(m_TemplateInstance->m_VARIABLES["VALUE"] / m_TemplateInstance->m_VARIABLES["DIVIDER"]);
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_VALUE, QStringLiteral("VALUE"));
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
                (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] = cf_Fix((*c_VARIABLES_VALUE) / (*c_VARIABLES_DIVIDER));

                //if (( m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] != QWDDX(0) ) && ( m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] == QWDDX(false) ))
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
                if (((*c_VARIABLES_TMP)[(*c_VARIABLES_I)] != 0 ) && ( (*c_VARIABLES_KEEPLOOPING) == false ))
                {
                    //m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QWDDX(true);
                    QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
                    (*c_VARIABLES_KEEPLOOPING) = true;
                }

                //m_TemplateInstance->m_VARIABLES["VALUE"] = cf_Fix(( m_TemplateInstance->m_VARIABLES["VALUE"] % m_TemplateInstance->m_VARIABLES["DIVIDER"] ) * QWDDX(10));
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_VALUE, QStringLiteral("VALUE"));
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
                *c_VARIABLES_VALUE = cf_Fix(( (*c_VARIABLES_VALUE) % (*c_VARIABLES_DIVIDER) ) * 10);
            }

            //if (m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] == QWDDX(true))
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
            if ((*c_VARIABLES_KEEPLOOPING) == true)
            {

                //if (m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] == QWDDX(true))
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_POSITIVESIGN, QStringLiteral("POSITIVESIGN"));
                if ((*c_VARIABLES_POSITIVESIGN) == true)
                {

                    //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);
                    QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                    (*c_VARIABLES_TRANSFER) = 0;

                    //for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QWDDX(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QWDDX(-1))
                    QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                    QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
                    for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I) >= 1; (*c_VARIABLES_I)--)
                    {
                        //m_TemplateInstance->m_VARIABLES["TMP_VAL"] = m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] + m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] + m_TemplateInstance->m_VARIABLES["TRANSFER"];
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                        (*c_VARIABLES_TMP_VAL) = (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] + (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] + (*c_VARIABLES_TRANSFER);

                        //if (m_TemplateInstance->m_VARIABLES["TMP_VAL"] > QWDDX(9))
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        if ((*c_VARIABLES_TMP_VAL) > 9)
                        {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] - QWDDX(10);
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) - 10;

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(1);
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 1;

                        } else {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"];
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL);

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 0;
                        }
                    }

                } else {

                    //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);
                    QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                    (*c_VARIABLES_TRANSFER) = 0;

                    //for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QWDDX(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QWDDX(-1))
                    QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                    QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
                    for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)  >=  1; (*c_VARIABLES_I)--)
                    {

                        //m_TemplateInstance->m_VARIABLES["TMP_VAL"] = m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] - m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] - m_TemplateInstance->m_VARIABLES["TRANSFER"];
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                        (*c_VARIABLES_TMP_VAL) = (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] - (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] - (*c_VARIABLES_TRANSFER);

                        //if (m_TemplateInstance->m_VARIABLES["TMP_VAL"] < QWDDX(0))
                        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        if ((*c_VARIABLES_TMP_VAL) < 0)
                        {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] + QWDDX(10);
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) + 10;

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(1);
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 1;

                        } else {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"];
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL);

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);
                            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 0;
                        }
                    }
                }

                //m_TemplateInstance->m_VARIABLES["DIVIDER"] = m_TemplateInstance->m_VARIABLES["DIVIDER"] + QWDDX(2);
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
                (*c_VARIABLES_DIVIDER) = (*c_VARIABLES_DIVIDER) + 2;

                //m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] =  !m_TemplateInstance->m_VARIABLES["POSITIVESIGN"];
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_POSITIVESIGN, QStringLiteral("POSITIVESIGN"));
                (*c_VARIABLES_POSITIVESIGN) =  !(*c_VARIABLES_POSITIVESIGN);
            }

            //m_TemplateInstance->m_VARIABLES["COUNTER"] = m_TemplateInstance->m_VARIABLES["COUNTER"] + QWDDX(1);
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_COUNTER, QStringLiteral("COUNTER"));
            (*c_VARIABLES_COUNTER) = (*c_VARIABLES_COUNTER) + 1;
        }

        //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QWDDX(0);
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
        (*c_VARIABLES_TRANSFER) = 0;

        //for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QWDDX(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QWDDX(-1))
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
        for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)  >=  1; (*c_VARIABLES_I)--)
        {
            //m_TemplateInstance->m_VARIABLES["TMP_VAL"] = ( m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] * QWDDX(4) ) + m_TemplateInstance->m_VARIABLES["TRANSFER"];
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
            (*c_VARIABLES_TMP_VAL) = ( (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] * 4 ) + (*c_VARIABLES_TRANSFER);

            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = cf_Fix(m_TemplateInstance->m_VARIABLES["TMP_VAL"] / QWDDX(10));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
            (*c_VARIABLES_TRANSFER) = cf_Fix((*c_VARIABLES_TMP_VAL) / 10);

            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] % QWDDX(10);
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) % 10;
		}

        //m_TemplateInstance->m_VARIABLES["PI"] = QString("");
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
        (*c_VARIABLES_PI) = QString();

        //for (m_TemplateInstance->m_VARIABLES["I"] = (QWDDX(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1)
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
        for ((*c_VARIABLES_I) = 1; (*c_VARIABLES_I) <= (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)++)
        {
            //m_TemplateInstance->m_VARIABLES["PI"] = m_TemplateInstance->m_VARIABLES["PI"] & cf_Chr(QWDDX(48) + m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]]);
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            (*c_VARIABLES_PI) = (*c_VARIABLES_PI) & cf_Chr(48 + (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)]);

            //if (m_TemplateInstance->m_VARIABLES["I"] == QWDDX(1))
            QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            if ((*c_VARIABLES_I) == 1)
            {
                //m_TemplateInstance->m_VARIABLES["PI"] = m_TemplateInstance->m_VARIABLES["PI"] & QString(".");
                QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
                (*c_VARIABLES_PI) = (*c_VARIABLES_PI) & QStringLiteral(".");
            }
		}

		p_TemplateInstance->m_CFOutput++;

        //f_WriteOutput(m_TemplateInstance->m_VARIABLES["PI"]);
        QCHECK_QWDDX_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
        f_WriteOutput((*c_VARIABLES_PI));

		p_TemplateInstance->m_CFOutput--;
	}
};
