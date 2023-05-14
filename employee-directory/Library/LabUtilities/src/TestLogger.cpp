#include "TestLogger.h"
#include <QDateTime>
#include <QtGlobal>

/*!
 * \brief Process the logger messages with QDebug
 * \param t Is the Qt Message type for logging wtih Qt4.8
 * \param msg The content of the message
 */
static void testLoggerHandler(QtMsgType t,const char *msg)
{
    TestLogger* logger = TestLogger::instance();
    logger->log(t, msg);
}

/*!
 * \brief Instantiate the logger
 */
TestLogger* TestLogger::INSTANCE;


/**
 * @brief Private constructor of the class
 */
TestLogger::TestLogger()
{
    list = new MessageList();
}

/*!
 * \brief Destructor of the class
 */
TestLogger::~TestLogger() {
    delete list;
    list = 0;
}

/*!
 * \brief Inits the logger, in future it could have file configurations or
 *        something like that
 */
TestLogger* TestLogger::instance()
{
    if(TestLogger::INSTANCE == 0) {
        TestLogger::newInstance();
    }
    return TestLogger::INSTANCE;
}


/*!
 * \brief Inits the logger, in future it could have file configurations or
 *        something like that
 */
TestLogger* TestLogger::newInstance()
{
    TestLogger::INSTANCE = new TestLogger();
    return TestLogger::INSTANCE;
}


void TestLogger::stop() {
    qInstallMsgHandler(testLoggerHandler);
}

/*!
 * \brief Clean the list of the log
 */
void TestLogger::clean() {
    this->list = new MessageList();
}

/*!
 * \brief TestLogger::getList
 * \return
 */
MessageList* TestLogger::getList()
{
    return list;
}


/*!
 * \brief Log a message using QDebug
 * \param t
 * \param msg
 */
void TestLogger::log(QtMsgType type, const char *msg)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    QString result;
    QTextStream text(&result);
    text << "[" << qPrintable(timestamp) << "]"
         << "---" ;


    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "[%s]---Debug: %s\n", qPrintable(timestamp), msg);
        text << "Debug: " << msg;
        list->add(Info, qPrintable(result));
        break;
    case QtWarningMsg:
        fprintf(stderr, "[%s]---Warning: %s\n", qPrintable(timestamp), msg);
        text << "Warning: " << msg;
        list->add(Warn, qPrintable(result));
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[%s]---Critical: %s\n", qPrintable(timestamp), msg);
        text << "Critical: " << msg;
        list->add(Error, qPrintable(result));
        break;
    case QtFatalMsg:
        fprintf(stderr, "[%s]---Fatal: %s\n", qPrintable(timestamp), msg);
        text << "Fatal: " << msg;
        list->add(Error, qPrintable(result));
        break;
    }
}

