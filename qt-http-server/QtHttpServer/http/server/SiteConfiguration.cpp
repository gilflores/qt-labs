#include "SiteConfiguration.h"


const QString SiteConfiguration::TEST_ROOT = "/home/dev/test";
const QString SiteConfiguration::TEST_DEFAULT_SITE = "/sites/testSite";
const QString SiteConfiguration::ROOT_SITE = ".";
const QString SiteConfiguration::DEFAULT_SITE = "/sites";
const QString SiteConfiguration::SERVER_NAME = "C++Grizzly";
const quint16 SiteConfiguration::DEFAULT_PORT = 8080;

SiteConfiguration::SiteConfiguration()
{

}

/*!
 * \brief Creates the site configuration for test environment
 * \return
 */
SiteConfiguration SiteConfiguration::createTestConfiguration()
{
    SiteConfiguration *config = new SiteConfiguration();
    config->rootPath = SiteConfiguration::TEST_ROOT;
    config->sitePath = SiteConfiguration::TEST_DEFAULT_SITE;
    config->tcpPort = 8081;
    config->serverName = SiteConfiguration::SERVER_NAME;
    return *config;
}

/*!
 * \brief Creates the configuration for the web server
 * \return
 */
SiteConfiguration SiteConfiguration::createDefaultConfiguration()
{
    SiteConfiguration *config = new SiteConfiguration();
    config->rootPath = SiteConfiguration::ROOT_SITE;
    config->sitePath = SiteConfiguration::DEFAULT_SITE;
    config->tcpPort = 8080;
    config->serverName = SiteConfiguration::SERVER_NAME;
    return *config;
}

/*!
 * \brief Returns the full site path
 * \return
 */
QString SiteConfiguration::getFullSitePath()
{
    return this->rootPath + this->sitePath;
}



QString SiteConfiguration::getRootPath()
{
    return this->rootPath;
}
QString SiteConfiguration::getSitePath()
{
    return this->sitePath;
}
QString SiteConfiguration::getServerName()
{
    return this->serverName;
}
quint16 SiteConfiguration::getTcpPort()
{
    return this->tcpPort;
}

