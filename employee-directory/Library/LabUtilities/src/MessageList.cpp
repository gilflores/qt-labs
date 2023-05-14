#include "Message.h"
#include "MessageList.h"
#include <QRegExp>

/*!
 * \brief Constructor of the class
 */
MessageList::MessageList()
{
    withError = false;
}

/*!
 * \brief Adds a message to the list, this methods validates if the message
 *        is an error
 * \param message The object message that will be added in the list of
 *       messages
 */
void MessageList::add(const Message& message)
{
    messages.append(message);
    if(message.getType() == Error ) {
        withError = true;
    }
}

/*!
 * \brief Adds a message to the list using the type and content
 * \param type The type of message to be added
 * \param content The content for the message that will be added to the list
 */
void MessageList::add(const MessageType type, const QString& content)
{
    Message message(type, content);
    add(message);
}

void MessageList::addError(const QString &content)
{
  Message message(Error, content);
  add(message);
}

/*!
 * \brief Adds a message of type Info in the list
 * \param content The content of the message to be added
 */
void MessageList::addInfo(const QString& content)
{
    Message message(Info, content);
    add(message);
}

/*!
 * \brief Returns the number of elements in the list
 * \return The number of elements
 */
int MessageList::lenght() const
{
    return messages.length();
}


/*!
 * \brief This method indicates whether the list has at least one
 *        message of type error
 * \return True if the list has at least one error false in other case
 */
bool MessageList::hasErrors() const
{
  return withError;
}

/*!
 * \brief Creates a String with the result of the validation
 * \return
 */
QString MessageList::toString() const
{
  QString s;
  for (int i =0; i < messages.length() ; i++)
    {
      Message m = messages.at(i);
      switch (m.getType())
        {
          case Debug: s += "DEBUG -"; break;
          case Info:  s += "INFO  -"; break;
          case Warn:  s += "WARN  -"; break;
          case Error: s += "ERROR -"; break;
        }
      s += m.getContent() + "\n";
    }
  return s;
}


/*!
 * \brief This method indicates whether the list has at least one message
 * \return True if the list has at least one message of any kind false in other case
 */
bool MessageList::hasMessages() const
{
    return (lenght() > 0);
}

/*!
 * \brief Returns true if the regexp matches in at least one of the messages
 *        in the lista
 * \param regexp The regexp pattern that will be searched in the list
 * \return True if at least one message exist false in other case.
 */
bool MessageList::containsWithRegExp(const QRegExp& regexp) const
{
    foreach(Message m, messages)
    {
        if(m.getContent().contains(regexp))
        {
            return true;
        }
    }
    return false;
}

/*!
 * \brief Returns true if the regexp matches in at least one of the messages
 *        in the lista
 * \param regexpString The regexp pattern that will be searched in the list
 * \return True if at least one message exist false in other case.
 */
bool MessageList::containsWithRegExp(const QString& regexpString) const
{
    QRegExp r(regexpString);
    return containsWithRegExp(r);
}

/*!
 * \brief Returns the number of messages that contains a regular expresion
 * \param regexp The regexp pattern that will be searched in the list
 * \return Number of messages that match with regular expresion
 */
int MessageList::countWithRegExp(const QRegExp& regexp) const
{
    int elements = 0;
    foreach(Message m, this->messages)
    {
        if(m.getContent().contains(regexp))
        {
            elements++;
        }
    }
    return elements;
}

/*!
 * \brief Returns the number of messages that contains a regular expresion using a
 *        QString with regular expresion
 * \param regexp The regexp pattern that will be searched in the list
 * \return Number of messages that match with regular expresion
 */
int MessageList::countWithRegExp(const QString& regexpString) const
{
    QRegExp r(regexpString);
    return countWithRegExp(r);
}
