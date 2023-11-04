#ifndef PACMAN_H
#define PACMAN_H

#include "qwidget.h"
#include "ghost.h"
#include "player.h"
#include "maze.h"

#include <QGraphicsScene>
#include <QTimer>

class PacMan
{
public:
    PacMan(QGraphicsScene *scPointer);
    virtual ~PacMan();
    void handleKeyPress(QKeyEvent event);

private:
    QGraphicsScene *sc;
    Maze *maze;
    Ghost *ghosts[4];
    Player *player;
};

#endif // PACMAN_H
