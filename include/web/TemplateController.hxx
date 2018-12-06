/**
 * @file    TemplateController.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 26, 2018, 01:08 PM
 */

#pragma once

#include "TemplateHolder.hxx"
#include "httpserver/httprequest.h"
#include "httpserver/httpresponse.h"
#include "httpserver/httprequesthandler.h"

namespace even {
using namespace stefanfrings;

/**
  This controller generates a website using the template engine.
  It generates a Latin1 (ISO-8859-1) encoded website from a UTF-8 encoded template file.
*/

class TemplateController : public HttpRequestHandler {
        Q_OBJECT
        Q_DISABLE_COPY(TemplateController)
    public:

        /** Constructor */
        TemplateController(TemplateHolder* holder_);

        /** Generates the response */
        void service(HttpRequest& request, HttpResponse& response);
    private:
        /** Cache for template files */
        TemplateHolder* _templateCache = nullptr;

}; // class TemplateController : public HttpRequestHandler {

}; // namespace even {
