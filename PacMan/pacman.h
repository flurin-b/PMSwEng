#ifndef PACMAN_H
#define PACMAN_H

 #include <QGraphicsScene>
#include "qwidget.h"
#include "ghost.h"
#include "player.h"
#include "maze.h"

class PacMan
{
public:
    PacMan(QGraphicsScene sc);
    void handleKeyPress(QKeyEvent event);

private:
    Maze maze;
    Ghost ghost;
    Player player;
};

#endif // PACMAN_H
