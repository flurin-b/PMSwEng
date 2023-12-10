#include "pacman.h"
#include "maze.h"
#include "qevent.h"

#include <stdio.h>


/**
 * @brief PacMan::PacMan Initalize everything needed for a round of Pac-Man
 * @param gvPointer A Pointer to the GraphicsView in which Pac-Man will be displayed
 */
PacMan::PacMan(QGraphicsView *gvPointer):gv{gvPointer}
{
    int fieldSize_px = 20;
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
    Inky *inky = new Inky  (gs,maze,player,ghosts[0]);
    ghosts[2] = inky;
    ghosts[3] = new Clyde (gs,maze,player);
    for(Ghost* ghost : ghosts)
    {
        QObject::connect(ghost, &Ghost::gameOver, this, &PacMan::gameOverHandler);
        QObject::connect(player, &Player::energizedChanged, ghost, &Ghost::setFrightened);
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
 * @brief PacMan::paint Handles the painting of the game
 */
void PacMan::paint()
{
    static QGraphicsTextItem* gameOverText = gs->addText("Game Over");
    if(gameOver) {
        gameOverText->setPlainText(gameWon ? "Game Over, you win!" : "Game Over, you loose!");
        gameOverText->setDefaultTextColor(Qt::white);
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
 * @brief PacMan::handleKeyPress Read the Keyboard Input and forwoard it to the appropriate method
 * @param event The pressed Key
 */
void PacMan::handleKeyPress(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if(!paused)
            player->changeDirection(event);
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        paused = !paused;
        player->setPaused(paused);
        for(Ghost* ghost : ghosts)
            ghost->setPaused(paused);
        break;
    default:
        break;
    }
}

/**
 * @brief PacMan::gameOverHandler Handle a GameOver caused bye either a ghost eating the Player or the Player eating every dot in the maze
 * @param won
 */
void PacMan::gameOverHandler(bool won) {
    this->gameOver = true;
    this->gameWon = won;
    player->setPaused(true);
    for(Ghost *ghost: ghosts) {
        ghost->setPaused(true);
    }
}
