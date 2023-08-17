#include "mainwindow.h"

#include <QApplication>
#include <QWebView>
#include <QUrl>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

/**
 QWebView view;
 view.show();
 view.load(QUrl("http://google.com"));

 return a.exec();
*/

  MainWindow w;
  w.show();
  return a.exec();
}
