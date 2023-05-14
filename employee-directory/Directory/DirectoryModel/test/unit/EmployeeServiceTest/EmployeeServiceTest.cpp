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
}

/*!
 * \brief Removes the resources for the test methods
 */
void EmployeeServiceTest::cleanup()
{
}



/*!
 * \brief Prepares the information for data validation
 */
void EmployeeServiceTest::testIsValidWithValidEmployee_data()
{
  printHeader(__PRETTY_FUNCTION__);

}

/*!
 * \brief Test the is valid method when the employee is valid, with the following
 * intentions:
 * - The employee must be valid
 * - The result should not have errors in validation
 */
void EmployeeServiceTest::testIsValidWithValidEmployee()
{

}
// -- testSaveValidEmployeeCaseSaveAndUpdate -----------------------------------

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
