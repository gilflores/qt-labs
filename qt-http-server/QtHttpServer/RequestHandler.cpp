#include "RequestHandler.h"
#include <QtDebug>

HttpRequestHandler::HttpRequestHandler(SiteRepository *site)
{
    this->siteRepository = site;
}


/*!
 * \brief Process the request
 * \param site
 * \param request
 * \return
 */
HttpResponse HttpRequestHandler::processRequest(HttpRequest request)
{
    qDebug() << "Reading request path " << request.getRequestPath();
    HttpResponse *response;
    QString path = request.getRequestPath();
    if(this->siteRepository->isInSite(path))
    {
        if(this->siteRepository->isFile(path))
        {
            QFileInfo fileInfo = siteRepository->getPathFileInfo(path);
            QString mimeType = siteRepository->getMimeType(path);
            QByteArray content = siteRepository->getFileContent(path);

            response = HttpResponse::createFileResponse(fileInfo, content, mimeType);
        }
        else
        {
            //We asume that we only have files an directories
            qDebug() << "Reading directory";
            response = new HttpResponse();
            QString htmlForDirectory = HttpResponse::HTTP_RESPONSE_DIRECTORY;
            htmlForDirectory = htmlForDirectory.replace("{directory}", path);
            response->setContent(htmlForDirectory.toUtf8());
            response->setStatusCode(OK);
            response->setContentType("text/html");
        }
    }
    else
    {
        response = HttpResponse::createErrorResponse(PageNotFound);
    }
    return *response;
}
