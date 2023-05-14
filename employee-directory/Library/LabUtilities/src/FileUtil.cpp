#include "FileUtil.h"
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>
#include <QProcessEnvironment>

/*!
 * \brief FileUtil::FileUtil
 */
FileUtil::FileUtil()
{

}


/*!
 * \brief Creates a file
 * \param path
 * \param fileName
 * \return
 */
bool FileUtil::createFile(QString path, QString fileName)
{
    QDir dir(path);
    if(!dir.exists())
    {
        dir.mkdir(path);
    }

    QFile file(path + "/" + fileName);
    if(!file.exists())
    {
        bool result = file.open(QIODevice::WriteOnly);
        return result;
    }
    return true;
}

/**
 * @brief Deletas a File of the system if exists
 * @param path
 * @return true if the file exists and removeit, if the file doesn't exists returns true,
 * if the file is a directory returns false;
 */
bool FileUtil::deleteFileIfExists(QString path)
{
    QFileInfo file(path);
    if(file.exists() && file.isFile())
    {
        return QFile::remove(path);
    }
    else if(!file.exists())
    {
        return true;
    }
    return false;
}

/*!
 * \brief Deletes a directory
 * \param path
 * \param deleteRecursive
 * \return
 */
bool FileUtil::deleteDirectory(QString path, bool deleteRecursive)
{
    bool result = true;
    QFileInfo dir(path);
    if(dir.exists())
    {
        if(dir.isDir())
        {
            QDir directory(path);
            if(deleteRecursive)
            {

                QFileInfoList list = directory.entryInfoList(
                            QDir::NoDotAndDotDot |
                            QDir::System |
                            QDir::Hidden  |
                            QDir::AllDirs |
                            QDir::Files,
                            QDir::DirsFirst);

                foreach(QFileInfo info, list)
                {
                    if(info.isDir())
                    {
                        result = deleteDirectory(info.absolutePath(), deleteRecursive);
                    }
                    else
                    {
                        result = QFile::remove(info.absolutePath());
                    }
                    if(!result) {
                        return result;
                    }
                }
            }
            return directory.rmdir(path);
        }
        else
        {
            qDebug() << "The path " << path << " isn't a directory.";
            return false;
        }
    }
    return result;
}


/*!
 * \brief Reads a file from directory
 * \param path
 * \param file
 * \return
 */
QByteArray FileUtil::readBinaryFile(QString path, QString file)
{
    return FileUtil::readBinaryFile(path + "/" + file);
}

/*!
 * \brief Reads a file from absolute path
 * \param absolutePath
 * \returnl
 */
QByteArray FileUtil::readBinaryFile(QString absolutePath)
{
    QByteArray bytes;
    QFile file(absolutePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        return bytes;
    }
    bytes = file.readAll();
    return bytes;
}

/*!
 * \brief Creates a directory if it not exists
 * \param path
 * \return True if the directory exist or it was created
 */
bool FileUtil::createDirectoryIfNotExists(QString path)
{
    QFileInfo dir(path);
    if(dir.exists())
    {
        return true;
    }
    else
    {
        QDir dir("./");
        return dir.mkpath(path);
    }
}

/*!
 * \brief Substitue in path the string {date} for current date time
 *  in format for file
 * \param path
 * \return
 */
QString FileUtil::addDateTimeToPath(QString path)
{
    QDateTime date = QDateTime::currentDateTime();
    path = path.replace("{date}", date.toString("yyyyMMdd_HHmmss"));
    return path;
}

/*!
 * \brief Checks if the file contains a text. This method is not created in the
 *      efficent way, it was created for testing. Avoid this method when using
 *      large files
 * \param filePath
 * \param text
 * \return
 */
bool FileUtil::containsStringTextFile(QString filePath, QString text,
        Qt::CaseSensitivity caseSensitivity)
{
    QFile file (filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QTextStream stream(&file);
    QString content = stream.readAll();
    bool result = content.contains(text,caseSensitivity);
    file.close();

    return result;
}

/*!
 * \brief Gets the value of an environment variable
 * \param variable
 * \return
 */
QString FileUtil::getSystemVariable(const QString &variable)
{
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  QString rootPath = env.value(variable);
  return rootPath;
}
