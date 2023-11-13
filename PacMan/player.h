#ifndef PLAYER_H
#define PLAYER_H

#include "pacmanlib_global.h"
#include "Maze.h"

#include <QGraphicsScene>
#include <QPoint>
#include <QObject>

class PACMANLIB_EXPORT Player : public QObject
{
    Q_OBJECT
public:
    Player(QGraphicsScene *scPointer, Maze *mazePointer);
    void step(void);
    QPoint getPosistion(void);
    void MovePlayer(QPoint offset);

public slots:
    void paint(void);

private:
    QGraphicsScene *sc;
    Maze *maze;
    QPoint playerPosistion;
};

#endif // PLAYER_H
