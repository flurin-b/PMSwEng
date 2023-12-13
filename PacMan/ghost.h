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
    Ghost(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer);
    ~Ghost();

    void setPaused(bool paused);
    QPoint getField(void);

public slots:
    void paint();
    void setFrightened(bool frightened);

protected slots:
    void nextMovementPattern();
    void toggleFrightenedSprite();

signals:
    void gameOver(bool won);

protected:
    QGraphicsScene *gs;
    Maze    *maze;
    Player  *player;
    QPoint  position;
    QPointF subposition;
    QPoint  direction{0, 0};

    #ifdef DEBUG_TARGETS
        QGraphicsRectItem *debugTarget;
        QColor color;
    #endif

    const QPoint resetPosition{13, 17};

    int dotLimitGhostHouse = 0;

    enum {
        stepIntervalNormal     = int(Maze::baseStepInterval / 0.75),
        stepIntervalTunnel     = int(Maze::baseStepInterval / 0.40),
        stepIntervalFrightened = int(Maze::baseStepInterval / 0.50),
        stepIntervalReturning  = int(Maze::baseStepInterval / 1.50),
    };
    enum{
        inMaze,
        inGhostHouse,
        leavingGhostHouse,
        enteringGhostHouse,
    } state = inGhostHouse;
    typedef enum {
        chase,
        scatter,
        frightened,
        returning,
    } movement_t;
    movement_t movement = chase;
    movement_t globalMovement = chase;

    static int nextGhostPoints;

    QTimer *movementTimer, *stepTick, *frightenedSpriteTimer;
    int movementTimerCache = -1, stepTickCache = -1, frightenedSpriteTimerCache = -1;
    int movementCounter = 0;

    static float getDistance(QPoint field1, QPoint field2);
    int getStepInterval(void);

    void step (QPoint target);

    enum{
        frightendBlue,
        frightendWhite
    } spriteStatus = frightendBlue;

    const float scaleFactor = 1.3;
    QPixmap spriteSideL, spriteSideR, spriteUp, spriteDown;
    QPixmap spriteFrightendBlue, spriteFrightendWhite;
    QPixmap eyeL, eyeR, eyeUp, eyeDown;
    QGraphicsPixmapItem *pixmap,*clonePixmap;
};

class PACMANLIB_EXPORT Blinky : public Ghost
{
public:
    Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer);
    void step(void);
private:
    const QPoint scatterTarget{25, 0};
};

class PACMANLIB_EXPORT Pinky : public Ghost
{
public:
    Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer);
    void step(void);
private:
    const QPoint scatterTarget{2, 0};
};

class PACMANLIB_EXPORT Inky : public Ghost
{
public:
    Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer, Ghost *blinkyPointer);
    void step(void);
private:
    const QPoint scatterTarget{27, 35};
    Ghost *blinky;
};

class PACMANLIB_EXPORT Clyde : public Ghost
{
public:
    Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer);
    void step(void);
private:
    const QPoint scatterTarget{0, 35};
};
#endif // GHOST_H
