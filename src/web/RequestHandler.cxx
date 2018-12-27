/**
 * @file    RequestHandler.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 19, 2018, 12:39 AM
 */

//#include <logging/filelogger.h>
#include "Logger.hxx"
#include "RequestHandler.hxx"
#include "TemplateController.hxx"
#include "SessionController.hxx"

#include <QJsonDocument>
#include <QDebug>
#include <QFile>

using namespace even;

/** Logger class */
//extern FileLogger* logger;

TemplateHolderPtr RequestHandler::templateCache = nullptr;
HttpSessionStorePtr RequestHandler::sessionStore = nullptr;
StaticFileControllerPtr RequestHandler::staticFileController = nullptr;

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

////------------------------------------------------------------------------------
//void RequestHandler::appendObject(QString name_, QObject* object_) {
//    _objectHash.insertMulti(name_, object_);
//}

//------------------------------------------------------------------------------
void RequestHandler::appendConfig(Config* config_, QString serialPath_) {
    _configHash.insertMulti((serialPath_.isEmpty())
                            ? config_->getValue(u8"object").toString()
                            : serialPath_
                              , config_);
// DEBUG out
//    for(auto e = _configHash.begin(); e != _configHash.end(); ++e)
//        INFO(15) << QString("Object %1 with %2 key")
//                    .arg((quintptr)e.value()
//                         , QT_POINTER_SIZE * 2, 16, QChar('0'))
//                    .arg(e.key());
}

//------------------------------------------------------------------------------
bool RequestHandler::parse(QString command_, HttpResponse& response_) {
    INFO(20) << QString("Have %1 command...").arg(command_);
//    if(command_ == "network") {
//        auto config = _configHash.value("network");
//        if(config != nullptr) {
//            QJsonObject json;
//            json.insert(command_, config->encode());
//            _encodeSerialize(json, response_);
//            return true;
//        }
//    } else if(command_.contains("node")
//              || command_.contains("process")) {
//        auto object = _configHash.value(command_);
//        if(object != nullptr) {
//            QJsonObject json;
//            if(object->serialize(command_, json)) {
//                _encodeSerialize(json, response_);
//                return true;
//            }
//        }
//    }
    auto object = _configHash.value(command_);
    if(object != nullptr) {
        QJsonObject json;
        if(object->serialize(command_, json)) {
            _encodeSerialize(json, response_);
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
void RequestHandler::_encodeSerialize(const QJsonObject& other_, HttpResponse& response_) {
    QJsonDocument jsonDoc(other_);
    QByteArray jsonData = jsonDoc.toJson();
    response_.setHeader("Content-Type","application/json");
    response_.setHeader("Content-Size",QByteArray::number(jsonData.size()));
    response_.write(jsonData, true);
}

//------------------------------------------------------------------------------
void RequestHandler::service(HttpRequest& request_, HttpResponse& response_)
{
    QByteArray path = request_.getPath();
    INFO(20) << QString("RequestHandler: path=%1").arg(path.data());

    // For the following pathes, each request gets its
    // own new instance of the related controller.

    if(!parse(path.remove(0, 1), response_)) {
        if (path.startsWith("/template"))
            TemplateController(templateCache.data()).service(request_, response_);
        else if (path.startsWith("/session"))
            SessionController(sessionStore.data()).service(request_, response_);
        else
            staticFileController->service(request_, response_);
    }

//    if (path.startsWith("/dump"))
//    {
//        DumpController().service(request, response);
//    }

//    else if (path.startsWith("/template"))
//    {
//        TemplateController().service(request, response);
//    }

//    else if (path.startsWith("/form"))
//    {
//        FormController().service(request, response);
//    }

//    else if (path.startsWith("/file"))
//    {
//        FileUploadController().service(request, response);
//    }

//    else if (path.startsWith("/session"))
//    {
//        SessionController().service(request, response);
//    }

    // All other pathes are mapped to the static file controller.
    // In this case, a single instance is used for multiple requests.
//    else
//    QByteArray language = request_.getHeader("Accept-Language");
//    QByteArray accept = request_.getHeader("Accept");
//    QByteArray path = request_.getPath();

//    QString file = path.data();

//    if(file[0] == "/")
//        file.remove(0, 1);
//    if(!file.length())
//        file = "index.html";

//    INFO(20) << QString("File with path: %1").arg(file);

//    if(!parse(file, response_)) {
//        INFO(20) << "Load " << qPrintable(file)
//                 << " template, codec " << language.toStdString().c_str()
//                 << QString(", enable caching %1").arg(templateCache->enable());
//        QFile stream(qPrintable(templateCache->filePath() + "/" + file));
//        Template t = (templateCache->enable())
//                ? templateCache->getTemplate(qPrintable(file), language)
//                : Template(stream, QTextCodec::codecForName("UTF-8"));
//        response_.setHeader("Content-Type", accept + "; charset=utf-8");
//        response_.write(t.toUtf8(), true);
//    }

    INFO(20) << "RequestHandler: finished request...";

    // Clear the log buffer
//    if (logger)
//    {
//        logger->clear();
//    }
}
