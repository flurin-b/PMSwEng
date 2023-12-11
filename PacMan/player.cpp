#include "player.h"
#include "Maze.h"
#include <QKeyEvent>

/**
 * @brief Player::Player Constructer of the Player entity
 * @param gsPointer Pointer to the GraphicScene where the Player should operate in
 * @param mazePointer Pointer to the Maze where the should operate in
 */
Player::Player(QGraphicsScene *gsPointer, Maze *mazePointer):gs{gsPointer},maze{mazePointer}
{
    //playerPosition Start unclear right now, change latter down the line
    position = QPoint{13,26};
    subposition = QPointF{position.x()+0.5, float(position.y())};
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
    spriteShut = QPixmap(":/Sprite/Player/PlayerShut.png").scaledToWidth(fieldWidth_px * scaleFactor);
    spriteOpen = QPixmap(":/Sprite/Player/PlayerOpen.png").scaledToWidth(fieldWidth_px * scaleFactor);
    pixmap = gs->addPixmap(spriteOpen);
    pixmap->setZValue(1);
    pixmap->setTransformOriginPoint((QPoint((fieldWidth_px * scaleFactor)/2,(fieldWidth_px * scaleFactor)/2)));
    clone = gs->addPixmap(spriteOpen);
    clone->setTransformOriginPoint((QPoint((fieldWidth_px * scaleFactor)/2,(fieldWidth_px * scaleFactor)/2)));
    spriteStatus = spriteIsOpen;
}

/**
 * @brief Player::setPaused Stop the Player logic from updating
 * @param paused Stop if true continue if false
 */
void Player::setPaused(bool paused)
{
    if(paused)
    {
        stepTickCache = stepTick.remainingTime();
        energizerTimeoutCache = energizerTimeout->remainingTime();
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
            spriteTimer.start();
    }
}

/**
 * @brief Player::paint Draw Player at new location and eat Dots if available
 */
void Player::paint(void)
{
    // if not paused, update subposition
    if(stepTick.remainingTime() != -1)
    {
        float delta = 1.0 - (float)stepTick.remainingTime() / getStepInterval();
        subposition = direction.toPointF();
        subposition *= delta;
        subposition -= direction;
        subposition += position.toPointF();
    }

    // check for 180 degree turns as otherwise the player could eat dots he hasn't touched yet
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


    if(direction.x() != 0)
    {
        pixmap->setRotation(direction.x() > 0 ? 0 : 180);
    }
    else if(direction.y() != 0)
    {
        pixmap->setRotation(direction.y() > 0 ? 90 : -90);
    }

    //Calculate the top left position if the sprite would be as wide as the field and subtract half of the wide pixels that are to wide becuse of the scaling
    float fieldWidth_px = maze->getFieldWidth();
    float xPosition = subposition.x() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
    float yPosition = subposition.y() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
    pixmap->setPos(xPosition, yPosition);

    // Test if the player is in the tunnel if so show clone at the other end of the tunnel for more emersion
    if ((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        clone->setVisible(true);
        if (position.x() == 0)
        {
            xPosition = (subposition.x() + maze->width) * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            yPosition = subposition.y() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            clone->setRotation(0);
            clone->setPos(xPosition,yPosition);
        }
        else
        {
            xPosition = (subposition.x() - maze->width) * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            yPosition = subposition.y() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            clone->setRotation(180);
            clone->setPos(xPosition,yPosition);
        }
    }
    else
    {
        clone->setVisible(false);
    }
}

/**
 * @brief Player::step Update Direction and move Player in the new Direction
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
    // If stoped deactivate the swaping of the sprites, otherwise check if the timer is already running
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

    //Move to the otherside of the tunnel
    if(position.x() < 0 || position.x() > 27)
    {
        position.setX((position.x()+maze->width) % maze->width);
    }
}

/**
 * @brief Player::getField Function used for getting the Field the Player is currently in
 * @return A QPoint in the maze with the position of Pac-Man
 */
QPoint Player::getField(void)
{
    QPointF subposition = direction.toPointF() * ((float)stepTick.remainingTime()/getStepInterval());
    return position - subposition.toPoint();
}

/**
 * @brief Player::getDirection Get the Current Direction the Player is heading as a QPoint
 * @return Up, Down,  Left, Right
 */
QPoint Player::getDirection(void)
{
    return direction;
}

/**
 * @brief Player::getStatus Get the Status of Player which depends on if a energizer was eaten
 * @return normal, energized
 */
char Player::getStatus(void)
{
    return status;
}

/**
 * @brief Player::changeDirection Read the direction inputed via Keyboard without normally changing the direction immediately
 * @param event The pressed Key
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
        if(stepTick.remainingTime() != -1)
            stepTick.setInterval(getStepInterval()-stepTick.remainingTime());
    }
    if (direction == QPoint{0, 0})
    {
        step();
    }
}

/**
 * @brief Player::eatItem Change the contend of a field in the Maze
 * @param location The Field which should be changed
 */
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

/**
 * @brief Player::resetEnergized Reset the Player status after a set amount of time specified with a timer
 */
void Player::resetEnergized(void)
{
    status = normal;
    emit Player::energizedChanged(false);
}

/**
 * @brief Player::getStepInterval Get the current Intervall time with which the function Player::step is called
 * @return Time in ms
 */
int Player::getStepInterval(void)
{

    if(status == energized)
        return eating ? stepIntervalEnergizedCoin : stepIntervalEnerfizedNoCoin;
    else
        return eating ? stepIntervalCoin : stepIntervalNoCoin;
}

/**
 * @brief Player::swapSprite Change between two sprite Version to create an eating animation
 */
void Player::swapSprite(void)
{
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
