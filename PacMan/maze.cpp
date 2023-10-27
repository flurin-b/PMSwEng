#include "maze.h"

Maze::Maze(QGraphicsScene *sc)
{

}

int Maze::getDots(QPoint position)
{
    return dots[position.x()][position.y()];
}

void Maze::setDots(QPoint position, int item)
{
    if(item >= noItem && item <= cherry)
    {
        dots[position.x()][position.y()] = item;
    }
}

std::vector<QPoint> Maze::getMaze(QPoint position)
{
    return maze[position.x()][position.y()];
}
