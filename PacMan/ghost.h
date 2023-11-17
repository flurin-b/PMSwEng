#ifndef GHOST_H
#define GHOST_H

#include "maze.h"
#include "player.h"
#include "pacmanlib_global.h"

#include <QGraphicsScene>
#include <QObject>
#include <QPoint>

class PACMANLIB_EXPORT Ghost : public QObject
{
    Q_OBJECT
public:
    Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    virtual ~Ghost();
    virtual void step(void) = 0;

public slots:
    virtual void paint(void) = 0;

signals:
    void gameOver(bool won);

protected:
    QGraphicsScene *gs;
    Maze *maze;
    QPointF position;
    QPoint direction;
    Player *playerRef;
    float getDistance(QPoint field1, QPoint field2);
};

class PACMANLIB_EXPORT Blinky : public Ghost
{
public:
    Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};

class PACMANLIB_EXPORT Pinky : public Ghost
{
public:
    Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};

class PACMANLIB_EXPORT Inky : public Ghost
{
public:
    Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};

class PACMANLIB_EXPORT Clyde : public Ghost
{
public:
    Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};
#endif // GHOST_H
