#include <QTextStream>
#include "Employee.h"

/*!
 * \brief Default constructor
 */
Employee::Employee() : _employeeId(0)
{

}

/*!
 * \brief Copy constructor
 * \param base
 */
Employee::Employee(const Employee &base)
{
  _employeeId = base.employeeId();
  _firstName = base.firstName();
  _lastName = base.lastName();
  _address = base.address();
  _mail = base.mail();
  _phone = base.phone();
  _extension = base.extension();
}

/*!
 * \brief Assignment operator
 * \param base The base employee to be assigned
 * \return
 */
Employee &Employee::operator=(const Employee &base)
{
  _employeeId = base.employeeId();
  _firstName = base.firstName();
  _lastName = base.lastName();
  _address = base.address();
  _mail = base.mail();
  _phone = base.phone();
  _extension = base.extension();
  return *this;
}

Employee::~Employee()
{

}

int Employee::employeeId() const
{
  return _employeeId;
}

void Employee::setEmployeeId(int employeeId)
{
  _employeeId = employeeId;
}

QString Employee::firstName() const
{
  return _firstName;
}

void Employee::setFirstName(const QString &firstName)
{
  _firstName = firstName;
}

QString Employee::lastName() const
{
  return _lastName;
}

void Employee::setLastName(const QString &lastName)
{
  _lastName = lastName;
}

QString Employee::address() const
{
  return _address;
}

void Employee::setAddress(const QString &address)
{
  _address = address;
}

QString Employee::mail() const
{
  return _mail;
}

void Employee::setMail(const QString &mail)
{
  _mail = mail;
}

long Employee::phone() const
{
  return _phone;
}

void Employee::setPhone(long phone)
{
  _phone = phone;
}

int Employee::extension() const
{
  return _extension;
}

void Employee::setExtension(int extension)
{
  _extension = extension;
}

/*!
 * \brief Generates a string to print the employee
 * \return
 */
QString Employee::toString()
{
  QString s;
  QTextStream ss(&s);
  ss << right
     << qSetFieldWidth(5)  << employeeId() << " "
     << left
     << qSetFieldWidth(25) << firstName()
     << qSetFieldWidth(25) << lastName()
     << qSetFieldWidth(30) << address()
     << qSetFieldWidth(30) << mail()
     << right
     << qSetFieldWidth(12) << phone()
     << qSetFieldWidth(5)  << extension();
  return s;
}

/*!
 * \brief Validates if two employees are exactly the same
 * \param o
 * \return
 */
bool Employee::equals(const Employee &o)
{
  if(this->employeeId() == o.employeeId()
     && this->firstName() == o.firstName()
     && this->lastName() == o.lastName()
     && this->address() == o.address()
     && this->mail() == o.mail()
     && this->phone() == o.phone()
     && this->extension() == o.extension() )
    {
      return true;
    }
  return false;
}
