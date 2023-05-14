#ifndef WIDGETPRINCIPAL_H
#define WIDGETPRINCIPAL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QDateTime>
#include "HttpServer.h"

class WidgetPrincipal : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetPrincipal(QWidget *parent = nullptr);
private:
    HttpServer *server;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *configurationButton;
    QPushButton *longTaskButton;
    QHBoxLayout *toolbarLayout;
    QVBoxLayout *mainLayout;
    QTableView *messageTable;
    QDialog *processDialog;
    QStandardItemModel *messageModel;
    QStandardItemModel* createModel();
    void addMessage(QStandardItemModel &model, QDateTime date, QString message);

    //bool blockUiEmpty();

signals:

public slots:
    void slotStartServer();
    void slotStopServer();
    void slotTestUi();
    void slotLongTask();
    void activateUi();

};


#endif // WIDGETPRINCIPAL_H
