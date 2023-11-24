#ifndef PACMAN_H
#define PACMAN_H

#include "ghost.h"
#include "player.h"
#include "maze.h"

#include "pacmanlib_global.h"

#include <QGraphicsView>
#include <QGraphicsScene>
//#include <QTimer>
#include <QKeyEvent>

class PACMANLIB_EXPORT PacMan : public QObject
{
    Q_OBJECT
public:
    PacMan(QGraphicsView *gvPointer);
    virtual ~PacMan();
    void paint();

public slots:
    void handleKeyPress(QKeyEvent *event);
    void gameOverHandler(bool won);

private:
    QGraphicsView *gv;
    QGraphicsScene *gs;
    Maze *maze;
    Ghost *ghosts[4];
    Player *player;
    QTimer *gameTick;

    bool gameOver = false;
    bool gameWon = false;
};

#endif // PACMAN_H
