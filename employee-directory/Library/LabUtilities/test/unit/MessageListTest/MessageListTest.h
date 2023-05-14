#ifndef MESSAGELISTTEST_H
#define MESSAGELISTTEST_H
#include <QtTest>
#include "TestLogger.h"

class MessageListTest : public QObject
{
    Q_OBJECT

public:
    ~MessageListTest();

private:
    TestLogger* logger;


private slots:
    void init();
    void cleanup();
    void testAdd();
    void testContainsWithRegExpExistsInTheList();
    void testContainsWithRegExpNotExistsInTheList();
};

#endif // MESSAGELISTTEST_H
