/**
  @file
  @author Stefan Frings
*/

#include "SessionController.hxx"

#include <QDateTime>

using namespace even;

//------------------------------------------------------------------------------
SessionController::SessionController(HttpSessionStore* session_)
    : _session(session_)
{}

//------------------------------------------------------------------------------
void SessionController::service(HttpRequest& request, HttpResponse& response) {

    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    // Get current session, or create a new one
    HttpSession session = _session->getSession(request,response);
    if (!session.contains("startTime"))
    {
        response.write("<html><body>New session started. Reload this page now.</body></html>");
        session.set("startTime",QDateTime::currentDateTime());
    }
    else
    {
        QDateTime startTime=session.get("startTime").toDateTime();
        response.write("<html><body>Your session started ");
        response.write(startTime.toString().toLatin1());
        response.write("</body></html>");
    }

}
