#ifndef MAZE_H
#define MAZE_H

#include "pacmanlib_global.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QObject>

class PACMANLIB_EXPORT Maze : public QObject
{
    Q_OBJECT
public:
    Maze(QGraphicsScene *gsPointer, QGraphicsView *gvPointer);

    typedef enum {
        noItem,
        smallPoint,
        bigPoint,
        error = 255
    } item_t;

    int getDots(QPoint position);
    int getDotsEaten(void);
    void setDots(QPoint position, item_t item);
    float getFieldWidth(void);
    std::vector<QPoint> getMaze(QPoint position);
    void increaseScore(int offset);

    const static int baseStepInterval = 100;

    const static int width = 28;
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

    int score = 0;
    const int dotCount = 240;
    int dotsEaten = 0;

    item_t dots[height][width] = {
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, bigPoint, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, bigPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, bigPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, bigPoint, noItem},
        {noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem},
        {noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem},
        {noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, noItem, noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem, noItem, smallPoint, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, smallPoint, noItem},
        {noItem, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, smallPoint, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        {noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem, noItem},
        };

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
