/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Loggerger.cxx
 * Author: zipper
 *
 * Created on August 27, 2018, 7:22 PM
 */

#include <QFile>
#include "Logger.hxx"

namespace even {

/** @brief Level verbosity of out line */
QMap<Logger::Severity, int> Logger::logLevel = {
    {Debug, 20},
    {Warning, 20},
    {Info, 20},
    {Critical, 10}
};

//------------------------------------------------------------------------------

Logger::Logger(Severity severity) :
    _severity(severity),
    _outMutex()
{
}

//------------------------------------------------------------------------------

void Logger::consoleMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    //fprintf(stderr, "MESSAGE (%s:%u %s): %s\n", context.file, context.line, context.function, localMsg.constData());
    fprintf(stderr, "%s\n", localMsg.constData());
    fflush(stderr);
}

//------------------------------------------------------------------------------

Logger::Message::Message(Logger& log, int level_, Severity severity, const QString& prefix,
                         const char * file, int line) :
    _log(log),
    _level(level_),
    _severity(severity),
    _prefix(prefix),
    _file(file == 0 ? QString() : file),
    _line(line),
    _ts(QDateTime::currentDateTime()),
    _content() {
}

//------------------------------------------------------------------------------
/** @brief Flush message destroy simualtaneosly  */
Logger::Message::~Message() {
    if (_severity > _log.getSeverity()) {
        return;
    }

    // If verbocity level more then predefined - breal log
    if(_level > Logger::logLevel[_severity])
        return;

    QMutexLocker locker(&(_log._outMutex));
    QDateTime dt(_ts);

    QStringList outline;

    outline << dt.toString("dd.MM.yy hh:mm:ss.zzz");

    if (!_prefix.isEmpty()) {
        outline << " [" << _prefix << "]";
    }
    if (!_file.isEmpty()) {
        outline << " " << _file << "[" << QString("%1").arg(_line) << "]";
    }
    outline << ":\t" << _content.join("");

    QString message = outline.join("");

    //< Log to console stdout
    qInstallMessageHandler(Logger::consoleMessageOutput);
    qDebug("%s", message.toLocal8Bit().data());

    //< Log to debugger window in QtCreator
    qInstallMessageHandler(0);
    //qDebug("%s", message.toLocal8Bit().data());

}

}

/** @brief Global  logger object */
even::Logger logger(even::Logger::Debug);

