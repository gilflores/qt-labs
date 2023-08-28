#include "webEngineTestMW.h"
#include "webEngineTestApp.h"
#include <QDebug>


int main(int argc, char **argv)
{
  webEngineTestApp app(argc,argv);

  webEngineTestMW *mw=new webEngineTestMW();
  mw->show();
  
  return app.exec();
}


