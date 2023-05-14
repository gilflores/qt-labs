#include "HttpRequestTest.h"
#include <QtTest>
#include "HttpRequest.h"

// add necessary includes here
const QString GET_ROOT_PATH = "GET / HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
        "\r\n";

const QString GET_SUBDIR_PATH = "GET /assets/css HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
        "\r\n";

const QString GET_CSS_PATH = "GET /assets/css/bootstrap.css HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
        "\r\n";

const QString POST_URL_PATH = "POST /api/Users/findAll HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
        "\r\n";

const QString REST_HTTP1_URL_PATH = "REST /api/Users/findAll HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
        "\r\n";

const QString GET_HTTP1_0_URL_PATH = "GET /api/Users/findAll HTTP/1.0\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
        "\r\n";

const QString GET_WITHOUT_HTTP_URL_PATH = "GET /api/Users/findAll PTTP/1.0\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
        "\r\n";


/*!
 * \brief Test the isValidRequest method with the following intentions:
 * - Using the GET with HTTP 1.0 and it should pass
 * - Using the REST with HTTP 1.1 and it should not pass
 * - Using the GET without HTTP and it sould not pass
 * - Using the POST with HTTP 1.0 and it should pass
 */
void HttpRequestTest::testIsValidRequest()
{
    HttpRequest request = HttpRequest::create(GET_HTTP1_0_URL_PATH);
    bool result = request.isRequestWellFormed();
    qDebug() << "Tesing GET HTTP 1.0 ";
    QVERIFY2(result, "Using the GET with HTTP 1.0 and it should pass");

    request = HttpRequest::create(REST_HTTP1_URL_PATH);
    result = request.isRequestWellFormed();
    qDebug() << "Tesing REST HTTP 1.1 ";
    QVERIFY2(!result, "Using the REST with HTTP 1.1 and it should not pass");

    request = HttpRequest::create(GET_WITHOUT_HTTP_URL_PATH);
    result = request.isRequestWellFormed();
    qDebug() << "Tesing GET without HTTP ";
    QVERIFY2(!result, "Using the GET without HTTP and it sould not pass");

    request = HttpRequest::create(POST_URL_PATH);
    result = request.isRequestWellFormed();
    qDebug() << "Tesing POST with HTTP ";
    QVERIFY2(result, "Using the POST with HTTP 1.0 and it should pass");
}


/*!
 * \brief Test the path processor of a Request,
 * the test assumes that the Client request is valid, the intentions are:
 * - Read a GET verb with the root path
 * - Read a GET verb with a directory
 * - Read a GET verb with a file
 * - Read a POST verb with URL
 */
void HttpRequestTest::testReadRequestPath()
{
    HttpRequest request = HttpRequest::create(GET_ROOT_PATH);
    QString path = request.getRequestPath();
    QString expectedPath = "/";
    qDebug() << "Tesing GET with PATH " << expectedPath;
    QCOMPARE(path,expectedPath);

    // Intention 2 - /assets/css
    request = HttpRequest::create(GET_SUBDIR_PATH);
    path = request.getRequestPath();
    expectedPath = "/assets/css";
    qDebug() << "Tesing GET with PATH " << expectedPath;
    QCOMPARE(path,expectedPath);

    // Intention 3 - /assets/css
    request = HttpRequest::create(GET_CSS_PATH);
    path = request.getRequestPath();
    expectedPath = "/assets/css/bootstrap.css";
    qDebug() << "Tesing GET with PATH " << expectedPath;
    QCOMPARE(path,expectedPath);

    request = HttpRequest::create(POST_URL_PATH);
    path = request.getRequestPath();
    expectedPath = "/api/Users/findAll";
    qDebug() << "Tesing POST with PATH " << expectedPath;
    QCOMPARE(path,expectedPath);

}


QTEST_APPLESS_MAIN(HttpRequestTest)

