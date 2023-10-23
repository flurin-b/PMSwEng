#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include "maze.h"

class Player
{
public:
    Player(QGraphicsScene *sc, Maze *maze);
    void step(void);
    void paint(void);

private:
    QGraphicsScene *sc;
    Maze *maze;
};

#endif // PLAYER_H
