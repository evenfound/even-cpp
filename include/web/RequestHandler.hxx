/**
 * @file    RequsetHandler.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 19, 2018, 12:34 AM
 */

#pragma once

#include "Config.hxx"
#include "TemplateHolder.hxx"
#include "httpserver/httprequesthandler.h"
#include "templateengine/templatecache.h"

#include <QSharedPointer>

namespace even {

using namespace stefanfrings;

/**
 * @brief Entity for request handler receives incoming HTTP requests and generates responses.
 */

class Config;
class TemplateHolder;

class RequestHandler : public HttpRequestHandler {
        Q_OBJECT
        Q_DISABLE_COPY(RequestHandler)
    public:
        /**
         * @brief Teamplate file buffer
         */
        static TemplateHolder* templateCache;
        /**
         * @brief Constructor.
         * @param parent Parent object
         */
        RequestHandler(QObject* parent = nullptr);

        /** @brief Add config array to reuqest handler */
        void appendConfig(Config* config_, QString serialPath_="");

        /**
         * @brief Destructor
         */
        ~RequestHandler() final;

        /**
         * @brief Process an incoming HTTP request.
         * @param request The received HTTP request
         * @param response Must be used to return the response
         */

        void service(HttpRequest& request, HttpResponse& response) final;

        /** @brief Parse request message and return responce data */
        bool parse(QString command_, HttpResponse& response_);

    private:
        /** @brief Pack Json object to responce and sent it to client. */
        void _encodeSerialize(const QJsonObject& other_, HttpResponse &response_);

        /** @brief Hash array of Config pointers array. */
        QHash<QString, Config*> _configHash;

};

};
