#include "HttpServer.h"
#include <QTcpServer>
#include <QDebug>
#include <QString>
#include <QHostAddress>
#include "HttpSocket.h"
#include "SiteConfiguration.h"




/*!
 * \brief Constructor of the class
 * \param parent
 */
HttpServer::HttpServer(QObject *parent, SiteConfiguration *configuration)
    : QObject (parent)
{
    homePage = "index.html";
    status = STOPED;
    siteRepository = new SiteRepository(configuration);
    this->configuration = configuration;
}



/*!
 * \brief Starts the TCP server
 * \return
 */
bool HttpServer::start()
{
    this->siteRepository->init();

    this->tcpServer = new HttpServerSocket(this, this->siteRepository);


    // We use the default port to listen the request
    if(!tcpServer->listen(QHostAddress::Any, configuration->getTcpPort()))
    {
        qDebug() << "Server could not start";
        return false;
    }
    qDebug() << "Server " << configuration->getServerName() <<
                "  started at port " << configuration->getTcpPort() << "!!";
    qDebug() << "Publishing site: " << configuration->getFullSitePath() << "!!";

    qDebug() << "Publishing Directory: " << QFileInfo(configuration->getFullSitePath()).absolutePath() << "!!";
    return true;
}


/*!
 * \brief HttpServer::getHomePage
 * \return
 */
QString HttpServer::getHomePage()
{
    return homePage;
}
