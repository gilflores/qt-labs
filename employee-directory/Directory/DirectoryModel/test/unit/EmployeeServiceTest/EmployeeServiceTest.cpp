#include "EmployeeServiceTest.h"
#include "FileUtil.h"
#include "EmployeeService.h"


const QString EmployeeServiceTest::FILE_ROOT = "./TEST_ROOT";

/*!
 * \brief Prepare the configuration for all unit testing
 */
void EmployeeServiceTest::initTestCase()
{
  qDebug() << "======================================================";
  qDebug() << "TestClass: EmployeeServiceTest";
  qDebug() << "======================================================";
  // Prepare the file folder in startup
  QString defaultTestRoot = EmployeeServiceTest::FILE_ROOT;
  bool directoryCreated = FileUtil::createDirectoryIfNotExists(defaultTestRoot);
  if(!directoryCreated)
    {
      QFAIL("The default directory could not be created");
    }
  // -- Create and configure ETROOT ---------------
  qputenv("FILE_ROOT", defaultTestRoot.toUtf8());
}


/*!
 * \brief Inits the information of the test case
 */
void EmployeeServiceTest::init()
{
    // Begin the logger for testing methods
    logger = TestLogger::newInstance();
}

/*!
 * \brief Removes the resources for the test methods
 */
void EmployeeServiceTest::cleanup()
{
    TestLogger::instance()->clean();
}



/*!
 * \brief Prepares the information for data validation
 */
void EmployeeServiceTest::testIsValidWithValidEmployee_data()
{
  printHeader(__PRETTY_FUNCTION__);
  QTest::addColumn<Employee>("employee");
  QTest::addColumn<bool>("expected");
  Employee e;
  e.setFirstName("Karla Alejandrina");
  e.setLastName("Garza de la barreda");
  e.setAddress("Cumbres de Universidad Etapa 4 # 2205");
  e.setMail("karla.alejandrina.garza.19@gmail.com");
  e.setPhone(1141832445);
  e.setExtension(8321);

  QTest::newRow("Valid employee") << e << true;
}

/*!
 * \brief Test the is valid method when the employee is valid, with the following
 * intentions:
 * - The employee must be valid
 * - The result should not have errors in validation
 */
void EmployeeServiceTest::testIsValidWithValidEmployee()
{
  QFETCH(Employee, employee);
  QFETCH(bool, expected);

  EmployeeService service;
  MessageList validationResult;
  bool result = service.isValid(employee, validationResult);
  qDebug() << validationResult.toString();
  QCOMPARE(result, expected);
  QVERIFY2(validationResult.hasErrors() == false,
           "The employee must not have errors in validation");
}
// -- testIsValidWithInvalidEmployee -------------------------------------------

/*!
 * \brief Prepares the data to execute isValid() method with invalid employee
 */
void EmployeeServiceTest::testIsValidWithInvalidEmployee_data()
{
  printHeader(__PRETTY_FUNCTION__);
  QTest::addColumn<Employee>("employee");
  QTest::addColumn<bool>("expected");
  QTest::addColumn<int>("numberOfExpectedErrors");
  QTest::addColumn<bool>("firstNameError");
  QTest::addColumn<bool>("lastNameError");
  QTest::addColumn<bool>("mailError");
  bool withFirstNameError = true;
  bool withLastNameError = true;
  bool withMailNameError = true;


  Employee e;
  e.setFirstName("Karla[]Alejandrina");
  e.setLastName("Garza de{} la barreda");
  e.setAddress("Cumbres de Universidad Etapa 4 # 2205");
  e.setMail("karla.alejan**ina.garza.19@gmail.com");
  e.setPhone(2141832445);
  e.setExtension(8321);


  QTest::newRow("Valid employee")
      << e << false << 3 << withFirstNameError
      << withLastNameError << withMailNameError;
}

/*!
 * \brief Test the method isValid() with a invalid Employee to check the
 * following intentions:
 * - The result must have errors
 * - If the employee is with errors for firstName, lastName and mail the
 *   test must validate an error message in the result
 */
void EmployeeServiceTest::testIsValidWithInvalidEmployee()
{
  QFETCH(Employee, employee);
  QFETCH(bool, expected);
  QFETCH(int, numberOfExpectedErrors);
  QFETCH(bool, firstNameError);
  QFETCH(bool, lastNameError);
  QFETCH(bool, mailError);

  EmployeeService service;
  MessageList validationResult;
  bool result = service.isValid(employee, validationResult);
  qDebug() << validationResult.toString();
  QCOMPARE(result, expected);
  QVERIFY2(validationResult.hasErrors() == true,
           "The employee must have errors in validation");

  // Validating the error list
  QString message = QString("The number of expected error must be the same as "
                            "the validation result list with: %1").
                    arg(numberOfExpectedErrors);
  QVERIFY2(numberOfExpectedErrors == validationResult.lenght(),
           message.toLatin1().data());

  if(firstNameError)
    {
      QString regexpString = "^(The first name is invalid)";
      int count = validationResult.countWithRegExp(regexpString);
      QVERIFY2(count == 1, "The list must contains 1 message for firstName");
    }

  if(lastNameError)
    {
      QString regexpString = "^(The last name is invalid)";
      int count = validationResult.countWithRegExp(regexpString);
      QVERIFY2(count == 1, "The list must contains 1 message for lastName");
    }
  if(mailError)
    {
      QString regexpString = "^(The mail is invalid)";
      int count = validationResult.countWithRegExp(regexpString);
      QVERIFY2(count == 1, "The list must contains 1 message for mail");
    }
}

/*!
 * \brief Test the save employee method with a a valid employee with the case
 * of saving and updating the employee. The intentions are:
 *
 * Save operation
 * - The save result must not have error
 * - The Result must have the flag save but not the updated flag
 * - The result must have the employee id assigned
 * - The employee object must has the employee id assigned
 *
 * Update operation
 * - The mail will be updated without errors
 * - The Result must have the flag save and updated to true
 * - The result must have the employee id assigned
 * - The saved employee and retrieved employee must be equal
 */
void EmployeeServiceTest::testSaveValidEmployeeCaseSaveAndUpdate()
{
  printHeader(__PRETTY_FUNCTION__);
  QString fileToTest = EmployeeServiceTest::FILE_ROOT + "/employee.data";
  FileUtil::deleteFileIfExists(fileToTest);

  Employee e;
  e.setFirstName("Karla Alejandrina");
  e.setLastName("Garza de la barreda");
  e.setAddress("Cumbres de Universidad Etapa 4 # 2205");
  e.setMail("karla.alejandrina.garza.19@gmail.com");
  e.setPhone(2141832445);
  e.setExtension(8321);

  EmployeeService service;
  SaveEmployeeResult result = service.save(e);

  // Validate the result
  QVERIFY2(!result.hasErrors(), "The result must not have errors");
  QVERIFY2(result.isSaved() && !result.isUpdated(),
           "The employee must be saved and not updated");
  QVERIFY2(result.employeeId() > 0, "The employee id must be assigned");
  QVERIFY2(e.employeeId() > 0, "The employee id must be assigned into the employee");

  // Update the employee
  e.setMail("kalejandria@gmail.com");
  result = service.save(e);
  QVERIFY2(!result.hasErrors(), "The mail will be updated without errors");
  QVERIFY2(result.isSaved() && result.isUpdated(),
           "The employee must be saved and updated");

  // Using the DAO to test the updated field
  EmployeeDao* dao = service.getEmployeeDaoInstance();
  Employee resultEmployee = dao->findByEmployeeId(e.employeeId());
  QVERIFY2(e.equals(resultEmployee),
           "The saved employee and retrieved employee must be equal");
}


/*!
 * \brief Print the header of the test
 * \param functionsName
 */
void EmployeeServiceTest::printHeader(const char *functionsName) const
{
  qDebug() << "---------------------------------------------------------------";
  qDebug() << functionsName;
  qDebug() << "---------------------------------------------------------------";
}


QTEST_APPLESS_MAIN(EmployeeServiceTest)
