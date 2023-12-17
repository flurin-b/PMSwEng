#ifndef PLAYER_H
#define PLAYER_H

#include "pacmanlib_global.h"
#include "Maze.h"

#include <QGraphicsScene>
#include <QPoint>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>


/**
 * @brief The Player class implements the yellow monster controlled by the player.
 */
class PACMANLIB_EXPORT Player : public QObject
{
    Q_OBJECT
public:
    Player(QGraphicsScene *scPointer, Maze *mazePointer);
    void setPaused (bool paused);
    void step(void);
    QPoint getField(void);
    QPoint getDirection(void);
    void changeDirection(QKeyEvent* event);

    /** @brief Defines how long an energizer lasts in ms. */
    static const int energizerDuration = 6000;

signals:
    void energizedChanged(bool energized);

public slots:
    void paint(void);

private slots:
    void resetEnergized(void);
    void swapSprite(void);

private:
    void eatItem(QPoint location);

    /** @brief The QGraphicsScene to draw to. */
    QGraphicsScene *gs;
    /** @brief The maze object to navigate and eat in. */
    Maze *maze;
    /** @brief The players current position in the Maze. */
    QPoint position;
    /** @brief The direction the Player is currently heading in. */
    QPoint direction;
    /** @brief The direction the Player will go in at the next opportunity. */
    QPoint pendingDirection;

    QTimer *energizerTimeout, stepTick, spriteTimer;
    /** @brief Stores the current remaining time of stepTick in Ghost::setPaused. */
    int stepTickCache = -1;
    /** @brief Stores the current remaining time of enetgizerTimeout in Ghost::setPaused. */
    int energizerTimeoutCache = -1;

    /** @brief Stores if the Player can eat Ghosts or not. */
    enum
    {
        normal,
        energized
    }status;

    /** @brief Stores the current position but as a float value. */
    QPointF subposition;
    /** @brief Stores if Player has eaten what is in the current field. */
    bool ate = false;
    /** @brief Used in Player::paint to check if Player has made a 180° turn so he can't eat dots he hast't touched yet. */
    QPoint lastDirection;

    /** @brief True when the Player is eating food. */
    bool eating;

    int getStepInterval (void);

    /** @brief Defines how fast the Player moves under different circumstances. */
    enum {
        stepIntervalCoin            = int(Maze::baseStepInterval / 0.71),
        stepIntervalNoCoin          = int(Maze::baseStepInterval / 0.80),
        stepIntervalEnergizedCoin   = int(Maze::baseStepInterval / 0.79),
        stepIntervalEnerfizedNoCoin = int(Maze::baseStepInterval / 0.90),
    };

    /** @brief Stores if the Player has his mouth open or closed. */
    enum
    {
        mouthOpen,
        mouthClosed,
    } spriteStatus;

    /** @brief Determines how large the sprite is in Fields */
    const float scaleFactor = 1.3;
    /** @brief Player sprite with its mouth shut. */
    QPixmap spriteShut;
    /** @brief Player sprite with its mouth open. */
    QPixmap spriteOpen;
    /** @brief QGraphicsItem that displays the Sprite. */
    QGraphicsPixmapItem *pixmap;
    /** @brief A Copy of Player::pixmap that is displayed when the Player goes through the tunnel. */
    QGraphicsPixmapItem *clone;
};

#endif // PLAYER_H
