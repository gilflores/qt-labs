#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <QString>

/*!
 * \brief Creates the
 */
class FileUtil
{
public:
    FileUtil();
    static bool deleteDirectory(QString path, bool deleteRecursive = false);
    static bool createFile(QString path, QString file);
    static bool createDirectoryIfNotExists(QString path);
    static QByteArray readBinaryFile(QString path, QString file);
    static QByteArray readBinaryFile(QString file);
    static QString addDateTimeToPath(QString path);
    static bool containsStringTextFile(QString filePath,
        QString text, Qt::CaseSensitivity caseSensitivity);

};

#endif // FILEUTIL_H
