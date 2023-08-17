#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QNetworkReply;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

protected slots:
  virtual void examineHeaders(QNetworkReply *);
  virtual void finished(bool ok);

private slots:
    void on_backButton_clicked();

    void on_forwardButton_clicked();

    void on_refreshButton_clicked();

    void on_goButton_clicked();

    void on_urlEdit_returnPressed();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
