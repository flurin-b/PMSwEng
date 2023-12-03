#include "ghost.h"

/**
 * @brief Ghost::Ghost Abstrakte Klasse die das Grund gerüst für Blinky/Pinky/Inky/Clyde ist
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerPointer A Pointer to the player so that they can chase him
 */
Ghost::Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer):gs(gsPointer),maze(mazePointer),player(playerPointer)
{
    connect(&movementTimer, &QTimer::timeout, this, &Ghost::nextMovementPattern);
    nextMovementPattern();
    movementTimer.stop();
}

/**
 * @brief Ghost::~Ghost Dealocate memory
 */
Ghost::~Ghost()
{}

void Ghost::setPaused(bool paused)
{
    if(paused)
    {
        stepTickCache = stepTick.remainingTime();
        movementTimerCache = movementTimer.remainingTime();
        stepTick.stop();
        movementTimer.stop();
    }
    else
    {
        if (stepTickCache != -1)
        {
            stepTick.start(stepTickCache);
            movementTimer.start(movementTimerCache);
        }
        else
        {
            stepTick.start();
            movementTimer.start();
        }
    }
}

void Ghost::setFrightened(bool frightened)
{
    if (frightened && movement != Ghost::frightened)
    {
        position -= direction;
        if (state == Ghost::inMaze)
            direction = -direction;
        stepTick.setInterval(Ghost::stepIntervalFrightened * stepTick.remainingTime()/getStepInterval());
        movement = Ghost::frightened;
    }
    else if (!frightened && movement == Ghost::frightened)
    {
        movement = globalMovement;
        stepTick.setInterval(getStepInterval() * stepTick.remainingTime()/Ghost::stepIntervalFrightened);
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

int Ghost::getStepInterval(void)
{
    if((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        return Ghost::stepIntervalTunnel;
    }
    else if(movement == Ghost::frightened)
    {
        return Ghost::stepIntervalFrightened;
    }
    else
    {
        return Ghost::stepIntervalNormal;
    }
}

QPoint Ghost::getField (void)
{
    return subposition.toPoint();
}

void Ghost::nextMovementPattern()
{
    const static int patternTimes[8] = {7000, 20000, 7000, 20000, 5000, 20000, 5000, 20000};
    
    if (globalMovement == chase)
    {
        globalMovement = scatter;
        movementTimer.setInterval(patternTimes[movementCounter++]);
    }
    else
    {
        globalMovement = chase;
        movementTimer.setInterval(patternTimes[movementCounter++]);
    }
    if (movementCounter >= 8)
        movementCounter = 7;
}

void Ghost::step(QPoint target) {
    #ifdef DEBUG_TARGETS
        debugTarget->setRect(target.x()*maze->getFieldWidth(), target.y()*maze->getFieldWidth(), maze->getFieldWidth(), maze->getFieldWidth());
    #endif
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
    {
        stepTick.setInterval(10);
        if(maze->getDotsEaten() >= dotLimitGhostHouse)
            state = leavingGhostHouse;
    }
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
            stepTick.setInterval(getStepInterval() / 2);
            return;
        }
        break;
    }
    }
    position += direction;

    if(position.x() < 0 || position.x() > 27)
        position.setX((position.x()+maze->width) % maze->width);

    stepTick.setInterval(getStepInterval());
}

void Ghost::paint()
{
    // if not paused, update subposition
    if(stepTick.remainingTime() != -1 && state != Ghost::inGhostHouse)
    {
        float delta = 1.0 - (float)stepTick.remainingTime() / getStepInterval();
        subposition = direction.toPointF();
        subposition *= delta;
        subposition -= direction;
        subposition += position.toPointF();
        if (state == Ghost::leavingGhostHouse)
        {
            subposition += QPointF{0.5, 0.0};
        }
    }

    bool tunneling = false;

    float fieldWidth_px = maze->getFieldWidth();
    sprite->setRect(subposition.x() * fieldWidth_px, subposition.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
    sprite->setBrush(QBrush(movement == Ghost::frightened ? frightenedColor : color));

    // Test if the ghost is in the tunnel
    if ((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        clone->setVisible(true);
        if (position.x() == 0)
            clone->setRect((subposition.x() + maze->width) * fieldWidth_px, subposition.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
        else
            clone->setRect((subposition.x() - maze->width) * fieldWidth_px, subposition.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
    }
    else
    {
        clone->setVisible(false);
    }

    // Check if the ghost ate PacMan or vice versa
    if (movement == Ghost::frightened)
    {
        if (player->getField() == subposition.toPoint()) {
            position = resetPosition;
            state = Ghost::leavingGhostHouse;
            movement = Ghost::chase;
            stepTick.setInterval(getStepInterval() * stepTick.remainingTime()/Ghost::stepIntervalFrightened);
            // TODO: give points for eating a ghost
        }
    }
    else
    {
        if (player->getField() == subposition.toPoint()) {
            emit gameOver(false);
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
    sprite = gs->addEllipse(0, 0, 0, 0);
    clone  = gs->addEllipse(0, 0, 0, 0);
    color = QColor::fromRgb(255, 0, 0);
    sprite->setBrush(QBrush(color));
    clone->setBrush(QBrush(color));

    #ifdef DEBUG_TARGETS
        debugTarget = gs->addRect(0, 0, 0, 0);
        debugTarget->setBrush(QBrush(color));
    #endif

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Blinky::step);
    stepTick.setInterval(0);
}

/**
 * @brief Blinky::step
 */
void Blinky::step(void)
{
    if(movement == chase || movement == scatter)
        movement = globalMovement;
    switch (movement)
    {
    case chase:
        Ghost::step(player->getField());
        break;
    case scatter:
    case frightened:
        Ghost::step(scatterTarget);
        break;
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
    sprite = gs->addEllipse(0, 0, 0, 0);
    clone  = gs->addEllipse(0, 0, 0, 0);
    color = QColor::fromRgb(255, 184, 255);
    sprite->setBrush(QBrush(color));
    clone->setBrush(QBrush(color));

    #ifdef DEBUG_TARGETS
        debugTarget = gs->addRect(0, 0, 0, 0);
        debugTarget->setBrush(QBrush(color));
    #endif

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Pinky::step);
    stepTick.setInterval(0);
}

/**
 * @brief Pinky::step
 */
void Pinky::step(void)
{
    if(movement == chase || movement == scatter)
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
    sprite = gs->addEllipse(0, 0, 0, 0);
    clone  = gs->addEllipse(0, 0, 0, 0);
    color = QColor::fromRgb(0, 255, 255);
    sprite->setBrush(QBrush(color));
    clone->setBrush(QBrush(color));

    #ifdef DEBUG_TARGETS
        debugTarget = gs->addRect(0, 0, 0, 0);
        debugTarget->setBrush(QBrush(color));
    #endif

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Inky::step);
    stepTick.setInterval(0);
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
    sprite = gs->addEllipse(0, 0, 0, 0);
    clone  = gs->addEllipse(0, 0, 0, 0);
    color = QColor::fromRgb(255, 184, 82);
    sprite->setBrush(QBrush(color));
    clone->setBrush(QBrush(color));

    #ifdef DEBUG_TARGETS
        debugTarget = gs->addRect(0, 0, 0, 0);
        debugTarget->setBrush(QBrush(color));
    #endif

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Clyde::step);
    stepTick.setInterval(0);
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
            Ghost::step(scatterTarget);
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
    }
}
