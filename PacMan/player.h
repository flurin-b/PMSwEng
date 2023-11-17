#ifndef PLAYER_H
#define PLAYER_H

#include "pacmanlib_global.h"
#include "Maze.h"

#include <QGraphicsScene>
#include <QPoint>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>



class PACMANLIB_EXPORT Player : public QObject
{
    Q_OBJECT
public:
    Player(QGraphicsScene *scPointer, Maze *mazePointer);
    void step(void);
    QPointF getPosistion(void);
    void changeDirection(QKeyEvent* event);
    char getStatus(void);

    typedef enum
    {
        normal,
        hunt
    }status_t;

public slots:
    void paint(void);

private slots:
    void stopHunt(void);

private:
    void eatItem(void);

    QGraphicsScene *gs;
    Maze *maze;
    QPointF position;
    QPoint direction;
    QPoint pendingDirection;

    status_t status;                 //marks if a energizer was eaten
    QTimer *energizerTime;
};

#endif // PLAYER_H
