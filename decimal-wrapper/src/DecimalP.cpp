#include "DecimalP.h"
#include <QDebug>

DecimalP::DecimalP():
    _numLong(0),
    _numDouble(0),
    _prec(0)
{

}//DecimalP()

DecimalP::DecimalP(int numInt, unsigned short int prec)
{
     setLong(numInt, prec); 
}//DecimalP(int numInt, unsigned short int prec)

DecimalP::DecimalP(double numDouble, unsigned short int prec) 
{ 
    setDouble(numDouble, prec); 
}//DecimalP(double numDouble, unsigned short int prec)

DecimalP::DecimalP(QString numStr, unsigned short int prec) 
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
}//DecimalP(QString numStr, unsigned short int prec)

DecimalP::DecimalP(const DecimalP& copyObj): 
    _numLong(copyObj._numLong), 
    _numDouble(copyObj._numDouble),
    _prec(copyObj._prec)
{

}//DecimalP(const DecimalP& copyObj) -Copy Ctr-

DecimalP::~DecimalP()
{

}//~DecimalP()

long DecimalP::getNum()
{ 
    return _numLong; 
}//getNum()

double DecimalP::getDouble()
{
    return _numDouble;
}//getDouble()

int DecimalP::getPrec()
{ 
    return _prec; 
}//getPrec()

void DecimalP::setLong(int num, unsigned short int prec)
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

void DecimalP::setDouble(double numDouble, unsigned short int prec)
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

void DecimalP::toEZC()
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

QString DecimalP::toString()
{
    return QString::number(_numDouble, 'f', _prec);
}//toString()

double DecimalP::operator+(const DecimalP& otherDec)
{
    return _numDouble + otherDec._numDouble;
}//operator+()

double DecimalP::operator-(const DecimalP& otherDec)
{
    return _numDouble - otherDec._numDouble;
}//operator-()

bool DecimalP::operator==(const DecimalP& otherDec)
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

bool DecimalP::operator!=(const DecimalP& otherDec)
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

bool DecimalP::operator>(const DecimalP& otherDec)
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

bool DecimalP::operator<(const DecimalP& otherDec)
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

bool DecimalP::operator>=(const DecimalP& otherDec)
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

bool DecimalP::operator<=(const DecimalP& otherDec)
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
QString DecimalP::adjPrec(QString value)
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

double DecimalP::longToDouble(long value)
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

long DecimalP::doubleToLong(double value)
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