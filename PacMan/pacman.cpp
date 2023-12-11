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

    initGameObjects();
}

/**
 * @brief PacMan::~PacMan Delets allocated memory during ctor
 */
PacMan::~PacMan()
{
    delete gs;
    gs = nullptr;

    delete maze;
    maze = nullptr;

    delete player;
    player = nullptr;

    for(Ghost* ghost : ghosts)
    {
        delete ghost;
        ghost = nullptr;
    }
}


/**
 * @brief PacMan::paint Handles the painting of the game
 */
void PacMan::paint()
{
    switch (gameState)
    {
    case won:
    case lost:
        gameStateText->setPlainText(gameState == won ? "Game Over, you win! Press ENTER to play again." : "Game Over, you loose! Press ENTER to play again.");
        gameStateText->show();
        break;
    case paused:
        gameStateText->setPlainText("Game Paused, press ENTER to resume.");
        gameStateText->show();
        break;
    case running:
        gameStateText->hide();
        break;
    case start:
        gameStateText->setPlainText("Press ENTER to start playing.");
        gameStateText->show();
        break;
    }
    maze->paint();
    player->paint();
    for(Ghost* ghost : ghosts)
        ghost->paint();
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
        if (gameState == running || gameState == start)
            player->changeDirection(event);
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        switch (gameState) {
        case paused:
        case start:
            player->setPaused(false);
            for(Ghost* ghost : ghosts)
                ghost->setPaused(false);
            gameState = running;
            break;
            break;
        case running:
            player->setPaused(true);
            for(Ghost* ghost : ghosts)
                ghost->setPaused(true);
            gameState = paused;
            break;
        case won:
        case lost:
            initGameObjects();
            gameState = start;
            break;
        }
    default:
        break;
    }
}

void PacMan::initGameObjects()
{
    gs->clear();

    delete maze;
    maze = new Maze(gs, gv);
    QObject::connect(maze, &Maze::gameOver, this, &PacMan::gameOverHandler);
    delete player;
    player = new Player(gs, maze);

    for (Ghost *ghost : ghosts)
        delete ghost;
    ghosts[0] = new Blinky (gs, maze, player);
    ghosts[1] = new Pinky  (gs, maze, player);
    ghosts[2] = new Inky   (gs, maze, player, ghosts[0]);
    ghosts[3] = new Clyde  (gs, maze, player);

    for(Ghost* ghost : ghosts)
    {
        QObject::connect(ghost, &Ghost::gameOver, this, &PacMan::gameOverHandler);
        QObject::connect(player, &Player::energizedChanged, ghost, &Ghost::setFrightened);
    }

    gameStateText = gs->addText("");
    gameStateText->setDefaultTextColor(Qt::white);
}

/**
 * @brief PacMan::gameOverHandler Handle a GameOver caused bye either a ghost eating the Player or the Player eating every dot in the maze
 * @param won
 */
void PacMan::gameOverHandler(bool won) {
    gameState = (won ? PacMan::won : PacMan::lost);

    player->setPaused(true);
    for(Ghost *ghost: ghosts) {
        ghost->setPaused(true);
    }
}
