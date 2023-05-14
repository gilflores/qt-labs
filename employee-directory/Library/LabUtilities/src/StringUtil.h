#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <QString>

/*!
 * \brief Contains some functions that helps in string process.
 */
class StringUtil
{

public:
    static const char* getCharPointer(const QString& string);

private:
    StringUtil();
};

#endif // STRINGUTIL_H
