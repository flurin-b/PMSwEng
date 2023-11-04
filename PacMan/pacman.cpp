#include "pacman.h"
#include "maze.h"
#include "qevent.h"

/**
 * @brief PacMan::PacMan
 * @param scPointer
 */
PacMan::PacMan(QGraphicsScene *scPointer):sc(scPointer)
{
    sc->addSimpleText("Hello World!"); //Remove latter down the line

    Maze* maze = new Maze(sc);
    Player* player = new Player(sc,maze);
    Ghost* ghosts[GHOST_NUMBERS] = {new Blinky(sc,maze,player), new Pinky(sc,maze,player), new Inky(sc,maze,player), new Clyde(sc,maze,player)};
}

/**
 * @brief PacMan::~PacMan
 */
PacMan::~PacMan()
{
    delete maze;
    maze = nullptr;

    delete player;
    player = nullptr;

    for(int i=0; i<GHOST_NUMBERS;i++)
    {
        delete ghosts[i];
        ghosts[i] = nullptr;
    }
}

/**
 * @brief PacMan::handleKeyPress
 * @param event
 */
void PacMan::handleKeyPress(QKeyEvent event)
{

}
