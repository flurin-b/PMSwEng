#ifndef MAZE_H
#define MAZE_H

#include <QGraphicsScene>

class Maze
{
public:
    Maze(QGraphicsScene sc);
    void paint(void);

    //Nicht klar ersichtbar wie die Definition gemeint ist im Klassendiagramm. Muss angepasst werden
    //std::vector<bool> dots;
   //const std::vector<std::vector<QPoint>> maze;

private:
    QGraphicsScene sc;
};

#endif // MAZE_H
