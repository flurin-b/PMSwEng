#include "player.h"

/**
 * @brief Player::Player
 * @param scPointer A Pointer to the maze where the player can move in
 * @param mazePointer
 */
Player::Player(QGraphicsScene *scPointer, Maze *mazePointer):sc(scPointer),maze(mazePointer),playerPosistion(0,0) //playerPosition Start unclear right now, change latter down the line
{

}

/**
 * @brief Player::paint
 */
void Player::paint(void)
{

}

/**
 * @brief Player::step
 */
void Player::step(void)
{

}

/**
 * @brief Player::getPosistion Function used for getting the Position of Pac-Man
 * @return A QPoint in the maze with the position of Pac-Man
 */
QPoint Player::getPosistion(void)
{
    return playerPosistion;
}

/**
 * @brief Player::MovePlayer
 * @param offset
 */
void Player::MovePlayer(QPoint offset)
{

}
