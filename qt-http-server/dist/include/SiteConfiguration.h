#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QString>

class SiteConfiguration
{
public:
    //Static constant
    const static QString TEST_ROOT;
    const static QString ROOT_SITE;
    const static QString DEFAULT_SITE;
    const static QString TEST_DEFAULT_SITE;
    const static QString SERVER_NAME;
    const static quint16 DEFAULT_PORT;


    SiteConfiguration();


    // Gets
    QString getFullSitePath();
    QString getRootPath();
    QString getSitePath();
    QString getServerName();
    quint16 getTcpPort();


    //Static
    static SiteConfiguration createTestConfiguration();
    static SiteConfiguration createDefaultConfiguration();

private:
    QString rootPath;
    QString sitePath;
    quint16 tcpPort;
    QString serverName;
};

#endif // CONFIGURATION_H

