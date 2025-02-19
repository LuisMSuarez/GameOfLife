#include <QtTest>

// add necessary includes here

class shark : public QObject
{
    Q_OBJECT

public:
    shark();
    ~shark();

private slots:
    void test_case1();

};

shark::shark()
{

}

shark::~shark()
{

}

void shark::test_case1()
{

}

QTEST_APPLESS_MAIN(shark)

#include "test_shark.moc"
