#ifndef CUSTOMWEBPAGE_H
#define CUSTOMWEBPAGE_H

#include <QWebPage>

class CustomWebPage : public QWebPage
{
    Q_OBJECT
public:
    CustomWebPage(QObject *parent = 0);

protected:
    virtual bool supportsExtension(Extension extension) const;
    virtual bool extension(Extension extension, 
                           const ExtensionOption *option = 0, 
                           ExtensionReturn *output = 0);
};

#endif // CUSTOMWEBPAGE_H