#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsScene>
#include "maze.h"
#include "player.h"

class Ghost
{
public:
    Ghost(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer);
    virtual ~Ghost();
    virtual void step(void) = 0;
    virtual void paint(void) = 0;

private:
    QGraphicsScene *sc;
    Maze *maze;
    QPoint ghostPosistion;
    Player *playerRef;
};

class Blinky : public Ghost
{
public:
    Blinky(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};

class Pinky : public Ghost
{
public:
    Pinky(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};

class Inky : public Ghost
{
public:
    Inky(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};

class Clyde : public Ghost
{
public:
    Clyde(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void) override;
    void paint(void) override;
};
#endif // GHOST_H
