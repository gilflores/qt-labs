#include "HttpServerSocket.h"
#include "HttpSocket.h"
#include <QDebug>
#include <QTcpSocket>

/*!
 * \brief Constructor of the class
 * \param parent
 */
HttpServerSocket::HttpServerSocket(QObject *parent, SiteRepository *site)
    : QTcpServer(parent)
{
    this->siteRepository = site;

    // QT has the hability to emit signal when a sockets is connected
    // we use the connect of QObject to brind the newConnection() of
    // TcpServer with my local method acceptRequest()
    connect(this, SIGNAL(newConnection()),
            this, SLOT(acceptRequest()));
}

/*!
 * \brief Accept incmming connections we use this connection schema to try
 *          use QThread Later
 * \param socketId
 */
void HttpServerSocket::incomingConnection(int socketId)
{
    qDebug () << "HttpServer incomming Connections id: " << socketId;
    HttpSocket *socket = new HttpSocket(this, siteRepository);
    socket->setSocketDescriptor(socketId);

}

void HttpServerSocket::acceptRequest()
{
    qDebug () << "HttpServer Accept request ";
}
