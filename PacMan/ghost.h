#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsScene>
#include "maze.h"
#include "player.h"

class Ghost
{
public:
    Ghost(QGraphicsScene *sc, Maze *maze, Player *playerRef);
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
    Blinky(QGraphicsScene *sc, Maze *maze, Player *playerRef);
    void step(void) override;
    void paint(void) override;
};

class Pinky : public Ghost
{
public:
    Pinky(QGraphicsScene *sc, Maze *maze, Player *playerRef);
    void step(void) override;
    void paint(void) override;
};

class Inky : public Ghost
{
public:
    Inky(QGraphicsScene *sc, Maze *maze, Player *playerRef);
    void step(void) override;
    void paint(void) override;
};

class Clyde : public Ghost
{
public:
    Clyde(QGraphicsScene *sc, Maze *maze, Player *playerRef);
    void step(void) override;
    void paint(void) override;
};
#endif // GHOST_H
