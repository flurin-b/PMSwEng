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
    PacMan(QGraphicsScene *sc);
    void handleKeyPress(QKeyEvent event);

private:
    QGraphicsScene *sc;
    Maze *maze;
    Ghost *ghost[4];
    Player *player;
};

#endif // PACMAN_H
