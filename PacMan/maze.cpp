#include "maze.h"

/**
 * @brief Maze::Maze Creates a Instace of Maze which contains all the eatables and the paths that can be taken from a certain position
 * @param scPointer A Pointer to the GraphicScene onto which the items will be placed
 */
Maze::Maze(QGraphicsScene *scPointer):sc(scPointer)
{

}

/**
 * @brief Maze::getDots A function for getting the Item contained in a field
 * @param position The field in the maze from which the item want to be known
 * @return Returns the Item that is conatined in posistion of the maze
 */
int Maze::getDots(QPoint position)
{
    ///If the requested position is outside of the border from the maze an error is returned otherwise the item contained in the field
    int contend = error;

    if(position.x() >= 0 && position.x() <= width-1)
    {
        if(position.y() >= 0 && position.y() <= height-1)
        {
            contend =  dots[position.x()][position.y()];
        }
    }

    return contend;
}

/**
 * @brief Maze::setDots Change the Item a specific field in the maze contains
 * @param position The point in the maze where the item should be changed
 * @param item The new item that should be placed at the defined position
 */
void Maze::setDots(QPoint position, int item)
{
    ///Only allows to set a new Item if the position requested is within the maze, and the Item exists
    if(position.x() >= 0 && position.x() <= width-1)
    {
        if(position.y() >= 0 && position.y() <= height-1)
        {
            if(item >= noItem && item <= cherry)
            {
                dots[position.x()][position.y()] = item;
            }
        }
    }
}

/**
 * @brief Maze::getMaze Gives back all the Points on to which a character can be moved
 * @param position The position in the maze the directions want to be known from
 * @return A vector of QPoint which are located around the specified posistion
 */
std::vector<QPoint> Maze::getMaze(QPoint position)
{
    ///If the requested Position doesn't exist No Offset willb be given back
    QPoint errorPosition(0,0);
    std::vector<QPoint> directions = {errorPosition};

    if(position.x() >= 0 && position.x() <= width-1)
    {
        if(position.y() >= 0 && position.y() <= height-1)
        {
            directions = maze[position.x()][position.y()];
        }
    }

    return directions;
}
