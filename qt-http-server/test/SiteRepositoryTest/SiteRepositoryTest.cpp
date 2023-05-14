#include <QtTest>
#include "SiteRepositoryTest.h"
#include <QDir>
#include <QFile>
#include <QIODevice>
#include "SiteRepository.h"
#include "FileUtil.h"

// add necessary includes here

SiteRepositoryTest::SiteRepositoryTest()
{

}

SiteRepositoryTest::~SiteRepositoryTest()
{

}

/*!
 * \brief Test the constructor of the class
 */
void SiteRepositoryTest::testConstructor()
{
    SiteConfiguration configuration = SiteConfiguration::createTestConfiguration();
    SiteRepository *repository = new SiteRepository(&configuration);
    QString expected = configuration.getFullSitePath();
    QString result = repository->getSiteRepositoryFolder();
    QCOMPARE(result, expected);
}


void SiteRepositoryTest::testInit()
{
    SiteConfiguration configuration = SiteConfiguration::createTestConfiguration();

    QString siteRepository = configuration.getFullSitePath();
    qDebug() << "Directory to test " << siteRepository;
    bool resultDelete = FileUtil::deleteDirectory(siteRepository);
    QVERIFY2(resultDelete, "The repository path can't be removed");


    SiteRepository *repository = new SiteRepository(&configuration);

    QString result = repository->getSiteRepositoryFolder();
    QCOMPARE(result, siteRepository);

    bool resultInit = repository->init();
    QVERIFY2(resultInit == true, "The folder doesn't exist" );

}


/*!
 * \brief Creates a file
 * \param path
 * \param fileName
 * \return
 */
bool SiteRepositoryTest::createFile(QString path, QString fileName)
{
    QDir dir(path);
    if(!dir.exists())
    {
        dir.mkdir(path);
    }

    QFile file(path + "/" + fileName);
    if(!file.exists())
    {
        bool result = file.open(QIODevice::WriteOnly);
        return result;
    }
    return true;
}



QTEST_MAIN(SiteRepositoryTest)
