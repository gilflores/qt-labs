#ifndef DECIMALP_H
#define DECIMALP_H

#include <QObject>

/*!
 * \brief  Class to handle decimal floating points
 */
class DecimalWrapper
{
public:
    DecimalWrapper();
    DecimalWrapper(int numInt, unsigned short int prec=0);
    // Converter: sólo se usa como valor default
    DecimalWrapper(double numDouble, unsigned short int prec);
    DecimalWrapper(QString numStr, unsigned short int prec);
    DecimalWrapper(const DecimalWrapper& copyObj); //Copy Ctr
    ~DecimalWrapper();  
    long getNum();
    double getDouble();
    int getPrec();
    void setLong(int num, unsigned short int prec);
    void setDouble(double numDouble, unsigned short int prec);
    void toEZC();
    QString toString();
    double operator+(const DecimalWrapper& otherDec);
    double operator-(const DecimalWrapper& otherDec);
    bool operator==(const DecimalWrapper& otherDec);
    bool operator!=(const DecimalWrapper& otherDec);
    bool operator>(const DecimalWrapper& otherDec);
    bool operator<(const DecimalWrapper& otherDec);
    bool operator>=(const DecimalWrapper& otherDec);
    bool operator<=(const DecimalWrapper& otherDec);

protected:
    QString adjPrec(QString value);
    double longToDouble(long value);
    long doubleToLong(double value);

private:
    long _numLong;
    double _numDouble;
    int _prec;
};

#endif // DECIMALP
