#include "TestLogger.h"
#include <QDateTime>
#include <QtGlobal>


#if (QT_VERSION < 0x050000)
/*!
 * \brief Process the logger messages with QDebug
 * \param t
 * \param msg
 */
static void testLoggerHandler(QtMsgType type, const char *msg)
{
  testLogger* logger = TestLogger::instance();
  logger->log(type, msg);
}
#endif

#if (QT_VERSION >= 0x050000)
static void qtLogger5(QtMsgType type, const QMessageLogContext& context, const QString& msg )
{
  TestLogger* logger = TestLogger::instance();
  logger->logQt5(type, context, msg);
}
#endif


/*!
 * \brief Instantiate the logger
 */
TestLogger* TestLogger::INSTANCE;


/**
 * @brief Private constructor of the class
 */
TestLogger::TestLogger()
{
    list = MessageList();
}

/*!
 * \brief Destructor of the class
 */
TestLogger::~TestLogger() {
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
  // Turn off the library messages and only use the traces
#if (QT_VERSION < 0x050000)
  qInstallMsgHandler(testLoggerHandler);
#else
  qInstallMessageHandler(qtLogger5);
#endif
}

/*!
 * \brief Clean the list of the log
 */
void TestLogger::clean() {
    this->list = MessageList();
}

/*!
 * \brief TestLogger::getList
 * \return
 */
const MessageList& TestLogger::getList() const {
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
        list.add(Info, qPrintable(result));
        break;
    case QtWarningMsg:
        fprintf(stderr, "[%s]---Warning: %s\n", qPrintable(timestamp), msg);
        text << "Warning: " << msg;
        list.add(Warn, qPrintable(result));
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[%s]---Critical: %s\n", qPrintable(timestamp), msg);
        text << "Critical: " << msg;
        list.add(Error, qPrintable(result));
        break;
    #if (QT_VERSION >= 0x050000)
    case QtInfoMsg:
        list.add(Info, qPrintable(result));
        break;
    #endif
    case QtFatalMsg:
        fprintf(stderr, "[%s]---Fatal: %s\n", qPrintable(timestamp), msg);
        text << "Fatal: " << msg;
        list.add(Error, qPrintable(result));
        break;
    }
}

#if (QT_VERSION >= 0x050000)
void TestLogger::logQt5(QtMsgType type, const QMessageLogContext& context, const QString& msg )
{

  const QDateTime now = QDateTime::currentDateTime();
  QString timestamp = now.toString("yyyy/MM/dd hh:mm:ss");
  QString result;

  switch (type) {
  case QtDebugMsg:
      printLogQt5(context, msg, "Debug", timestamp);
      list.add(Info, qPrintable(msg), now);
      break;
  case QtWarningMsg:
      printLogQt5(context, msg, "Warning", timestamp);
      list.add(Warn, qPrintable(msg), now);
      break;
  case QtCriticalMsg:
      printLogQt5(context, msg, "Critical", timestamp);
      list.add(Error, qPrintable(msg), now);
      break;
  case QtInfoMsg:
      printLogQt5(context, msg, "Info", timestamp);
      list.add(Info, qPrintable(msg), now);
      break;
  case QtFatalMsg:
      printLogQt5(context, msg, "Fatal", timestamp);
      list.add(Fatal, qPrintable(msg), now);
      break;
  }
}

/**
 * @brief Print in the standar output the Log information
 * @param context
 * @param msg
 * @param level
 * @param timestamp
 */
void TestLogger::printLogQt5(const QMessageLogContext& context,
                             const QString& msg,
                             const QString& level,
                             const QString& timestamp) {
  const char *file = context.file ? context.file : "";
  const char *function = context.function ? context.function : "";
  fprintf(stdout, "[%s][%s::%s:line:%d]---%s: %s\n",
          qPrintable(timestamp), file, function,
          context.line, qPrintable(level), qPrintable(msg));
}
#endif


