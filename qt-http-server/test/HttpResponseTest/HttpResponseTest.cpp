#include "HttpResponseTest.h"
#include <QtTest>
#include <string>
#include <HttpResponse.h>
#include <FileUtil.h>

using namespace std;


const QString HttpResponseTest::TestSiteFolder = "./testSite";

HttpResponseTest::HttpResponseTest()
{

}
HttpResponseTest::~HttpResponseTest()
{

}

/*!
 * \brief Test the generation of a response using a file.
 * The intentions for the test are:
 * - The file with the response must be created
 * - The size of the file must be greater than content of the response
 * - The file must have the response content
 */
void HttpResponseTest::testWriteResponseToAFile()
{
    // Creating a response
    HttpResponse *response = new HttpResponse();
    QString demoHtml = "<!DOCTYPE html>"
            "<html>"
            "<body>"
            "<h1>HttpResponse</h1>"
            "<p>Testing generation</p>"
            "</body>"
            "</html>";
    response->setContent(demoHtml.toUtf8());
    response->setStatusCode(OK);
    response->setContentType("text/html");

    QByteArray bytes = response->prepareResponse();

    // Creating the file
    QString directory = HttpResponseTest::TestSiteFolder;
    QString filePath = FileUtil::addDateTimeToPath(
                directory + "/response-{date}.log");
    bool directorySite = FileUtil::createDirectoryIfNotExists(directory);
    QVERIFY2(directorySite, "The directory for testing must exists ");

    bool fileExist = HttpResponse::log(response, filePath);
    QVERIFY2(fileExist, "The file must exists");

    QFileInfo fileInfo(filePath);
    qDebug() << "The file for log: " << fileInfo.absoluteFilePath();
    long fileSize = fileInfo.size();
    QVERIFY2(fileSize > response->getContentLenght(),
        "The size of the file must be greater than content of the response");

    bool containsHtml = FileUtil::containsStringTextFile(
                fileInfo.absoluteFilePath(), demoHtml,
                Qt::CaseInsensitive);
    QVERIFY2(containsHtml, "The response must contains the html");
}

/*!
 * \brief This method test the generation of the test error response
 *  based in some Http Status Code s
 * Intentions:
 * - The response must contains the status code like Error {statusCode}
 */
void HttpResponseTest::testCreateErrorResponse()
{
    HttpStatusCode code = BadRequest;

    QString httpCodeString = HttpResponse::getHttpStatusCodeAsString(code);

    QString errorMessage = "Error " +  httpCodeString;
    HttpResponse *response = HttpResponse::createErrorResponse(code);
    QByteArray content = response->prepareResponse();

    bool result = content.contains(errorMessage.toUtf8());
    QVERIFY2(result, "The reponse must have the error code");
}

QTEST_APPLESS_MAIN(HttpResponseTest)
