#include "wePage.h"
#include <QDebug>

class wePagePrivate
{
public:
  wePagePrivate()
  {
  }
  ~wePagePrivate()
  {
  }
};

wePage::wePage(QWidget *parent):QWebEnginePage(parent)
{
  p=new wePagePrivate();

}
wePage::wePage(QWebEngineProfile *profile,QWidget *parent):QWebEnginePage(profile,parent)
{
  p=new wePagePrivate();

}

wePage::~wePage()
{
  delete p;
}

bool wePage::certificateError(const QWebEngineCertificateError&)
{
  qDebug() << "cert error override";
  return true;
}
