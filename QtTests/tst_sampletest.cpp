#include <QTest>
//#include <QTest>

// add necessary includes here

class sampletest : public QObject
{
    Q_OBJECT

public:
    sampletest();
    ~sampletest();

private slots:
    void test_case1();

};

sampletest::sampletest()
{

}

sampletest::~sampletest()
{

}

void sampletest::test_case1()
{

}

QTEST_APPLESS_MAIN(sampletest)

#include "tst_sampletest.moc"
