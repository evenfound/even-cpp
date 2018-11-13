/**
 * @file    RequestHandler.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 19, 2018, 12:39 AM
 */

//#include <logging/filelogger.h>
#include "Logger.hxx"
#include "RequestHandler.hxx"

#include <QJsonDocument>
#include <QDebug>

using namespace even;

/** Logger class */
//extern FileLogger* logger;

TemplateHolder*  RequestHandler::templateCache = 0;

//------------------------------------------------------------------------------
RequestHandler::RequestHandler(QObject* parent)
    :HttpRequestHandler(parent)
{
    INFO(15) << "RequestHandler: created";
}

//------------------------------------------------------------------------------
RequestHandler::~RequestHandler()
{
    INFO(15) << "RequestHandler: deleted";
}

//------------------------------------------------------------------------------
void RequestHandler::appendObject(QString name_, QObject* object_) {
    _objectHash.insert(name_, object_);
}

//------------------------------------------------------------------------------
void RequestHandler::appendConfig(Config* config_) {
    _configHash.insertMulti(config_->getValue(u8"object").toString()
                       , config_);
}

//------------------------------------------------------------------------------
bool RequestHandler::parse(QString command_, HttpResponse& response_) {
    INFO(15) << QString("Have %1 command...").arg(command_);
    if(command_ == "boffin") {
        QJsonObject json;
        for(auto c: _configHash) {
            json.insert(u8"boffin", c->encode());
        }
        QJsonDocument jsonDoc(json);
        QByteArray jsonData = jsonDoc.toJson();
        response_.setHeader("Content-Type","application/json");
        response_.setHeader("Content-Size",QByteArray::number(jsonData.size()));
        response_.write(jsonData, true);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
void RequestHandler::service(HttpRequest& request_, HttpResponse& response_)
{
    QByteArray language = request_.getHeader("Accept-Language");
    QByteArray accept = request_.getHeader("Accept");
    QByteArray path = request_.getPath();

    QString file = path.data();

    if(file[0] == "/")
        file.remove(0, 1);
    if(!file.length())
        file = "index.html";

    INFO(15) << QString("File with path: %1").arg(file);

    if(!parse(file, response_)) {
        Template t = templateCache->getTemplate(qPrintable(file), language);
        response_.setHeader("Content-Type", accept + "; charset=utf-8");
        response_.write(t.toUtf8(), true);
    }

    INFO(15) << "RequestHandler: finished request...";

    // Clear the log buffer
//    if (logger)
//    {
//        logger->clear();
//    }
}
