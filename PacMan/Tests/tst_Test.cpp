#include "../Test.h"
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

QTEST_MAIN(TestTest)

#include "tst_Test.moc"
