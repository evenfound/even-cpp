/**
 * @file    TemplateController.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 26, 2018, 01:10 AM
 */

#include "TemplateController.hxx"

using namespace even;

//------------------------------------------------------------------------------
TemplateController::TemplateController(TemplateHolder* holder_)
    : _templateCache(holder_) {

}

//------------------------------------------------------------------------------
void TemplateController::service(HttpRequest& request, HttpResponse& response)
{
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    Template t = _templateCache->getTemplate("demo",request.getHeader("Accept-Language"));
    t.enableWarnings();
    t.setVariable("path",request.getPath());

    QMap<QByteArray,QByteArray> headers=request.getHeaderMap();
    QMapIterator<QByteArray,QByteArray> iterator(headers);
    t.loop("header",headers.size());
    int i=0;
    while (iterator.hasNext())
    {
        iterator.next();
        t.setVariable(QString("header%1.name").arg(i),QString(iterator.key()));
        t.setVariable(QString("header%1.value").arg(i),QString(iterator.value()));
        ++i;
    }

    response.write(t.toLatin1(),true);
}
