#include "mainWindow.h"

#include <QApplication>
#include <QWebView>
#include <QUrl>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

/*
 QWebView view;
 view.show();
 view.load(QUrl("https://knlazopp.reflexisinc.com/RWS4/WebClockLogin.jsp?UnitID=0110"));

 QWebView view2;
 view2.show();
 view2.load(QUrl("https://knlazo.reflexisinc.com/RWS4/WebClockLogin.jsp?UnitID=0110"));

 QWebView view3;
 view3.show();
 view3.load(QUrl("https://www.bing.com"));
*/
 //return a.exec();


  MainWindow w;
  w.show();
  return a.exec();
}
