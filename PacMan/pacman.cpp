#include "pacman.h"
#include "maze.h"
#include "qevent.h"

#include <stdio.h>

// Set sizeof fields
int fieldSize_px = 20;

/**
 * @brief PacMan::PacMan Creates the Pac-Man which is moveable from the Player
 * @param scPointer
 */
PacMan::PacMan(QGraphicsView *gvPointer):gv{gvPointer}
{
    QGraphicsScene* gs = new QGraphicsScene();
    gv->setScene(gs);
    gv->setFixedSize(maze->width*fieldSize_px + 1, maze->height*fieldSize_px);

    maze= new Maze(gs, gv);
    // add one pixel to width in order to compensate for the margin of QGraphicsView.
    player = new Player(gs,maze);
    ghosts[0] = new Blinky(gs,maze,player);
    ghosts[1] = new Pinky (gs,maze,player);
    ghosts[2] = new Inky  (gs,maze,player);
    ghosts[3] = new Clyde (gs,maze,player);

    gameTick = new QTimer();
    gameTick->start(50);
    QObject::connect(gameTick, &QTimer::timeout, maze, &Maze::paint);
    QObject::connect(gameTick, &QTimer::timeout, player, &Player::paint);
    for (Ghost* ghost : ghosts) {
        QObject::connect(gameTick, &QTimer::timeout, ghost, &Ghost::paint);
    }
}

/**
 * @brief PacMan::~PacMan Delets allocated memory during ctor
 */
PacMan::~PacMan()
{
    delete maze;
    maze = nullptr;

    delete player;
    player = nullptr;

    for(Ghost* ghost : ghosts)
    {
        delete ghost;
        ghost = nullptr;
    }

    delete gameTick;
    gameTick = nullptr;
}

/**
 * @brief PacMan::handleKeyPress
 * @param event
 */
void PacMan::handleKeyPress(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        player->changeDirection(event);
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        break;
    default:
        break;
    }
}
