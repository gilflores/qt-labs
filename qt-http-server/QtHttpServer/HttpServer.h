#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QString>
#include "HttpRequest.h"
#include "SiteRepository.h"
#include "HttpServerSocket.h"

/*!
 * \brief This enum helps to check the status of the server
 */
enum ServerStatus {
    STOPED = 0,
    STARTED = 1
};

/*!
 * \brief Controls the http server in the application
 */
class HttpServer : public QObject
{
    Q_OBJECT

public:

    HttpServer(QObject *parent, SiteConfiguration *configuration);

    bool start();
    bool stop();
    QString getHomePage();
    ServerStatus getStatus();



private:
    QString homePage;    
    ServerStatus status;

    HttpServerSocket *tcpServer;
    SiteRepository *siteRepository;
    SiteConfiguration *configuration;

};

#endif // HTTPSERVER_H
