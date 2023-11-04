#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include "maze.h"

class Player
{
public:
    Player(QGraphicsScene *scPointer, Maze *mazePointer);
    void step(void);
    void paint(void);
    QPoint getPosistion(void);
    void MovePlayer(QPoint offset);

private:
    QGraphicsScene *sc;
    Maze *maze;
    QPoint playerPosistion;
};

#endif // PLAYER_H
