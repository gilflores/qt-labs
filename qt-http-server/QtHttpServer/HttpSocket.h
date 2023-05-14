#ifndef REQUESTSOCKET_H
#define REQUESTSOCKET_H

#include <QTcpSocket>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "SiteRepository.h"

class HttpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    HttpSocket(QObject *parent, SiteRepository *site);
    // Public for testing
    HttpResponse processRequest(HttpRequest request);

private slots:
    void readRequest();

private:
    SiteRepository *siteRepository;
    HttpRequest createRequest();
};

#endif // REQUESTSOCKET_H
