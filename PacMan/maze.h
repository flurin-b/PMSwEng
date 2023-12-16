#ifndef MAZE_H
#define MAZE_H

#include "pacmanlib_global.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QFontDatabase>
#include <QObject>

/**
 * @brief The Maze class stores the current state of the playfield (what food is where), the score, implements the movement of the other game objects and checks if Player has eaten all the dots.
 */
class PACMANLIB_EXPORT Maze : public QObject
{
    Q_OBJECT
public:
    Maze(QGraphicsScene *gsPointer, QGraphicsView *gvPointer);

    /**
     * @brief Describes the possible contents of a field.
     */
    typedef enum {
        noItem,
        dot,
        energizer,
    } item_t;

    item_t getItemAt(QPoint position);
    void setItemAt(QPoint position, item_t item);
    int getDotsEaten(void);
    float getFieldWidth(void);
    std::vector<QPoint> getMaze(QPoint position);
    void increaseScore(int offset);
    int getScore(void);

    /**
     * @brief baseStepInterval determines how many ms it takes to travel 1 Field at 100 % speed.
     */
    const static int baseStepInterval = 100;

    /**
     * @brief The widtht of the Maze in Fields.
     */
    const static int width = 28;
    /**
     * @brief The height of the Maze in Fields.
     */
    const static int height = 36;

public slots:
    void paint(void);

signals:
    void gameOver(bool won);

private:
    QGraphicsScene *gs;
    QGraphicsView  *gv;

    QGraphicsSimpleTextItem *scoreText;
    QGraphicsEllipseItem    *dotSprites[width][height];

    /**
     * @brief Stores the current score.
     */
    int score = 0;
    /**
     * @brief The total ammoutn of dots on the field used to check if the player has won.
     */
    const int dotCount = 240;
    /**
     * @brief Stores how many dots have been eaten so far.
     */
    int dotsEaten = 0;

    /**
     * @brief A 1:1 mapping of the maze. Each cell stores what kind of item is on the corresponding field in the Maze.
     */
    item_t dots[height][width] = {
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, energizer, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, energizer, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, dot, dot, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, dot, dot, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, energizer, dot, dot, noItem, noItem, dot, dot, dot, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, dot, dot, dot, noItem, noItem, dot, dot, energizer, noItem},
        {noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem},
        {noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem},
        {noItem, dot, dot, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, noItem, noItem, dot, dot, dot, dot, dot, dot, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem, noItem, dot, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, dot, noItem},
        {noItem, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        };

    /**
     * @brief Codes how Player and Ghost can move in the maze. Each std::vector contains the directions that are possible when standing on the corresponding field.
     */
    const std::vector<QPoint> maze[height][width] = {
        {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
        {{}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}, {}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0)}, {}, {}, {QPoint(0, -1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}, {}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0)}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}},
        {{}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}, {}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(0, 1.0), QPoint(-1.0, 0)}, {}, {}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0)}, {}},
        {{}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}},
        {{}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}},
        {{}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0)}, {}, {}, {QPoint(0, -1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}, {}, {QPoint(1.0, 0), QPoint(0, 1.0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0)}, {}, {}, {QPoint(0, -1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {QPoint(0, -1.0), QPoint(0, 1.0)}, {}},
        {{}, {QPoint(0, -1.0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(-1.0, 0), QPoint(1.0, 0)}, {QPoint(0, -1.0), QPoint(-1.0, 0)}, {}},
        {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
        {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
        };

};

#endif // MAZE_H
