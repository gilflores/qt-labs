#ifndef webEngineTestApp_H_
#define webEngineTestApp_H_

#include <QApplication>

class webEngineTestApp:public QApplication
{
  Q_OBJECT
public:
  webEngineTestApp(int& argc,char **argv);
  virtual ~webEngineTestApp();
};

#endif

