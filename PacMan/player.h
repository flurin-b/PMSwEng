#ifndef PLAYER_H
#define PLAYER_H

#include "pacmanlib_global.h"
#include "Maze.h"

#include <QGraphicsScene>
#include <QPoint>
#include <QObject>
#include <QKeyEvent>



class PACMANLIB_EXPORT Player : public QObject
{
    Q_OBJECT
public:
    Player(QGraphicsScene *scPointer, Maze *mazePointer);
    void step(void);
    QPointF getPosistion(void);
    void changeDirection(QKeyEvent* event);
    void increaseScore(int offset);
    char getStatus(void);

public slots:
    void paint(void);

private:
    QGraphicsScene *gs;
    Maze *maze;
    QPointF position;
    QPoint direction;
    QPoint pendingDirection;
    int score;
    char status;                 //marks if a energizer was eaten
};

#endif // PLAYER_H
