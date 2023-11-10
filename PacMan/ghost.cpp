#include "ghost.h"
#include "player.h"

/**
 * @brief Ghost::Ghost Abstrakte Klasse die das Grund gerüst für Blinky/Pinky/Inky/Clyde ist
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Ghost::Ghost(QGraphicsScene *scPointer, Maze *mazePointer, Player *playerRefPointer):sc(scPointer),maze(mazePointer),playerRef(playerRefPointer)
{

}

/**
 * @brief Ghost::~Ghost Dealocate memory
 */
Ghost::~Ghost()
{

}

/**
 * @brief Blinky::Blinky Creates a Ghost with a chase pattern of Blinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
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
 * @brief Pinky::Pinky Creates a Ghost with a chase pattern of Pinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
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
 * @brief Inky::Inky Creates a Ghost with a chase pattern of Inky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
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
 * @brief Clyde::Clyde Creates a Ghost with a chase pattern of Clyde
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
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
