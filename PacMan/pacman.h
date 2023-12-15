#ifndef PACMAN_H
#define PACMAN_H

#define ENABLE_FPS_COUNTER

#include "ghost.h"
#include "player.h"
#include "maze.h"

#include "pacmanlib_global.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFontDatabase>
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
    QGraphicsScene    *gameScene, *menuScene;
    QGraphicsTextItem *menuPrompt = nullptr, *menuText = nullptr, *gameStateText = nullptr, *scoreText = nullptr;
    QFont              pacManFont, pacManFontLarge;

    Maze    *maze      =  nullptr;
    Player  *player    =  nullptr;
    Ghost   *ghosts[4] = {nullptr, nullptr, nullptr, nullptr};


#ifdef ENABLE_FPS_COUNTER
    int fpsCounter = 0, fps = 0;
    QTimer *fpsTimer = nullptr;
    QGraphicsTextItem *fpsText;
#endif // ENABLE_FPS_COUNTER

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
