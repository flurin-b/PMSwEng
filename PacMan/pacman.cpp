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
    menuScene = new QGraphicsScene();
    gameScene = new QGraphicsScene();

    int id = QFontDatabase::addApplicationFont(":/Sprite/Font/emulogic.ttf");
    pacManFont      = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 10);
    pacManFontLarge = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 18);

    gv->setScene(menuScene);
    gv->setFixedSize(Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    menuScene->setSceneRect(0, 0, Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    menuScene->setBackgroundBrush(Qt::black);
    gameScene->setSceneRect(0, 0, Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    gv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    initGameObjects();
}

/**
 * @brief PacMan::~PacMan Delets allocated memory during ctor
 */
PacMan::~PacMan()
{
    delete gameScene;
    gameScene = nullptr;

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
    gv->setScene(menuScene);

    switch (gameState)
    {
    case won:
    case lost:
    {
        menuText->setFont(pacManFontLarge);
        menuText->setPlainText(gameState == won ? "Game Over, you win!" : "Game Over, you loose!");
        menuPrompt->setFont(pacManFont);
        menuPrompt->setPlainText("Press ENTER to play again.");
        scoreText->setFont(pacManFont);
        char buf[14] = "";
        sprintf(buf, "Score: %06d", maze->getScore());
        scoreText->setPlainText(buf);
        menuText->setPos((QPoint((menuScene->sceneRect().width() - menuText->boundingRect().width()) / 2, (menuScene->sceneRect().height() - menuText->boundingRect().height()) * 0.3)));
        menuPrompt->setPos((QPoint((menuScene->sceneRect().width() - menuPrompt->boundingRect().width()) / 2, (menuScene->sceneRect().height() - menuPrompt->boundingRect().height()) * 0.35)));
        scoreText->setPos((QPoint((menuScene->sceneRect().width() - scoreText->boundingRect().width()) / 2, (menuScene->sceneRect().height() - scoreText->boundingRect().height()) * 0.40)));
        break;
    }
    case paused:
        gv->setScene(gameScene);
        gameStateText->setFont(pacManFont);
        gameStateText->setPlainText("Game Paused, press ENTER to resume.");
        gameStateText->show();
        break;
    case running:
        gv->setScene(gameScene);
        gameStateText->hide();
        break;
    case start:
        gv->setScene(gameScene);
        gameStateText->setFont(pacManFont);
        gameStateText->setPlainText("Press ENTER to start playing.");
        gameStateText->show();
        break;
    }
    maze->paint();
    player->paint();
    for(Ghost* ghost : ghosts)
        ghost->paint();

#ifdef ENABLE_FPS_COUNTER
    fpsCounter ++;
    fpsText->setFont(pacManFont);
    fpsText->setPos(QPoint((gameScene->sceneRect().width() - fpsText->boundingRect().width() - 5), 25));
    char buf[9] = "";
    sprintf(buf, "Fps: %04d", fps);
    fpsText->setPlainText(buf);
#endif // ENABLE_FPS_COUNTER
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
    gameScene->clear();
    menuScene->clear();

    delete maze;
    maze = new Maze(gameScene, gv);
    QObject::connect(maze, &Maze::gameOver, this, &PacMan::gameOverHandler);
    delete player;
    player = new Player(gameScene, maze);

    for (Ghost *ghost : ghosts)
        delete ghost;
    ghosts[0] = new Blinky (gameScene, maze, player);
    ghosts[1] = new Pinky  (gameScene, maze, player);
    ghosts[2] = new Inky   (gameScene, maze, player, ghosts[0]);
    ghosts[3] = new Clyde  (gameScene, maze, player);

    for(Ghost* ghost : ghosts)
    {
        QObject::connect(ghost, &Ghost::gameOver, this, &PacMan::gameOverHandler);
        QObject::connect(player, &Player::energizedChanged, ghost, &Ghost::setFrightened);
    }

    menuText = menuScene->addText("");
    menuText->setDefaultTextColor(Qt::white);
    menuPrompt = menuScene->addText("");
    menuPrompt->setDefaultTextColor(Qt::white);
    scoreText = menuScene->addText("");
    scoreText->setDefaultTextColor(Qt::white);

    gameStateText = gameScene->addText("");
    gameStateText->setDefaultTextColor(Qt::white);

#ifdef ENABLE_FPS_COUNTER
    fpsText = gameScene->addText("");
    fpsText->setDefaultTextColor(Qt::white);
    delete fpsTimer;
    fpsTimer = new QTimer();
    fpsTimer->setTimerType(Qt::PreciseTimer);
    connect(fpsTimer, &QTimer::timeout, this, [this]{fps = fpsCounter; fpsCounter = 0;});
    fpsTimer->start(1000);
#endif // ENABLE_FPS_COUNTER
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
