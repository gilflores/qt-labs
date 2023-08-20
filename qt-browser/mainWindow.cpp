#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "CustomWebPage.h"

#include <QDebug>
#include <QNetworkReply>
#include <QWebFrame>


const QString BASE_URL = "https://www.bing.com";

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->urlEdit->setPlainText(BASE_URL);
  page = new CustomWebPage(this);
  ui->webView->setPage(page);
  ui->webView->load(QUrl(BASE_URL));
  //page->mainFrame()->load(QUrl(BASE_URL));

  ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
  ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
  ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanCloseWindows, true);
  ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

  connect(ui->webView->page()->networkAccessManager(),
      SIGNAL(finished(QNetworkReply *)),
      this,SLOT(analyzeHeaders(QNetworkReply *)));

  connect(ui->webView->page(),
          SIGNAL(linkClicked(const QUrl&)),
          this,SLOT(linkClicked(const QUrl&)));

  connect(ui->webView,
          SIGNAL(linkClicked(const QUrl&)),
          this,SLOT(linkClicked(const QUrl&)));
  connect(ui->webView,SIGNAL(loadFinished(bool)), this,SLOT(finished(bool)));


}

MainWindow::~MainWindow()
{
  delete ui;
  page->deleteLater();
}


void MainWindow::on_backButton_clicked()
{
    ui->webView->back();
    ui->urlEdit->setPlainText(ui->webView->url().toString());
}

void MainWindow::on_forwardButton_clicked()
{
    ui->webView->forward();
}

void MainWindow::on_refreshButton_clicked()
{
    ui->webView->reload();
}

void MainWindow::on_goButton_clicked()
{
    // We just type the domain without "http://"

    QTextCursor cursor(ui->urlEdit->textCursor());
    const QString url = ui->urlEdit->toPlainText();
    qDebug() << "Loading URL: " << url << " ... ";
    //page->mainFrame()->load(url);
    ui->webView->load(url);

}


void MainWindow::finished(bool ok)
{
  qInfo() << "-----------------------------------------------";
  qInfo() << "Load finished correctly: "  << ok;
  if(!ok)
    {
      qInfo() << "JS Enabled:" << ui->webView->settings()->testAttribute(QWebSettings::JavascriptCanOpenWindows);
      QString  html = ui->webView->page()->currentFrame()->toHtml();
      qWarning() << html;
      return;
    }
  qInfo() <<  "Rquested URL: "  << page->mainFrame()->requestedUrl(); 
  qInfo() <<  "ContentSize:  "  << page->mainFrame()->contentsSize();
}

void MainWindow::analyzeHeaders(QNetworkReply *reply)
{
  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  qDebug() << "Checking headers: " << reply->url()
           << "Status: " << statusCode;
  if(reply)
    {
      reply->deleteLater();
    }


  if ((reply->error() != QNetworkReply::NoError))
    {
        qWarning() << "NETWORK ERROR: [code:" << reply->error()
                   << ",http_status_code:" << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt()
                   << ",http_redirect:" << reply->attribute( QNetworkRequest::RedirectionTargetAttribute ).toUrl().toString()
                   << ",url:" << reply->url().toString() << ",error:" << reply->errorString() << "]";
    }
  foreach (QNetworkReply::RawHeaderPair pair, reply->rawHeaderPairs()) 
    {
      //qInfo() << "Header: " << pair.first << " Value: " << pair.second;
    }
}

void MainWindow::on_urlEdit_returnPressed()
{
    // Same as goButton click
    on_goButton_clicked();
}

void MainWindow::linkClicked(const QUrl& url)
{
  qWarning() << url << "was clicked";
}
