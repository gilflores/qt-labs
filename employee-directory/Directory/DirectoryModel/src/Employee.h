#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QString>
#include <QtCore/QMetaType>

class Employee
{
  Q_GADGET
public:

  Employee();
  Employee(const Employee& base);
  Employee& operator=(const Employee& base);
  ~Employee();

  int employeeId() const;
  void setEmployeeId(int employeeId);


  QString firstName() const;
  void setFirstName(const QString &firstName);

  QString lastName() const;
  void setLastName(const QString &lastName);

  QString address() const;
  void setAddress(const QString &address);

  QString mail() const;
  void setMail(const QString &mail);

  long phone() const;
  void setPhone(long phone);

  int extension() const;
  void setExtension(int extension);

  QString toString();
  bool equals(const Employee& o);

private:
  int _employeeId;
  QString _firstName;
  QString _lastName;
  QString _address;
  QString _mail;

  long _phone;
  int _extension;

};

Q_DECLARE_METATYPE(Employee)
Q_DECLARE_METATYPE(Employee*)

#endif // EMPLOYEE_H
