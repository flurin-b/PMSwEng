#include "../Ghost.h"
#include <QTest>

class GhostTest : public QObject
{
    Q_OBJECT

private slots:
    void getDistanceTest_data();
    void getDistanceTest();
};

void GhostTest::getDistanceTest_data()
{
    QTest::addColumn<QPoint>("field1");
    QTest::addColumn<QPoint>("field2");
    QTest::addColumn<float>("distance");

    QTest::newRow("Field 1 = Field2") << QPoint(10,10) << QPoint(10,10) << 0.0f;
    QTest::newRow("Field 1 top of Field2") << QPoint(10,10) << QPoint(10,20) << 10.0f;
    QTest::newRow("Field 1 bottom of Field2") << QPoint(10,10) << QPoint(10,0) << 10.0f;
    QTest::newRow("Field 1 left of Field2") << QPoint(0,10) << QPoint(10,10) << 10.0f;
    QTest::newRow("Field 1 right of Field2") << QPoint(20,10) << QPoint(10,10)<< 10.0f;
}

void GhostTest::getDistanceTest()
{
    QFETCH(QPoint, field1);
    QFETCH(QPoint, field2);
    QFETCH(float, distance);

    //The Output value is a float thus a diffrence up to 0.1 is accepted
    QCOMPARE_LE(Ghost::getDistance(field1,field2) - distance,0.01f);
}

QTEST_APPLESS_MAIN(GhostTest)

#include "tst_Ghost.moc"
