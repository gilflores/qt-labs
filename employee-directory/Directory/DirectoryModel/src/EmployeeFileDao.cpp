#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include <QDebug>
#include "EmployeeFileDao.h"

const QString EmployeeFileDao::DEFAULT_FILE = "./data/employee.data";
const QString EmployeeFileDao::FILE_CODEC = "UTF-8";

/*!
 * \brief Default constructor
 */
EmployeeFileDao::EmployeeFileDao()
{
   _filePath = EmployeeFileDao::DEFAULT_FILE;
}

/*!
 * \brief Constructor to assign the file
 * \param filePath
 */
EmployeeFileDao::EmployeeFileDao(const QString &filePath)
{
  _filePath = filePath;
}

/*!
 * \brief Destructor of the class
 */
EmployeeFileDao::~EmployeeFileDao()
{

}

/*!
 * \copydoc EmployeeDao::count()
 */
int EmployeeFileDao::count()
{
  QFileInfo fileInfo(this->_filePath);
  if(!fileInfo.exists() || !fileInfo.isFile())
    {
      qWarning() << "The file " << this->_filePath
                 << " doesn't exists or is not a file ";
      return 0;
    }
  int lines = 0;
  QFile file(this->_filePath);
  if (file.open(QIODevice::ReadOnly))
    {
      QTextStream in(&file);
      while(!in.atEnd())
        {
          QString line = in.readLine();
          if(!line.isEmpty())
            {
              lines++;
            }
        }
    }
  file.close();
  return lines;
}

/*!
 * \copydoc EmployeeDao::add()
 */
bool EmployeeFileDao::add(Employee &employee)
{
  int numberOfRegisters = count();

  QFile file(this->_filePath);
  if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
      file.seek(file.size());
      QTextStream out(&file);
      employee.setEmployeeId(numberOfRegisters + 1);
      out << toFileData(employee) << endl;
      file.close();
      return true;
    }
  return false;
}

/*!
 * \copydoc EmployeeDao::update()
 */
bool EmployeeFileDao::update(const Employee &employee)
{
  bool isEmployeeUpdated = false;
  QList<Employee> list;
  bool listReaded = readFile(_filePath, list);
  if(!listReaded)
    {
      qCritical() << __PRETTY_FUNCTION__
                  << "The list of al employees could not be read from file "
                  << _filePath << " when update employee";
      return false;
    }
  QFile file(_filePath);
  if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
      file.seek(file.size());
      QTextStream out(&file);
      foreach(Employee e, list)
        {
          if(e.employeeId() == employee.employeeId())
            {
              out << toFileData(employee) << endl;
              isEmployeeUpdated = true;
            }
          else
            {
              out << toFileData(e) << endl;
            }
        }
      file.close();
    }

  if(isEmployeeUpdated)
    {
      qWarning() << "The employee with id " << employee.employeeId()
                 << " doesn't exist in the file";
    }
  return isEmployeeUpdated;
}

/*!
 * \copydoc EmployeeDao::findByEmployeeId()
 */
Employee EmployeeFileDao::findByEmployeeId(const int employeeId)
{
  QList<Employee> list;
  bool listReaded = readFile(_filePath, list);
  if(!listReaded)
    {
      qCritical() << __PRETTY_FUNCTION__
                  << "The list of al employees could not be read from file "
                  << _filePath << " when findEmployeeById()";
      return Employee(); // Return empty employee
    }
  foreach(Employee e, list)
    {
      if(e.employeeId() == employeeId)
        {
          return e;
        }
    }
  return Employee();
}

/*!
 * \copydoc EmployeeDao::findAll()
 */
QList<Employee> EmployeeFileDao::findAll()
{
  QList<Employee> list;
  bool listReaded = readFile(_filePath, list);
  if(!listReaded)
    {
      qCritical() << __PRETTY_FUNCTION__
                  << "The list of al employees could not be read from file "
                  << _filePath;
      return list;
    }
  return list;
}


/*!
 * \brief Read the information of the file an convert it into a QList
 * \param fileName The file name to be read
 * \param list
 * \return
 */
bool EmployeeFileDao::readFile(const QString &fileName, QList<Employee>& result)
{
  bool success = true;
  QFile file(fileName);
  if(!file.open(QIODevice::ReadOnly))
    {
      qCritical() << __FUNCTION__ <<  "The file " << qPrintable(fileName)
                  << " could not be opened to read the information.";
      return !success;
    }
  QTextStream in(&file);
  while(!in.atEnd())
    {
      QString line = in.readLine();
      result.append(convert(line));
    }
  file.close();
  return success;
}

/*!
 * \brief Writes a list of employees in the de file, and overwrites all the file
 * \param fileName The file in which the information will be written
 * \param employees The list of employees that will be written in the file
 * \return
 */
bool EmployeeFileDao::writeList(const QString& fileName,
                                const QList<Employee> employees)
{
  bool success = true;
  QFile file(fileName);
  if(!file.open(QIODevice::WriteOnly))
    {
      qCritical() << __FUNCTION__ <<  "The file " << qPrintable(fileName)
                  << " could not be opened to write the employees.";
      return !success;
    }
  QTextStream out(&file);
  foreach(Employee e, employees)
    {
      out << toFileData(e);
      out << endl;
    }
  return success;
}

/*!
 * \brief Creates a String to write the employee into the file
 * \param employee
 * \return
 */
QByteArray EmployeeFileDao::toFileData(const Employee &employee)
{
  QByteArray ss;
  ss.append(QString("%1").arg(employee.employeeId()).toUtf8());
  ss.append("||");
  ss.append(employee.firstName().toUtf8());
  ss.append("||");
  ss.append(employee.lastName().toUtf8());
  ss.append("||");
  ss.append(employee.address().toUtf8());
  ss.append("||");
  ss.append(employee.mail().toUtf8());
  ss.append("||");
  ss.append(QString("%1").arg(employee.phone()).toUtf8());
  ss.append("||");
  ss.append(QString("%1").arg(employee.extension()).toUtf8());
  return ss;

}

/*!
 * \brief Creates an instance of the employee from a QString that
 *        represents a employee register
 * \param data The line with serialized employee information.
 * \return An instance of employee
 */
Employee EmployeeFileDao::convert(const QString &data)
{
  QStringList fields = data.split("||");
  Employee e;
  int id = QString(fields[0]).toInt();
  e.setEmployeeId(id);
  e.setFirstName(fields[1]);
  e.setLastName(fields[2]);
  e.setAddress(fields[3]);
  e.setMail(fields[4]);
  e.setPhone(fields[5].toLong());
  e.setExtension(fields[6].toInt());
  return e;
}
