#include "HttpResponse.h"
#include <string>
#include <QDataStream>
#include <QDebug>


using namespace std;

const QString HttpResponse::HTTP_RESPONSE_HEADER = "HTTP/2.0 {httpStatusCode} OK\r\n"
     "Date:  {date}\r\n"
     "Server: {serverName}/1.0\r\n"
     "Content-Type: {contentType}\r\n"
     "Expires: Sun, 01 Feb 2020 00:00:00 GMT\r\n"
     "Content-Length: {contentLengt} \r\n"
     "Last-modified: {lastModified} \r\n"
     "\r\n";

const QString HttpResponse::HTTP_RESPONSE_DIRECTORY = "<!DOCTYPE html>"
     "<html>"
     "<body>"
     "<h1>Directory {directory}</h1>"
     "<h2>Content.</h2>"
     "{content}"
     "</body>"
     "</html>";

const QString HttpResponse::HTTP_ERROR_RESPONSE = "<!DOCTYPE html>"
    "<html>"
    "   <title>Error {statusCode}</title>"
    "<body>"
    "<h1>Problem reading the content</h1>"
    "{message}"
    "</body>"
    "</html>";

const QString HttpResponse::HTTP_DATE_FORMAT = "ddd, dd MMM yyyy hh:mm:ss";

HttpResponse::HttpResponse()
{

}

/*!
 * \brief Writes the response over HTTP
 * \param stream
 */
void HttpResponse::writeResponse(QDataStream *stream)
{
    QByteArray bytes = prepareResponse();
    stream->writeRawData(bytes.data(), bytes.length());
}

/*!
 * \brief Prepares all the response for the server
 * \return
 */
QByteArray HttpResponse::prepareResponse()
{
    QString responseHeader = createHttpHeader(
        this->httpStatusCode,
        QDateTime::currentDateTimeUtc(),
        this->contentType,
        this->getContentLenght(),
        QDateTime::currentDateTimeUtc());

    QByteArray bytes = responseHeader.toUtf8();    
    qDebug() << "Adding response content";
    bytes.append(this->content);
    return bytes;
}

/*!
 * \brief Creates a http response for a file in the site
 * \param fileInfo
 * \param content
 * \param mimeType
 * \return
 */
HttpResponse* HttpResponse::createFileResponse(QFileInfo fileInfo,
    QByteArray content, QString mimeType)
{
    HttpResponse *response = new HttpResponse();
    response->httpStatusCode = OK;
    response->content = content;
    response->contentType = mimeType;
    response->path = fileInfo.path();
    return response;
}

/*!
 * \brief Creates a response for Error response
 * \param code
 * \return
 */
HttpResponse* HttpResponse::createErrorResponse(HttpStatusCode code)
{
    QString htmlError = HttpResponse::HTTP_ERROR_RESPONSE;

    QString httpCodeString = getHttpStatusCodeAsString(code);
    htmlError = htmlError.replace("{statusCode}", httpCodeString);

    HttpResponse *response = new HttpResponse();
    response->httpStatusCode = code;
    response->setContent(htmlError.toUtf8());
    //Move to a constant
    response->contentType = "text/html";
    return response;
}

/*!
 * \brief Transform the http status code to string
 * \param code
 * \return
 */
QString HttpResponse::getHttpStatusCodeAsString(HttpStatusCode code)
{
    QString httpCodeString = QString::fromUtf8(to_string(code).c_str());
    return httpCodeString;
}


/*!
 * \brief Creates the HTTP header fpr a request
 * \param httpCode
 * \param date
 * \param contentType
 * \param contentLenght
 * \param lastModified
 * \return
 */
QString HttpResponse::createHttpHeader(
        HttpStatusCode httpCode, QDateTime date,
        QString contentType, long contentLenght,
        QDateTime lastModified)
{

    QString httpCodeString = getHttpStatusCodeAsString(httpCode);
    QString lenght = QString::fromUtf8(to_string(contentLenght).c_str());

    QString header = HTTP_RESPONSE_HEADER;
    header = header.replace("{httpStatusCode}", httpCodeString);
    header = header.replace("{date}",
                date.toString());
    header = header.replace("{serverName}", "QtServer");
    header = header.replace("{contentType}", contentType);
    header = header.replace("{contentLengt}", lenght);
    header = header.replace("{lastModified}",
                lastModified.toString());
    return header;

}

/*!
 * \brief Logs the response in a file
 * \param response
 * \param path If the path contains the string {date} the log will add the
 *      date and time to the file name;
 * \return True if the file created or exists
 */
bool HttpResponse::log(HttpResponse *response, QString path)
{
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QDataStream *out = new QDataStream(&file);
    //Writting the response
    response->writeResponse(out);
    // Clossing the file
    file.close();
    return file.exists();
}


// -- Gets y Sets ----------------------------------------

HttpStatusCode HttpResponse::getStatusCode()
{
    return this->httpStatusCode;
}

void HttpResponse::setStatusCode(HttpStatusCode code)
{
    this->httpStatusCode = code;
}

QString HttpResponse::getContentType()
{
    return this->contentType;
}
void HttpResponse::setContentType(QString contentType)
{
    this->contentType = contentType;
}

long HttpResponse::getContentLenght()
{
    if(!this->content.isNull() && this->content.length() > 0)
    {
        return this->content.length();
    }
    return 0;
}

void HttpResponse::setContent(QByteArray c)
{
    this->content = c;
}
QByteArray HttpResponse::getContent()
{
    return content;
}

