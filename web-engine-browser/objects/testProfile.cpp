#include "testProfile.h"
#include <QDebug>


class testProfilePrivate
{
public:
  testProfilePrivate()
  {
  }
  ~testProfilePrivate()
  {
  }
};

testProfile::testProfile(QObject *parent):QWebEngineProfile(parent)
{
  p=new testProfilePrivate();
  qDebug() << "testProfile Created";
}

testProfile::~testProfile()
{
  delete p;
}

