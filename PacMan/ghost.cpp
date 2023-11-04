#include "ghost.h"
#include "player.h"

/**
 * @brief Ghost::Ghost
 * @param scPointer
 * @param mazePointer
 * @param playerRefPointer
 */
Ghost::Ghost(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer):sc(scPointer),maze(mazePointer),playerRef(playerRefPointer)
{

}

/**
 * @brief Ghost::~Ghost
 */
Ghost::~Ghost()
{

}

/**
 * @brief Blinky::Blinky
 * @param scPointer
 * @param mazePointer
 * @param playerRefPointer
 */
Blinky::Blinky(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(scPointer,mazePointer,playerRefPointer)
{

}

/**
 * @brief Blinky::step
 */
void Blinky::step(void)
{

}
/**
 * @brief Blinky::paint
 */
void Blinky::paint(void)
{

}

/**
 * @brief Pinky::Pinky
 * @param scPointer
 * @param mazePointer
 * @param playerRefPointer
 */
Pinky::Pinky(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(scPointer,mazePointer,playerRefPointer)
{

}

/**
 * @brief Pinky::step
 */
void Pinky::step(void)
{

}

/**
 * @brief Pinky::paint
 */
void Pinky::paint(void)
{

}

/**
 * @brief Inky::Inky
 * @param scPointer
 * @param mazePointer
 * @param playerRefPointer
 */
Inky::Inky(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(scPointer,mazePointer,playerRefPointer)
{

}

/**
 * @brief Inky::step
 */
void Inky::step(void)
{

}

/**
 * @brief Inky::paint
 */
void Inky::paint(void)
{

}

/**
 * @brief Clyde::Clyde
 * @param scPointer
 * @param mazePointer
 * @param playerRefPointer
 */
Clyde::Clyde(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(scPointer,mazePointer,playerRefPointer)
{

}

/**
 * @brief Clyde::step
 */
void Clyde::step(void)
{

}


/**
 * @brief Clyde::paint
 */
void Clyde::paint(void)
{

}
