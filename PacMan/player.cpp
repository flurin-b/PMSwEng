#include "player.h"
#include <QKeyEvent>

/**
 * @brief Player::Player
 * @param scPointer A Pointer to the maze where the player can move in
 * @param mazePointer
 */
Player::Player(QGraphicsScene *gsPointer, Maze *mazePointer):gs{gsPointer},maze{mazePointer}
{
    //playerPosition Start unclear right now, change latter down the line
    position = QPointF{14,14.5};
    direction = QPoint{0,0};
}

/**
 * @brief Player::paint
 */
void Player::paint(void)
{
    // TODO: Needs to vary depending on movement mode and if there is food on the current tile.
    float stepSize = 0.1;

    // TODO: Verry verry dirty, do not leave like this!!!
    if (abs(10 * int(position.x()) - int(10 * position.x() + 0.5)) == 5 && abs(10 * int(position.y()) - int(10 * position.y() + 0.5)) == 5) {
        step();
    }
    position += stepSize*QPointF{direction};


    float fieldWidth_px = maze->getFieldWidth();
    gs->addEllipse((position.x()-0.5) * fieldWidth_px, (position.y()-0.5) * fieldWidth_px, fieldWidth_px, fieldWidth_px);
}

/**
 * @brief Player::step Update Direction based on Keyboard Inputed Direction and Current Direction
 */
void Player::step(void)
{
    std::vector<QPoint> possibleDirs = maze->getMaze((position - QPointF{0.5, 0.5}).toPoint());

    int i = 0;
    do
    {
        // Debug
        /*qDebug("i =  %d",i);
        qDebug("Size of possibleDirs: %zu", possibleDirs.size());
        for(int j=0; j < possibleDirs.size(); j++)
        {
            qDebug("possibleDirs[%d] = (%d,%d)",j,possibleDirs[j].x(),possibleDirs[j].y());
        }
        qDebug("Direction = (%d,%d)",direction.x(),direction.y());
        qDebug("pendingDirection = (%d,%d)",pendingDirection.x(),pendingDirection.y());
        qDebug("");*/

        // Take requested turn if possible
        if(possibleDirs[i] == pendingDirection)
        {
            direction = pendingDirection;
            qDebug("");
            return;
        }
        // If the direction is neither the requested one nor straight, delete it
        else if(possibleDirs[i] != direction)
        {
            possibleDirs.erase(possibleDirs.begin() + i);
            i--;
        }
        i++;
    }while(i < possibleDirs.size());

    if(possibleDirs.size() != 1) {
        direction = QPoint(0,0);
    }
}

/**
 * @brief Player::getPosistion Function used for getting the Position of Pac-Man
 * @return A QPoint in the maze with the position of Pac-Man
 */
QPointF Player::getPosistion(void)
{
    return position;
}

void Player::increaseScore(int offset)
{
    if(offset > 0)
    {
        score += offset;
    }
}

char Player::getStatus(void)
{
    return status;
}

/**
 * @brief Player::MovePlayer Read which Key was pressed
 * @param event
 */
void Player::changeDirection(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        pendingDirection = QPoint{0,-1};
        break;

    case Qt::Key_Down:
        pendingDirection = QPoint{0,1};
        break;

    case Qt::Key_Left:
        pendingDirection = QPoint{-1,0};
        break;

    case Qt::Key_Right:
        pendingDirection = QPoint{1,0};
        break;
    }

    // Let the player immediately change direction if he is standing still or making a 180 degree turn.
    if (direction == QPoint{0, 0} || direction == -pendingDirection){
        step();
    }
}
