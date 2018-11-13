/**
 * @file    FileConfig.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 19, 2018, 10:29 AM
 */

#include <QDir>

#include "FileConfig.hxx"
#include "Logger.hxx"
#include "Singleton.hxx"

using namespace even;

//------------------------------------------------------------------------------
FileConfig::FileConfig(QObject* parent_)
    :QObject(parent_)
{
}

//------------------------------------------------------------------------------
FileConfig* FileConfig::createInstance()
{
    return new FileConfig();
}

//------------------------------------------------------------------------------
FileConfig::~FileConfig()
{
    INFO(10) << "FileConfig singleton destroyed..";
}

//------------------------------------------------------------------------------
QSettings* FileConfig::group(QString appName_, QString groupName_)
{
    QSettings* settings = new QSettings(FileConfig::instance()->searchConfigFile(appName_)
                                        , QSettings::IniFormat
                                        , QCoreApplication::instance());
    settings->beginGroup(groupName_);
    return settings;
}

//------------------------------------------------------------------------------
FileConfig* FileConfig::instance()
{
    return Singleton<FileConfig>::instance(FileConfig::createInstance);
}

//------------------------------------------------------------------------------
QString FileConfig::searchConfigFile(const QString& appname_)
{
    QString binDir = QCoreApplication::applicationDirPath();
    QString fileName(appname_ + ".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../" + appname_ + "/etc"); // for development with shadow build
    searchList.append(binDir+"/../../" + appname_ + "/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../" + appname_ + "/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../" + appname_ + "/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../" + appname_ + "/etc"); // for development with shadow build
    searchList.append(QDir::rootPath() + "etc/opt");
    searchList.append(QDir::rootPath() + "etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir + "/" + fileName);
        if (file.exists())
        {
            // found
            fileName = QDir(file.fileName()).canonicalPath();
            INFO(15) << QString("Using config file %1")
                        .arg(qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        CRITICAL(1) << QString("%1/%2 not found")
                       .arg(qPrintable(dir))
                       .arg(qPrintable(fileName));
    }
    CRITICAL(1) << QString("Cannot find config file %1")
                   .arg(qPrintable(fileName));
    return 0;
}
