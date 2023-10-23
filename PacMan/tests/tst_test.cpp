#include "../test.h"
#include <QTest>

class TestTest : public QObject
{
    Q_OBJECT

private slots:
    void passTest();
    void failTest();
};

void TestTest::passTest()
{
    Test t;
    QCOMPARE(t.returnTrue(), true);
}

void TestTest::failTest()
{
    Test t;
    QCOMPARE(t.returnFalse(), true);
}

QTEST_MAIN(TestTest)

#include "tst_test.moc"
