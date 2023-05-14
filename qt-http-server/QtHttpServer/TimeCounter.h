#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H

#include <QString>
#include <QDateTime>

class TimeCounter 
{
  public:
    TimeCounter(QString operation);
    readTimeInSeconds();
    stop();

  private:
    QDateTime startTime;
    QDateTime endTime;
    double seconds;
    QString operation;
};

#endif