#ifndef EMPLOYEEDAO_H
#define EMPLOYEEDAO_H

#include <QObject>
#include <QList>
#include "Employee.h"

class EmployeeDao : public QObject
{
  Q_OBJECT
public:
  EmployeeDao();
  virtual ~EmployeeDao();

  /*!
   * \brief Counts the number of employees of the datasource.
   * \return  The number of registers
   */
  virtual int count() = 0;

  /*!
   * \brief Adds one employee inside the file and assigns the idEmployee
   *        into the object #Employee counting the number of registers from the
   *        datasource.
   *
   *
   * \param employee The reference to the employee structure.
   * \return True if the employee is added into the datasource
   */
  virtual bool add(Employee& employee) = 0;

  /*!
   * \brief Updates the information of one employee using the employeeId
   * \param employee The employee to be updated
   * \return True if everything is ok, false with each error.
   */
  virtual bool update(const Employee& employee) = 0;

  /*!
   * \brief Finds and employee in the file using the employeeId  and returns an
   *        instance of #Employee.
   * \param employeeId The id of the employee to be find in the file
   * \return  An #Employee object with the information of the employee, if
   *          something fails returns and empty object
   */
  virtual Employee findByEmployeeId(const int employeeId) = 0;

  /*!
   * \brief  Read all the employees from the file. If the datasource doesn't
   *         have records the methods returns an empty QList
   * \return A List with the employees from the datasource
   */
  virtual QList<Employee> findAll() = 0;
};

#endif // EMPLOYEEDAO_H
