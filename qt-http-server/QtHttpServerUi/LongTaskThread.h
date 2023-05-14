#ifndef LONG_TASK_THREAD_H
#define LONG_TASK_THREAD_H

#include <QThread>
#include <QDateTime>
#include <QStandardItemModel>


class LongTaskThread : public QThread
{
  Q_OBJECT

  public:
    LongTaskThread(QObject *parent, QStandardItemModel *model);
    void stop();

  protected:
    void run();

  signals:
    void finishProcess();

  private:
    volatile bool running;
    QStandardItemModel *model;
    QDateTime startTime;
    QDateTime endTime;
    void addMessage(QStandardItemModel &model, QDateTime date, QString message);
};


#endif // LONG_TASK_THREAD_H