#include "player.h"
#include "Maze.h"
#include <QKeyEvent>

/**
 * @brief Initializes all attributes, sprites and timer used by a Player object.
 * @param Pointer to the GraphicScene where the Player should be displayed.
 * @param Pointer to the Maze where the Player should operate in.
 */
Player::Player(QGraphicsScene *gsPointer, Maze *mazePointer):gs{gsPointer},maze{mazePointer}
{
    //Set the start Position from the Player
    position = QPoint{13,26};
    subposition = QPointF{position.x()+0.5, float(position.y())};
    direction = QPoint{-1,0};

    //Create a Timer which will reset the energizer status after the defined time in the variable energizerDuration
    energizerTimeout = new QTimer();
    energizerTimeout->setSingleShot(true);
    QObject::connect(energizerTimeout, &QTimer::timeout, this, &Player::resetEnergized);

    // Timer that calls the periodic step function.
    // This Timer is set to be a Precise Timer because it determines the movement speed of the Player.
    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Player::step);
    stepTick.setInterval(stepIntervalNoCoin/2);

    //Timer that calls the method which "animates" the Player by swapping between two sprites
    spriteTimer.setTimerType(Qt::PreciseTimer);
    QObject::connect(&spriteTimer, &QTimer::timeout, this, &Player::swapSprite);
    spriteTimer.setInterval(150);

    //Load the two Sprites from the ResourceSystem into variables for easy access in the Code later
    float fieldWidth_px = maze->getFieldWidth();
    spriteShut = QPixmap(":/Sprite/Player/PlayerShut.png").scaledToWidth(fieldWidth_px * scaleFactor);
    spriteOpen = QPixmap(":/Sprite/Player/PlayerOpen.png").scaledToWidth(fieldWidth_px * scaleFactor);
    pixmap = gs->addPixmap(spriteOpen);
    pixmap->setZValue(1);
    //Move the center for rotation into the middle of the pixmap
    pixmap->setTransformOriginPoint((QPoint((fieldWidth_px * scaleFactor)/2,(fieldWidth_px * scaleFactor)/2)));
    clone = gs->addPixmap(spriteOpen);
    clone->setTransformOriginPoint((QPoint((fieldWidth_px * scaleFactor)/2,(fieldWidth_px * scaleFactor)/2)));
    spriteStatus = mouthOpen;
}

/**
 * @brief Enables pausing of all logic.
 * @param Pause if true, resume if false.
 */
void Player::setPaused(bool paused)
{
    if(paused)
    {
        // Load the timer caches with the current timer values.
        stepTickCache = stepTick.remainingTime();
        energizerTimeoutCache = energizerTimeout->remainingTime();
        // Stop the timers.
        stepTick.stop();
        energizerTimeout->stop();
        spriteTimer.stop();
    }
    else
    {
        if (stepTickCache != -1)
        {
            // Reload the timers to the previous period if there is a cached value.
            stepTick.start(stepTickCache);
        }
        else
        {
            // If there are no cached values, just start the timers.
            stepTick.start();
        }

        if(energizerTimeoutCache != -1)
        {
            // Reload the timers to the previous period if there is a cached value.
            energizerTimeout->start(energizerTimeoutCache);
        }
        else
        {
            // If there are no cached values, just start the timers.
            energizerTimeout->start();
        }
        //Start the Timer for the Player animation always when changing from paused to some other state
        spriteTimer.start();
    }
}

/**
 * @brief Update the Player sprite and eat dots if applicable.
 */
void Player::paint(void)
{
    // if not paused, update subposition
    if(stepTick.remainingTime() != -1)
    {
        subposition = position.toPointF() + direction.toPointF() * (-(float)stepTick.remainingTime() / getStepInterval());
    }

    // check for 180 degree turns as otherwise the player could eat dots he hasn't touched yet
    if (lastDirection == -direction)
        ate = true;
    lastDirection = direction;

    // If the player hasn't eaten yet and has reached the new field, eat what's in it.
    if (subposition.toPoint() == position){
        if (!ate) {
            eating = maze->getItemAt(position);
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

    // Set the direction in wich the player pixmap faces.
    if(direction.x() != 0)
    {
        pixmap->setRotation(direction.x() > 0 ? 0 : 180);
    }
    else if(direction.y() != 0)
    {
        pixmap->setRotation(direction.y() > 0 ? 90 : -90);
    }

    // Calculate the sprites position to make it appear centered over its current position.
    //   To do this, the subposition is multiplied with the field width to get the top left corner of the current "subfield" in pixels.
    //   To correct for the Pixmap being bigger than a field, the length in Fields the Sprite is bigger than a field (scaleFactor - 1) is halved and subtracted from the subposition.
    float fieldWidth_px = maze->getFieldWidth();
    float xPosition = fieldWidth_px * (subposition.x() - ((scaleFactor - 1.0) * 0.5));
    float yPosition = fieldWidth_px * (subposition.y() - ((scaleFactor - 1.0) * 0.5));
    pixmap->setPos(xPosition, yPosition);

    // Test if the player is in the tunnel and if it is show clone at the other end of the tunnel for ✨more emersion✨
    if (position.x() <= 0 && direction.x() > 0)
    {
        xPosition = fieldWidth_px * ((subposition.x() + maze->width) - ((scaleFactor - 1.0) * 0.5));
        clone->setRotation(0);
        clone->setPos(xPosition,yPosition);
        clone->setVisible(true);
    }
    else if(position.x() >= (maze->width-1) && direction.x() < 0)
    {
        xPosition = fieldWidth_px * ((subposition.x() - maze->width) - ((scaleFactor - 1.0) * 0.5));
        clone->setRotation(180);
        clone->setPos(xPosition,yPosition);
        clone->setVisible(true);
    }
    else
    {
        clone->setVisible(false);
    }
}

/**
 * @brief Update wich direction the player should go in and move the Player in that direction.
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

    //Move to the otherside of the tunnel when the end is reached
    if(position.x() < 0 || position.x() > 27)
    {
        position.setX((position.x()+maze->width) % maze->width);
    }
}

/**
 * @brief Used for getting the field the Player is currently in.
 * @return The players position in the Maze.
 */
QPoint Player::getField(void)
{
    return subposition.toPoint();
}

/**
 * @brief Get the Current Direction the Player is heading in.
 * @return The players direction as a QPoint.
 */
QPoint Player::getDirection(void)
{
    return direction;
}

/**
 * @brief Process keyboard inputs and change Player::direction or Player::pendingDirection accordingly.
 * @param The QKeyEvent to process.
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
        //Set the time when the next step is made to the time it was already traveling in this field, as it made a 180° turn
        if(stepTick.remainingTime() != -1)
            stepTick.setInterval(getStepInterval()-stepTick.remainingTime());
    }
    if (direction == QPoint{0, 0})
    {
        //Call step() if not moving at the moment, as otherwise nothing would call step() and get the Playe moving again
        step();
    }
}

/**
 * @brief Eat whatever is in the supplied field and react accordingly.
 * @param The Field that should be eaten.
 */
void Player::eatItem(QPoint location)
{
    char Item = maze->getItemAt(location);

    switch(Item)
    {
    case Maze::noItem:
        break;
    case Maze::dot:
        maze->setItemAt(location,Maze::noItem);
        maze->increaseScore(10);
        break;
    case Maze::energizer:
        maze->setItemAt(location,Maze::noItem);
        maze->increaseScore(50);
        //Let the Ghost know they should be frightend now
        status = Player::energized;
        energizerTimeout->start(energizerDuration);
        emit Player::energizedChanged(true);
        break;
    }
}

/**
 * @brief Reset the Player status to normal.
 */
void Player::resetEnergized(void)
{
    //Let the Ghost know they can hunt the Player again without fear
    status = normal;
    emit Player::energizedChanged(false);
}

/**
 * @brief Get the current Intervall with which the function Player::step should be called.
 * @return Time in ms
 */
int Player::getStepInterval(void)
{
    //Return the Intervall time depending on the status of the Player and if he is eatinng a dot in this field
    if(status == energized)
        return eating ? stepIntervalEnergizedCoin : stepIntervalEnerfizedNoCoin;
    else
        return eating ? stepIntervalCoin : stepIntervalNoCoin;
}

/**
 * @brief Change between two sprite Versions to create an eating animation.
 */
void Player::swapSprite(void)
{
    if(spriteStatus == mouthOpen)
    {
        pixmap->setPixmap(spriteShut);
        clone->setPixmap(spriteShut);
        spriteStatus = mouthClosed;
    }
    else
    {
        pixmap->setPixmap(spriteOpen);
        clone->setPixmap(spriteOpen);
        spriteStatus = mouthOpen;
    }
}
