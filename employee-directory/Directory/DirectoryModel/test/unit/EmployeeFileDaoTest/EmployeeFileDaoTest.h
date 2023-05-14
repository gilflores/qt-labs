#ifndef EMPLOYEEFILEDAOTEST_H
#define EMPLOYEEFILEDAOTEST_H

#include <QObject>
#include <QList>
#include <QtTest>
#include "Employee.h"

/*!
 * \brief Test EmployeeFileDao using scenarios in which create files and registers
 * and validate the content of the files
 */
class EmployeeFileDaoTest: public QObject
{
    Q_OBJECT

public:

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testAdd();

    void testAddMultiple_data();
    void testAddMultiple();

    void testUpdate();
    void testFindAll();
    void testFindEmployeeById();

private:
  static const QString DEFAULT_FILE;
  static const QString DEFAULT_DIRECTORY;
  QString fileToTest;

  Employee createEmployee(const QString& firstName, const QString& lastName,
        const QString& address, const QString& mail, long phone, int extension);
  QList<Employee> createListOfEmployees();
  void addList(const QString& fileName, QList<Employee>& employees);
  void printHeader(const char* functionsName) const;

};

#endif // EMPLOYEEFILEDAOTEST_H
