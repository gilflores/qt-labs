#include <QtTest>
#include "DecimalP.h"

class DecimalPTest : public QObject
{
    Q_OBJECT

public:
    DecimalPTest();
    ~DecimalPTest();

private slots:
    void initTestCase(); //objects init
    void testToString(); //toString function
    void testToEZC(); //toEZC function
    void testOperators(); //operators
    void cleanupTestCase();
};

DecimalPTest::DecimalPTest()
{

}

DecimalPTest::~DecimalPTest()
{

}

void DecimalPTest::initTestCase()
{
    int intValue;
    double doubleValue;
    QString strValue;

    qDebug() << "init objects validations";
    qDebug() << "Should initialize the objects as intended in the Ctrs";
    qDebug() << "";

    qDebug() << "Test: int ctr (prec = 0)";
    qDebug() << "Create a DecimalP object based on an int value and prec=0";
    qDebug() << "Should store and return the original int value";
    intValue = 5;
    DecimalP b(intValue);
    qDebug() << "Convtr Ctr: Num(" << b.getNum() <<"), Double(" << b.getDouble()
             << "), Prec(" << b.getPrec() <<")";
    qDebug() << "";
    QVERIFY(b.getNum() == 5);
    QVERIFY(b.getDouble() == 5.0);

    qDebug() << "Test: double ctr, prec=1";
    qDebug() << "Create a DecimalP object based on a double value and prec=1";
    qDebug() << "Should store and return original double value @ 1 digit mant";
    doubleValue = 5.05;
    DecimalP c(doubleValue, 1);
    qDebug() << "Ctr: Num(" << c.getNum() <<"), Double(" << c.toString()
             << "), Prec(" << c.getPrec() <<")";
    qDebug() << "";
    QVERIFY(c.getNum() == 50);
    QVERIFY(c.getDouble() == 5.0);

    qDebug() << "Test: int ctr, prec=2";
    qDebug() << "Create a DecimalP object based on an int value and prec=2";
    qDebug() << "Should store and return original int value @ 2 digit mant "
                "if shown as a double";
    intValue = 500;
    DecimalP d(intValue, 2);
    qDebug() << "Ctr: Num(" << d.getNum() <<"), Double(" << d.toString()
             << "), Prec(" << d.getPrec() <<")";
    qDebug() << "";
    QVERIFY(d.getNum() == 500);
    QVERIFY(d.getDouble() == 5.00);

    qDebug() << "Test: double ctr, prec=4";
    qDebug() << "Create a DecimalP object based on a double value and prec=4";
    qDebug() << "Should store and return original double value @ 4 digit mant";
    doubleValue = 555.7777;
    DecimalP f(doubleValue,4);
    qDebug() << "double Ctr: Num(" << f.getNum() <<"), Double(" << f.toString()
             << "), Prec(" << f.getPrec() <<")";
    qDebug() << "";
    QVERIFY(f.getNum() == 5557777);
    QVERIFY(f.getDouble() == 555.7777);
}

void DecimalPTest::testToString()
{
    int intValue;
    double doubleValue;
    QString strValue;

    qDebug() << ".toString validations";
    qDebug() << "Should return the stored double value in String format";
    qDebug() << "";

    intValue = 5;
    DecimalP b(intValue);
    qDebug() << "Convtr Ctr: Num(" << b.getNum() <<"), Double(" << b.getDouble()
             << "), Prec(" << b.getPrec() <<")";
    qDebug() << "";
    QVERIFY(b.toString() == "5");

    doubleValue = 5.05;
    DecimalP c(doubleValue, 1);
    qDebug() << "Ctr: Num(" << c.getNum() <<"), Double(" << c.toString()
             << "), Prec(" << c.getPrec() <<")";
    qDebug() << "";
    QVERIFY(c.toString() == "5.0");

    intValue = 500;
    DecimalP d(intValue, 2);
    qDebug() << "Ctr: Num(" << d.getNum() <<"), Double(" << d.toString()
             << "), Prec(" << d.getPrec() <<")";
    qDebug() << "";
    QVERIFY(d.toString() == "5.00");

    doubleValue = 555.7777;
    DecimalP f(doubleValue,4);
    qDebug() << "double Ctr: Num(" << f.getNum() <<"), Double(" << f.toString()
             << "), Prec(" << f.getPrec() <<")";
    qDebug() << "";
    QVERIFY(f.toString() == "555.7777");
}

void DecimalPTest::testToEZC()
{
    double doubleValue;
    QString strValue;

    qDebug() << ".toEZC validations";
    qDebug() << "Should return the stored value in EZC format";
    qDebug() << "";

    doubleValue = 555.7777;
    DecimalP f(doubleValue,4);
    qDebug() << "double Ctr: Num(" << f.getNum() <<"), Double(" << f.toString()
             << "), Prec(" << f.getPrec() << ")";
    qDebug() << "";
    QVERIFY(f.toString() == "555.7777");

    f.toEZC();
    qDebug() << "EZC: Num(" << f.getNum() <<"), Double(" << f.toString()
             << "), Prec(" << f.getPrec() <<")";
    qDebug() << "";
    QVERIFY(f.toString() == "555.77");
}

void DecimalPTest::testOperators()
{
    int intValue;
    double doubleValue;
    QString strValue;

    doubleValue = 5.05;
    DecimalP c(doubleValue, 1);

    intValue = 500;
    DecimalP d(intValue, 2);

    intValue = 400;
    DecimalP e(intValue,2); //int ctr

    doubleValue = 555.7777;
    DecimalP f(doubleValue,4);

    qDebug() << "operator+: c(" << c.toString() << ") + d(" << d.toString() <<
                ") = " << QString::number(c+d, 'g');
    QVERIFY(c + d == c.getDouble() + d.getDouble());

    qDebug() << "operator-: c(" << c.toString() << ") - d(" << d.toString() <<
                ") = " << QString::number(c-d, 'g');
    QVERIFY(c - d == c.getDouble() - d.getDouble());

    //qDebug() << "operator==: e(" << e.toString() << ") == f(" << f.toString() <<
    //            ") -> "<< (e==f);
    //QVERIFY(e.getDouble() == f.getDouble());

    qDebug() << "operator!=: e(" << e.toString() << ") != f(" << f.toString() <<
                ") -> "<< (e!=f);
    QVERIFY(e.getDouble() != f.getDouble());

    //qDebug() << "operator>: e(" << e.toString() << ") > f(" << f.toString() <<
    //            ") -> "<< (e>f);
    //QVERIFY(e.getDouble() > f.getDouble());

    qDebug() << "operator<: e(" << e.toString() << ") < f(" << f.toString() <<
                ") -> "<< (e<f);
    QVERIFY(e.getDouble() < f.getDouble());

    //qDebug() << "operator>=: e(" << e.toString() << ") >= f(" << f.toString() <<
    //            ") -> "<< (e>=f);
    //QVERIFY(e.getDouble() >= f.getDouble());

    qDebug() << "operator<=: e(" << e.toString() << ") <= f(" << f.toString() <<
                ") -> "<< (e<=f);
    QVERIFY(e.getDouble() <= f.getDouble());
}

void DecimalPTest::cleanupTestCase()
{

}
QTEST_APPLESS_MAIN(DecimalPTest)

#include "tst_decimalptest.moc"
