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

/**
 * @brief The Ghost class implements a basic movement function (Ghost::step) as well as a paint function (Ghost::paint). <br>
 *        It also implements functions to pause movement and calculate distances and some more obscure game mechanics.
 */
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
    /**
     * @brief Ghost::gameOver is emitted if the ghost has eaten PacMan.
     * @param won Wether or not the player has won the game. (Ghost will only emit this signal with won == false.)
     */
    void gameOver(bool won);

protected:
    /**
     * @brief The QGraphicsScene the Ghost will be rendered to.
     */
    QGraphicsScene *gs;
    /**
     * @brief The Maze in which the Ghost will move and eat.
     */
    Maze    *maze;
    /**
     * @brief The Player that is in the Maze together with the Ghost.
     */
    Player  *player;
    /**
     * @brief The current position of the ghost in Fields.
     */
    QPoint  position;
    /**
     * @brief The subposition of the ghost in Fields used in Ghost::paint to draw the sprites.
     */
    QPointF subposition;
    /**
     * @brief The direction the ghost is currently moving in.
     */
    QPoint  direction{0, 0};

    #ifdef DEBUG_TARGETS
        QGraphicsRectItem *debugTarget;
        QColor color;
    #endif

    /**
     * @brief The position the Ghost will return to after being eaten.
     */
    const QPoint resetPosition{13, 17};

    /**
     * @brief The ammout of dots the Player needs to eat before the ghost can leave the ghost house.
     */
    int dotLimitGhostHouse = 0;

    /**
     *  @brief This enum stores the step intervals for the different movement speeds.
     */
    enum {
        stepIntervalNormal     = int(Maze::baseStepInterval / 0.75),
        stepIntervalTunnel     = int(Maze::baseStepInterval / 0.40),
        stepIntervalFrightened = int(Maze::baseStepInterval / 0.50),
        stepIntervalReturning  = int(Maze::baseStepInterval / 1.50),
    };
    /**
     * @brief state stores where the ghost currently is.
     */
    enum{
        inMaze,
        inGhostHouse,
        leavingGhostHouse,
        enteringGhostHouse,
    } state = inGhostHouse;
    /**
     * @brief movement_t describes a type that is used to store the current movement type. <br>
     *        This determines speed, sprite and some other things.
     */
    typedef enum {
        chase,
        scatter,
        frightened,
        returning,
    } movement_t;
    /**
     * @brief The current movement pattern of the ghost.
     */
    movement_t movement = chase;
    /**
     * @brief The global movement of the ghosts. <br>
     *        This will determine if the ghosts scatter or chase while they're not busy being frightened or returning.
     */
    movement_t globalMovement = chase;

    // brief in ghost.cpp
    static int nextGhostPoints;

    /**
     * @brief Switches globalMovement between scatter and chase.
     */
    QTimer *movementTimer;
    /**
     * @brief Calls the step function.
     */
    QTimer *stepTick;
    /**
     * @brief Swaps the frightened ghosts sprites when the energizer time is running out.
     */
    QTimer  *frightenedSpriteTimer;
    /**
     * @brief Stores the movementTimer interval when the game is paused.
     */
    int movementTimerCache = -1;
    /**
     * @brief Stores the stepTick interval when the game is paused.
     */
    int stepTickCache = -1;
    /**
     * @brief Stores the frightenedSpriteTimer interval when the game is paused.
     */
    int frightenedSpriteTimerCache = -1;
    /**
     * @brief Used by nextMovementPattern to determine if the next pattern should be scatter or chase.
     */
    int movementCounter = 0;

    static float getDistance(QPoint field1, QPoint field2);
    int getStepInterval(void);

    void step (QPoint target);

    /**
     * @brief spriteStatus stores the color of the sprite that is currently displayed. <br>
     *        This in only used in frightened mode.
     */
    enum{
        frightendBlue,
        frightendWhite
    } spriteStatus = frightendBlue;
    /**
     * @brief Determines how big the Ghost sprites should be in Fields.
     */
    const float scaleFactor = 1.3;

    /** @brief Sprite of the ghost going left. */
    QPixmap spriteSideL;
    /** @brief Sprite of the ghost going right. */
    QPixmap spriteSideR;
    /** @brief Sprite of the ghost going up. */
    QPixmap spriteUp;
    /** @brief Sprite of the ghost going down. */
    QPixmap spriteDown;

     /** @brief Sprite of the ghost while frightened and blue. */
    QPixmap spriteFrightendBlue;
    /** @brief Sprite of the ghost while frightened and white. */
    QPixmap spriteFrightendWhite;

    /** @brief Sprite of the ghost returning and going left. */
    QPixmap eyeL;
    /** @brief Sprite of the ghost returning and going right. */
    QPixmap eyeR;
    /** @brief Sprite of the ghost returning and going up. */
    QPixmap eyeUp;
    /** @brief Sprite of the ghost returning and going down. */
    QPixmap eyeDown;

    /** @brief Pointer to the object used to display the current sprite. */
    QGraphicsPixmapItem *pixmap;
    /** @brief Pointer to the object used to display the current sprites clone. */
    QGraphicsPixmapItem *clonePixmap;
};

/**
 * @brief Blinky targets Player directly.
 */
class PACMANLIB_EXPORT Blinky : public Ghost
{
public:
    Blinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer);
    void step(void);
private:
    const QPoint scatterTarget{25, 0};
};

/**
 * @brief Pinky targets four fields in front of the Player in the current movement direction of the Player.
 */
class PACMANLIB_EXPORT Pinky : public Ghost
{
public:
    Pinky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer);
    void step(void);
private:
    const QPoint scatterTarget{2, 0};
};

/**
 * @brief Inky uses the current position of the Player and Blinky and adds the difference of the two to the Players current position to calculate its target.
 */
class PACMANLIB_EXPORT Inky : public Ghost
{
public:
    Inky(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer, Ghost *blinkyPointer);
    void step(void);
private:
    const QPoint scatterTarget{27, 35};
    Ghost *blinky;
};

/**
 * @brief Clyde moves like Blinky as long as his distance to the Player is more than 8 tiles. <br>
 *        If the Player is closer, he tries to get away from him as fast as possible.
 */
class PACMANLIB_EXPORT Clyde : public Ghost
{
public:
    Clyde(QGraphicsScene *gsPointer, Maze *mazePointer, Player *playerPointer);
    void step(void);
private:
    const QPoint scatterTarget{0, 35};
};
#endif // GHOST_H
