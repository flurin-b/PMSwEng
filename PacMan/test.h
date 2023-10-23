#ifndef TEST_H
#define TEST_H
#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    Test();
    bool returnTrue();
    bool returnFalse();
};

#endif // TEST_H
