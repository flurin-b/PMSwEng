#include "pacman.h"
#include "maze.h"
#include "qevent.h"

#include <stdio.h>

// Set sizeof fields
int fieldSize_px = 20;

/**
 * @brief PacMan::PacMan Creates the Pac-Man which is moveable from the Player
 * @param scPointer
 */
PacMan::PacMan(QGraphicsView *gvPointer):gv{gvPointer}
{
    gs = new QGraphicsScene();
    gv->setScene(gs);
    gv->setFixedSize(Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    gs->setSceneRect(0, 0, Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    gv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    maze= new Maze(gs, gv);
    // add one pixel to width in order to compensate for the margin of QGraphicsView.
    player = new Player(gs,maze);
    ghosts[0] = new Blinky(gs,maze,player);
    ghosts[1] = new Pinky (gs,maze,player);
    ghosts[2] = new Inky  (gs,maze,player);
    ghosts[3] = new Clyde (gs,maze,player);
    for(Ghost* ghost : ghosts)
    {
        QObject::connect(ghost, &Ghost::gameOver, this, &PacMan::gameOverHandler);
    }
}

/**
 * @brief PacMan::~PacMan Delets allocated memory during ctor
 */
PacMan::~PacMan()
{
    delete maze;
    maze = nullptr;

    delete player;
    player = nullptr;

    for(Ghost* ghost : ghosts)
    {
        delete ghost;
        ghost = nullptr;
    }

    delete gameTick;
    gameTick = nullptr;
}


/**
 * @brief PacMan::paint Paints all menu items.
 */
void PacMan::paint()
{
    static QGraphicsTextItem* gameOverText = gs->addText("Game Over");
    if(gameOver) {
        gameOverText->setPlainText(gameWon ? "Game Over, you win!" : "Game Over, you loose!");
        gameOverText->show();
    }
    else {
        gameOverText->hide();

        maze->paint();
        player->paint();
        for(Ghost* ghost : ghosts)
            ghost->paint();
    }
}

/**
 * @brief PacMan::handleKeyPress
 * @param event
 */
void PacMan::handleKeyPress(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        player->changeDirection(event);
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        break;
    default:
        break;
    }
}

void PacMan::gameOverHandler(bool won) {
    this->gameOver = true;
    this->gameWon = won;
}
