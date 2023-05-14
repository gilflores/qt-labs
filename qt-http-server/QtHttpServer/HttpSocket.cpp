#include "HttpSocket.h"
#include <QDebug>
#include <QDataStream>

/*!
 * \brief Constructor of the class
 * \param parent
 */
HttpSocket::HttpSocket(QObject *parent, SiteRepository *site) : QTcpSocket (parent)
{
    this->siteRepository = site;

    // We connect the TcpSocket Signal to local slots
    connect(this, SIGNAL(readyRead()),
             this, SLOT(readRequest()));
    connect(this, SIGNAL(disconnected()),
            this, SLOT(deleteLater()));
}


/*!
 * \brief Read the client request
 */
void HttpSocket::readRequest()
{
    QDataStream *out = new QDataStream(this);

    QString clientRequest = this->readAll();
    HttpRequest request = HttpRequest::create(clientRequest);
    qDebug() <<"[" << this->socketDescriptor()  << "] Reading data from client" << clientRequest;
    qDebug() <<"Request: \n" <<
               " - IsWellFormed: " << request.isRequestWellFormed() << "\n" <<
               " - Http Verb:    " <<  request.getHttpVerbAsString() <<  "\n" <<
               " - Request Path: " << request.getRequestPath() <<  "\n";

    HttpResponse response = processRequest(request);
    response.writeResponse(out);
    this->flush();
}


/*!
 * \brief Process the request and prepares the information for the user
 * \param request
 * \return
 */
HttpResponse HttpSocket::processRequest(HttpRequest request)
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

