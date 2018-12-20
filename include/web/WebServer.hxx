/**
 * @file    WebServer.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 1, 2018, 07:02 PM
 */

#pragma once

#include "httpserver/httplistener.h"
#include "RequestHandler.hxx"


namespace even {

using namespace stefanfrings;

/**
 * @brief @brief Synonims of shared pointer object types
 */
typedef QSharedPointer<RequestHandler> RequestHandlerPtr;

/** @brief Entity of WebServer object */
class WebServer : public HttpListener
{
    public:
        virtual ~WebServer();

        /** @brief Take a singleton object pointer */
        static WebServer* instance();

        /** @brief Add config array to request handler */
        void appendConfig(Config* config_, QString serialPath_="");

    private:
        explicit WebServer(QObject* parent_ = nullptr);

        /** @brief Create singleton once object */
        static WebServer* createInstance();

        /** @brief Appname for object if singletoning it's */
        static QString appName;

        /** @brief Pointer to request handler object */
        static RequestHandlerPtr handler;

};
};

