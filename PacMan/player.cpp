#include "player.h"
#include "maze.h"
#include <QKeyEvent>

/**
 * @brief Player::Player
 * @param scPointer A Pointer to the maze where the player can move in
 * @param mazePointer
 */
Player::Player(QGraphicsScene *gsPointer, Maze *mazePointer):gs{gsPointer},maze{mazePointer}
{
    //playerPosition Start unclear right now, change latter down the line
    position = QPointF{14,26.5};
    direction = QPoint{0,0};
    energizerTime = new QTimer();
    energizerTime->setSingleShot(true);
    QObject::connect(energizerTime, &QTimer::timeout, this, &Player::stopHunt);

}

/**
 * @brief Player::paint
 */
void Player::paint(void)
{
    // TODO: Needs to vary depending on movement mode and if there is food on the current tile.
    float stepSize = 0.1;

    // TODO: Verry verry dirty, do not leave like this!!!

    //Possible alternative to check if player is in the middle of the field. With the draw back that the arguemnt will be true even when the distance is <= than max stepSize
    //const QPointF &distanceVector = (position - QPointF(qFloor(position.x()) + 0.5, qFloor(position.y()) + 0.5));
    //float distance = QPointF::dotProduct(distanceVector,distanceVector);

    if (abs(10 * int(position.x()) - int(10 * position.x() + 0.5)) == 5 && abs(10 * int(position.y()) - int(10 * position.y() + 0.5)) == 5)
    {
        step();
        eatItem();
    }

    position += stepSize*QPointF{direction};

    //Reposition the Player if he goes into the tunnel
    if(position.x() <= 0.0)
    {
        position = QPointF(27.9,17.5);
    }

    else if(position.x() >= 28)
    {
        position = QPointF(0.1,17.5);
    }

    float fieldWidth_px = maze->getFieldWidth();
    gs->addEllipse((position.x()-0.5) * fieldWidth_px, (position.y()-0.5) * fieldWidth_px, fieldWidth_px, fieldWidth_px);
}

/**
 * @brief Player::step Update Direction based on Keyboard Inputed Direction and Current Direction
 */
void Player::step(void)
{
    std::vector<QPoint> possibleDirs = maze->getMaze(QPoint(qFloor(position.x()), qFloor(position.y())));

    int i = 0;
    do
    {
        // Take requested turn if possible
        if(possibleDirs[i] == pendingDirection)
        {
            direction = pendingDirection;
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

/**
 * @brief Player::getField Function used for getting the Field Pac-Man is currently in
 * @return A QPoint in the maze with the position of Pac-Man
 */
QPoint Player::getField(void)
{
    return QPoint(int(position.x()), int(position.y()));
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

void Player::eatItem(void)
{
    QPoint location = QPoint(qFloor(position.x()), qFloor(position.y()));
    //QPoint location = (position - QPointF{0.5, 0.5}).toPoint();
    char Item = maze->getDots(location);

    switch(Item)
    {
    case Maze::noItem:
        break;
    case Maze::smallPoint:
        maze->setDots(location,Maze::noItem);
        maze->increaseScore(10);
        break;
    case Maze::bigPoint:
        maze->setDots(location,Maze::noItem);
        maze->increaseScore(50);
        status = hunt;
        energizerTime->start(6000);
        break;
    }
}

void Player::stopHunt(void)
{
    status = normal;
}
