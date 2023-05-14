#ifndef MESSAGELIST_H
#define MESSAGELIST_H

#include "Message.h"

#include <QList>
#include <QString>



/*!
 * \brief The MessageList class contains the information of process execution in
 * a list of object of type Message.
 *
 * The list has an indicator if the list has an error message inside it.
 * The error flags tells the process has an error.
 *
 * The Messages can have the following levels:
 * - Error: Fail o error exist in the proccess
 * - Warning: Warning message that isn't an error
 * - Info: It's a informative message, some time it could use to show message
 *         to the user for instructions or notifications.
 * - Debug: Is use in some cases that dev requere a special message for debuging
 *          or testing
 *
 */
class MessageList
{
public:
    MessageList();
    void add(const Message& message);
    void add(const MessageType type, const QString& content);
    void add(const MessageType type, const QString& content, const QDateTime& date);
    void addError(const QString& content);
    void addInfo(const QString& content);
    int lenght() const;
    bool hasMessages() const;
    bool hasErrors() const;
    QString toString() const;
    bool containsWithRegExp(const QRegExp& regexp) const;
    bool containsWithRegExp(const QString& regexpString) const;
    int countWithRegExp(const QRegExp& regexp) const;
    int countWithRegExp(const QString& regexpString) const;


protected:
    QList<Message> messages;
    bool withError;
};

#endif // MESSAGELIST_H
