#ifndef HTTPRESPONSETEST_H
#define HTTPRESPONSETEST_H

#include <QtTest>

class HttpResponseTest : public QObject
{
    Q_OBJECT

public:
    HttpResponseTest();
    ~HttpResponseTest();

private slots:
    void testWriteResponseToAFile();
    void testCreateErrorResponse();

private:
    static const QString TestSiteFolder;
};
#endif // HTTPRESPONSETEST_H
