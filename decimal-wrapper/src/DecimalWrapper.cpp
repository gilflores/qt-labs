#include "DecimalWrapper.h"
#include <QDebug>

DecimalWrapper::DecimalWrapper():
    _numLong(0),
    _numDouble(0),
    _prec(0)
{

}//DecimalWrapper()

DecimalWrapper::DecimalWrapper(int numInt, unsigned short int prec)
{
     setLong(numInt, prec); 
}//DecimalWrapper(int numInt, unsigned short int prec)

DecimalWrapper::DecimalWrapper(double numDouble, unsigned short int prec) 
{ 
    setDouble(numDouble, prec); 
}//DecimalWrapper(double numDouble, unsigned short int prec)

DecimalWrapper::DecimalWrapper(QString numStr, unsigned short int prec) 
{
    if (prec>10) 
      {
        qDebug() << "Precision cannot be greater than 10; adjusted to cap.";
        _prec = 10;
      }
    else
      {
        _prec = prec;
      }
    numStr = adjPrec(numStr);

    _numDouble = numStr.toDouble();
    _numLong = doubleToLong(_numDouble);
}//DecimalWrapper(QString numStr, unsigned short int prec)

DecimalWrapper::DecimalWrapper(const DecimalWrapper& copyObj): 
    _numLong(copyObj._numLong), 
    _numDouble(copyObj._numDouble),
    _prec(copyObj._prec)
{

}//DecimalWrapper(const DecimalWrapper& copyObj) -Copy Ctr-

DecimalWrapper::~DecimalWrapper()
{

}//~DecimalWrapper()

long DecimalWrapper::getNum()
{ 
    return _numLong; 
}//getNum()

double DecimalWrapper::getDouble()
{
    return _numDouble;
}//getDouble()

int DecimalWrapper::getPrec()
{ 
    return _prec; 
}//getPrec()

void DecimalWrapper::setLong(int num, unsigned short int prec)
{
    if (prec>10) 
      {
        qDebug() << "Precision cannot be greater than 10; adjusted to cap.";
        _prec = 10;
      }
    else 
      {
        _prec = prec;
      }
    _numLong = num;
    _numDouble = longToDouble(num);
}//setLong(int num, unsigned short int prec)

void DecimalWrapper::setDouble(double numDouble, unsigned short int prec)
{
    QString auxValue = "";

    if (prec>10) 
      {
        qDebug() << "Precision cannot be greater than 10; adjusted to cap.";
        _prec = 10;
      }
    else 
      {
        _prec = prec;
      }
    auxValue = QString::number(numDouble, 'f', _prec);
    auxValue = adjPrec(auxValue);


    _numDouble = auxValue.toDouble();
    _numLong = doubleToLong(_numDouble);
}//setDouble(double numDouble, unsigned short int prec)

void DecimalWrapper::toEZC()
{
    QString auxValue = QString::number(_numLong);
    int i;

    if (_numLong<0) 
      {
        qDebug() << "Value("<< _numLong << ") "
                    "is negative: it cannot be formated to EZC.";
      }
    else 
      {
        if (_prec>2) 
          {
            auxValue.chop(_prec-2);
          }
        else 
          {
            for (i=0; i<2-_prec; i++)
              {
                auxValue.append("0");
              }
          }
        _prec = 2;
        _numLong = auxValue.toLong();
        _numDouble = longToDouble(_numLong);
    }
}//toEZC()

QString DecimalWrapper::toString()
{
    return QString::number(_numDouble, 'f', _prec);
}//toString()

double DecimalWrapper::operator+(const DecimalWrapper& otherDec)
{
    return _numDouble + otherDec._numDouble;
}//operator+()

double DecimalWrapper::operator-(const DecimalWrapper& otherDec)
{
    return _numDouble - otherDec._numDouble;
}//operator-()

bool DecimalWrapper::operator==(const DecimalWrapper& otherDec)
{
    if (_numDouble == otherDec._numDouble)
      {
        return true;
      }
    else
      {
        return false;
      }
}//operator==()

bool DecimalWrapper::operator!=(const DecimalWrapper& otherDec)
{
    if (_numDouble != otherDec._numDouble)
      {
        return true;
      }
    else
      {
        return false;
      }
}//operator!=()

bool DecimalWrapper::operator>(const DecimalWrapper& otherDec)
{
    if (_numDouble > otherDec._numDouble)
      {
        return true;
      }
    else
      {
        return false;
      }
}//operator>()

bool DecimalWrapper::operator<(const DecimalWrapper& otherDec)
{
    if (_numDouble < otherDec._numDouble)
      {
        return true;
      }
    else
      {
        return false;
      }
}//operator<()

bool DecimalWrapper::operator>=(const DecimalWrapper& otherDec)
{
    if (_numDouble >= otherDec._numDouble)
      {
        return true;
      }
    else
      {
        return false;
      }
}//operator>=()

bool DecimalWrapper::operator<=(const DecimalWrapper& otherDec)
{
    if (_numDouble <= otherDec._numDouble)
      {
        return true;
      }
    else
      {
        return false;
      }
}//operator<=()

// UTILITIES
QString DecimalWrapper::adjPrec(QString value)
{
    int dotLoc = 0;

    if (value.contains("."))
      { //double
        dotLoc = value.indexOf(".",dotLoc);
        if ( ((value.length()-dotLoc-1) - _prec) >0 )
          { //aseguramos valor @_prec
            value.chop((value.length()-dotLoc-1) - _prec);
          }
        else
          {

          }
      }
    else
      { //int
        if (_prec>0)
          {
            value.insert(_prec-1, ".");
          }
        else
          {

          }
    }
    return value;
}//adjPrec()

double DecimalWrapper::longToDouble(long value)
{
    double valueAsDouble = (double)value;
    int i;

    if (_prec<=0)
      {

      }
    else
      {
        for (i=1; i<=_prec; i++)
          {
            valueAsDouble=valueAsDouble/10;
          }
      }
    return valueAsDouble;
}//longToDouble()

long DecimalWrapper::doubleToLong(double value)
{
    int i;

    if (_prec<=0)
      {

      }
    else
      {
        for (i=1; i<=_prec; i++)
          {
            value=value*10;
          }
      }
    return (long)value;
}//doubleToLong()