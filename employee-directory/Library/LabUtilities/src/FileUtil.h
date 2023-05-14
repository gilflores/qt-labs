#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <QString>

/*!
 * \brief Helps to create and validate files and directories. The FileUtil helps
 * in Unit testing to validate some folders or files.
 */
class FileUtil
{
public:
    FileUtil();
    static bool deleteDirectory(QString path, bool deleteRecursive = false);
    static bool deleteFileIfExists(QString path);
    static bool createFile(QString path, QString file);
    static bool createDirectoryIfNotExists(QString path);
    static QByteArray readBinaryFile(QString path, QString file);
    static QByteArray readBinaryFile(QString file);
    static QString addDateTimeToPath(QString path);
    static bool containsStringTextFile(QString filePath,
        QString text, Qt::CaseSensitivity caseSensitivity);

    static QString getSystemVariable(const QString& variable);

};

#endif // FILEUTIL_H
