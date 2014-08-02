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

#ifndef QCHECK_QCFVARIANT_VAR_CACHE
#define QCHECK_QCFVARIANT_VAR_CACHE(VAR, STR) \
    if (VAR == nullptr) \
    { \
        if (!m_VARIABLES.m_Struct->contains(STR)) \
        { \
            (*m_VARIABLES.m_Struct)[STR] = QCFVariant(); \
        } \
        VAR = &(*m_VARIABLES.m_Struct)[STR]; \
    }
#endif


class QCFGeneratedWorkerThreadOpt2 : public QCFWorkerThread
{
public:
    QCFGeneratedWorkerThreadOpt2()
    {
        //m_isModified.m_Filename = QStringLiteral("/var/www/pi.cfm");
        //m_isModified.m_Size = 2081;
        //m_isModified.m_Modified = 1374408058;
    }

    virtual ~QCFGeneratedWorkerThreadOpt2()
    {
    }

    virtual void executePage() override
    {
        QCFVariant *c_VARIABLES_FINAL = 0;
        QCFVariant *c_VARIABLES_TMP = 0;
        QCFVariant *c_VARIABLES_PRECISION = 0;
        QCFVariant *c_VARIABLES_I = 0;
        QCFVariant *c_VARIABLES_KEEPLOOPING = 0;
        QCFVariant *c_VARIABLES_DIVIDER = 0;
        QCFVariant *c_VARIABLES_POSITIVESIGN = 0;
        QCFVariant *c_VARIABLES_COUNTER = 0;
        QCFVariant *c_VARIABLES_VALUE = 0;
        QCFVariant *c_VARIABLES_REMAINING = 0;
        QCFVariant *c_VARIABLES_TRANSFER = 0;
        QCFVariant *c_VARIABLES_TMP_VAL = 0;
        QCFVariant *c_VARIABLES_PI = 0;

        //m_VARIABLES["FINAL"] = cf_ArrayNew(QCFVariant(1));
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
        (*c_VARIABLES_FINAL) = cf_ArrayNew(1);

        //m_VARIABLES["TMP"] = cf_ArrayNew(QCFVariant(1));
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
        *c_VARIABLES_TMP = cf_ArrayNew(1);

        //m_VARIABLES["PRECISION"] = QCFVariant(6);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
        *c_VARIABLES_PRECISION = 6;

        //for (m_VARIABLES["I"] = (QCFVariant(1)).toNumber(); (m_VARIABLES["I"]).toNumber()  <=  (m_VARIABLES["PRECISION"]).toNumber(); m_VARIABLES["I"] = (m_VARIABLES["I"]).toNumber() + 1)
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
        for (*c_VARIABLES_I = 1; (*c_VARIABLES_I) <= (*c_VARIABLES_PRECISION); *c_VARIABLES_I = *c_VARIABLES_I + 1)
        {
            //m_VARIABLES["FINAL"][m_VARIABLES["I"]] = QCFVariant(0);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            (*c_VARIABLES_FINAL)[*c_VARIABLES_I] = 0;

            //m_VARIABLES["TMP"][m_VARIABLES["I"]] = QCFVariant(0);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            (*c_VARIABLES_TMP)[*c_VARIABLES_I] = 0;
        }

        //m_VARIABLES["KEEPLOOPING"] = QCFVariant(true);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
        *c_VARIABLES_KEEPLOOPING = true;

        //m_VARIABLES["DIVIDER"] = QCFVariant(1);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
        *c_VARIABLES_DIVIDER = 1;

        //m_VARIABLES["POSITIVESIGN"] = QCFVariant(true);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_POSITIVESIGN, QStringLiteral("POSITIVESIGN"));
        *c_VARIABLES_POSITIVESIGN = true;

        //m_VARIABLES["COUNTER"] = QCFVariant(0);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_COUNTER, QStringLiteral("COUNTER"));
        *c_VARIABLES_COUNTER = 0;

        while(*c_VARIABLES_KEEPLOOPING == true)
        {
            //m_VARIABLES["KEEPLOOPING"] = QCFVariant(false);
            *c_VARIABLES_KEEPLOOPING = false;

            //m_VARIABLES["VALUE"] = QCFVariant(1);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_VALUE, QStringLiteral("VALUE"));
            *c_VARIABLES_VALUE = 1;

            //m_VARIABLES["REMAINING"] = QCFVariant(0);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_REMAINING, QStringLiteral("REMAINING"));
            *c_VARIABLES_REMAINING = 0;

            //for (m_VARIABLES["I"] = (QCFVariant(1)).toNumber(); (m_VARIABLES["I"]).toNumber()  <=  (m_VARIABLES["PRECISION"]).toNumber(); m_VARIABLES["I"] = (m_VARIABLES["I"]).toNumber() + 1)
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
            for ((*c_VARIABLES_I) = 1; (*c_VARIABLES_I) <= (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)++)
            {
                //m_VARIABLES["TMP"][m_VARIABLES["I"]] = cf_Fix(m_VARIABLES["VALUE"] / m_VARIABLES["DIVIDER"]);
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_VALUE, QStringLiteral("VALUE"));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
                (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] = cf_Fix((*c_VARIABLES_VALUE) / (*c_VARIABLES_DIVIDER));

                //if (( m_VARIABLES["TMP"][m_VARIABLES["I"]] != QCFVariant(0) ) && ( m_VARIABLES["KEEPLOOPING"] == QCFVariant(false) ))
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
                if (((*c_VARIABLES_TMP)[(*c_VARIABLES_I)] != 0 ) && ( (*c_VARIABLES_KEEPLOOPING) == false ))
                {
                    //m_VARIABLES["KEEPLOOPING"] = QCFVariant(true);
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
                    (*c_VARIABLES_KEEPLOOPING) = true;
                }

                //m_VARIABLES["VALUE"] = cf_Fix(( m_VARIABLES["VALUE"] % m_VARIABLES["DIVIDER"] ) * QCFVariant(10));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_VALUE, QStringLiteral("VALUE"));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
                *c_VARIABLES_VALUE = cf_Fix(( (*c_VARIABLES_VALUE) % (*c_VARIABLES_DIVIDER) ) * 10);
            }

            //if (m_VARIABLES["KEEPLOOPING"] == QCFVariant(true))
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, QStringLiteral("KEEPLOOPING"));
            if ((*c_VARIABLES_KEEPLOOPING) == true)
            {

                //if (m_VARIABLES["POSITIVESIGN"] == QCFVariant(true))
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_POSITIVESIGN, QStringLiteral("POSITIVESIGN"));
                if ((*c_VARIABLES_POSITIVESIGN) == true)
                {

                    //m_VARIABLES["TRANSFER"] = QCFVariant(0);
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                    (*c_VARIABLES_TRANSFER) = 0;

                    //for (m_VARIABLES["I"] = (m_VARIABLES["PRECISION"]).toNumber(); (m_VARIABLES["I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_VARIABLES["I"] = (m_VARIABLES["I"]).toNumber() + QCFVariant(-1))
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
                    for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I) >= 1; (*c_VARIABLES_I)--)
                    {
                        //m_VARIABLES["TMP_VAL"] = m_VARIABLES["FINAL"][m_VARIABLES["I"]] + m_VARIABLES["TMP"][m_VARIABLES["I"]] + m_VARIABLES["TRANSFER"];
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                        (*c_VARIABLES_TMP_VAL) = (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] + (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] + (*c_VARIABLES_TRANSFER);

                        //if (m_VARIABLES["TMP_VAL"] > QCFVariant(9))
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        if ((*c_VARIABLES_TMP_VAL) > 9)
                        {
                            //m_VARIABLES["FINAL"][m_VARIABLES["I"]] = m_VARIABLES["TMP_VAL"] - QCFVariant(10);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) - 10;

                            //m_VARIABLES["TRANSFER"] = QCFVariant(1);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 1;

                        }
                        else
                        {
                            //m_VARIABLES["FINAL"][m_VARIABLES["I"]] = m_VARIABLES["TMP_VAL"];
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL);

                            //m_VARIABLES["TRANSFER"] = QCFVariant(0);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 0;
                        }
                    }

                }
                else
                {

                    //m_VARIABLES["TRANSFER"] = QCFVariant(0);
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                    (*c_VARIABLES_TRANSFER) = 0;

                    //for (m_VARIABLES["I"] = (m_VARIABLES["PRECISION"]).toNumber(); (m_VARIABLES["I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_VARIABLES["I"] = (m_VARIABLES["I"]).toNumber() + QCFVariant(-1))
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
                    for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)  >=  1; (*c_VARIABLES_I)--)
                    {

                        //m_VARIABLES["TMP_VAL"] = m_VARIABLES["FINAL"][m_VARIABLES["I"]] - m_VARIABLES["TMP"][m_VARIABLES["I"]] - m_VARIABLES["TRANSFER"];
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, QStringLiteral("TMP"));
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                        (*c_VARIABLES_TMP_VAL) = (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] - (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] - (*c_VARIABLES_TRANSFER);

                        //if (m_VARIABLES["TMP_VAL"] < QCFVariant(0))
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                        if ((*c_VARIABLES_TMP_VAL) < 0)
                        {
                            //m_VARIABLES["FINAL"][m_VARIABLES["I"]] = m_VARIABLES["TMP_VAL"] + QCFVariant(10);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) + 10;

                            //m_VARIABLES["TRANSFER"] = QCFVariant(1);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 1;

                        }
                        else
                        {
                            //m_VARIABLES["FINAL"][m_VARIABLES["I"]] = m_VARIABLES["TMP_VAL"];
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL);

                            //m_VARIABLES["TRANSFER"] = QCFVariant(0);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
                            (*c_VARIABLES_TRANSFER) = 0;
                        }
                    }
                }

                //m_VARIABLES["DIVIDER"] = m_VARIABLES["DIVIDER"] + QCFVariant(2);
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, QStringLiteral("DIVIDER"));
                (*c_VARIABLES_DIVIDER) = (*c_VARIABLES_DIVIDER) + 2;

                //m_VARIABLES["POSITIVESIGN"] =  !m_VARIABLES["POSITIVESIGN"];
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_POSITIVESIGN, QStringLiteral("POSITIVESIGN"));
                (*c_VARIABLES_POSITIVESIGN) =  !(*c_VARIABLES_POSITIVESIGN);
            }

            //m_VARIABLES["COUNTER"] = m_VARIABLES["COUNTER"] + QCFVariant(1);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_COUNTER, QStringLiteral("COUNTER"));
            (*c_VARIABLES_COUNTER) = (*c_VARIABLES_COUNTER) + 1;
        }

        //m_VARIABLES["TRANSFER"] = QCFVariant(0);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
        (*c_VARIABLES_TRANSFER) = 0;

        //for (m_VARIABLES["I"] = (m_VARIABLES["PRECISION"]).toNumber(); (m_VARIABLES["I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_VARIABLES["I"] = (m_VARIABLES["I"]).toNumber() + QCFVariant(-1))
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
        for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)  >=  1; (*c_VARIABLES_I)--)
        {
            //m_VARIABLES["TMP_VAL"] = ( m_VARIABLES["FINAL"][m_VARIABLES["I"]] * QCFVariant(4) ) + m_VARIABLES["TRANSFER"];
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
            (*c_VARIABLES_TMP_VAL) = ( (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] * 4 ) + (*c_VARIABLES_TRANSFER);

            //m_VARIABLES["TRANSFER"] = cf_Fix(m_VARIABLES["TMP_VAL"] / QCFVariant(10));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, QStringLiteral("TRANSFER"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
            (*c_VARIABLES_TRANSFER) = cf_Fix((*c_VARIABLES_TMP_VAL) / 10);

            //m_VARIABLES["FINAL"][m_VARIABLES["I"]] = m_VARIABLES["TMP_VAL"] % QCFVariant(10);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, QStringLiteral("TMP_VAL"));
            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) % 10;
        }

        //m_VARIABLES["PI"] = QString("");
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
        (*c_VARIABLES_PI) = QString();

        //for (m_VARIABLES["I"] = (QCFVariant(1)).toNumber(); (m_VARIABLES["I"]).toNumber()  <=  (m_VARIABLES["PRECISION"]).toNumber(); m_VARIABLES["I"] = (m_VARIABLES["I"]).toNumber() + 1)
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, QStringLiteral("PRECISION"));
        for ((*c_VARIABLES_I) = 1; (*c_VARIABLES_I) <= (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)++)
        {
            //m_VARIABLES["PI"] = m_VARIABLES["PI"] & cf_Chr(QCFVariant(48) + m_VARIABLES["FINAL"][m_VARIABLES["I"]]);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, QStringLiteral("FINAL"));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            (*c_VARIABLES_PI) = (*c_VARIABLES_PI) & cf_Chr(48 + (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)]);

            //if (m_VARIABLES["I"] == QCFVariant(1))
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, QStringLiteral("I"));
            if ((*c_VARIABLES_I) == 1)
            {
                //m_VARIABLES["PI"] = m_VARIABLES["PI"] & QString(".");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
                (*c_VARIABLES_PI) = (*c_VARIABLES_PI) & QStringLiteral(".");
            }
        }

        m_CFOutput++;

        //f_WriteOutput(m_VARIABLES["PI"]);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, QStringLiteral("PI"));
        f_WriteOutput((*c_VARIABLES_PI));

        m_CFOutput--;
    }
};
