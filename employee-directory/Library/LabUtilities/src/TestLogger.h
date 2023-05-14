#ifndef TESTLOGGER_H
#define TESTLOGGER_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>

#include "MessageList.h"

/*!
 * \brief Helps to test the message send it to the logger using QDebug.
 * It's used specially in testing to validate the messages of the process.
 */
class TestLogger
{


public:
    ~TestLogger();
    void log(QtMsgType t, const char *msg);
    #if (QT_VERSION >= 0x050000)
    void logQt5(QtMsgType type, const QMessageLogContext& context, const QString& msg );
    void printLogQt5(const QMessageLogContext& context,
                     const QString& msg, const QString& level, const QString& timestamp);
    #endif

    static TestLogger* instance();
    static TestLogger* newInstance();
    const MessageList& getList() const;
    void clean();
    void stop();

private:
    TestLogger();
    
    // Why we use pointers not only a variable
    MessageList list;
    static TestLogger* INSTANCE;
};

#endif // TESTLOGGER_H

