#ifndef PACMAN_H
#define PACMAN_H

#include "ghost.h"
#include "player.h"
#include "maze.h"

#include "pacmanlib_global.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>

class PACMANLIB_EXPORT PacMan : public QObject
{
    Q_OBJECT
public:
    PacMan(QGraphicsView *gvPointer);
    virtual ~PacMan();

public slots:
    void handleKeyPress(QKeyEvent *event);

private:
    QGraphicsView *gv;
    QGraphicsScene *gs;
    Maze *maze;
    Ghost *ghosts[4];
    Player *player;

    QTimer *gameTick;
};

#endif // PACMAN_H
