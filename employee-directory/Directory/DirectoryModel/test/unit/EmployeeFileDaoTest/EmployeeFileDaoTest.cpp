#include "EmployeeFileDaoTest.h"
#include "FileUtil.h"
#include "EmployeeFileDao.h"
#include "EmployeeDao.h"


const QString EmployeeFileDaoTest::DEFAULT_DIRECTORY = "./TEST_ROOT";
const QString EmployeeFileDaoTest::DEFAULT_FILE = "employee.data";


void EmployeeFileDaoTest::initTestCase()
{
  fileToTest = DEFAULT_DIRECTORY + "/" + DEFAULT_FILE;
  FileUtil::createDirectoryIfNotExists(DEFAULT_DIRECTORY);
  FileUtil::deleteFileIfExists(fileToTest);
}

void EmployeeFileDaoTest::cleanupTestCase()
{

}

/*!
 * \brief Test the add method with the following intentions:
 *
 */
void EmployeeFileDaoTest::testAdd()
{
  printHeader(__PRETTY_FUNCTION__);
  const QString fileName = DEFAULT_DIRECTORY + "/employee-add.data";
  FileUtil::deleteFileIfExists(fileName);
  Employee e;
  e.setFirstName("Karla Alejandrina");
  e.setLastName("Garza de la barreda");
  e.setAddress("Cumbres de Universidad Etapa 4 # 2205");
  e.setMail("karla.alejandrina.garza.19@gmail.com.uk");
  e.setPhone(1141832445);
  e.setExtension(8321);

  EmployeeFileDao dao(fileName);
  int registers = dao.count();
  QVERIFY2(registers == 0, "The file must be empty");
  bool employeeAdded = dao.add(e);
  QVERIFY2(employeeAdded, "The employee must be added");
  registers = dao.count();
  QVERIFY2(registers == 1, "The Dao must add only one register");

  // Addind the register again
  employeeAdded = dao.add(e);
  QVERIFY2(employeeAdded, "The employee must be added");
  registers = dao.count();
  QCOMPARE(registers, 2);

}

/*!
 * \brief Prepares the data for multiple add with fetch
 */
void EmployeeFileDaoTest::testAddMultiple_data()
{
  printHeader(__PRETTY_FUNCTION__);

  const QString fileToTest = DEFAULT_DIRECTORY + "/employee-addMultiple.data";
  FileUtil::deleteFileIfExists(fileToTest);

  QTest::addColumn<QString>("firstName");
  QTest::addColumn<QString>("lastName");
  QTest::addColumn<QString>("address");
  QTest::addColumn<QString>("mail");
  QTest::addColumn<long>("phone");
  QTest::addColumn<int>("extension");
  QTest::addColumn<QString>("fileToTest");

  QTest::newRow("Employee1") << "Michael" << "Tempuri"
                             << "1980 Jackovson Rd"
                             << "tempuri@visual.com"
                             << 899123987l << 20 << fileToTest;

  QTest::newRow("Employee2") << "Rod" << "Bashlet"
                             << "2304 Sunshine Dr"
                             << "rod.bashlet@office345.com"
                             << 233123987l << 782 << fileToTest;

}

/*!
 * \brief Testing the add method with data the intensions of the test are:
 * - Write a user in the file and the employeeId must be greater than 0
 * - The employee will be readed using find method and must be equal than
 *   the base employe
 */
void EmployeeFileDaoTest::testAddMultiple()
{
  QFETCH(QString, firstName);
  QFETCH(QString, lastName);
  QFETCH(QString, address);
  QFETCH(QString, mail);
  QFETCH(long, phone);
  QFETCH(int, extension);
  QFETCH(QString, fileToTest);

  Employee baseEmployee;
  baseEmployee.setFirstName(firstName);
  baseEmployee.setLastName(lastName);
  baseEmployee.setAddress(address);
  baseEmployee.setMail(mail);
  baseEmployee.setPhone(phone);
  baseEmployee.setExtension(extension);

  EmployeeFileDao dao(fileToTest);
  dao.add(baseEmployee);
  QVERIFY2(baseEmployee.employeeId() > 0, "The employeeId must be the same");
  Employee resultEmployee = dao.findByEmployeeId(baseEmployee.employeeId());

  QVERIFY2(baseEmployee.equals(resultEmployee),
           "The values in the result employee must be the same");
  qDebug() << qPrintable(baseEmployee.toString());

}

/*!
 * \brief Test the update method
 */
void EmployeeFileDaoTest::testUpdate()
{
  printHeader(__PRETTY_FUNCTION__);

  const QString fileToTest = DEFAULT_DIRECTORY + "/employee-update.data";
  FileUtil::deleteFileIfExists(fileToTest);

  // Adding registers into file
  QList<Employee> list = createListOfEmployees();
  addList(fileToTest, list);

  // Reading the information

  //Update The employee 3;
  Employee e;
  e.setEmployeeId(3);
  e.setFirstName("Karla Alejandrina");
  e.setLastName("Garza de la barreda");
  e.setAddress("Cumbres de Universidad Etapa 4 # 2205");
  e.setMail("karla.alejandrina.garza.19@gmail.com.uk");
  e.setPhone(1141832445);
  e.setExtension(8321);

  EmployeeFileDao dao(fileToTest);
  dao.update(e);
  Employee resultEmployee = dao.findByEmployeeId(e.employeeId());
  QVERIFY2(resultEmployee.employeeId() == e.employeeId(),
           "The employeeId must be the same");
  QVERIFY2(e.equals(resultEmployee),
           "The values in the result employee must be the same");
  qDebug() << qPrintable(e.toString());
}


/*!
 * \brief Test the find all employees using the DAO, The intentions are:
 *      - The file must contains five elements in the file
 *      - The employee list must be printed to verify visually.
 */
void EmployeeFileDaoTest::testFindAll()
{
  printHeader(__PRETTY_FUNCTION__);
  const QString fileToTest = DEFAULT_DIRECTORY + "/employee-findall.data";
  FileUtil::deleteFileIfExists(fileToTest);

  // Adding registers into file
  QList<Employee> list = createListOfEmployees();
  addList(fileToTest, list);

  // Reading the information
  EmployeeFileDao dao(fileToTest);
  QList<Employee> result = dao.findAll();
  int rowsExpected = 5;
  QCOMPARE(rowsExpected, result.count());

  foreach (Employee e, result)
    {
      qDebug() << qPrintable(e.toString());
    }
}

/*!
 * \brief Test the method find employee by id, with the following intentions
 * - The method will register 5 employees
 * - All the employees registered must exists it in the file
 * - All the field of the employees must be the same
 */
void EmployeeFileDaoTest::testFindEmployeeById()
{
  printHeader(__PRETTY_FUNCTION__);

  const QString fileToTest = DEFAULT_DIRECTORY + "/employee-findById.data";
  FileUtil::deleteFileIfExists(fileToTest);

  // Adding registers into file
  QList<Employee> list = createListOfEmployees();
  addList(fileToTest, list);

  // Reading the information
  EmployeeFileDao dao(fileToTest);
  for (int i =0;i < list.count(); i++)
    {
      Employee& e = list[i];
      Employee resultEmployee = dao.findByEmployeeId(e.employeeId());
      QVERIFY2(resultEmployee.employeeId() > 0,
               "The employeeId must be greater than 0");
      QVERIFY2(e.equals(resultEmployee),
               "The values in the result employee must be the same");
      qDebug() << qPrintable(e.toString());
    }
}

/*!
 * \brief EmployeeFileDaoTest::createEmployee
 * \param firstName The fist name of the employee
 * \param lastName The last name of the employee
 * \param address The full addres of the employee
 * \param mail The valid email of the employee
 * \param phone The phone of the employee as long
 * \param extension The extension of the employee on the office
 * \return The #Employee instance to test.
 */
Employee EmployeeFileDaoTest::createEmployee(const QString &firstName,
                                             const QString &lastName,
                                             const QString &address,
                                             const QString &mail,
                                             long phone,
                                             int extension)
{
  Employee e;
  e.setFirstName(firstName);
  e.setLastName(lastName);
  e.setAddress(address);
  e.setMail(mail);
  e.setPhone(phone);
  e.setExtension(extension);
  return e;
}

/*!
 * \brief  Create a list of employees for the test case
 * \return A list with 5 employees to test
 */
QList<Employee> EmployeeFileDaoTest::createListOfEmployees()
{
  QList<Employee> result;
  Employee e;
  // -- Employee
  e = createEmployee("Alejandro Andres","Almanza Robledo", "Juan Altamirano #4998",
                     "alejandro.robledo@gmail.com", 1149883982, 8990);
  result.append(e);

  // -- Employee
  e = createEmployee("Mario","Rodriguez", "Emiliano Zapata 31800",
                     "mario.rodriquez@hotmail.com", 1149883982, 230);
  result.append(e);

  // -- Employee
  e = createEmployee("Pedro","Ruiz Cortinez",
                     "Lomas del Pedregral 4998", "pruiz@gmail.com.mx",
                     1149883982, 790);
  result.append(e);

  // -- Employee
  e = createEmployee("Maura Marcela","Barraza de la rosa",
                     "Juan Rangel de Biesma #1443", "mbarraza@yahoo.com.mx",
                     1149883982, 899);
  result.append(e);
  e = createEmployee("Andy Remo","Smith",
                     "Blvd Ortiz Mena #12", "a_smith@yahoo.com",
                     1273283982, 7872);
  result.append(e);

  return result;
}

/*!
 * \brief Save the list of employees into the database
 * \param fileName
 * \param employees
 * \return
 */
void EmployeeFileDaoTest::addList(const QString &fileName, QList<Employee>& employees)
{
  EmployeeFileDao dao(fileName);
  // Adding registers into file
  for (int i =0;i < employees.count(); i++)
    {
      Employee& e = employees[i];
      dao.add(e);
    }
}

/*!
 * \brief Print the header of the test
 * \param functionsName
 */
void EmployeeFileDaoTest::printHeader(const char *functionsName) const
{
  qDebug() << "---------------------------------------------------------------";
  qDebug() << functionsName;
  qDebug() << "---------------------------------------------------------------";
}

// Used to create the main method of the test
QTEST_APPLESS_MAIN(EmployeeFileDaoTest)
