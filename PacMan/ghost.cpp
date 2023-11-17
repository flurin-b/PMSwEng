#include "ghost.h"

/**
 * @brief Ghost::Ghost Abstrakte Klasse die das Grund gerüst für Blinky/Pinky/Inky/Clyde ist
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Ghost::Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):gs(gsPointer),maze(mazePointer),playerRef(playerRefPointer)
{

}

/**
 * @brief Ghost::~Ghost Dealocate memory
 */
Ghost::~Ghost()
{

}

/**
 * @brief Ghost::getDistanceTo Calculates and returns the distance from one Field to another.
 * @param field1 Field on the Board
 * @param field2 Field on the Board
 */
float Ghost::getDistance(QPoint field1, QPoint field2){
    return sqrt(field1.x()*field1.x()+field2.y()+field2.y());
}

/**
 * @brief Blinky::Blinky Creates a Ghost with a chase pattern of Blinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Blinky::Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(gsPointer,mazePointer,playerRefPointer)
{
    position = QPointF {14, 14.5};
    direction = QPoint {-1, 0};
}

/**
 * @brief Blinky::step
 */
void Blinky::step(void)
{
    // get all possible direction
    std::vector<QPoint> possibleDirs = maze->getMaze((position - QPointF{0.5, 0.5}).toPoint());
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
        char smallest = 0;
        QPoint target = playerRef->getField();
        QPoint currentField = QPoint(position.x(), position.y());
        for(int i = 1; i < possibleDirs.size(); i++){
            if (getDistance(currentField+possibleDirs[smallest], target) > getDistance(currentField+possibleDirs[i], target))
            {
                smallest = i;
            }
        }
    }
}
/**
 * @brief Blinky::paint
 */
void Blinky::paint(void)
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

    // Check if the ghost ate PacMan
    if (playerRef->getField().x() == int(position.x()) && playerRef->getField().y() == int(position.y())) {
        emit gameOver(false);
    }
}

/**
 * @brief Pinky::Pinky Creates a Ghost with a chase pattern of Pinky
 * @param scPointer A Pointer to the GraphicScene where the ghosts will be placed
 * @param mazePointer A Pointer to the maze where to ghosts operade in
 * @param playerRefPointer A Pointer to the player so that they can chase him
 */
Pinky::Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer):Ghost(gsPointer,mazePointer,playerRefPointer)
{

}

/**
 * @brief Pinky::step
 */
void Pinky::step(void)
{

}

/**
 * @brief Pinky::paint
 */
void Pinky::paint(void)
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

}

/**
 * @brief Inky::step
 */
void Inky::step(void)
{

}

/**
 * @brief Inky::paint
 */
void Inky::paint(void)
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

}

/**
 * @brief Clyde::step
 */
void Clyde::step(void)
{

}


/**
 * @brief Clyde::paint
 */
void Clyde::paint(void)
{

}
