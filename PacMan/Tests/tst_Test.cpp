#include "../Test.h"
#include <QTest>

class TestTest : public QObject
{
    Q_OBJECT

private slots:
    void passTest();
};

void TestTest::passTest()
{
    Test t;
    QCOMPARE(t.returnTrue(), true);
}

QTEST_APPLESS_MAIN(TestTest)

#include "tst_Test.moc"
