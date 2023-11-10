#ifndef PACMAN_H
#define PACMAN_H

#include "qwidget.h"
#include "ghost.h"
#include "player.h"
#include "maze.h"

#include <QGraphicsScene>
#include <QTimer>


#define GHOST_NUMBERS   4

class PacMan
{
public:
    PacMan(QGraphicsScene *scPointer);
    virtual ~PacMan();
    void handleKeyPress(QKeyEvent event);

private:
    QGraphicsScene *sc;
    Maze *maze;
    Ghost *ghosts[GHOST_NUMBERS];
    Player *player;
};

#endif // PACMAN_H
