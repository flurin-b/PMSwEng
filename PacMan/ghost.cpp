#include "ghost.h"

/**
 * @brief Ghost::Ghost Create the base for any specific Ghost (Blinky/Pinky/Inky/Clyde)
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerPointer A Pointer to the player so that they can chase him
 */
Ghost::Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):gs(gsPointer),maze(mazePointer),player(playerPointer)
{
    // Timer that calls the function to switch between the movement modes chase and scatter.
    movementTimer = new QTimer;
    connect(movementTimer, &QTimer::timeout, this, &Ghost::nextMovementPattern);
    nextMovementPattern();
    movementTimer->stop();

    // All the sprites to display the ghosts.
    spriteFrightendBlue =  QPixmap(":/Sprite/Ghost/GhostFrightend.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteFrightendWhite = QPixmap(":/Sprite/Ghost/GhostFrightendEnding.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeL = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeR = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeUp = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeDown = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);

    // Timer that calls the periodic step function.
    // This Timer is set to be a Precise Timer because it determines the movement speed of the ghosts.
    stepTick = new QTimer;
    stepTick->setTimerType(Qt::PreciseTimer);

    // This Timer controlls the ghosts blinking when he nears his frightened period.
    frightenedSpriteTimer = new QTimer;
    QObject::connect(frightenedSpriteTimer, &QTimer::timeout, this, &Ghost::toggleFrightenedSprite);
}

/**
 * @brief Ghost::~Ghost Dealocate memory
 */
Ghost::~Ghost()
{
    delete movementTimer;
    delete stepTick;
    delete frightenedSpriteTimer;
}

/**
 * @brief Ghost::setPaused Pause or resume the ghosts movement.
 * @param paused Stop if true, resume if false.
 */
void Ghost::setPaused(bool paused)
{
    if(paused)
    {
        // Load the timer caches with the current timer values.
        stepTickCache = stepTick->remainingTime();
        movementTimerCache = movementTimer->remainingTime();
        frightenedSpriteTimerCache = frightenedSpriteTimer->remainingTime();
        // Stop the timers.
        stepTick->stop();
        movementTimer->stop();
        frightenedSpriteTimer->stop();
    }
    else
    {
        if (stepTickCache != -1)
        {
            // Reload the timers to the previous period if there is a cached value.
            stepTick->start(stepTickCache);
            movementTimer->start(movementTimerCache);
        }
        else
        {
            // If there are no cached values, just start the timers.
            stepTick->start();
            movementTimer->start();
        }

        // frightenedSpriteTimer is not always running, therefore
        // a seperate check checks weather it should be startet or not.
        if (frightenedSpriteTimerCache != -1)
        {
            frightenedSpriteTimer->start(frightenedSpriteTimerCache);
        }
    }
}

/**
 * @brief Ghost::nextGhostPoints Stores how many points are awarded for eating the next ghost.
 */
int Ghost::nextGhostPoints;

/**
 * @brief Ghost::setFrightened puts the Ghost into firghtened or normal mode if applicable.
 * @param frightened Wether or not the ghost should be frightened.
 */
void Ghost::setFrightened(bool frightened)
{
    // Reset the nextGhostPoints variable as every first
    // ghost eaten after an energizer is worth 200 points.
    nextGhostPoints = 200;

    // Do not frighten returning ghosts.
    if(movement == returning)
        return;

    // If the Ghost should be frightened, frighten it!
    if (frightened)
    {
        // Set the Pixmap to the frightened one and start the timer that makes them blink
        // before returning to normal.
        pixmap->setPixmap(spriteFrightendBlue);
        spriteStatus = frightendBlue;
        frightenedSpriteTimer->setInterval(Player::energizerDuration * 0.7);
        frightenedSpriteTimer->start();

        // If the Ghost is not yet frightened, frighten it.
        if (movement != Ghost::frightened)
        {
            // Reverse direction if the Ghost is in the maze.
            if (state == Ghost::inMaze)
            {
                position -= direction;
                stepTick->setInterval(Ghost::stepIntervalFrightened * (1.0 - ((float)stepTick->remainingTime()/getStepInterval())));
                direction = -direction;
            }
            movement = Ghost::frightened;
        }
    }
    // If the ghost shouldn't be frightened, un-frighten it.
    else
    {
        // If the ghosts should not be frightened but are, un-frighten them.
        if (movement == Ghost::frightened)
        {
            movement = globalMovement;
            stepTick->setInterval(getStepInterval() * stepTick->remainingTime()/Ghost::stepIntervalFrightened);

            frightenedSpriteTimer->stop();
        }
    }
}

/**
 * @brief Ghost::toggleFrightenedSprite Swap between the two frightend sprites to show the Player the energized Time is running out.
 */
void Ghost::toggleFrightenedSprite(void)
{
    if(spriteStatus == frightendBlue)
    {
        frightenedSpriteTimer->setInterval(200);
        pixmap->setPixmap(spriteFrightendWhite);
        clonePixmap->setPixmap(spriteFrightendWhite);
        spriteStatus = frightendWhite;
    }
    else if(spriteStatus == frightendWhite)
    {
        pixmap->setPixmap(spriteFrightendBlue);
        clonePixmap->setPixmap(spriteFrightendBlue);
        spriteStatus = frightendBlue;
    }
}

/**
 * @brief Ghost::getDistanceTo Calculates and returns the distance from one Field to another.
 * @param field1 Field on the Board
 * @param field2 Field on the Board
 */
float Ghost::getDistance(QPoint field1, QPoint field2){
    int dx = field1.x()-field2.x();
    int dy = field1.y()-field2.y();
    return sqrt(dx*dx + dy*dy);
}

/**
 * @brief Ghost::getStepInterval Get the current Time between step calls.
 * @return Zeit in ms
 */
int Ghost::getStepInterval(void)
{
    // If the Ghost is in the tunnel return stepIntervalTunnel
    if((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
        return Ghost::stepIntervalTunnel;

    // Otherwise decide which interval to return based on movement patterns.
    switch (movement)
    {
    case chase:
    case scatter:
        return stepIntervalNormal;
    case frightened:
        return stepIntervalFrightened;
    case returning:
        return stepIntervalReturning;
    }
    return 0;
}

/**
 * @brief Ghost::getField Get the field in which the Ghost is currently in.
 * @return A field in the Maze as a QPoint
 */
QPoint Ghost::getField (void)
{
    return subposition.toPoint();
}

/**
 * @brief Ghost::nextMovementPattern Sets the next movement pattern and restarts the movementTimer for the next phase.
 */
void Ghost::nextMovementPattern()
{
    const static int patternTimes[8] = {7000, 20000, 7000, 20000, 5000, 20000, 5000, 20000};
    
    // Only update modes when there is still a next phase
    if (movementCounter < 8)
    {
        // Toggle the globalMovement movement mode.
        if (globalMovement == chase)
            globalMovement = scatter;
        else
            globalMovement = chase;
        // Set the new patternTime
        movementTimer->setInterval(patternTimes[movementCounter++]);
    }
}

/**
 * @brief Ghost::step Called periodically to update the ghosts position.
 * @param target
 */
void Ghost::step(QPoint target) {
#ifdef DEBUG_TARGETS
    debugTarget->setRect(target.x()*maze->getFieldWidth(), target.y()*maze->getFieldWidth(), maze->getFieldWidth(), maze->getFieldWidth());
#endif

    // Check if a returning ghost has reached the ghost house entrance
    // and if so, set its state to enteringGhostHouse.
    if(movement == returning && state != enteringGhostHouse)
    {
        if (direction == QPoint{1, 0})
        {
            if(getField() == resetPosition + QPoint{0, -3})
            {
                state = enteringGhostHouse;
                stepTick->setInterval(getStepInterval()/2);
                return;
            }
        }
        else if (direction == QPoint{-1, 0})
        {
            if(getField() == resetPosition + QPoint{1, -3})
            {
                position += direction;
                state = enteringGhostHouse;
                stepTick->setInterval(getStepInterval()/2);
                return;
            }
        }
    }

    switch (state)
    {
        // If the ghost is in the maze, pathfind towards its target.
        case Ghost::inMaze:
        {
            // Get all possible directions.
            std::vector<QPoint> possibleDirs = maze->getMaze(position);
            int i = 0;

            // Delete the opposite of the current direction as no 180 degree turns can be made by ghosts.
            for(QPoint possibleDir : possibleDirs)
            {
                if(possibleDir == -direction)
                {
                    possibleDirs.erase(possibleDirs.begin() + i);
                }
                else
                {
                    i++;
                }
            }

            // If there is only one direction, go in that direction,
            if (possibleDirs.size() == 1)
            {
                direction = possibleDirs[0];
            }
            // otherwise decide where to go.
            else
            {
                // When frightened, choose a random direction.
                if (movement == Ghost::frightened)
                {
                    static QRandomGenerator r;
                    direction = possibleDirs[r.bounded(possibleDirs.size())];
                }
                // Otherwise move to the field closest to the target.
                else
                {
                    // Find field nearest to target.
                    int nearest = 0;
                    for(int i = 1; i < possibleDirs.size(); i++){
                        if (getDistance(position+possibleDirs[nearest], target) > getDistance(position+possibleDirs[i], target))
                        {
                            nearest = i;
                        }
                    }
                    direction = possibleDirs[nearest];
                }
            }
            break;
        }
        // If the ghost is in the ghost house, only check if the dot limit is reached
        // and if so, leave the ghost house.
        case Ghost::inGhostHouse:
        {
            stepTick->setInterval(10);
            if(maze->getDotsEaten() < dotLimitGhostHouse)
                return;
            else
                state = Ghost::leavingGhostHouse;
            // There is intentionally no brake here, so the ghost
            // immediately starts leaving the ghost house
        }
        // Makes the ghost move towards the exit of the ghost house.
        case Ghost::leavingGhostHouse:
        {
            // This case uses the ghosts current position to determine
            // the direction it should move in.
            // Move right if too far left.
            if (position.x() < resetPosition.x())
            {
                direction = QPoint(1, 0);
            }
            // Move left if too far right.
            else if (position.x() > resetPosition.x())
            {
                direction = QPoint(-1, 0);
            }
            // Move up if horizontal position is correct but the ghost is too far down.
            else if (position.y() > 14)
            {
                direction = QPoint(0, -1);
            }
            // If the ghost is out of the ghost house, decide in what direction it should go.
            else
            {
                float distance_left = getDistance(position, target);
                float distance_right = getDistance(position + QPoint(1,0), target);
                if(distance_left < distance_right)
                {
                    direction = QPoint(-1, 0);
                }
                else
                {
                    direction = QPoint(1, 0);
                    position += direction;
                }
                state = Ghost::inMaze;
                stepTick->setInterval(getStepInterval() / 2);
                return;
            }
            break;
        }
        // Move towards the reset position and re-exit the ghost house once the reset position is reached.
        case Ghost::enteringGhostHouse:
        {
            if (position.y() < resetPosition.y())
            {
                direction = QPoint{0, 1};
            }
            else
            {
                state = leavingGhostHouse;
                movement = globalMovement;
                direction = -direction;
            }
        }
    }
    // Go in the determined direction
    position += direction;

    // When tunneling, jump to the other side of the maze
    if(position.x() < 0 || position.x() > 27)
        position.setX((position.x()+maze->width) % maze->width);

    // Update the stepTick interval
    stepTick->setInterval(getStepInterval());
}

/**
 * @brief Ghost::paint paints the ghost onto the GraphigsScene in its current position and state.
 */
void Ghost::paint(void)
{
    // If not paused, update subposition
    if(stepTick->remainingTime() != -1 && state != Ghost::inGhostHouse)
    {
        // Determine subposition based on the remaining time of the stepTick counter.
        float delta = 1.0 - (float)stepTick->remainingTime() / getStepInterval();
        subposition = direction.toPointF();
        subposition *= delta;
        subposition -= direction;
        subposition += position.toPointF();
        // Add 0.5 in the x direction because the fields inside the ghost house don't align with the maze fields.
        if (state == Ghost::leavingGhostHouse || state == Ghost::enteringGhostHouse)
        {
            subposition += QPointF{0.5, 0.0};
        }
    }

    // Paint the correct sprite based on the current movement move.
    switch (movement)
    {
    // Use the normal sprite while chase scatter.
    case chase:
    case scatter:
        if(direction.x() != 0)
        {
            pixmap->setPixmap(direction.x() > 0 ? spriteSideR : spriteSideL);
        }

        else
        {
            pixmap->setPixmap(direction.y() < 0 ? spriteUp : spriteDown);
        }
        break;
    // Use the exe sprites while returning.
    case returning:
        if(direction.x() != 0)
        {
            pixmap->setPixmap(direction.x() > 0 ? eyeR : eyeL);
        }
        else
        {
            pixmap->setPixmap(direction.y() < 0 ? eyeUp : eyeDown);
        }
        break;
    // Frightened sprites are set by toggleFrightenedSprite.
    case frightened:
        break;
    }

    // Calculate the sprites position to make it appear centered over its current position.
    //   To do this, the subposition is multiplied with the field width to get the top left corner of the current "subfield" in pixels.
    //   To correct for the Pixmap being bigger than a field, the length in Fields the Sprite is bigger than a field (scaleFactor - 1) is halved and subtracted from the subposition.
    float fieldWidth_px = maze->getFieldWidth();
    float xPosition = (subposition.x() - (scaleFactor - 1.0) / 2) * fieldWidth_px;
    float yPosition = (subposition.y() - (scaleFactor - 1.0) / 2) * fieldWidth_px;
    pixmap->setPos(xPosition, yPosition);

    // Make a second sprite visible if the ghost is in the tunnel so the ghost appears on both ends of the tunnel.
    if ((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        clonePixmap->setVisible(true);
        if (position.x() == 0)
        {
            // Add the maze width in pixels to xPosition to make the clone appear on the right side of the screen.
            xPosition += maze->getFieldWidth() * maze->width;
            clonePixmap->setPixmap(spriteSideL);
        }
        else
        {
            // Subtract the maze width in pixels to xPosition to make the clone appear on the left side of the screen.
            xPosition -= maze->getFieldWidth() * maze->width;
            clonePixmap->setPixmap(spriteSideR);
        }
        clonePixmap->setPos(xPosition,yPosition);
    }
    // Hide said clone if the ghost is not in the tunnel.
    else
    {
        clonePixmap->setVisible(false);
    }

    // Check if the ghost ate PacMan or vice versa
    if (player->getField() == subposition.toPoint())
    {
        switch (movement)
        {
        // Make the Ghost return to the ghost house if it is eaten.
        case frightened:
            // Update stepTick with the new speed
            stepTick->setInterval(stepTick->remainingTime() * stepIntervalReturning / getStepInterval());
            movement = returning;
            // Stop frightenedTimer to prevent it from setting any frightened sprites.
            frightenedSpriteTimer->stop();
            // Give points for eating a ghost and increment the points that are awarded for eating the next ghost.
            maze->increaseScore(nextGhostPoints);
            nextGhostPoints *= 2;
            break;
        case scatter:
        case chase:
            // If the ghost ate the Player, the game is lost.
            emit gameOver(false);
            break;
        case returning:
            break;
        }
    }
}

/**
 * @brief Blinky::Blinky creates a Ghost object with the chase pattern of Blinky.
 * @param scPointer Pointer to the GraphicsScene where Blinky will be displayed
 * @param mazePointer Pointer to the Maze object so Blinky can eat and navigate
 * @param playerPointer Pointer to the Player so Blinky can chase him
 */
Blinky::Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):Ghost(gsPointer,mazePointer,playerPointer)
{
    // Blinky starts in the maze and always moves right first.
    position = QPoint {13, 14};
    subposition = QPointF {position.x()+0.5, float(position.y())}; // Add 0.5 to the subposition because the ghost house and maze fields are not aligned.
    direction = QPoint {-1, 0};
    state = Ghost::inMaze;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(255, 0, 0);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    QObject::connect(stepTick, &QTimer::timeout, this, &Blinky::step);
    stepTick->setInterval(Ghost::stepIntervalNormal / 2);

    // Setup the sprites.
    spriteSideL = QPixmap(":/Sprite/Blinky/BlinkySideL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteSideR = QPixmap(":/Sprite/Blinky/BlinkySideR.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteUp = QPixmap(":/Sprite/Blinky/BlinkyUp.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteDown = QPixmap(":/Sprite/Blinky/BlinkyDown.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    pixmap = gs->addPixmap(spriteSideL);
    pixmap->setZValue(1);
    clonePixmap = gs->addPixmap(spriteSideL);
    clonePixmap->setVisible(false);
}

/**
 * @brief Blinky::step Step function that calls Ghost::step with the appropriate target.
 */
void Blinky::step(void)
{
    if(movement == chase or movement == scatter)
    {
        movement = globalMovement;
    }

    switch (movement)
    {
    // Target the player when in chase mode.
    case chase:
        Ghost::step(player->getField());
        break;
    // Target scatterTarget when in scatter mode.
    case scatter:
        Ghost::step(scatterTarget);
        break;
    // There is no target in frightened mode -> just set target to (0; 0)
    case frightened:
        Ghost::step(QPoint(0, 0));
        break;
    // When returning, target three fields above the reset position.
    // This represents the field on the top left of the ghost house exit.
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
    }
}

/**
 * @brief Pinky::Pinky Creates a Ghost with the chase pattern of Pinky
 * @param scPointer A Pointer to the GraphicsScene where Pinky will be displayed
 * @param mazePointer A Pointer to the maze object so Pinky can eat and navigate
 * @param playerPointer A Pointer to the player so Pinky can chase him
 */
Pinky::Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):Ghost(gsPointer,mazePointer,playerPointer)
{
    // Pinky starts in the center of the ghost house but immediately leaves.
    position = resetPosition;
    subposition = QPointF {position.x()+0.5, float(position.y())}; // Add 0.5 to the subposition because the ghost house and maze fields are not aligned.
    state = Ghost::leavingGhostHouse;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(255, 184, 255);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    // Connect stepTick and set Interval to 0 so Blinky immediately starts moving.
    QObject::connect(stepTick, &QTimer::timeout, this, &Pinky::step);
    stepTick->setInterval(0);

    // Setup the sprites.
    spriteSideL = QPixmap(":/Sprite/Pinky/PinkySideL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteSideR = QPixmap(":/Sprite/Pinky/PinkySideR.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteUp = QPixmap(":/Sprite/Pinky/PinkyUp.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteDown = QPixmap(":/Sprite/Pinky/PinkyDown.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    pixmap = gs->addPixmap(spriteSideL);
    pixmap->setZValue(1);
    clonePixmap = gs->addPixmap(spriteSideL);
    clonePixmap->setVisible(false);
}

/**
 * @brief Blinky::step calls Ghost::step with the appropriate target.
 */
void Pinky::step(void)
{
    if (movement == chase or movement == scatter)
        movement = globalMovement;

    switch (movement)
    {
    // Target four spaces ahead of the player in chase mode.
    case chase:
        Ghost::step(player->getField() + player->getDirection() * 4);
        break;
    // Target scatterTarget when in scatter mode.
    case scatter:
        Ghost::step(scatterTarget);
        break;
    // There is no target in frightened mode -> just set target to (0; 0)
    case frightened:
        Ghost::step(QPoint(0, 0));
        break;
    // When returning, target three fields above the reset position.
    // This represents the field on the top left of the ghost house exit.
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
    }
}

/**
 * @brief Inky::Inky Creates a Ghost with the chase pattern of Inky
 * @param scPointer Pointer to the GraphicsScene where Inky will be displayed
 * @param mazePointer Pointer to the Maze object so Inky can eat and navigate
 * @param playerPointer A Pointer to the Player so Inky can chase him
 * @param blinkyPointer A Pointer to Blinky as Inkys targeting depends on Blinkys position
 */
Inky::Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer, Ghost *blinkyPointer):Ghost(gsPointer,mazePointer,playerPointer),blinky{blinkyPointer}
{
    // Inky starts to the left of the ghost house and has a dot limit of 30.
    position = resetPosition + QPoint {-2, 0};
    subposition = QPointF {position.x()+0.5, float(position.y())}; // Add 0.5 to the subposition because the ghost house and maze fields are not aligned.
    dotLimitGhostHouse = 30;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(0, 255, 255);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    // Connect stepTick and set Interval so Inky checks every 100 ms if it should start moving.
    QObject::connect(stepTick, &QTimer::timeout, this, &Inky::step);
    stepTick->setInterval(100);

    // Setup the sprites.
    spriteSideL = QPixmap(":/Sprite/Inky/InkySideL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteSideR = QPixmap(":/Sprite/Inky/InkySideR.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteUp = QPixmap(":/Sprite/Inky/InkyUp.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteDown = QPixmap(":/Sprite/Inky/InkyDown.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    pixmap = gs->addPixmap(spriteSideR);
    pixmap->setZValue(1);
    clonePixmap = gs->addPixmap(spriteSideL);
    clonePixmap->setVisible(false);
}

/**
 * @brief Blinky::step calls Ghost::step with the appropriate target.
 */
void Inky::step(void)
{
    if(movement == chase or movement == scatter)
        movement = globalMovement;

    switch (movement)
    {
    // Target the players position plus the difference between the players and pinkys position.
    case chase:
        Ghost::step(player->getField() + player->getField()-blinky->getField());
        break;
    // Target scatterTarget when in scatter mode.
    case scatter:
        Ghost::step(scatterTarget);
        break;
    // There is no target in frightened mode -> just set target to (0; 0)
    case frightened:
        Ghost::step(QPoint(0, 0));
        break;
    // When returning, target three fields above the reset position.
    // This represents the field on the top left of the ghost house exit.
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
    }
}

/**
 * @brief Clyde::Clyde creates a Ghost with the chase pattern of Clyde.
 * @param scPointer Pointer to the GraphicsScene where Clyde will be displayed
 * @param mazePointer Pointer to the Maze object so Clyde can eat and navigate
 * @param playerPointer Pointer to the Player so Clyde can chase him
 */
Clyde::Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):Ghost(gsPointer,mazePointer,playerPointer)
{
    // Clyde starts on the right og the ghost house and has a dot limit of 60
    position = resetPosition + QPoint {2, 0};
    subposition = QPointF {position.x()+0.5, (float)position.y()}; // Add 0.5 to the subposition because the ghost house and maze fields are not aligned.
    dotLimitGhostHouse = 60;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(255, 184, 82);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    // Connect stepTick and set Interval so Clyde checks if he should start moving every 100 ms.
    QObject::connect(stepTick, &QTimer::timeout, this, &Clyde::step);
    stepTick->setInterval(10);

    // Setup the sprites.
    spriteSideL = QPixmap(":/Sprite/Clyde/ClydeSideL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteSideR = QPixmap(":/Sprite/Clyde/ClydeSideR.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteUp = QPixmap(":/Sprite/Clyde/ClydeUp.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteDown = QPixmap(":/Sprite/Clyde/ClydeDown.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    pixmap = gs->addPixmap(spriteSideL);
    pixmap->setZValue(1);
    clonePixmap = gs->addPixmap(spriteSideL);
    clonePixmap->setVisible(false);
}

/**
 * @brief Blinky::step calls Ghost::step with the appropriate target.
 */
void Clyde::step(void)
{
    if(movement == chase or movement == scatter)
        movement = globalMovement;

    switch (movement)
    {
    // Calculate the targets that will make Clyde move into the correct direction.
    case chase:
        // If the distance to the player is more than 8 fields, target the player directly.
        if(getDistance(getField(), player->getField()) >= 8)
        {

            Ghost::step(player->getField());
        }
        // Otherwise get as far away from the player as possible
        else
        {
            // Get all possible directions.
            std::vector<QPoint> possibleDirs = maze->getMaze(position);
            // Delete the opposite of the current direction as ghosts can't make 180 degree turns.
            int i = 0;
            for(QPoint possibleDir : possibleDirs)
            {
                // If possibleDire is the opposite of the current direction, delete it,
                // otherwise increment the index to point to the next direction.
                if(possibleDir == -direction)
                    possibleDirs.erase(possibleDirs.begin() + i);
                else
                    i++;
            }
            // Decide where to go to get as far away from the player as possible.
            QPoint target = player->getField();
            int largest = 0;
            for(int i = 1; i < possibleDirs.size(); i++){
                if (getDistance(position+possibleDirs[largest], target) < getDistance(position+possibleDirs[i], target))
                {
                    largest = i;
                }
            }
            // Step with the target set to the field that takes Clyde as far away from the player as possible.
            target = possibleDirs[largest] + position;
            Ghost::step(target);
        }
        break;
    // Target scatterTarget when in scatter mode.
    case scatter:
        Ghost::step(scatterTarget);
        break;
    // There is no target in frightened mode -> just set target to (0; 0)
    case frightened:
        Ghost::step(QPoint(0, 0));
        break;
    // When returning, target three fields above the reset position.
    // This represents the field on the top left of the ghost house exit.
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
    }
}
