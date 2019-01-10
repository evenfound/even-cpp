/**
 * @file    SessionController.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 26, 2018, 01:36 PM
 */

#pragma once

#include "httpserver/httprequest.h"
#include "httpserver/httpresponse.h"
#include "httpserver/httprequesthandler.h"
#include "httpserver/httpsessionstore.h"

namespace even {
using namespace stefanfrings;

/**
  This controller for use sessions.
*/

class SessionController : public HttpRequestHandler {
        Q_OBJECT
        Q_DISABLE_COPY(SessionController)
    public:

        /** Constructor */
        SessionController(HttpSessionStore* session_);

        /** Generates the response */
        void service(HttpRequest& request, HttpResponse& response);

    private:
        HttpSessionStore* _session = nullptr;

}; // class SessionController : public HttpRequestHandler {

}; // namespace even {
