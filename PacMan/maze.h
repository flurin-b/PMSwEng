#ifndef MAZE_H
#define MAZE_H

#include <QGraphicsScene>

#define GHOST_NUMBERS   4

enum
{
    noItem,
    smallPoint,
    bigPoint,
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
    int dots[MAZE_WITH][MAZE_HEIGHT] = {{noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem},
                                        {noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem},
                                        {noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem},
                                        {noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem,noItem},
                                        {noItem,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,noItem,noItem,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,smallPoint,noItem},
                                        {noItem,smallPoint,noItem,noItem,noItem,noItem,smallPoint,noItem,noItem,noItem,noItem,noItem,smallPoint,noItem,noItem,smallPoint,noItem,noItem,noItem,noItem,noItem,smallPoint,noItem,noItem,noItem,noItem,smallPoint,noItem}};

    std::vector<QPoint> maze[MAZE_WITH][MAZE_HEIGHT] = {{{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
                                                        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
                                                        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
                                                        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
                                                        {{},{QPoint(1,0),QPoint(0,-1)}}}; //More to come
};

#endif // MAZE_H
