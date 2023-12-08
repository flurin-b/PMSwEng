#ifndef GHOST_H
#define GHOST_H

/* debug defines */
//#define DEBUG_TARGETS

#include "maze.h"
#include "player.h"
#include "pacmanlib_global.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QRandomGenerator>

class PACMANLIB_EXPORT Ghost : public QObject
{
    Q_OBJECT
public:
    Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    ~Ghost();

    void setPaused(bool paused);
    void setFrightened(bool frightened);
    QPoint getField(void);

public slots:
    void paint();

protected slots:
    void nextMovementPattern();

signals:
    void gameOver(bool won);

protected:
    QGraphicsScene *gs;
    Maze    *maze;
    Player  *playerRef;
    QPoint  position;
    QPointF subposition;
    QPoint  direction;

    #ifdef DEBUG_TARGETS
        QGraphicsRectItem *debugTarget;
        QColor color;
    #endif

    const QPoint resetPosition{13, 16};

    int dotLimitGhostHouse = 0;

    enum {
        stepIntervalNormal     = int(Maze::baseStepInterval / 0.75),
        stepIntervalTunnel     = int(Maze::baseStepInterval / 0.40),
        stepIntervalFrightened = int(Maze::baseStepInterval / 0.50),
    };
    typedef enum{
        inMaze,
        inGhostHouse,
        leavingGhostHouse,
    } state_t;
    state_t state;
    typedef enum {
        normal,
        scatter,
        frightened,
    } movement_t;
    movement_t movement = normal;
    QTimer movementTimer{}, stepTick{};
    int movementTimerCache = -1, stepTickCache = -1;
    int movementCounter = 0;
    movement_t globalMovement = normal;

    static float getDistance(QPoint field1, QPoint field2);
    int getStepInterval(void);

    void step (QPoint target);

    QPixmap spriteSideL;
    QPixmap spriteSideR;
    QPixmap spriteUp;
    QPixmap spriteDown;
    QPixmap spriteFrightend;
    QGraphicsPixmapItem *pixmap,*clonePixmap;
};

class PACMANLIB_EXPORT Blinky : public Ghost
{
public:
    Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void);
private:
    const QPoint scatterTarget{25, 0};
};

class PACMANLIB_EXPORT Pinky : public Ghost
{
public:
    Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void);
private:
    const QPoint scatterTarget{2, 0};
};

class PACMANLIB_EXPORT Inky : public Ghost
{
public:
    Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer, Ghost *blinkyRefPointer);
    void step(void);
private:
    const QPoint scatterTarget{27, 35};
    Ghost *blinkyRef;
};

class PACMANLIB_EXPORT Clyde : public Ghost
{
public:
    Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerRefPointer);
    void step(void);
private:
    const QPoint scatterTarget{0, 35};
};
#endif // GHOST_H
