#include "SaveEmployeeResult.h"

/*!
 * \brief Default constructor of the class
 */
SaveEmployeeResult::SaveEmployeeResult()
{

}

/*!
 * \brief Copy constructor
 * \param base
 */
SaveEmployeeResult::SaveEmployeeResult(const SaveEmployeeResult &base)
{
  _saved = base.isSaved();
  _updated = base.isUpdated();
  _employeeId = base.employeeId();
  messages = base.messages;
  withError = base.withError;
}

/*!
 * \brief Assignment operator
 * \param base
 * \return
 */
SaveEmployeeResult &SaveEmployeeResult::operator=(const SaveEmployeeResult &base)
{
  _saved = base.isSaved();
  _updated = base.isUpdated();
  _employeeId = base.employeeId();
  messages = base.messages;
  withError = base.withError;
  return *this;
}

/*!
 * \brief SaveEmployeeResult::~SaveEmployeeResult
 */
SaveEmployeeResult::~SaveEmployeeResult()
{

}

bool SaveEmployeeResult::isSaved() const
{
  return _saved;
}

void SaveEmployeeResult::setSaved(bool saved)
{
  _saved = saved;
}

bool SaveEmployeeResult::isUpdated() const
{
  return _updated;
}

void SaveEmployeeResult::setUpdated(bool updated)
{
  _updated = updated;
}

int SaveEmployeeResult::employeeId() const
{
  return _employeeId;
}

void SaveEmployeeResult::setEmployeeId(int employeeId)
{
  _employeeId = employeeId;
}
