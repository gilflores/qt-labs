#include "StringUtil.h"



StringUtil::StringUtil()
{
}

/*!
 * \brief Converts a QString to char pointer (char *). This function is used a lot in the conversion
 *      to use C functions. The function uses toLocal8Bit()
 *
 * \param string
 * \return
 */
const char* StringUtil::getCharPointer(const QString& string)
{
    QByteArray array = string.toLatin1();
    const char *stringChar = array.constData();
    return stringChar;
}
