/**
 * @file    FileConfig.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 19, 2018, 10:25 AM
 */

#pragma once

#include <QCoreApplication>
#include <QSettings>

namespace even {

/** @brief Entity for control of ini files configuration */
class FileConfig : public QObject
{
        Q_OBJECT

    public:

        virtual ~FileConfig();

        /** @brief Take a singleton object pointer */
        static FileConfig* instance();

        /** @brief Search the configuration file */
        QString searchConfigFile(const QString& appname_);

        /** @brief Got a section of inputed groupName_ from config named appName_ */
        QSettings* group(QString appName_, QString groupName_);

    private:
        explicit FileConfig(QObject* parent_ = nullptr);

        /** @brief Create singleton once object */
        static FileConfig* createInstance();

};
};

