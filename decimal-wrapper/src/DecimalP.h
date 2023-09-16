#ifndef DECIMALP_H
#define DECIMALP_H

#include <QObject>

/*!
 * \brief  Class to handle decimal floating points
 */
class DecimalP
{
public:
    DecimalP();
    DecimalP(int numInt, unsigned short int prec=0);
    // Converter: sólo se usa como valor default
    DecimalP(double numDouble, unsigned short int prec);
    DecimalP(QString numStr, unsigned short int prec);
    DecimalP(const DecimalP& copyObj); //Copy Ctr
    ~DecimalP();  
    long getNum();
    double getDouble();
    int getPrec();
    void setLong(int num, unsigned short int prec);
    void setDouble(double numDouble, unsigned short int prec);
    void toEZC();
    QString toString();
    double operator+(const DecimalP& otherDec);
    double operator-(const DecimalP& otherDec);
    bool operator==(const DecimalP& otherDec);
    bool operator!=(const DecimalP& otherDec);
    bool operator>(const DecimalP& otherDec);
    bool operator<(const DecimalP& otherDec);
    bool operator>=(const DecimalP& otherDec);
    bool operator<=(const DecimalP& otherDec);

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
