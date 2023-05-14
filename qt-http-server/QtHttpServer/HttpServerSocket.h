#ifndef HTTPSERVERSOCKET_H
#define HTTPSERVERSOCKET_H

#include <QObject>
#include <QTcpServer>
#include "SiteRepository.h"

class HttpServerSocket : public QTcpServer
{
    Q_OBJECT

public:    
    HttpServerSocket(QObject *parent, SiteRepository *site);

private:
    SiteRepository *siteRepository;

private slots:
    void acceptRequest();

protected:
    virtual void incomingConnection(int socketId) override;

};

#endif // HTTPSERVERSOCKET_H
