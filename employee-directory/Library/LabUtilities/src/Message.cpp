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
    if(type == Error)
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
