#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QString>
enum HttpVerb {
    GET = 0,
    POST = 1,
    PUT = 2,
    DELETE = 3,
    OTHER = 99,
};


class HttpRequest
{
public:

    static const QString HTTP_1_1;
    static const QString HTTP_1_0;
    static const QString GET_VERB;
    static const QString POST_VERB;
    static const QString PUT_VERB;
    static const QString DELETE_VERB;


    static HttpRequest create(QString clientRequest);
    static bool isValidRequest(QString clientRequest);
    static bool hasHttpRequestVerb(QString request);
    static bool hasHttpVersion(QString request);

    // Properties
    bool isRequestWellFormed();
    HttpVerb getHttpVerb();
    QString getRequestPath();
    QString getHttpVerbAsString();

private:
    HttpRequest();
    bool requestWellFormed;
    HttpVerb httpVerb;
    QString requestPath;


    HttpVerb readHttpVerb(QString clientRequest);
    QString getHttpVerbAsString(HttpVerb verb);
    QString readRequestPath(HttpVerb httpVerb, QString clientRequest);


};

#endif // HTTPREQUEST_H
