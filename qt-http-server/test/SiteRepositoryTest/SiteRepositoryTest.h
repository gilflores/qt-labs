#ifndef SITEREPOSITORYTEST_H
#define SITEREPOSITORYTEST_H

#include <QtTest>

// add necessary includes here

class SiteRepositoryTest : public QObject
{
    Q_OBJECT

public:
    SiteRepositoryTest();
    ~SiteRepositoryTest();
    static const QString DefaultBaseDirectory;

private slots:
    void testConstructor();
    void testInit();

private:
    bool deleteSiteRepository(QString path);
    bool createFile(QString path, QString file);

};


#endif // SITEREPOSITORYTEST_H
