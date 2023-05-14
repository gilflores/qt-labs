#ifndef SITEREPOSITORY_H
#define SITEREPOSITORY_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QList>
#include <QMap>
#include "SiteConfiguration.h"

class SiteRepository
{
public:    
    SiteRepository(SiteConfiguration *configuration);

    bool init();
    bool isInSite(QString path);
    bool isFile(QString path);
    bool isDirectory(QString path);

    // GETS
    QString getSiteRepositoryFolder();
    QFileInfo getPathFileInfo(QString path);
    QString getMimeType(QString path);
    QByteArray getFileContent(QString path);

private:
    SiteConfiguration *siteConfiguration;
    QString siteRepositoryPath;
    QDir *baseSiteDirectory;
    QMap<QString, QString> mimeType;
    QMap<QString, QString> createMimeTypeMap();

};

#endif // SITEREPOSITORY_H
