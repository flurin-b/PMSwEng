#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsScene>
#include "maze.h"

class Ghost
{
public:
    Ghost(QGraphicsScene sc, Maze maze);
    virtual void step(void) = 0;
    virtual void paint(void) = 0;

private:
    QGraphicsScene sc;
    Maze maze;
};

#endif // GHOST_H
