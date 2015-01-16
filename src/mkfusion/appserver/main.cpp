#include "qmkfusionservice.h"
#include "qcfcompiler.h"
#include <QCoreApplication>
#include <QDir>

int main(int argc, char **argv)
{
    if ((argc == 2)&&(strcmp(argv[1], "-precompile") == 0))
    {
        QCoreApplication app(argc, argv);

        QDir path = QDir(QCoreApplication::applicationDirPath());
        path.cdUp();

        QCFCompiler::rebuildPrecompiledHeader(path.absolutePath() + "/");

        return 0;
    }

    QMKFusionService service(argc, argv);
    return service.exec();
}
