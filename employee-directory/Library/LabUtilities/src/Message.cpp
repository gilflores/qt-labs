#include "Message.h"

/*!
 * \brief Constructor of the class
 * \param type
 * \param content
 */
Message::Message(MessageType type, QString content)
{
    this->type = type;
    this->content = content;
    this->date = QDateTime::currentDateTime();
    if(type == Error)
    {
        this->error = true;
    }
}

/*!
 * \brief Constructor of the class
 * \param type Type of message, example: Info, Warn
 * \param content Includes the content of the message
 * \param date
 */
Message::Message(const MessageType type, const  QString& content, 
                 const  QDateTime& date)
{
  this->date = date;
  this->type = type;
  this->content = content;
  if(this->type == Error)
    {
      this->error = true;
    }
}


/*!
 * \brief Gets the value for the content
 * \return
 */
QString Message::getContent() const
{
    return content;
}


/*!
 * \brief Gets the type of the message
 * \return
 */
MessageType Message::getType() const
{
    return type;
}

/*!
 * \brief This property
 * \return
 */
bool Message::isError() const
{
    return error;
}
