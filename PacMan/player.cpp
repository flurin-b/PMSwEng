#include "player.h"
#include "Maze.h"
#include <QKeyEvent>

/**
 * @brief Player::Player
 * @param scPointer A Pointer to the maze where the player can move in
 * @param mazePointer
 */
Player::Player(QGraphicsScene *gsPointer, Maze *mazePointer):gs{gsPointer},maze{mazePointer}
{
    //playerPosition Start unclear right now, change latter down the line
    position = QPoint{13,26};
    direction = QPoint{-1,0};
    energizerTimeout = new QTimer();
    energizerTimeout->setSingleShot(true);
    QObject::connect(energizerTimeout, &QTimer::timeout, this, &Player::resetEnergized);

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Player::step);
    stepTick.setInterval(stepIntervalNoCoin/2);

    spriteTimer.setTimerType(Qt::PreciseTimer);
    QObject::connect(&spriteTimer, &QTimer::timeout, this, &Player::swapSprite);
    spriteTimer.setInterval(150);

    float fieldWidth_px = maze->getFieldWidth();
    spriteShut = QPixmap(":/Sprite/Player/PlayerShut.png").scaledToWidth(fieldWidth_px);
    spriteOpen = QPixmap(":/Sprite/Player/PlayerOpen.png").scaledToWidth(fieldWidth_px);
    pixmap = gs->addPixmap(spriteOpen);
    pixmap->setTransformOriginPoint((QPoint(fieldWidth_px/2,fieldWidth_px/2)));
    clone = gs->addPixmap(spriteOpen);
    clone->setTransformOriginPoint((QPoint(fieldWidth_px/2,fieldWidth_px/2)));
    spriteStatus = spriteIsOpen;
}

void Player::setPaused(bool paused)
{
    static int stepTickCache = -1, energizerTimeoutCache = -1;//,spriteTimerChache = -1;
    if(paused)
    {
        stepTickCache = stepTick.remainingTime();
        energizerTimeoutCache = energizerTimeout->remainingTime();
        //spriteTimerChache = spriteTimer.remainingTime();
        stepTick.stop();
        energizerTimeout->stop();
        spriteTimer.stop();
    }
    else
    {
        if (stepTickCache != -1)
            stepTick.start(stepTickCache);
        else
            stepTick.start();

        if(energizerTimeoutCache != -1)
            energizerTimeout->start(energizerTimeoutCache);
        else
            energizerTimeout->start();

        /*if(spriteTimerChache != -1)
            spriteTimer.start();
        else*/
            spriteTimer.start();
    }
}

/**
 * @brief Player::paint
 */
void Player::paint(void)
{
    static QPointF subposition{position.x()+0.5, float(position.y())};
    // if not paused, update subposition
    if(stepTick.remainingTime() != -1)
    {
        float delta = 1.0 - (float)stepTick.remainingTime() / getStepInterval();
        subposition = direction.toPointF();
        subposition *= delta;
        subposition -= direction;
        subposition += position.toPointF();
    }

    static bool ate = false; // true if PacMan has eaten whatever was in the current field
    // check for 180 degree turns as otherwise the player could eat dots he hasn't touched yet
    static QPoint lastDirection(direction);
    if (lastDirection == -direction)
        ate = true;
    lastDirection = direction;

    if (subposition.toPoint() == position){
        if (!ate) {
            eating = maze->getDots(position);
            if (eating)
            {
                eatItem(subposition.toPoint());
                stepTick.setInterval(getStepInterval()/2);
                ate = true;
            }
        }
    }
    else
    {
        ate = false;
    }

    float fieldWidth_px = maze->getFieldWidth();
    pixmap->setPos(subposition.x() * fieldWidth_px, subposition.y() * fieldWidth_px);
    if(direction.x() != 0)
    {
        pixmap->setRotation(direction.x() > 0 ? 0 : 180);
    }
    else if(direction.y() != 0)
    {
        pixmap->setRotation(direction.y() > 0 ? 90 : -90);
    }

    // Test if the player is in the tunnel
    if ((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        clone->setVisible(true);
        if (position.x() == 0)
        {
            clone->setRotation(0);
            clone->setPos((subposition.x() + maze->width) * fieldWidth_px, subposition.y() * fieldWidth_px);
        }
        else
        {
            clone->setRotation(180);
            clone->setPos((subposition.x() - maze->width) * fieldWidth_px, subposition.y() * fieldWidth_px);
        }
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
    // If stoped deactive the swaping of the sprites, otherwise check if the timer is already running
    if(direction.manhattanLength() == 0)
    {
        spriteTimer.stop();
    }
    else if(spriteTimer.isActive() == 0)
    {
        spriteTimer.start();
    }

    position += direction;
    stepTick.setInterval(getStepInterval());

    if(position.x() < 0 || position.x() > 27)
    {
        position.setX((position.x()+maze->width) % maze->width);
    }
}

/**
 * @brief Player::getField Function used for getting the Field Pac-Man is currently in
 * @return A QPoint in the maze with the position of Pac-Man
 */
QPoint Player::getField(void)
{
    QPointF subposition = direction.toPointF() * ((float)stepTick.remainingTime()/getStepInterval());
    return position - subposition.toPoint();
}

QPoint Player::getDirection(void)
{
    return direction;
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

void Player::eatItem(QPoint location)
{
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
        emit Player::energizedChanged(true);
        break;
    }
}

void Player::resetEnergized(void)
{
    status = normal;
    emit Player::energizedChanged(false);
}

int Player::getStepInterval(void)
{

    if(status == energized)
        return eating ? stepIntervalEnergizedCoin : stepIntervalEnerfizedNoCoin;
    else
        return eating ? stepIntervalCoin : stepIntervalNoCoin;
}

void Player::swapSprite(void)
{
    //Animate the Player sprite by swaping between two versions
    if(spriteStatus == spriteIsOpen)
    {
        pixmap->setPixmap(spriteShut);
        clone->setPixmap(spriteShut);
        spriteStatus = spriteIsShut;
    }
    else
    {
        pixmap->setPixmap(spriteOpen);
        clone->setPixmap(spriteOpen);
        spriteStatus = spriteIsOpen;
    }
}
