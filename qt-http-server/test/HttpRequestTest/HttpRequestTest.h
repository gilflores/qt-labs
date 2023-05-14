#ifndef HTTPREQUESTTEST_H
#define HTTPREQUESTTEST_H

#include <QtTest>

class HttpRequestTest : public QObject
{
    Q_OBJECT

public:



private slots:
    void testReadRequestPath();
    void testIsValidRequest();

};

#endif // HTTPREQUESTTEST_H
