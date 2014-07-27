#include "qmkfusionservice.h"
#include "qcfgenerator.h"
#include <QCoreApplication>
#include <QDir>


int main(int argc, char **argv)
{
    if ((argc == 2)&&(strcmp(argv[1], "-precompile") == 0))
    {
        QDir path = QDir(QCoreApplication::applicationDirPath());
        path.cdUp();

        QCFGenerator::rebuildPrecompiledHeader(path.absolutePath() + "/");

        return 0;
    }

    QMKFusionService service(argc, argv);
    return service.exec();
}
