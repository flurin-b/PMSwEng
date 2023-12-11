#include "ghost.h"

/**
 * @brief Ghost::Ghost Create the base for any specific Ghost (Blinky/Pinky/Inky/Clyde)
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerPointer A Pointer to the player so that they can chase him
 */
Ghost::Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):gs(gsPointer),maze(mazePointer),player(playerPointer)
{
    movementTimer = new QTimer;
    connect(movementTimer, &QTimer::timeout, this, &Ghost::nextMovementPattern);
    nextMovementPattern();
    movementTimer->stop();

    spriteFrightendBlue =  QPixmap(":/Sprite/Ghost/GhostFrightend.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    spriteFrightendWhite = QPixmap(":/Sprite/Ghost/GhostFrightendEnding.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeL = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeR = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeUp = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);
    eyeDown = QPixmap(":/Sprite/Ghost/AugenL.PNG").scaledToWidth(maze->getFieldWidth() * scaleFactor);

    stepTick = new QTimer;
    stepTick->setTimerType(Qt::PreciseTimer);

    frightenedSpriteTimer = new QTimer;
    frightenedSpriteTimer->setTimerType(Qt::PreciseTimer);
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
 * @brief Ghost::setPaused Stop the Ghost logic from updating
 * @param paused Stop if true continue if false
 */
void Ghost::setPaused(bool paused)
{
    if(paused)
    {
        stepTickCache = stepTick->remainingTime();
        movementTimerCache = movementTimer->remainingTime();
        frightenedSpriteTimerCache = frightenedSpriteTimer->remainingTime();
        stepTick->stop();
        movementTimer->stop();
        frightenedSpriteTimer->stop();
    }
    else
    {
        if (stepTickCache != -1)
        {
            stepTick->start(stepTickCache);
            movementTimer->start(movementTimerCache);
        }
        else
        {
            stepTick->start();
            movementTimer->start();
        }
        if (frightenedSpriteTimer->remainingTime() != -1)
        {
            frightenedSpriteTimer->start(frightenedSpriteTimerCache);
        }
    }
}

/**
 * @brief Ghost::setFrightened
 * @param frightened
 */
void Ghost::setFrightened(bool frightened)
{
    if(frightened && movement != returning)
    {
        pixmap->setPixmap(spriteFrightendBlue);
        spriteStatus = frightendBlue;
        frightenedSpriteTimer->setInterval(Player::energizerDuration * 0.7);
        frightenedSpriteTimer->start();

        if (movement != Ghost::frightened)
        {
            if (state == Ghost::inMaze)
                position -= direction;
                direction = -direction;
            stepTick->setInterval(Ghost::stepIntervalFrightened * stepTick->remainingTime()/getStepInterval());
            movement = Ghost::frightened;
        }
    }
    else if (!frightened && movement == Ghost::frightened)
    {
        movement = globalMovement;
        stepTick->setInterval(getStepInterval() * stepTick->remainingTime()/Ghost::stepIntervalFrightened);

        frightenedSpriteTimer->stop();
    }
}

/**
 * @brief Ghost::toggleFrightenedSprite Swap between two frightend sprites to show the Player the energized Time is running out
 */
void Ghost::toggleFrightenedSprite()
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
 * @brief Ghost::getStepInterval Get the current Intervall time with which the function Ghost::step is called
 * @return Time in ms
 */
int Ghost::getStepInterval(void)
{
    if((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        return Ghost::stepIntervalTunnel;
    }
    else
    {
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
    }
    return 0;
}

/**
 * @brief Ghost::getField Get the field in which the Ghost is currently in
 * @return A field in the Maze
 */
QPoint Ghost::getField (void)
{
    return subposition.toPoint();
}

/**
 * @brief Ghost::nextMovementPattern
 */
void Ghost::nextMovementPattern()
{
    const static int patternTimes[8] = {7000, 20000, 7000, 20000, 5000, 20000, 5000, 20000};
    
    if (globalMovement == chase)
    {
        globalMovement = scatter;
        movementTimer->setInterval(patternTimes[movementCounter++]);
    }
    else
    {
        globalMovement = chase;
        movementTimer->setInterval(patternTimes[movementCounter++]);
    }
    if (movementCounter >= 8)
        movementCounter = 7;
}

/**
 * @brief Ghost::step
 * @param target
 */
void Ghost::step(QPoint target) {
#ifdef DEBUG_TARGETS
    debugTarget->setRect(target.x()*maze->getFieldWidth(), target.y()*maze->getFieldWidth(), maze->getFieldWidth(), maze->getFieldWidth());
#endif

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
    case Ghost::inMaze:
    {
        // get all possible directions
        std::vector<QPoint> possibleDirs = maze->getMaze(position);
        int i = 0;
        // delete opposite of current direction as no 180 degree turns can be made
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
        // if there is only one direction, go in that direction.
        if (possibleDirs.size() == 1)
        {
            direction = possibleDirs[0];
        }
        // otherwise decide where to go
        else
        {
            if (movement == Ghost::frightened)
            {
                static QRandomGenerator r;
                direction = possibleDirs[r.bounded(possibleDirs.size())];
            }
            else
            {
                int smallest = 0;
                for(int i = 1; i < possibleDirs.size(); i++){
                    if (getDistance(position+possibleDirs[smallest], target) > getDistance(position+possibleDirs[i], target))
                    {
                        smallest = i;
                    }
                }
                direction = possibleDirs[smallest];
            }
        }
        break;
    }
    case Ghost::inGhostHouse:
        stepTick->setInterval(10);
        if(maze->getDotsEaten() < dotLimitGhostHouse)
            return;
        else
            state = Ghost::leavingGhostHouse;
    case Ghost::leavingGhostHouse:
    {
        if (position.x() < resetPosition.x())
        {
            direction = QPoint(1, 0);
        }
        else if (position.x() > resetPosition.x())
        {
            direction = QPoint(-1, 0);
        }
        else if (position.y() > 14)
        {
            direction = QPoint(0, -1);
        }
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
    position += direction;

    if(position.x() < 0 || position.x() > 27)
        position.setX((position.x()+maze->width) % maze->width);

    stepTick->setInterval(getStepInterval());
}

/**
 * @brief Ghost::paint
 */
void Ghost::paint()
{
    // if not paused, update subposition
    if(stepTick->remainingTime() != -1 && state != Ghost::inGhostHouse)
    {
        float delta = 1.0 - (float)stepTick->remainingTime() / getStepInterval();
        subposition = direction.toPointF();
        subposition *= delta;
        subposition -= direction;
        subposition += position.toPointF();
        if (state == Ghost::leavingGhostHouse || state == Ghost::enteringGhostHouse)
        {
            subposition += QPointF{0.5, 0.0};
        }
    }

    switch (movement)
    {
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
    case frightened:
        break;
    }

    //Calculate the top left position if the sprite would be as wide as the field and subtract half of the wide pixels that are to wide becuse of the scaling
    float fieldWidth_px = maze->getFieldWidth();
    float xPosition = subposition.x() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
    float yPosition = subposition.y() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
    pixmap->setPos(xPosition, yPosition);

    // Test if the ghost is in the tunnel
    if ((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        clonePixmap->setVisible(true);
        if (position.x() == 0)
        {
            xPosition = (subposition.x() + maze->width) * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            yPosition = subposition.y() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            clonePixmap->setPixmap(spriteSideL);
            clonePixmap->setPos(xPosition,yPosition);
        }
        else
        {
            xPosition = (subposition.x() - maze->width) * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            yPosition = subposition.y() * fieldWidth_px - fieldWidth_px*(scaleFactor - 1.0) * 0.5;
            clonePixmap->setPixmap(spriteSideR);
            clonePixmap->setPos(xPosition,yPosition);
        }
    }
    else
    {
        clonePixmap->setVisible(false);
    }

    // Check if the ghost ate PacMan or vice versa
    if (player->getField() == subposition.toPoint())
    {
        switch (movement)
        {
        case frightened:
            stepTick->setInterval(stepTick->remainingTime() * stepIntervalReturning / getStepInterval());
            movement = returning;
            frightenedSpriteTimer->stop();
            // TODO: give points for eating a ghost
            break;
        case scatter:
        case chase:
            emit gameOver(false);
            break;
        case returning:
            break;
        }
    }
}

/**
 * @brief Blinky::Blinky Creates a Ghost with a chase pattern of Blinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerPointer A Pointer to the player so that they can chase him
 */
Blinky::Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):Ghost(gsPointer,mazePointer,playerPointer)
{
    position = QPoint {13, 14};
    subposition = QPointF {position.x()+0.5, float(position.y())};

    direction = QPoint {-1, 0};
    state = Ghost::inMaze;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(255, 0, 0);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    QObject::connect(stepTick, &QTimer::timeout, this, &Blinky::step);
    stepTick->setInterval(Ghost::stepIntervalNormal / 2);

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
 * @brief Blinky::step
 */
void Blinky::step(void)
{
    if(movement == chase || movement == scatter)
    {
        movement = globalMovement;
    }

    switch (movement)
    {
    case chase:
        Ghost::step(player->getField());
        break;
    case scatter:
    case frightened:
        Ghost::step(scatterTarget);
        break;
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
    }
}

/**
 * @brief Pinky::Pinky Creates a Ghost with a chase pattern of Pinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerPointer A Pointer to the player so that they can chase him
 */
Pinky::Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):Ghost(gsPointer,mazePointer,playerPointer)
{
    position = resetPosition;
    subposition = QPointF {position.x()+0.5, float(position.y())};

    //direction = QPoint {0, -1};
    state = Ghost::leavingGhostHouse;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(255, 184, 255);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    QObject::connect(stepTick, &QTimer::timeout, this, &Pinky::step);
    stepTick->setInterval(0);

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
 * @brief Pinky::step
 */
void Pinky::step(void)
{
    if (movement == chase || movement == scatter)
        movement = globalMovement;

    switch (movement)
    {
    case chase:
        Ghost::step(player->getField() + player->getDirection() * 4);
        break;
    case scatter:
    case frightened:
        Ghost::step(scatterTarget);
        break;
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
        break;
    }
}

/**
 * @brief Inky::Inky Creates a Ghost with a chase pattern of Inky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerPointer A Pointer to the player so that they can chase him
 */
Inky::Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer, Ghost *blinkyPointer):Ghost(gsPointer,mazePointer,playerPointer)
{
    blinky = blinkyPointer;
    position = resetPosition + QPoint {-2, 0};
    subposition = QPointF {position.x()+0.5, float(position.y())};
    dotLimitGhostHouse = 30;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(0, 255, 255);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    QObject::connect(stepTick, &QTimer::timeout, this, &Inky::step);

    stepTick->setInterval(10);

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
 * @brief Inky::step
 */
void Inky::step(void)
{
    if(movement == chase || movement == scatter)
        movement = globalMovement;

    switch (movement)
    {
    case chase:
        Ghost::step(player->getField() + player->getField()-blinky->getField());
        break;
    case scatter:
    case frightened:
        Ghost::step(scatterTarget);
        break;
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
    }
}

/**
 * @brief Clyde::Clyde Creates a Ghost with a chase pattern of Clyde
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerPointer A Pointer to the player so that they can chase him
 */
Clyde::Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):Ghost(gsPointer,mazePointer,playerPointer)
{
    position = resetPosition + QPoint {2, 0};
    subposition = QPointF {position.x()+0.5, (float)position.y()};
    dotLimitGhostHouse = 60;

#ifdef DEBUG_TARGETS
    color = QColor::fromRgb(255, 184, 82);
    debugTarget = gs->addRect(0, 0, 0, 0);
    debugTarget->setBrush(QBrush(color));
#endif

    QObject::connect(stepTick, &QTimer::timeout, this, &Clyde::step);
    stepTick->setInterval(10);

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
 * @brief Clyde::step
 */
void Clyde::step(void)
{
    if(movement == chase || movement == scatter)
        movement = globalMovement;

    switch (movement)
    {
    case chase:
        if(getDistance(getField(), player->getField()) < 8)
        {
            QPoint target;
            // get all possible directions
            std::vector<QPoint> possibleDirs = maze->getMaze(position);
            int i = 0;
            // delete opposite of current direction as no 180 degree turns can be made
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
            // decide where to go to get as far away from the player as possible.
            int largest = 0;
            for(int i = 1; i < possibleDirs.size(); i++){
                if (getDistance(position+possibleDirs[largest], target) > getDistance(position+possibleDirs[i], target))
                {
                    largest = i;
                }
            }
            target = possibleDirs[largest] + getField();
            Ghost::step(target);
        }
        else
        {
            Ghost::step(player->getField());
        }
        break;
    case scatter:
    case frightened:
        Ghost::step(scatterTarget);
        break;
    case returning:
        Ghost::step(resetPosition + QPoint{0, -3});
    }
}
