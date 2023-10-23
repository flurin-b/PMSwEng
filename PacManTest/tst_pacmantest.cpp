#include <QtTest>

// add necessary includes here

class PacManTest : public QObject
{
    Q_OBJECT

public:
    PacManTest();
    ~PacManTest();

private slots:
    void test_case1();

};

PacManTest::PacManTest()
{

}

PacManTest::~PacManTest()
{

}

void PacManTest::test_case1()
{

}

QTEST_APPLESS_MAIN(PacManTest)

#include "tst_pacmantest.moc"
