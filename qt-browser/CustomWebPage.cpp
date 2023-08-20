
// mywebpage.cpp
#include "CustomWebPage.h"

#include <QMessageBox>
#include <QDebug>

CustomWebPage::CustomWebPage(QObject *parent) :
    QWebPage(parent)
{
}

bool CustomWebPage::supportsExtension(Extension extension) const
{
  qWarning() << "-------------------------------";
  qWarning() << "Testing support extension ";


  // Only support the ErrorPageExtension
  return extension == ErrorPageExtension;
}

bool CustomWebPage::extension(Extension extension, const ExtensionOption *option, ExtensionReturn *output)
{

    qWarning() << "-------------------------------";
    qWarning() << "Testing extensions";

    if (extension == ErrorPageExtension)
    {
        // Cast the option and output to the correct types
        const ErrorPageExtensionOption *errorOption = static_cast<const ErrorPageExtensionOption*>(option);
        ErrorPageExtensionReturn *errorOutput = static_cast<ErrorPageExtensionReturn*>(output);

        // Show a message box with the error information
        QMessageBox::critical(0, tr("Error"), tr("Failed to load %1: %2").arg(errorOption->url.toString(), errorOption->errorString));

        // Set the output content to an empty string
        //errorOutput->content = QString();

        return true;
    }
    return false;
}
