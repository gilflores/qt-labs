#include <dlfcn.h>
//#include <string.h>
#include <stdio.h>
#include <string.h>
#include <QByteArray>
#include <QList>
#include <QHash>
#include <QDebug>
#include <QLocalSocket>


static void *(*libc_memcpy)(void *,const void *,size_t)=0;

QHash<QString, QString> parseResponseLines(QList<QByteArray> list, QList<QString> headersToSerach) {
  QHash<QString, QString> headers;
  foreach(QByteArray line, list) 
    {
      qInfo() << "- " << qPrintable(line);
      foreach (const QString &header, headersToSerach) 
        {
          if (line.contains(header.toLatin1())) 
            {
              qInfo() << "- <Catch>: " << qPrintable(line);
              QList<QString> values = QString(line).split(":");
              headers[values[0]] = values[1];
            }
        }
    }
    return headers;
}


void parseHttpHeader(const char *buf,size_t count)
{
  QList<QString> searchHeaders;
  searchHeaders.append("EmployeeID");
  searchHeaders.append("Zebra-Header");

  QByteArray httpReceptor(buf,count);
  
  if(httpReceptor.contains("\r\n"))
    {
      httpReceptor = httpReceptor.left(httpReceptor.indexOf("\r\n\r\n"));
    }
  QList<QByteArray> list= httpReceptor.split('\n');
  
  foreach(QByteArray body,list)
    {
      QByteArray header;
      QByteArray value;
      if (!body.contains("EmployeeID")) 
        {
          continue; // Invalid
        }
      
      QHash<QString, QString> headers = parseResponseLines(
        httpReceptor.split('\0'), searchHeaders);
      qInfo() << headers;

      body = body.mid(body.indexOf(':')+1);
      value = body.simplified();
      qInfo() << "<<<< Captured Header:" << header << "value" << value;
      QLocalSocket socket;
      socket.connectToServer("/tmp/headerSocket");
      socket.write(value);
      socket.waitForBytesWritten(250);
      socket.close();      
    }
}

extern "C" void *memcpy(void *dest,const void *src, size_t count)
{
  if(!libc_memcpy)
    {
      libc_memcpy=(void *(*)(void *,const void *,size_t))dlsym(RTLD_NEXT,"memcpy");
      if(!libc_memcpy)
        {
          fprintf(stderr,"Unable to load LIBC ::read at runtime!");
        }
    }
  void *r=libc_memcpy(dest,src,count);
 
   if(count >=4 && !memcmp(src,"HTTP",4))
      {
        fprintf(stdout,"Snagged an HTTP Response\n");
        // this is actually really important...
        // as soon as we start messing with parsing the headers
        // we will be firing a bunch of memcpy's off ourselves
        // we are changing the character at the start
        // so we don't recursively capture our own processing
        // of the input data
        char *buf=(char *)malloc(count);
        libc_memcpy(buf,src,count);
        buf[0]='h';

        parseHttpHeader(buf,count);
      }
  return r;
}
