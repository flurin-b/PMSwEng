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

/**
 * @brief The PacMan class brings all the game objects together and exposes them to the user.
 */
class PACMANLIB_EXPORT PacMan : public QObject
{
    Q_OBJECT
public:
    PacMan(QGraphicsView *gvPointer);
    virtual ~PacMan();

public slots:
    void handleKeyPress(QKeyEvent *event);
    void handleGameOver(bool won);

private:
    /** @brief Stores the QGraphicsView everything is rendered to. */
    QGraphicsView     *gv;
    /** @brief Displays the game. */
    QGraphicsScene    *gameScene;
    /** @brief Displays the Game Over screen. */
    QGraphicsScene    *menuScene;

    /** @brief Displays "Game Over". */
    QGraphicsTextItem *menuText = nullptr;
    /** @brief Tells the player to press enter after Game Over. */
    QGraphicsTextItem *menuPrompt = nullptr;
    /** @brief Displays the score on Game Over. */
    QGraphicsTextItem *scoreText = nullptr;
    /** @brief Tells the player to press enter to start the game or resume after pausing. */
    QGraphicsTextItem *gameStateText = nullptr;

    /** @brief The font normal Text is written in. */
    QFont   pacManFont;
    /** @brief The font "Game Over" is written in. */
    QFont   pacManFontLarge;

    /** @brief Calls PacMan::paint periodically. */
    QTimer  frameTimer;

    /** @brief A reference to the current Maze object. */
    Maze    *maze      =  nullptr;
    /** @brief A reference to the current Player object. */
    Player  *player    =  nullptr;
    /** @brief References to the current Ghost objects. */
    Ghost   *ghosts[4] = {nullptr, nullptr, nullptr, nullptr};


#ifdef ENABLE_FPS_COUNTER
    int fpsCounter = 0, fps = 0;
    QTimer *fpsTimer = nullptr;
    QGraphicsTextItem *fpsText;
#endif // ENABLE_FPS_COUNTER

    /** @brief Stores the current state of the game */
    enum {
        start,
        running,
        paused,
        won,
        lost
    } gameState = start;

    void initGameObjects(void);
    void paint(void);
};

#endif // PACMAN_H
