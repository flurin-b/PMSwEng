#ifndef MAZE_H
#define MAZE_H

#include <QGraphicsScene>

#define MAZE_WITH       28
#define MAZE_HEIGHT     36
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



private:
    QGraphicsScene *sc;
    int dots[MAZE_WITH][MAZE_HEIGHT];
    std::vector<QPoint> maze[MAZE_WITH][MAZE_HEIGHT];
};

#endif // MAZE_H
