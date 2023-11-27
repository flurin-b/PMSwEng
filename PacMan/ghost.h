#ifndef GHOST_H
#define GHOST_H

#include "maze.h"
#include "player.h"
#include "pacmanlib_global.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPoint>
#include <QTimer>

class PACMANLIB_EXPORT Ghost : public QObject
{
    Q_OBJECT
public:
    Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    virtual ~Ghost();

public slots:
    void paint();

signals:
    void gameOver(bool won);

protected:
    QGraphicsScene *gs;
    QGraphicsEllipseItem *sprite, *clone;
    Maze    *maze;
    Player  *playerRef;
    QPoint  position;
    QPoint  direction;
    QTimer  stepTick;
    enum {
        stepIntervalStandard   = int(Maze::baseStepInterval / 0.75),
        stepIntervalTunnel     = int(Maze::baseStepInterval / 0.40),
        stepIntervalFrightened = int(Maze::baseStepInterval / 0.50),
    };

    static float getDistance(QPoint field1, QPoint field2);
    int getInterval(void);

    void step (QPoint target);
};

class PACMANLIB_EXPORT Blinky : public Ghost
{
public:
    Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void);
};

class PACMANLIB_EXPORT Pinky : public Ghost
{
public:
    Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void);
    void paint(void);
};

class PACMANLIB_EXPORT Inky : public Ghost
{
public:
    Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void);
    void paint(void);
};

class PACMANLIB_EXPORT Clyde : public Ghost
{
public:
    Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void);
    void paint(void);
};
#endif // GHOST_H
