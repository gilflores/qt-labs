#ifndef WEPAGE_H_
#define WEPAGE_H_


#include <QWebEnginePage>


class wePagePrivate;
class wePage:public QWebEnginePage
{
  Q_OBJECT
public:
  wePage(QWidget *parent=0);
  wePage(QWebEngineProfile *profile,QWidget *parent=0);
  virtual ~wePage();
protected:
  bool certificateError(const QWebEngineCertificateError&);
private:
  wePagePrivate *p;
};


#endif
