#ifndef SAVEEMPLOYEERESULT_H
#define SAVEEMPLOYEERESULT_H

#include "MessageList.h"

class SaveEmployeeResult : public MessageList
{
public:
  SaveEmployeeResult();
  SaveEmployeeResult(const SaveEmployeeResult& base);
  SaveEmployeeResult& operator=(const SaveEmployeeResult& base);
  ~SaveEmployeeResult();

  bool isSaved() const;
  void setSaved(bool isSaved);

  bool isUpdated() const;
  void setUpdated(bool isUpdated);

  int employeeId() const;
  void setEmployeeId(int employeeId);

private:
  bool _saved;
  bool _updated;
  int _employeeId;

};

#endif // SAVEEMPLOYEERESULT_H
