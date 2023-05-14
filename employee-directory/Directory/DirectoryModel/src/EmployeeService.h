#ifndef EMPLOYEESERVICE_H
#define EMPLOYEESERVICE_H

#include <QObject>
#include "Employee.h"
#include "EmployeeDao.h"
#include "MessageList.h"
#include "SaveEmployeeResult.h"

/*!
 * \brief Process the business operations of one employee
 */
class EmployeeService
{
public:

  bool isValid(const Employee& employee, MessageList& list);
  SaveEmployeeResult save(Employee& employee);
  EmployeeDao* getEmployeeDaoInstance();

private:
  static const QString FIRST_NAME_REGEXP;
  static const QString LAST_NAME_REGEXP;
  static const QString MAIL_REGEXP;

};
#endif // EMPLOYEESERVICE_H
