#ifndef MAZE_H
#define MAZE_H

#include <QGraphicsScene>

enum
{
    noItem,
    smallPoint,
    bigPoint,
    cherry,
};

class Maze
{
public:
    Maze(QGraphicsScene *sc);
    void paint(void);
    int getDots(QPoint position);
    void setDots(QPoint position, int item);
    std::vector<QPoint> getMaze(QPoint position);



private:
    QGraphicsScene *sc;
    int dots[28][36];
    std::vector<QPoint> maze[28][36];
};

#endif // MAZE_H
