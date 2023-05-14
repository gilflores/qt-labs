#ifndef EMPLOYEESERVICETEST_H
#define EMPLOYEESERVICETEST_H


#include <QObject>
#include <QList>
#include <QtTest>
#include "Employee.h"
#include "TestLogger.h"


class EmployeeServiceTest: public QObject
{
    Q_OBJECT

public:

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void testIsValidWithValidEmployee_data();
    void testIsValidWithValidEmployee();

    void testIsValidWithInvalidEmployee_data();
    void testIsValidWithInvalidEmployee();

    void testSaveValidEmployeeCaseSaveAndUpdate();

private:
    TestLogger* logger;
    static const QString FILE_ROOT;
    void printHeader(const char* functionsName) const;

};
#endif // EMPLOYEESERVICETEST_H
