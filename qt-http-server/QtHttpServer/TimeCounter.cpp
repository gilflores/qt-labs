#include "TimeCounter.h"

/*! \brief Register the time in which one operation start and end, to now
 *         the time that consumes the operation.
 * 
 */
TimerCounter::TimerCounter(QString operation) 
{
  this->operation = operation;
  this->startTime = QDateTime::currentDateTime();
  this->seconds = 0;
}

/*! \brief stops the time counter and print the enlapsed time
 *
 */
TimerCounter::stop() 
{
  this->endTime = QDateTime::currentDateTime();
  qint64 millisecondsDiff = startTime.msecsTo(endTime);
  double seconds 
}