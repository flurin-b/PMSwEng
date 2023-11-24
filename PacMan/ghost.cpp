#include "ghost.h"

/**
 * @brief Ghost::Ghost Abstrakte Klasse die das Grund gerüst für Blinky/Pinky/Inky/Clyde ist
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Ghost::Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):gs(gsPointer),maze(mazePointer),playerRef(playerRefPointer)
{
    sprite = gs->addEllipse(0, 0, 0, 0);
    clone  = gs->addEllipse(0, 0, 0, 0);
}

/**
 * @brief Ghost::~Ghost Dealocate memory
 */
Ghost::~Ghost()
{}

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

int Ghost::getInterval(void)
{
    if((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
    {
        return Ghost::stepIntervalTunnel;
    }
    else if(playerRef->getStatus() == Player::energized)
    {
        return Ghost::stepIntervalFrightened;
    }
    else
    {
        return Ghost::stepIntervalStandard;
    }
}

void Ghost::step(QPoint target) {
    // get all possible direction
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
        int smallest = 0;
        for(int i = 1; i < possibleDirs.size(); i++){
            if (getDistance(position+possibleDirs[smallest], target) > getDistance(position+possibleDirs[i], target))
            {
                smallest = i;
            }
        }
        direction = possibleDirs[smallest];
    }

    position += direction;

    if(position.x() < 0 || position.x() > 27)
        position.setX((position.x()+maze->width) % maze->width);
    stepTick.setInterval(getInterval());
}

void Ghost::paint()
{
    float delta = 1.0 - (float)stepTick.remainingTime() / getInterval();
    bool tunneling = false;
    // Test if the ghost is in the tunnel
    if ((position.x() >= 27 && direction.x() < 0) || (position.x() <= 0 && direction.x() > 0))
        tunneling = true;

    QPointF positionF(direction);
    positionF *= delta;
    positionF -= direction;
    positionF += position.toPointF();

    float fieldWidth_px = maze->getFieldWidth();
    sprite->setRect(positionF.x() * fieldWidth_px, positionF.y() * fieldWidth_px, fieldWidth_px, fieldWidth_px);
    //    static QGraphicsRectItem* s = gs->addRect(position.x()*fieldWidth_px, position.y()*fieldWidth_px, fieldWidth_px, fieldWidth_px);
    //    s->setRect(position.x()*fieldWidth_px, position.y()*fieldWidth_px, fieldWidth_px, fieldWidth_px);

    if (tunneling)
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

    // Check if the ghost ate PacMan
    if (playerRef->getField() == positionF.toPoint()) {
        emit gameOver(false);
    }
}

/**
 * @brief Blinky::Blinky Creates a Ghost with a chase pattern of Blinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Blinky::Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(gsPointer,mazePointer,playerRefPointer)
{
    position = QPoint {14, 14};
    direction = QPoint {-1, 0};

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Blinky::step);
    stepTick.start(10);
}

/**
 * @brief Blinky::step
 */
void Blinky::step(void)
{
    Ghost::step(playerRef->getField());
}

/**
 * @brief Pinky::Pinky Creates a Ghost with a chase pattern of Pinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Pinky::Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(gsPointer,mazePointer,playerRefPointer)
{
    position = QPoint {14, 16};
    direction = QPoint {0, 0};

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Pinky::step);
    stepTick.start(10);
}

/**
 * @brief Pinky::step
 */
void Pinky::step(void)
{

}

/**
 * @brief Inky::Inky Creates a Ghost with a chase pattern of Inky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Inky::Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(gsPointer,mazePointer,playerRefPointer)
{
    position = QPoint {14, 16};
    direction = QPoint {0, 0};

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Inky::step);
    stepTick.start(10);
}

/**
 * @brief Inky::step
 */
void Inky::step(void)
{

}

/**
 * @brief Clyde::Clyde Creates a Ghost with a chase pattern of Clyde
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Clyde::Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(gsPointer,mazePointer,playerRefPointer)
{
    position = QPoint {14, 16};
    direction = QPoint {0, 0};

    stepTick.setTimerType(Qt::PreciseTimer);
    QObject::connect(&stepTick, &QTimer::timeout, this, &Clyde::step);
    stepTick.start(10);
}

/**
 * @brief Clyde::step
 */
void Clyde::step(void)
{

}
