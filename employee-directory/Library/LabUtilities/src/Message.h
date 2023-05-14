#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>


/*!
 * \enum MessageType
 * \brief The MessageType enum
 */
enum MessageType {
    Debug, /*!< Is use in some cases that dev require a special message for debug
 *          or testing */
    Info, /*!< It's a informative message, some time it could use to show message
 *         to the user for instructions or notifications. */
    Warn, /*!< Is used for alerts or unexpected but controlled events */
    Error, /*!< Unexpected events, Fail o error exist in the proccess.
            This kind of messages could create problems in the application. */
    Fatal
};

/*!
 * \brief The Message class can contain a Message type to categorize the information
 * send to the user or log after process finish.
 *
 */
class Message
{

public:
    Message(MessageType type, QString content);
    Message(const MessageType type, const QString& content, const QDateTime& date);
    QString getContent() const;
    MessageType getType() const;
    bool isError() const;


private:
    MessageType  type;
    QString content;
    bool error;
    QDateTime date;
};

#endif // MESSAGE_H
