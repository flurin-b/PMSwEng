#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsScene>
#include "maze.h"

class Ghost
{
public:
    Ghost(QGraphicsScene *sc, Maze *maze);
    virtual void step(void) = 0;
    virtual void paint(void) = 0;

private:
    QGraphicsScene *sc;
    Maze *maze;
};

class Blinky : public Ghost
{
    Blinky(QGraphicsScene *sc, Maze *maze);
    void step(void) override;
    void paint(void) override;
};

class Pinky : public Ghost
{
    Pinky(QGraphicsScene *sc, Maze *maze);
    void step(void) override;
    void paint(void) override;
};

class Inky : public Ghost
{
    Inky(QGraphicsScene *sc, Maze *maze);
    void step(void) override;
    void paint(void) override;
};

class Clyde : public Ghost
{
    Clyde(QGraphicsScene *sc, Maze *maze);
    void step(void) override;
    void paint(void) override;
};
#endif // GHOST_H
