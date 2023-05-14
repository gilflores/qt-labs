#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>


/*!
 * \enum MessageType
 * \brief The MessageType enum
 */
enum MessageType {
    Debug, /*!< Is use in some cases that dev requere a special message for debuging
 *          or testing */
    Info, /*!< It's a informative message, some time it could use to show message
 *         to the user for instructions or notifications. */
    Warn, /*!< Is used for alerts or unexpected but controlled events */
    Error /*!< Unexpected events, Fail o error exist in the proccess.
            This kind of messages could create problems in the application. */
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
    QString getContent() const;
    MessageType getType() const;
    bool isError() const;


private:
    MessageType  type;
    QString content;
    bool error;

};

#endif // MESSAGE_H
