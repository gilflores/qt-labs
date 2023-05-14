#include "LongTaskThread.h"
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>

/*! \brief Constuctor of the class 
 */
LongTaskThread::LongTaskThread(QObject *parent, QStandardItemModel *model) {
  this->model = model;
  this->running = false;
}

/*! \brief Thread method
 */
void LongTaskThread::run() {
  running = true;

  this->startTime = QDateTime::currentDateTime();
  this->addMessage(*model, startTime, "Starting Long task");
  qDebug() << "Running thread";

  int counter = 0;
  int milliseconds = 1000;
  while(counter < 8) {
    QThread::msleep(milliseconds);
    int time  = (counter + 1) * milliseconds;
    QString message = QString("Wainting %1 milliseconds").arg(time);
    qDebug() << message ;
    this->addMessage(*model, QDateTime::currentDateTime(), message);
    counter ++;
  }
  this->endTime = QDateTime::currentDateTime();
  this->addMessage(*model, endTime, "Ending Long task");
  emit finishProcess();
}

/*! \brief Add message on the table
 */
void LongTaskThread::addMessage(QStandardItemModel &model, QDateTime date, QString message) {
  QList<QStandardItem*> items;
  items.append(new QStandardItem(date.toString("dd/MM/yyyy - HH:mm:ss:sss") ));
  items.append(new QStandardItem(message));
  model.appendRow(items);
}

void LongTaskThread::stop() {
  this->running = false;
}
