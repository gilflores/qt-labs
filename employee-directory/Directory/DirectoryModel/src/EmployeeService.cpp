#include <QRegExp>
#include <QDebug>
#include "EmployeeService.h"
#include "EmployeeFileDao.h"
#include "FileUtil.h"

const QString EmployeeService::FIRST_NAME_REGEXP =
    "[\\.a-zA-Z0-9\\x00C0-\\x00FF\\s]+";
const QString EmployeeService::LAST_NAME_REGEXP =
    "[\\.a-zA-Z0-9\\x00C0-\\x00FF\\s]+";
const QString EmployeeService::MAIL_REGEXP =
    "^[0-9a-zA-Z-_\\.]+@[0-9a-zA-Z-]+\\.[0-9a-zA-Z-.]+[0-9a-zA-Z]+$|^$";


/*!
 * \brief Validates the fields of the employee
 * \param employee
 * \return
 */
bool EmployeeService::isValid(const Employee &employee, MessageList& list)
{
  QRegExp firstNameRegexp(FIRST_NAME_REGEXP);
  QRegExp lastNameRegexp(LAST_NAME_REGEXP);
  QRegExp mailRegexp(MAIL_REGEXP);


  if(employee.firstName().isEmpty() ||
     !firstNameRegexp.exactMatch(employee.firstName()) )
    {
      list.addError("The first name is invalid");
    }

  if(employee.lastName().isEmpty() ||
     !lastNameRegexp.exactMatch(employee.lastName()) )
    {
      list.addError("The last name is invalid");
    }

  if(employee.mail().isEmpty() ||
     !mailRegexp.exactMatch(employee.mail()) )
    {
      list.addError("The mail is invalid");
    }
  return !list.hasErrors();
}

/*!
 * \brief Saves the employee in the persistence layer
 * \param employee
 * \return
 */
SaveEmployeeResult EmployeeService::save(Employee &employee)
{
  SaveEmployeeResult result;
  if(!isValid(employee, result))
    {
     return result;
    }
  EmployeeDao* dao = getEmployeeDaoInstance();
  Employee e = dao->findByEmployeeId(employee.employeeId());
  // Check if the id exists
  if( e.employeeId() <= 0)
    {
      if(dao->add(employee))
        {
          result.setSaved(true);
        }
      else
        {
          QString error = "Error saving employee " + employee.toString();
          result.addError(error);
        }
    }
  else
    {
      if(dao->update(employee))
        {
          result.setSaved(true);
          result.setUpdated(true);
        }
      else
        {
          QString error = "Error updating employee " + employee.toString();
          result.addError(error);
        }
    }
  result.setEmployeeId(employee.employeeId());
  delete dao;
  return result;
}

/*!
 * \brief Gets an instance of the DAO
 * \return
 */
EmployeeDao* EmployeeService::getEmployeeDaoInstance()
{
  QString fileBasePath = FileUtil::getSystemVariable("FILE_ROOT");
  QString filePath = QString("%1/employee.data").arg(fileBasePath);
  return new EmployeeFileDao(filePath);
}
