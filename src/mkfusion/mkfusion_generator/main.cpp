#include "qcfcomponentgenerator.h"
#include "qcftemplategenerator.h"
#include "qcfgenerator.h"

#include <QTemporaryFile>
#include <QTextStream>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QDir>

#include <stdio.h>


int main(int argc, char **argv)
{
    if ((argc < 2)||(argc > 3))
    {
        puts("Usage: mkfusion_generator <source_file> [destination_file]");

        return 1;
    }

    QString srcFile;
    QString dstFile;
    bool tmpFile;

    srcFile = QString::fromUtf8(argv[1]);

    if (argc == 3)
    {
        dstFile = QString::fromUtf8(argv[2]);
        tmpFile = false;
    }
    else
    {
        dstFile = QDir::tempPath() + QDir::separator() + "mkfusion_generator-" + QString::number(rand(), 16) + ".cpp";
        tmpFile = true;
    }

    QFileInfo fi(srcFile);
    if(!fi.exists())
    {
        printf("Source file (%s) doesn't exists.\n", argv[1]);

        return 2;
    }

    QCFGenerator *generator = nullptr;
    QString ext = fi.suffix();

    if (ext.compare("cfm", Qt::CaseInsensitive) == 0)
    {
        generator = new QCFTemplateGenerator();
    }
    else if (ext.compare("cfc", Qt::CaseInsensitive) == 0)
    {
        generator = new QCFComponentGenerator();
    }
    else
    {
        printf("Source file (%s) has invalid extension. Only cfm and cfc are valid\n", argv[1]);

        return 3;
    }

    if (!generator->generate(srcFile, dstFile))
    {
        printf("Cpp code generation failed. Reason: %s\n", generator->error().toUtf8().constData());

        delete generator;
        generator = nullptr;

        return 4;
    }

    delete generator;
    generator = nullptr;

    if (tmpFile)
    {
        QFile file(dstFile);

        if (!file.open(QIODevice::ReadOnly))
        {
            puts("Can't open tmp file.");

            return 5;
        }

        QString fileContent = QTextStream(&file).readAll();

        file.close();

        file.remove();

        puts(fileContent.toUtf8().constData());
    }

    return 0;
}
