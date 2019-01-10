/**
 * @file    Logger.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 27, 2018, 7:49 PM
 */

#pragma once

#include <iostream>
#include <qlogging.h>
#include <qdebug.h>
#include <QMap>
#include <QStringList>
#include <QTextStream>
#include <QMutexLocker>
#include <QDateTime>

namespace even {

/** @brief Class Loggerger - manage out log message to directed output.*/

class Logger {
    public:

        /** @brief Type of outline message */
        enum Severity {
            Silent = 0,
            Critical = 10,
            Warning = 20,
            Info = 30,
            Debug = 40
        };

        /** @brief Message logger callback. */
        static void consoleMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

        /** @brief Level verbosity of out line. */
        static QMap<Severity, int> logLevel;

        /** @brief Inherit class for object Message type. */
        class Message {
            public:
                Message(Logger& log, int level_, Severity severity, const QString& prefix = QString(),
                        const char * file = nullptr, int line = 0);

                ~Message();

                /**
                * @param val Value to append to message text internal string stream
                * @return Reference to log message object
                * @tparam T Value type
                */
                template <typename T> Message& operator<<(const T& val) {
                    _content << val;
                    return *this;
                }

            private:
                Logger& _log;
                int _level;
                Severity _severity;
                QString _prefix;
                QString _file;          ///< File name;
                int _line;
                const QDateTime _ts;    ///< Current time stamp.
                QStringList _content;   ///< Content string list.
        };

        explicit Logger(Severity severity);

        /**
        * @brief getSeverity - Got the type log level
        * @return - type Severity
        */
        inline Severity getSeverity() {
            QMutexLocker locker(&_severityMutex);
            return _severity;
        }

        /** @brief Set log type. */
        inline void setSeverity(Severity newSeverety) {
            QMutexLocker locker(&_severityMutex);
            _severity = newSeverety;
        }

    private:
        /** @brief Type of message. */
        Severity _severity;

        /** @brief Sinchronisation objects. */
        QMutex _outMutex, _severityMutex;

};

} // namespace even

/** @brief Global value of logger */
extern even::Logger logger;

#define LOG(level, severity, prefix, file, line) ::even::Logger::Message(logger, (level), (severity), (prefix), (file), (line))
#define DEBUG(l)    LOG((l), ::even::Logger::Debug, "DEBUG", 0, 0)
#define INFO(l)     LOG((l), ::even::Logger::Info, "INFO", 0, 0)
#define WARNING(l)  LOG((l), ::even::Logger::Warning, "WARNING", 0, 0)
#define CRITICAL(l) LOG((l), ::even::Logger::Critical, "CRITICAL", __FILE__, __LINE__)
//#define SILENT(l) LOG((l), ::even::Logger::Silent, "SILENT", __FILE__, __LINE__)



