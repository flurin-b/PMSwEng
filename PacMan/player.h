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
    void swapSprite(void);

private:
    void eatItem(QPoint location);

    QGraphicsScene *gs;
    Maze *maze;
    QPoint position;
    QPoint direction;
    QPoint pendingDirection;

    // used in setPaused()
    int stepTickCache = -1, energizerTimeoutCache = -1;//,spriteTimerChache = -1;

    // used in paint()
    QPointF subposition;
    bool ate = false;
    QPoint lastDirection;

    status_t status;                 // marks if a energizer was eaten
    bool eating;                     // marks if any food is being eaten
    QTimer *energizerTimeout, stepTick, spriteTimer;

    const int energizerDuration = 6000;
    int getStepInterval (void);

    enum {
        stepIntervalCoin            = int(Maze::baseStepInterval / 0.71),
        stepIntervalNoCoin          = int(Maze::baseStepInterval / 0.80),
        stepIntervalEnergizedCoin   = int(Maze::baseStepInterval / 0.79),
        stepIntervalEnerfizedNoCoin = int(Maze::baseStepInterval / 0.90),
    };

    typedef enum
    {
        spriteIsOpen,
        spriteIsShut
    }spriteStatus_t;

    spriteStatus_t spriteStatus;
    QPixmap spriteShut;
    QPixmap spriteOpen;
    QGraphicsPixmapItem *pixmap, *clone;
};

#endif // PLAYER_H
