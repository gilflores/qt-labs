#ifndef TESTPROFILE_H_
#define TESTPROFILE_H_


#include <QWebEngineProfile>


class testProfilePrivate;
class testProfile:public QWebEngineProfile
{
  Q_OBJECT
public:
  testProfile(QObject *parent=0);
  virtual ~testProfile();

private:
  testProfilePrivate *p;
};


#endif
