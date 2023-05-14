#include "MessageListTest.h"
#include "MessageList.h"

/*!
 * \brief Removes the reourses for the tests. We need this method because we
 *
 */
MessageListTest::~MessageListTest()
{
    if(logger != 0) 
      {
        delete logger;
        logger = 0;
      }
    
}


/*!
 * \brief Inits the information of the test case
 */
void MessageListTest::init()
{
    // Begin the logger for testing methods
    logger = TestLogger::newInstance();
    //qDebug() << "Log prepared";
}

/*!
 * \brief Removes the resources for the test methods
 */
void MessageListTest::cleanup()
{
    qDebug() << "Cleaning the log";
    TestLogger::instance()->clean();
}

/*!
 * \brief Test the adding elements to a message list
 *        - The list must contains 2 elements
 *        - After add one element the list must contains 3 elements
 *        - The list must contains 3 messages with pattern "Message number :number"
 */
void MessageListTest::testAdd()
{
    qDebug() << "Test add method";
    MessageList list;
    list.addInfo("Message number 1");
    list.addInfo("Message number 2");
    int expected = 2;
    QCOMPARE(expected, list.lenght());

    list.addInfo("Message number 3");
    expected = 3;
    QCOMPARE(expected, list.lenght());

    QString regexpString = "^(Message number [0-9]{1})";
    int result = list.countWithRegExp(regexpString);
    QVERIFY2(expected == result, "The list must contains 3 messages "
                            "with pattern 'Message number :number'");
}

/*!
 * \brief Test the methods containsWithRegExp() using the following intentions:
 *        - The list must contains a message for first name
 *        - The list must contains a message for address is requerid
 */
void MessageListTest::testContainsWithRegExpExistsInTheList()
{
    MessageList list;
    list.addInfo("The first name of the employee must have 10 characters");
    list.addInfo("The last name of the employee must have 10 characters");
    list.addInfo("The addres of the employee is required");

    QString regexpString = "^(The last name of the employee must have [0-9]{0,9} characters)";
    bool containsMessage = list.containsWithRegExp(regexpString);
    QString message = "The message list must have a message for first name " + regexpString;
    QVERIFY2(containsMessage, message.toUtf8());

    regexpString = "^(The addres of the employee is required)";
    containsMessage = list.containsWithRegExp(regexpString);
    message = "The message list must have a message for first name " + regexpString;
    QVERIFY2(containsMessage, message.toUtf8());
}

/*!
 * \brief Test the methods containsWithRegExp() using the following intentions:
 *        - The list doesn't contains a message for phone
 *        - The list doesn't contains a message for first name is requerid
 */
void MessageListTest::testContainsWithRegExpNotExistsInTheList()
{
    MessageList list;
    list.addInfo("The first name of the employee must have 10 characters");
    list.addInfo("The last name of the employee must have 10 characters");
    list.addInfo("The addres of the employee is required");

    QString regexpString = "^(The phone is requerid)";
    bool containsMessage = list.containsWithRegExp(regexpString);
    QString message = "The message list must have a message for phone " + regexpString;
    QVERIFY2(!containsMessage, message.toUtf8());

    regexpString = "^(The first name of the employee is required)";
    containsMessage = list.containsWithRegExp(regexpString);
    message = "The message list must have a message for first name " + regexpString;
    QVERIFY2(!containsMessage, message.toUtf8());
}


QTEST_APPLESS_MAIN(MessageListTest)
