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
    QGraphicsView     *gv;
    QGraphicsScene    *gs;
    QGraphicsTextItem *gameStateText = nullptr;

    Maze    *maze      =  nullptr;
    Player  *player    =  nullptr;
    Ghost   *ghosts[4] = {nullptr, nullptr, nullptr, nullptr};

    enum {
        start,
        running,
        paused,
        won,
        lost
    } gameState = start;

    void initGameObjects();
};

#endif // PACMAN_H
