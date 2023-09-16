#include <QCoreApplication>
#include <QDebug>
#include "DecimalWrapper.h"

//En C++ int y long son el mismo tipo de dato, por consiguiente,
//los valores dentro de -2,147,483,648 to 2,147,483,647
//toman el constructor int .:. prec max = 10

bool isValidNum(QString value)
{
    bool convOk;
    long longTest;
    double doubleTest;

    if (value.contains("."))
      {
        doubleTest = value.toDouble(&convOk);
      }
    else
      {
        longTest = value.toLong(&convOk, 10);
      }

    if (convOk==true)
      {
        return true;
      }
    else
      {
        return false;
      }
}//isValidNum()

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    //QTextStream qOut(stdout);
    int intValue; //no podemos usar long porque por "data promotion"
                  //long -> double y crea ambigüedad
    double doubleValue;
    QString strValue;

    qDebug() << "Default Ctr cannot be reached!";
    qDebug() << "";

    intValue = 5;
    DecimalWrapper b(intValue); //int ctr (prec = 0)
    qDebug() << "Convtr Ctr: Num(" << b.getNum() <<"), Double(" << b.getDouble()
             << "), Prec(" << b.getPrec() <<")";
    qDebug() << "";

    doubleValue = 5.05;
    DecimalWrapper c(doubleValue,1); //double ctr
    qDebug() << "double Ctr: Num(" << c.getNum() <<"), Double(" << c.toString()
             << "), Prec(" << c.getPrec() <<")";
    qDebug() << "";

    intValue = 500;
    DecimalWrapper d(intValue,2); //int ctr
    qDebug() << "int Ctr: Num(" << d.getNum() <<"), Double(" << d.toString()
             << "), Prec(" << d.getPrec() <<")";
    qDebug() << "";

    intValue = 400;
    DecimalWrapper e(intValue,2); //int ctr
    qDebug() << "int Ctr: Num(" << e.getNum() <<"), Double(" << e.toString()
             << "), Prec(" << e.getPrec() <<")";
    qDebug() << "";

    doubleValue = 555.7777;
    DecimalWrapper f(doubleValue,4); //double ctr
    qDebug() << "double Ctr: Num(" << f.getNum() <<"), Double(" << f.toString()
             << "), Prec(" << f.getPrec() <<")";
    qDebug() << "";

    f.toEZC();
    qDebug() << "EZC: Num(" << f.getNum() <<"), Double(" << f.toString() <<
                "), Prec(" << f.getPrec() <<")";
    qDebug() << "";

    strValue = "5003055";
    if (isValidNum(strValue)==true)
      {
        DecimalWrapper g(strValue,4); //QString ctr
        qDebug() << "QString Ctr: Num(" << g.getNum() <<"), Double(" <<
                    g.toString() << "), Prec(" << g.getPrec() <<")";
        qDebug() << "";
      }
    else
      {
        qDebug() << "Value("<< strValue << ") is not a valid Long or "
                                           "Double value!";
      }

    strValue = "204800.96";
    if (isValidNum(strValue)==true)
      {
        DecimalWrapper h(strValue,4); //QString ctr
        qDebug() << "QString Ctr: Num(" << h.getNum() <<"), Double(" <<
                    h.toString() << "), Prec(" << h.getPrec() <<")";
        qDebug() << "";
      }
    else
      {
        qDebug() << "Value("<< strValue << ") is not a valid Long or "
                                           "Double value!";
      }

    DecimalWrapper i(f); //copy
    qDebug() << "Copy: Num(" << i.getNum() <<"), Double(" << i.toString() <<
                "), Prec(" << i.getPrec() <<")";
    qDebug() << "";

    qDebug() << "operator+: c(" << c.toString() << ") + d(" << d.toString() <<
                ") = " << QString::number(c+d, 'g');
    qDebug() << "operator-: c(" << c.toString() << ") - d(" << d.toString() <<
                ") = " << QString::number(c-d, 'g');
    qDebug() << "operator==: e(" << e.toString() << ") == f(" << f.toString() <<
                ") -> " << (e==f);
    qDebug() << "operator!=: e(" << e.toString() << ") != f(" << f.toString() <<
                ") -> " << (e!=f);
    qDebug() << "operator>: e(" << e.toString() << ") > f(" << f.toString() <<
                ") -> " << (e>f);
    qDebug() << "operator<: e(" << e.toString() << ") < f(" << f.toString() <<
                ") -> " << (e<f);
    qDebug() << "operator>=: e(" << e.toString() << ") >= f(" << f.toString() <<
                ") -> " << (e>=f);
    qDebug() << "operator<=: e(" << e.toString() << ") <= f(" << f.toString() <<
                ") -> " << (e<=f);

    return app.exec();
}//main()
