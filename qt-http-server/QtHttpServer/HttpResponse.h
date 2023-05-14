#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>
#include <QDataStream>
#include <QDate>
#include <QFileInfo>

enum HttpStatusCode
{
    OK = 200,
    BadRequest = 400,
    PageNotFound = 404
};

class HttpResponse
{
public:
    HttpResponse();
    static const QString HTTP_RESPONSE_HEADER;
    static const QString HTTP_DATE_FORMAT;
    static const QString HTTP_RESPONSE_DIRECTORY;
    static const QString HTTP_ERROR_RESPONSE;


    void writeResponse(QDataStream *stream);
    QByteArray prepareResponse();

    // Sets y gets
    HttpStatusCode getStatusCode();
    void setStatusCode(HttpStatusCode code);

    QString getContentType();
    void setContentType(QString contentType);

    long getContentLenght();

    void setContent(QByteArray content);
    QByteArray getContent();


    //Methods
    static bool log(HttpResponse *response, QString path);

    static HttpResponse* createFileResponse(
            QFileInfo file, QByteArray array, QString mimeType);

    static HttpResponse* createErrorResponse(HttpStatusCode code);

    static QString getHttpStatusCodeAsString(HttpStatusCode code);


private:
    HttpStatusCode httpStatusCode;
    QByteArray content;
    QString contentType;
    QString path;
    QString createHttpHeader(HttpStatusCode httpCode, QDateTime date,
        QString contentType, long contentLenght,
        QDateTime lastModified);


};

#endif // HTTPRESPONSE_H
