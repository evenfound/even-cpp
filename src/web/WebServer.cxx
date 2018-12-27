/**
 * @file    WebServer.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 1, 2018, 07:15 PM
 */

#include "FileConfig.hxx"
#include "WebServer.hxx"
#include "Logger.hxx"
#include "Singleton.hxx"

#include <QDir>

using namespace even;

RequestHandlerPtr WebServer::handler = nullptr;

// If you need create WebServer with config, contained in another
// file name until the default - init appName global before
// first call the WebServer::instance singleton
QString WebServer::appName = "";

//------------------------------------------------------------------------------
WebServer::WebServer(QObject* parent_)
    :HttpListener(FileConfig::instance()->group(WebServer::appName, "listener")
                  , WebServer::handler.data()
                  , parent_)
{
}

//------------------------------------------------------------------------------
WebServer* WebServer::createInstance()
{
    return new WebServer();
}

//------------------------------------------------------------------------------
WebServer::~WebServer()
{
    INFO(10) << "WebServer singleton destroyed..";
}

//------------------------------------------------------------------------------
void WebServer::appendConfig(Config* config_, QString serialPath_)
{
    if(!WebServer::handler.isNull())
        WebServer::handler->appendConfig(config_, serialPath_);
    else
        CRITICAL(1) << QString("Error adding config 0x%1 to request handler...")
                       .arg((quintptr)config_
                            , QT_POINTER_SIZE * 2, 16, QChar('0'));
}

//------------------------------------------------------------------------------
WebServer* WebServer::instance()
{
    if(WebServer::appName.isEmpty())
        WebServer::appName = QCoreApplication::applicationName() + ".web";
    if(WebServer::handler.isNull()) {
        // First create template loader issue
        QSettings* settings = new QSettings(FileConfig::instance()->searchConfigFile(WebServer::appName)
                                            , QSettings::IniFormat
                                            , QCoreApplication::instance());
        settings->beginGroup("templates");
        RequestHandler::templateCache = TemplateHolderPtr(new TemplateHolder(settings
                , QCoreApplication::instance()));
        // Configure session store
        QSettings* sessionSettings = new QSettings(FileConfig::instance()->searchConfigFile(WebServer::appName)
                                                   , QSettings::IniFormat
                                                   , QCoreApplication::instance());
        sessionSettings->beginGroup("sessions");
        RequestHandler::sessionStore = HttpSessionStorePtr(new HttpSessionStore(sessionSettings
                                                            , QCoreApplication::instance()));

        // Configure static file controller
        QSettings* fileSettings=new QSettings(FileConfig::instance()->searchConfigFile(WebServer::appName)
                                              , QSettings::IniFormat
                                              , QCoreApplication::instance());
        fileSettings->beginGroup("docroot");
        RequestHandler::staticFileController=StaticFileControllerPtr(new StaticFileController(fileSettings
                                                                      , QCoreApplication::instance()));

        // Second - create Http parser handler --
        WebServer::handler = RequestHandlerPtr(new RequestHandler(QCoreApplication::instance()));
    }
    return Singleton<WebServer>::instance(WebServer::createInstance);
}


