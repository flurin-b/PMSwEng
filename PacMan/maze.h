#ifndef MAZE_H
#define MAZE_H

#include <QGraphicsScene>

#define GHOST_NUMBERS   4

enum
{
    noItem,
    smallPoint,
    bigPoint,
    cherry,
    error = 255
};

class Maze
{
public:
    Maze(QGraphicsScene *scPointer);
    void paint(void);
    int getDots(QPoint position);
    void setDots(QPoint position, int item);
    std::vector<QPoint> getMaze(QPoint position);
    const static int width = 28;
    const static int height = 36;



private:
    QGraphicsScene *sc;
    int dots[width][height];
    std::vector<QPoint> maze[width][height];
};

#endif // MAZE_H
