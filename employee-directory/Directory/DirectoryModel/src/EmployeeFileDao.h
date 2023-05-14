#ifndef EMPLOYEEFILEDAO_H
#define EMPLOYEEFILEDAO_H

#include <QObject>
#include <QList>
#include "Employee.h"
#include "EmployeeDao.h"

/*!
 * \brief Implements the Data acces object of the employee class using a
 * Text file
 */
class EmployeeFileDao : public EmployeeDao
{
  Q_OBJECT
public:
  Q_INVOKABLE EmployeeFileDao();
  Q_INVOKABLE EmployeeFileDao(const QString& filePath);
  virtual ~EmployeeFileDao();

  int count();
  bool add(Employee &employee);
  bool update(const Employee &employee);
  Employee findByEmployeeId(const int employeeId);
  QList<Employee> findAll();

private:
  static const QString DEFAULT_FILE;
  static const QString FILE_CODEC;
  QString _filePath;

  bool readFile(const QString& fileName, QList<Employee>& result);
  bool writeList(const QString& fileName, const QList<Employee> employees);

  QByteArray toFileData(const Employee& employee);
  Employee convert(const QString& data);
};

#endif // EMPLOYEEFILEDAO_H
