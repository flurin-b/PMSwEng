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
    void setPaused (bool paused);
    void step(void);
//    QPointF getPosistion(void);
    QPoint getField(void);
    QPoint getDirection(void);
    void changeDirection(QKeyEvent* event);
    char getStatus(void);

    typedef enum
    {
        normal,
        energized
    }status_t;

signals:
    void energizedChanged(bool energized);

public slots:
    void paint(void);

private slots:
    void resetEnergized(void);

private:
    void eatItem(QPoint location);

    QGraphicsScene *gs;
    Maze *maze;
    QPoint position;
    QPoint direction;
    QPoint pendingDirection;

    status_t status;                 // marks if a energizer was eaten
    bool eating;                     // marks if any food is being eaten
    QTimer *energizerTimeout, stepTick;

    const int energizerDuration = 6000;
    int getStepInterval (void);

    enum {
        stepIntervalCoin            = int(Maze::baseStepInterval / 0.71),
        stepIntervalNoCoin          = int(Maze::baseStepInterval / 0.80),
        stepIntervalEnergizedCoin   = int(Maze::baseStepInterval / 0.79),
        stepIntervalEnerfizedNoCoin = int(Maze::baseStepInterval / 0.90),
    };
};

#endif // PLAYER_H
