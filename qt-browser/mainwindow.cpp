#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QNetworkReply>
#include <QWebFrame>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->urlEdit->setPlainText("https://knlazopp.reflexisinc.com/RWS4/WebClockLogin.jsp");
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_backButton_clicked()
{
    ui->webView->back();
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

    qDebug() << "URL: " << url;

    QWebPage *page = new QWebPage(this);
    ui->webView->setPage(page);
    ui->webView->load(url);

    connect(ui->webView->page()->networkAccessManager(),
        SIGNAL(finished(QNetworkReply *)),
        this,SLOT(examineHeaders(QNetworkReply *)));

    connect(ui->webView,SIGNAL(loadFinished(bool)),
            this,SLOT(finished(bool)));
}


void MainWindow::finished(bool ok)
{
  if(!ok)
    return;

  QString  text = ui->webView->page()->currentFrame()->toHtml();

  qInfo() << text;
}

void MainWindow::examineHeaders(QNetworkReply *r)
{
  qDebug() << "Checking headers: " << r->url();

  if(r)
    r->deleteLater();

  foreach (QNetworkReply::RawHeaderPair pair, r->rawHeaderPairs()) {
      //qInfo() << "Header: " << pair.first << " Value: " << pair.second;
  }
}



void MainWindow::on_urlEdit_returnPressed()
{
    // Same as goButton click
    on_goButton_clicked();
}
