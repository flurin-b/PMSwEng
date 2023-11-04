#include "player.h"

/**
 * @brief Player::Player
 * @param scPointer
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
 * @brief Player::getPosistion
 * @return
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
