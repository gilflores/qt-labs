#include "SiteRepository.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <FileUtil.h>



/*!
 * \brief Constructor of the class
 * \param path
 */
SiteRepository::SiteRepository(SiteConfiguration *configuration)
{
    siteConfiguration = configuration;
    QString path = configuration->getFullSitePath();
    siteRepositoryPath = path;
    baseSiteDirectory = new QDir(path);
    mimeType = createMimeTypeMap();
}


QString SiteRepository::getSiteRepositoryFolder()
{
   return siteRepositoryPath;
}

/*!
 * \brief Initialize the folder of repository if it does not exist
 * \return
 */
bool SiteRepository::init()
{
    QFileInfo siteRepositoryDir(getSiteRepositoryFolder());
    if(siteRepositoryDir.exists())
    {
        if(siteRepositoryDir.isDir())
        {
            return true;
        }
        else
        {
            qDebug() << "The path " << getSiteRepositoryFolder() << " isn't a directory.";
            return false;
        }
    }
    else
    {
        qDebug() << "Creating directory " << getSiteRepositoryFolder();
        QDir directory(getSiteRepositoryFolder());
        bool directoryCreated = directory.mkpath(getSiteRepositoryFolder());
        if(directoryCreated)
        {
            return true;
        }
        return false;
    }
}

/*!
 * \brief Verifies if the file or directory exists in repository
 * \param path
 * \return
 */
bool SiteRepository::isInSite(QString path)
{
    QString fullPath = this->siteRepositoryPath + "/" +
            path;
    QFileInfo file(fullPath);
    return file.exists();

}

QByteArray SiteRepository::getFileContent(QString path)
{
    QString fullPath = this->siteRepositoryPath + "/" + path;
    QByteArray content = FileUtil::readBinaryFile(fullPath);
    return content;
}


/*!
 * \brief Checks if the path is a file
 * \param path
 * \return
 */
bool SiteRepository::isFile(QString path)
{
    QString fullPath = this->siteRepositoryPath + "/" +
            path;
    QFileInfo file(fullPath);
    return file.isFile();
}

/*!
 * \brief Check if the path is a directory
 * \param path
 * \return
 */
bool SiteRepository::isDirectory(QString path)
{
    QString fullPath = this->siteRepositoryPath + "/" +
            path;
    QFileInfo file(fullPath);
    return file.isFile();
}

/*!
 * \brief Gets the file info of the file
 * \param path
 * \return
 */
QFileInfo SiteRepository::getPathFileInfo(QString path){
    QString fullPath = this->siteRepositoryPath + "/" +
            path;
    QFileInfo file(fullPath);
    return file;
}

/*!
 * \brief Reads the mime type for a path
 * \param path
 * \return
 */
QString SiteRepository::getMimeType(QString path) {
    QFileInfo fileInfo(path);
    QString ext = fileInfo.suffix();
    QString contentType;
    if(!ext.isNull())
    {
        contentType = this->mimeType.value("." + ext);
        if(contentType.isNull()) {
            contentType = this->mimeType.value("stream");
        }
    }
    else
    {
        contentType = this->mimeType.value("stream");
    }
    return contentType;
}



/*!
 * \brief createmimeTypeMao
 * \return
*/
QMap<QString, QString> SiteRepository::createMimeTypeMap() {
    QString tipoImagen = "image/";
    QString tipoTexto = "text/";
    QString tipoAplicacion = "application/";
    QMap<QString, QString> mimeType;
    mimeType[".jpg"] = "";
    mimeType[".html"] = tipoTexto + "html";
    mimeType[".htm"] = tipoTexto + "htm";
    mimeType[".txt"] = tipoTexto + "plain";
    mimeType[".css"] = tipoTexto + "css; charset=utf-8";
    mimeType[".js"] = tipoAplicacion + "javascript; charset=utf-8";
    // tipos para imagen
    mimeType[".gif"] = tipoImagen + "gif";
    mimeType[".jpg"] = tipoImagen + "jpeg";
    mimeType[".jpeg"] = tipoImagen + "jpeg";
    mimeType[".png"] = tipoImagen + "png";
    // Tipo Excel
    mimeType[".xls"] = tipoAplicacion + "vnd.ms-excel";
    // Tipo default
    mimeType["stream"] = "application/octet-stream";
    return mimeType;
}



