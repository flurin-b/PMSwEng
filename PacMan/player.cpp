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
    position = QPoint{14,26};
    direction = QPoint{0,0};
    energizerTimeout = new QTimer();
    energizerTimeout->setSingleShot(true);
    QObject::connect(energizerTimeout, &QTimer::timeout, this, &Player::resetStatus);

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Player::step);
    stepTick.start(stepIntervalNoCoin);
}

/**
 * @brief Player::paint
 */
void Player::paint(void)
{
    float delta = 1.0 - (float)stepTick.remainingTime() / getStepInterval();

    QPointF positionF(direction);
    positionF *= delta;
    positionF -= direction;
    positionF += position.toPointF();

    float fieldWidth_px = maze->getFieldWidth();
    static QGraphicsEllipseItem* g = gs->addEllipse(positionF.x() * fieldWidth_px, positionF.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
    g->setRect(positionF.x() * fieldWidth_px, positionF.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
    //    static QGraphicsRectItem* s = gs->addRect(position.x()*fieldWidth_px, position.y()*fieldWidth_px, fieldWidth_px, fieldWidth_px);
    //    s->setRect(position.x()*fieldWidth_px, position.y()*fieldWidth_px, fieldWidth_px, fieldWidth_px);

    static QGraphicsEllipseItem* clone = gs->addEllipse(positionF.x() * fieldWidth_px, positionF.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);

    // Test if the player is in the tunnel
    if ((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        clone->setVisible(true);
        if (position.x() == 0)
            clone->setRect((positionF.x() + maze->width) * fieldWidth_px, positionF.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
        else
            clone->setRect((positionF.x() - maze->width) * fieldWidth_px, positionF.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
    }
    else
    {
        clone->setVisible(false);
    }
}

/**
 * @brief Player::step Update Direction based on Keyboard Inputed Direction and Current Direction
 */
void Player::step(void)
{
    // get all possible direction
    std::vector<QPoint> possibleDirs = maze->getMaze(position);
    int i = 0;
    // Check if pendingDirection is possible
    QPoint oldDirection(direction);
    direction = QPoint(0, 0);
    for(QPoint possibleDir : possibleDirs)
        if (possibleDir == pendingDirection)
        {
            direction = pendingDirection;
            break;
        }
    // If not, try to continue straight
    if(direction.manhattanLength() == 0)
        for(QPoint possibleDir : possibleDirs)
            if (possibleDir == oldDirection)
            {
                direction = oldDirection;
                break;
            }
    // If that is not possible either, stop.

    eating = maze->getDots(position) != Maze::noItem;
    eatItem();
    stepTick.setInterval(getStepInterval());

    position += direction;

    if(position.x() < 0 || position.x() > 27)
    {
        position.setX((position.x()+maze->width) % maze->width);
    }
}

///**
// * @brief Player::getPosistion Function used for getting the Position of Pac-Man
// * @return A QPoint in the maze with the position of Pac-Man
// */
//QPointF Player::getPosistion(void)
//{
//    return position;
//}

/**
 * @brief Player::getField Function used for getting the Field Pac-Man is currently in
 * @return A QPoint in the maze with the position of Pac-Man
 */
QPoint Player::getField(void)
{
    QPointF subposition = direction * ((stepTick.remainingTime()-stepTick.interval())/stepTick.interval());
    return (position+subposition).toPoint();
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
    if (direction == -pendingDirection)
    {
        position -= direction;
        direction = pendingDirection;
        stepTick.setInterval(getStepInterval()-stepTick.remainingTime());
    }
    if (direction == QPoint{0, 0})
    {
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
        status = Player::energized;
        energizerTimeout->start(energizerDuration);
        break;
    }
}

void Player::resetStatus(void)
{
    status = normal;
}

int Player::getStepInterval (void)
{

    if(status == energized)
        return eating ? stepIntervalEnergizedCoin : stepIntervalEnerfizedNoCoin;
    else
        return eating ? stepIntervalCoin : stepIntervalNoCoin;
}
