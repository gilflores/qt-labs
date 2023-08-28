#ifndef WEBENGINETESTMW_H_
#define WEBENGINETESTMW_H_


#include <QMainWindow>
#include <QWebEngineCertificateError>

class webEngineTestMWPrivate;
class webEngineTestMW:public QMainWindow
{
  Q_OBJECT
public:
  webEngineTestMW(QWidget *parent=0);

  virtual ~webEngineTestMW();
public slots:
  void socketConnection();
  void handleCert(const QWebEngineCertificateError&);
private:
  webEngineTestMWPrivate *p;
};


#endif
