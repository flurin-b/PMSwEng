#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QKeyEvent>
#include <QTimer>

#include <vector>
#include <algorithm>

struct dirs {
};

class Snake : public QObject
{
    Q_OBJECT
public:
    Snake(QGraphicsScene* sc);
    void begin();
public slots:
    void onKeyPress(QKeyEvent* event);
    void onStep();
signals:
    void exit();

private:
    const QPoint LEFT   = QPoint(-1,  0);
    const QPoint RIGHT  = QPoint( 1,  0);
    const QPoint UP     = QPoint( 0, -1);
    const QPoint DOWN   = QPoint( 0,  1);

    void paint();
    void gameOver();
    void spawnFood();

    QGraphicsScene* sc;
    QTimer* stepTimer;
    std::vector<QPoint> body;

    int playAreaWidth = 25;
    int playAreaHeight = 25;
    int stepTimerDecrement = 1;

    double margins = 0.1;
    QPoint currentDirection, nextDirection, nextNextDirection;
    QPoint food;
};

#endif // SNAKE_H
