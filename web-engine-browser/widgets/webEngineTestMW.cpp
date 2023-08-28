#include "webEngineTestMW.h"
#include <QDebug>
#include <QApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include "testProfile.h"
#include  <QMessageBox>
#include "ui_webEngineTestMW.h"
#include "wePage.h"

using namespace Ui;

class webEngineTestMWPrivate:public Ui::webEngineTestMWUi
{
public:
  webEngineTestMWPrivate():Ui::webEngineTestMWUi()
  {
  }
  ~webEngineTestMWPrivate()
  {
  }
  QLocalServer s;
};

webEngineTestMW::webEngineTestMW(QWidget *parent):QMainWindow(parent)
{
  p=new webEngineTestMWPrivate();
  p->setupUi(this);
  qDebug() << __PRETTY_FUNCTION__;

  connect(p->actionE_xit,SIGNAL(triggered()),qApp,SLOT(quit()));
  p->webEngineView->setPage(new wePage(new testProfile(),p->webEngineView));

  QUrl url("http://localhost:9093/site/employee/view");
  
  //p->webEngineView->setUrl(QUrl("https://knlazopp.reflexisinc.com/RWS4/WebClockLogin.jsp?UnitID=0110"));
  p->webEngineView->setUrl(url);
  QLocalServer::removeServer("/tmp/headerSocket");
  p->s.listen("/tmp/headerSocket");
  connect(&p->s,SIGNAL(newConnection()),this,SLOT(socketConnection()));
  
}

webEngineTestMW::~webEngineTestMW()
{
  QLocalServer::removeServer("/tmp/headerSocket");
  delete p;
}

void webEngineTestMW::socketConnection()
{
  qDebug() << "Connection to local socket";
  QLocalSocket *socket = p->s.nextPendingConnection();
  if(!socket->waitForReadyRead(500))
    {
      qDebug() << "Failed to read from socket";
      return;
    }
  QByteArray b=socket->readAll();
  socket->deleteLater();
  qDebug() << "---------------------------" << b;
  qDebug() << "Read from socket" << b;
  QMessageBox::critical(this,tr("Header Received"),b);
  
}
void webEngineTestMW::handleCert(const QWebEngineCertificateError&)
{
  qDebug() << "Handle Cert";
}
