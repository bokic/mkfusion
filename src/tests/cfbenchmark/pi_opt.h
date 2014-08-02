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


class QCFGeneratedWorkerThreadOpt : public QCFWorkerThread
{
public:
    QCFGeneratedWorkerThreadOpt()
    {
        //m_isModified.m_Filename = QString::fromWCharArray(L"/var/www/pi.cfm");
        //m_isModified.m_Size = 2081;
        //m_isModified.m_Modified = 1374408058;
    }

    virtual ~QCFGeneratedWorkerThreadOpt()
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

        //m_TemplateInstance->m_VARIABLES["FINAL"] = cf_ArrayNew(QCFVariant(1));
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
        (*c_VARIABLES_FINAL) = cf_ArrayNew(1);

        //m_TemplateInstance->m_VARIABLES["TMP"] = cf_ArrayNew(QCFVariant(1));
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, "TMP");
        *c_VARIABLES_TMP = cf_ArrayNew(1);

        //m_TemplateInstance->m_VARIABLES["PRECISION"] = QCFVariant(6);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, "PRECISION");
        *c_VARIABLES_PRECISION = 6;

        //for (m_TemplateInstance->m_VARIABLES["I"] = (QCFVariant(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1)
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
        for (*c_VARIABLES_I = 1; (*c_VARIABLES_I)  <=  (*c_VARIABLES_PRECISION); *c_VARIABLES_I = c_VARIABLES_I->toNumber() + 1)
        {
            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = QCFVariant(0);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
            (*c_VARIABLES_FINAL)[*c_VARIABLES_I] = 0;

            //m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] = QCFVariant(0);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, "TMP");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
            (*c_VARIABLES_TMP)[*c_VARIABLES_I] = 0;
        }

        //m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QCFVariant(true);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, "KEEPLOOPING");
        *c_VARIABLES_KEEPLOOPING = true;

        //m_TemplateInstance->m_VARIABLES["DIVIDER"] = QCFVariant(1);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, "DIVIDER");
        *c_VARIABLES_DIVIDER = 1;

        //m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] = QCFVariant(true);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_POSITIVESIGN, "POSITIVESIGN");
        *c_VARIABLES_POSITIVESIGN = true;

        //m_TemplateInstance->m_VARIABLES["COUNTER"] = QCFVariant(0);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_COUNTER, "COUNTER");
        *c_VARIABLES_COUNTER = 0;

        while(*c_VARIABLES_KEEPLOOPING == true)
        {
            //m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QCFVariant(false);
            *c_VARIABLES_KEEPLOOPING = false;

            //m_TemplateInstance->m_VARIABLES["VALUE"] = QCFVariant(1);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_VALUE, "VALUE");
            *c_VARIABLES_VALUE = 1;

            //m_TemplateInstance->m_VARIABLES["REMAINING"] = QCFVariant(0);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_REMAINING, "REMAINING");
            *c_VARIABLES_REMAINING = 0;

            //for (m_TemplateInstance->m_VARIABLES["I"] = (QCFVariant(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1)
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, "PRECISION");
            for ((*c_VARIABLES_I) = 1; (*c_VARIABLES_I) <= (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)++)
            {
                //m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] = cf_Fix(m_TemplateInstance->m_VARIABLES["VALUE"] / m_TemplateInstance->m_VARIABLES["DIVIDER"]);
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, "TMP");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_VALUE, "VALUE");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, "DIVIDER");
                (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] = cf_Fix((*c_VARIABLES_VALUE) / (*c_VARIABLES_DIVIDER));

                //if (( m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] != QCFVariant(0) ) && ( m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] == QCFVariant(false) ))
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, "TMP");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, "KEEPLOOPING");
                if (((*c_VARIABLES_TMP)[(*c_VARIABLES_I)] != 0 ) && ( (*c_VARIABLES_KEEPLOOPING) == false ))
                {
                    //m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] = QCFVariant(true);
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, "KEEPLOOPING");
                    (*c_VARIABLES_KEEPLOOPING) = true;
                }

                //m_TemplateInstance->m_VARIABLES["VALUE"] = cf_Fix(( m_TemplateInstance->m_VARIABLES["VALUE"] % m_TemplateInstance->m_VARIABLES["DIVIDER"] ) * QCFVariant(10));
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_VALUE, "VALUE");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, "DIVIDER");
                *c_VARIABLES_VALUE = cf_Fix(( (*c_VARIABLES_VALUE) % (*c_VARIABLES_DIVIDER) ) * 10);
            }

            //if (m_TemplateInstance->m_VARIABLES["KEEPLOOPING"] == QCFVariant(true))
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_KEEPLOOPING, "KEEPLOOPING");
            if ((*c_VARIABLES_KEEPLOOPING) == true)
            {

                //if (m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] == QCFVariant(true))
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_POSITIVESIGN, "POSITIVESIGN");
                if ((*c_VARIABLES_POSITIVESIGN) == true)
                {

                    //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QCFVariant(0);
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                    (*c_VARIABLES_TRANSFER) = 0;

                    //for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QCFVariant(-1))
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, "PRECISION");
                    for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I) >= 1; (*c_VARIABLES_I)--)
                    {
                        //m_TemplateInstance->m_VARIABLES["TMP_VAL"] = m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] + m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] + m_TemplateInstance->m_VARIABLES["TRANSFER"];
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, "TMP");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                        (*c_VARIABLES_TMP_VAL) = (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] + (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] + (*c_VARIABLES_TRANSFER);

                        //if (m_TemplateInstance->m_VARIABLES["TMP_VAL"] > QCFVariant(9))
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                        if ((*c_VARIABLES_TMP_VAL) > 9)
                        {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] - QCFVariant(10);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) - 10;

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QCFVariant(1);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                            (*c_VARIABLES_TRANSFER) = 1;

                        }
                        else
                        {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"];
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL);

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QCFVariant(0);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                            (*c_VARIABLES_TRANSFER) = 0;
                        }
                    }

                }
                else
                {

                    //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QCFVariant(0);
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                    (*c_VARIABLES_TRANSFER) = 0;

                    //for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QCFVariant(-1))
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                    QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, "PRECISION");
                    for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)  >=  1; (*c_VARIABLES_I)--)
                    {

                        //m_TemplateInstance->m_VARIABLES["TMP_VAL"] = m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] - m_TemplateInstance->m_VARIABLES["TMP"][m_TemplateInstance->m_VARIABLES["I"]] - m_TemplateInstance->m_VARIABLES["TRANSFER"];
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP, "TMP");
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                        (*c_VARIABLES_TMP_VAL) = (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] - (*c_VARIABLES_TMP)[(*c_VARIABLES_I)] - (*c_VARIABLES_TRANSFER);

                        //if (m_TemplateInstance->m_VARIABLES["TMP_VAL"] < QCFVariant(0))
                        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                        if ((*c_VARIABLES_TMP_VAL) < 0)
                        {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] + QCFVariant(10);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) + 10;

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QCFVariant(1);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                            (*c_VARIABLES_TRANSFER) = 1;

                        }
                        else
                        {
                            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"];
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
                            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL);

                            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QCFVariant(0);
                            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
                            (*c_VARIABLES_TRANSFER) = 0;
                        }
                    }
                }

                //m_TemplateInstance->m_VARIABLES["DIVIDER"] = m_TemplateInstance->m_VARIABLES["DIVIDER"] + QCFVariant(2);
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_DIVIDER, "DIVIDER");
                (*c_VARIABLES_DIVIDER) = (*c_VARIABLES_DIVIDER) + 2;

                //m_TemplateInstance->m_VARIABLES["POSITIVESIGN"] =  !m_TemplateInstance->m_VARIABLES["POSITIVESIGN"];
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_POSITIVESIGN, "POSITIVESIGN");
                (*c_VARIABLES_POSITIVESIGN) =  !(*c_VARIABLES_POSITIVESIGN);
            }

            //m_TemplateInstance->m_VARIABLES["COUNTER"] = m_TemplateInstance->m_VARIABLES["COUNTER"] + QCFVariant(1);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_COUNTER, "COUNTER");
            (*c_VARIABLES_COUNTER) = (*c_VARIABLES_COUNTER) + 1;
        }

        //m_TemplateInstance->m_VARIABLES["TRANSFER"] = QCFVariant(0);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
        (*c_VARIABLES_TRANSFER) = 0;

        //for (m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  >=  (QCFVariant(1)).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + QCFVariant(-1))
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, "PRECISION");
        for ((*c_VARIABLES_I) = (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)  >=  1; (*c_VARIABLES_I)--)
        {
            //m_TemplateInstance->m_VARIABLES["TMP_VAL"] = ( m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] * QCFVariant(4) ) + m_TemplateInstance->m_VARIABLES["TRANSFER"];
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
            (*c_VARIABLES_TMP_VAL) = ( (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] * 4 ) + (*c_VARIABLES_TRANSFER);

            //m_TemplateInstance->m_VARIABLES["TRANSFER"] = cf_Fix(m_TemplateInstance->m_VARIABLES["TMP_VAL"] / QCFVariant(10));
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TRANSFER, "TRANSFER");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
            (*c_VARIABLES_TRANSFER) = cf_Fix((*c_VARIABLES_TMP_VAL) / 10);

            //m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]] = m_TemplateInstance->m_VARIABLES["TMP_VAL"] % QCFVariant(10);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_TMP_VAL, "TMP_VAL");
            (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)] = (*c_VARIABLES_TMP_VAL) % 10;
        }

        //m_TemplateInstance->m_VARIABLES["PI"] = QString("");
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, "PI");
        (*c_VARIABLES_PI) = QString("");

        //for (m_TemplateInstance->m_VARIABLES["I"] = (QCFVariant(1)).toNumber(); (m_TemplateInstance->m_VARIABLES["I"]).toNumber()  <=  (m_TemplateInstance->m_VARIABLES["PRECISION"]).toNumber(); m_TemplateInstance->m_VARIABLES["I"] = (m_TemplateInstance->m_VARIABLES["I"]).toNumber() + 1)
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PRECISION, "PRECISION");
        for ((*c_VARIABLES_I) = 1; (*c_VARIABLES_I) <= (*c_VARIABLES_PRECISION); (*c_VARIABLES_I)++)
        {
            //m_TemplateInstance->m_VARIABLES["PI"] = m_TemplateInstance->m_VARIABLES["PI"] & cf_Chr(QCFVariant(48) + m_TemplateInstance->m_VARIABLES["FINAL"][m_TemplateInstance->m_VARIABLES["I"]]);
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, "PI");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_FINAL, "FINAL");
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
            (*c_VARIABLES_PI) = (*c_VARIABLES_PI) & cf_Chr(48 + (*c_VARIABLES_FINAL)[(*c_VARIABLES_I)]);

            //if (m_TemplateInstance->m_VARIABLES["I"] == QCFVariant(1))
            QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_I, "I");
            if ((*c_VARIABLES_I) == 1)
            {
                //m_TemplateInstance->m_VARIABLES["PI"] = m_TemplateInstance->m_VARIABLES["PI"] & QString(".");
                QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, "PI");
                (*c_VARIABLES_PI) = (*c_VARIABLES_PI) & QString(".");
            }
        }

        m_CFOutput++;

        //f_WriteOutput(m_TemplateInstance->m_VARIABLES["PI"]);
        QCHECK_QCFVARIANT_VAR_CACHE(c_VARIABLES_PI, "PI");
        f_WriteOutput((*c_VARIABLES_PI));

        m_CFOutput--;
    }
};
