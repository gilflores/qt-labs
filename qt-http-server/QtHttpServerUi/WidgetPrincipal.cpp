#include "WidgetPrincipal.h"

#include <QDebug>
#include <QApplication>
#include <QHeaderView>
#include <QThread>
#include <QMessageBox>
#include <QProgressDialog>
#include <QLabel>
#include <QDialog>
#include "LongTaskThread.h"

WidgetPrincipal::WidgetPrincipal(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 400);

    // -- Toolbar -----
    toolbarLayout = new QHBoxLayout();

    startButton = new QPushButton("Start service");
    toolbarLayout->addWidget(startButton);

    stopButton = new QPushButton("Stop service");
    toolbarLayout->addWidget(stopButton);

    configurationButton = new QPushButton("Configuration");
    toolbarLayout->addWidget(configurationButton);

    longTaskButton = new QPushButton("Long task");
    toolbarLayout->addWidget(longTaskButton);

    // -- Table -------------------
    messageTable = new QTableView();
    messageModel = createModel();
    messageTable->setModel(messageModel);
    messageTable->verticalHeader()->hide();
    messageTable->horizontalHeader()->setStretchLastSection(true);

    // -- Main layout
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(toolbarLayout);
    mainLayout->addWidget(messageTable);

    this->setLayout(mainLayout);
    // -- Signals ----
    connect(startButton, SIGNAL(pressed()),
            this, SLOT(slotStartServer()));
    connect(stopButton, SIGNAL(pressed()),
            this, SLOT(slotStopServer()));
    connect(longTaskButton, SIGNAL(pressed()),
            this, SLOT(slotLongTask()));
}

/*!
 * \brief WidgetPrincipal::createModel Creates a model for de TableView
 * \return
 */
QStandardItemModel* WidgetPrincipal::createModel() {
  QStandardItemModel *model = new QStandardItemModel();
  model->setHorizontalHeaderLabels(
        QStringList() << QApplication::translate("WebServer", "Date")
                      << QApplication::translate("WebServer", "Message")
        );
  this->addMessage(*model, QDateTime::currentDateTime(), "Application started ...");
  return model;
}

/*!
 * \brief addMessage Add new row on the table
 * \param model
 * \param date
 * \param messege
 * \return
 */
void WidgetPrincipal::addMessage(QStandardItemModel &model, QDateTime date, QString message) {
  QList<QStandardItem*> items;
  items.append(new QStandardItem(date.toString("HH:mm:ss") ));
  items.append(new QStandardItem(message));
  model.appendRow(items);
}

/*!
 * \brief Starts the web server of the application
 */
void WidgetPrincipal::slotStartServer()
{
    qDebug("Waiting to start");
    qDebug("Starting server");
    SiteConfiguration configuration = SiteConfiguration::createDefaultConfiguration();
    server = new HttpServer(this, &configuration);
    bool started = server->start();
    if(started)
    {
        qDebug() << "The server is running";
    }
    else
    {
        qDebug() << "The server couldn't start";
    }
}

/*!
 * \brief Stop the server
 */
void WidgetPrincipal::slotStopServer()
{
    qDebug() << "Stoping server" << "...";
}

void WidgetPrincipal::slotTestUi() {
    qDebug() << "Test ui" << "...";
}

/*! \brief Run the long task
 */
void WidgetPrincipal::slotLongTask() {
    qDebug() << "Long task" << "...";
    this->startButton->setEnabled(false);
    this->stopButton->setEnabled(false);
    this->configurationButton->setEnabled(false);

    // Open the diaglog
    processDialog = new QDialog( this );
    Qt::WindowFlags flags = processDialog->windowFlags();
    QLabel *label =new QLabel("<center>Processing request</center>");
    QHBoxLayout *dialogLayout = new QHBoxLayout(processDialog);
    dialogLayout->addWidget(label);;

    processDialog->setLayout(dialogLayout);
    processDialog->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    processDialog->setFixedSize(300, 200);
    processDialog->show();



    // Execute long term task
    LongTaskThread *longTask = new LongTaskThread(this, this->messageModel);
    connect(longTask,  SIGNAL(finishProcess()), 
        this, SLOT(activateUi()));

    longTask->start();
}

/*! \brief Activate the ui
 */
void WidgetPrincipal::activateUi() {
    this->startButton->setEnabled(true);
    this->stopButton->setEnabled(true);
    this->configurationButton->setEnabled(true);
    processDialog->hide();    
}
