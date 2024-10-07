#include "qcfcompiler.h"

#include <QFileInfo>
#include <QDateTime>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QDir>


QCFCompiler::QCFCompiler()
#ifdef QT_NO_DEBUG
    : m_Strip(true)
#else
    : m_Strip(false)
#endif
{
}

void QCFCompiler::setTargetPath(const QString &target)
{
    m_TargetPath = target;
}

QString QCFCompiler::compile(const QString &cppFile, QString &libFile)
{
    qint64 elapsedMS, startMS, endMS;

    QFileInfo file(cppFile);
    QString l_NewTarget = file.baseName();
    QProcess process;

#ifdef Q_OS_WIN
    libFile = file.path() + QDir::separator() + file.completeBaseName() + ".dll";
#else
    libFile = file.path() + QDir::separator() + file.completeBaseName() + ".so";
#endif

    // Compile
    startMS = QDateTime::currentMSecsSinceEpoch();
#ifdef Q_OS_WIN
    QString l_QtPath = QDir::toNativeSeparators(m_TargetPath) + "bin\\qt\\";
    QString l_MingwPath = QDir::toNativeSeparators(m_TargetPath) + "bin\\mingw\\";
    //process.start(l_MingwPath + "bin\\g++.exe", commonCompileSwitches(p_MKFusionPath));
#elif defined Q_OS_LINUX
    //process.start("g++", commonCompileSwitches(p_MKFusionPath));
#endif
    bool finished = process.waitForFinished(-1);
    endMS = QDateTime::currentMSecsSinceEpoch();
    elapsedMS = endMS - startMS;
    qDebug() << "Compiling" << l_NewTarget << "took" << elapsedMS << "miliseconds.";

#ifdef QT_NO_DEBUG
    QFile::remove(m_TargetPath + "templates/" + l_NewTarget + ".cpp");
#endif

    if ((finished == false)||(process.exitCode() != 0))
    {
        return "compile error: " + QString::fromUtf8(process.readAllStandardError()) + QString::fromUtf8(process.readAllStandardOutput());
    }

    // Link
    startMS = QDateTime::currentMSecsSinceEpoch();
#ifdef Q_OS_WIN
    process.start(l_MingwPath + "bin\\g++.exe", QStringList()
#elif defined Q_OS_LINUX
    process.start("g++", QStringList()
#else
#error Windows and Linux OSs are currently supported.
#endif

#ifdef __x86_64__
                  << "-m64"
#endif

#if defined Q_OS_LINUX && defined QT_NO_DEBUG
                  << "-Wl,-O1"
#endif

#ifdef Q_OS_WIN
                  << "-Wl,-enable-stdcall-fixup" << "-Wl,-enable-auto-import" << "-Wl,-enable-runtime-pseudo-reloc"
#ifdef QT_NO_DEBUG
                  << "-Wl,-s"
#endif
                  << "-mthreads"
#endif

                  << "-shared"

#ifdef Q_OS_WIN
                  << "-o" << (m_TargetPath + "templates" + QDir::separator() + l_NewTarget + ".dll")
#else
                  << "-o" << (m_TargetPath + "templates" + QDir::separator() + l_NewTarget + ".so")
#endif

                  << (m_TargetPath + "templates" + QDir::separator() + l_NewTarget + ".o")

#ifdef Q_OS_WIN
                  << "-L" << (l_QtPath + "lib") << (m_TargetPath + "lib\\mkfusion.a")
#else
                  << "-L/usr/lib/x86_64-linux-gnu" << "-lrt" << "-lpthread"
#endif

#if defined Q_OS_WIN && !defined QT_NO_DEBUG
                  << "-lQt6Concurrentd" << "-lQt6Cored"
#else
                  << "-lQt6Concurrent" << "-lQt6Core"
#endif
                 );

    finished = process.waitForFinished(-1);
    endMS = QDateTime::currentMSecsSinceEpoch();
    elapsedMS = endMS - startMS;
    qDebug() << "Linking" << l_NewTarget << "took" << elapsedMS << "miliseconds.";

    QFile::remove(m_TargetPath+"templates/"+l_NewTarget+".o");

    if ((finished == false)||(process.exitCode() != 0))
    {
        return "link error: " + process.readAllStandardError() + process.readAllStandardOutput();
    }

    if (m_Strip)
    {
        process.start("strip", QStringList()
#ifdef Q_OS_WIN
                      << (m_TargetPath + "templates" + QDir::separator() + l_NewTarget + ".dll")
#else
                      << (m_TargetPath + "templates" + QDir::separator() + l_NewTarget + ".so")
#endif
                     );

        process.waitForFinished(-1);
    }

    return "";
}

QString QCFCompiler::generateCpp(const QString &cfmlFilePath, QString &cppFilePath)
{
    QProcess process;

    cppFilePath = m_TargetPath + "templates" + QDir::separator() + QFileInfo(cfmlFilePath).baseName() + "_" + QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()) + ".cpp";

    int ret = process.execute("mkfusion-generator", QStringList() << cfmlFilePath << cppFilePath);

    if (ret == 0)
    {
        return "";
    }

    return QString("Parser error(code %1):").arg(ret) + QString::fromLatin1(process.readAllStandardOutput());
}

void QCFCompiler::rebuildPrecompiledHeader(const QString &p_MKFusionPath)
{
    QProcess process;
    QString headerFile = p_MKFusionPath + "include/mkfusion.h";

#ifdef Q_OS_WIN
    QString l_MingwPath = QDir::toNativeSeparators(p_MKFusionPath) + "bin\\mingw\\";
    process.start(l_MingwPath + "bin\\g++.exe", commonCompileSwitches(p_MKFusionPath)
#elif defined Q_OS_LINUX
    process.start("g++", commonCompileSwitches(p_MKFusionPath)
#else
#error Windows and Linux OSs are currently supported.
#endif
        << headerFile
    );

    process.waitForFinished(-1);
}

QStringList QCFCompiler::commonCompileSwitches(const QString &p_MKFusionPath)
{
#ifdef Q_OS_WIN
    QString l_QtPath = QDir::toNativeSeparators(p_MKFusionPath) + "bin\\qt\\";
    QString l_MingwPath = QDir::toNativeSeparators(p_MKFusionPath) + "bin\\mingw\\";
#endif
    return QStringList()
        << "-c"

#ifdef __x86_64__
        << "-m64"
#endif

#ifdef Q_OS_LINUX
        << "-pipe"
#endif

#ifdef __arm__
        << "-march=armv6" << "-mfloat-abi=hard" << "-mfpu=vfp"
#endif

#ifdef QT_NO_DEBUG
        << "-O2"
#else
        << "-g"
#endif

#ifdef __arm__
        << "-pipe" << "-fstack-protector" << "--param=ssp-buffer-size=4"
#endif

        << "-std=c++0x"

#ifdef Q_OS_WIN
        << "-frtti" << "-fexceptions" << "-mthreads"
#endif

        << "-Wall"

#ifdef Q_OS_LINUX
        << "-Wall" << "-W" << "-D_REENTRANT" << "-fPIE"
#endif

#ifdef Q_OS_WIN
        << "-DQT_LARGEFILE_SUPPORT" << "-DQT_DLL"
#endif

#ifdef QT_NO_DEBUG
        << "-DQT_NO_DEBUG"
#endif

        << "-DQT_CORE_LIB"

#ifdef Q_OS_LINUX
        << "-DQT_SHARED"
#endif

#ifdef Q_OS_WIN
        << "-DQT_THREAD_SUPPORT"
#endif

#ifdef Q_OS_WIN
        << "-I" << (l_MingwPath + "include")
        << "-I" << (l_QtPath + "include" + QDir::separator() + "QtCore")
        << "-I" << (l_QtPath + "include" + QDir::separator() + "QtNetwork")
        << "-I" << (l_QtPath + "include" + QDir::separator() + "QtConcurrent")
        << "-I" << (l_QtPath + "include")
        << "-I" << (p_MKFusionPath + "include")
#elif defined Q_OS_LINUX
#ifdef __x86_64__
        << "-I" << "/usr/share/qt6/mkspecs/linux-g++-64"
        << "-I" << "/usr/lib/qt/mkspecs/linux-g++-64" // Arch linux uses this path
#else
        << "-I" << "/usr/share/qt6/mkspecs/linux-g++"
        << "-I" << "/usr/lib/qt/mkspecs/linux-g++" // Arch linux uses this path
#endif
        << "-I" << "."
        << "-I" << "/usr/include/qt6/QtCore"
        << "-I" << "/usr/include/qt6/QtNetwork"
        << "-I" << "/usr/include/qt6/QtConcurrent"
        << "-I" << "/usr/include/qt6"
        << "-I" << "/usr/include/qt/QtCore" // Arch linux uses this path
        << "-I" << "/usr/include/qt/QtNetwork" // Arch linux uses this path
        << "-I" << "/usr/include/qt/QtConcurrent" // Arch linux uses this path
        << "-I" << "/usr/include/qt" // Arch linux uses this path
        << "-I" << (p_MKFusionPath + "include")
#endif
 ;
}

int QCFCompiler::buildPrecompiledHeader()
{
    Q_UNIMPLEMENTED();

    return 0;
}

int QCFCompiler::deletePrecompiledHeader()
{
    Q_UNIMPLEMENTED();

    return 0;
}

QHash<QString, QString> QCFCompiler::qmakeQuery()
{
    QHash<QString, QString> ret;
    QProcess proc;

    proc.start("/usr/bin/qtchooser", QStringList() << "-run-tool=qmake" << "-qt=5" << "-query");
    proc.waitForFinished();

    if (proc.exitCode() == 0)
    {
        QStringList lines = QString::fromUtf8(proc.readAllStandardOutput()).split('\n');

        for(const QString &line: lines)
        {
            int index = line.indexOf(':');

            if (index > 0)
            {
                QString key = line.left(index);
                QString value = line.right(line.length() - index - 1);

                ret[key] = value;
            }
        }
    }

    return ret;
}
