#include "pacman.h"
#include "maze.h"
#include "qevent.h"

#include <stdio.h>


/**
 * @brief PacMan::PacMan Initalize everything needed for a round of Pac-Man
 * @param A Pointer to the GraphicsView in which Pac-Man will be displayed
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
    gv->setInteractive(false);
    gv->setFixedSize(Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    menuScene->setSceneRect(0, 0, Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    menuScene->setBackgroundBrush(Qt::black);
    gameScene->setSceneRect(0, 0, Maze::width*fieldSize_px + 1, Maze::height*fieldSize_px);
    gv->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    initGameObjects();

    // Setup the frameTimer that triggers the paint loop.
    QObject::connect(&frameTimer, &QTimer::timeout, this, &PacMan::paint);
    frameTimer.start(0);                            // paint as often as possible but...
    frameTimer.setTimerType(Qt::VeryCoarseTimer);   // make everything else more important.
}

/**
 * @brief Initializes all game objects. To start a new round, just call this function again.
 */
void PacMan::initGameObjects()
{
    gameScene->clear();
    menuScene->clear();

    delete maze;
    maze = new Maze(gameScene, gv);
    QObject::connect(maze, &Maze::gameOver, this, &PacMan::handleGameOver);
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
        QObject::connect(ghost, &Ghost::gameOver, this, &PacMan::handleGameOver);
        QObject::connect(player, &Player::energizedChanged, ghost, &Ghost::setFrightened);
    }

    menuText = menuScene->addText("");
    menuText->setDefaultTextColor(Qt::white);
    menuText->setFont(pacManFontLarge);
    menuPrompt = menuScene->addText("Press ENTER to play again.");
    menuPrompt->setDefaultTextColor(Qt::white);
    menuPrompt->setFont(pacManFont);
    scoreText = menuScene->addText("");
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(pacManFont);

    gameStateText = gameScene->addText("");
    gameStateText->setDefaultTextColor(Qt::white);
    gameStateText->setFont(pacManFont);

#ifdef ENABLE_FPS_COUNTER
    fpsText = gameScene->addText("Fps: 0000");
    fpsText->setDefaultTextColor(Qt::white);
    fpsText->setFont(pacManFont);
    delete fpsTimer;
    fpsTimer = new QTimer();
    fpsTimer->setTimerType(Qt::PreciseTimer);
    connect(fpsTimer, &QTimer::timeout, this, [this]{fps = fpsCounter; fpsCounter = 0;});
    fpsTimer->start(1000);
#endif // ENABLE_FPS_COUNTER
}

/**
 * @brief Deletes allocated memory.
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
 * @brief Paints global menu items and calls the paint function of all game objects.
 */
void PacMan::paint()
{
    switch (gameState)
    {
    case won:
    case lost:
    {
        if (gv->scene() != menuScene)
        {
            gameStateText->hide();
            gv->setScene(menuScene);
            menuText->setPlainText(gameState == won ? "Game Over, you win!" : "Game Over, you loose!");
            char buf[14] = "";
            sprintf(buf, "Score: %06d", maze->getScore());
            scoreText->setPlainText(buf);
            menuText->setPos((QPoint((menuScene->sceneRect().width() - menuText->boundingRect().width()) / 2, (menuScene->sceneRect().height() - menuText->boundingRect().height()) * 0.3)));
            menuPrompt->setPos((QPoint((menuScene->sceneRect().width() - menuPrompt->boundingRect().width()) / 2, (menuScene->sceneRect().height() - menuPrompt->boundingRect().height()) * 0.35)));
            scoreText->setPos((QPoint((menuScene->sceneRect().width() - scoreText->boundingRect().width()) / 2, (menuScene->sceneRect().height() - scoreText->boundingRect().height()) * 0.40)));
        }
        break;
    }
    case paused:
        if (gv->scene() != gameScene)
            gv->setScene(gameScene);
        if (!gameStateText->isVisible())
        {
            gameStateText->setPlainText("Game Paused, press ENTER to resume.");
            gameStateText->show();
        }
        break;
    case running:
        if (gv->scene() != gameScene)
            gv->setScene(gameScene);
        if (gameStateText->isVisible())
            gameStateText->hide();
        break;
    case start:
        if (gv->scene() != gameScene)
            gv->setScene(gameScene);
        if (!gameStateText->isVisible())
        {
            gameStateText->show();
            gameStateText->setPlainText("Press ENTER to start playing.");
        }
        break;
    }

    maze->paint();
    player->paint();
    for(Ghost* ghost : ghosts)
        ghost->paint();

#ifdef ENABLE_FPS_COUNTER
    fpsCounter ++;
    fpsText->setPos(QPoint((gameScene->sceneRect().width() - fpsText->boundingRect().width() - 5), 25));
    char buf[9] = "";
    sprintf(buf, "Fps: %04d", fps);
    fpsText->setPlainText(buf);
#endif // ENABLE_FPS_COUNTER
}

/**
 * @brief Process the keyboard input and take appropriate action.
 * @param The QKeyEvent to process.
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

/**
 * @brief Handle a GameOver caused by either a Ghost eating the Player or the Player eating every dot in the Maze.
 * @param If the player has won.
 */
void PacMan::handleGameOver(bool won) {
    gameState = (won ? PacMan::won : PacMan::lost);

    player->setPaused(true);
    for(Ghost *ghost: ghosts) {
        ghost->setPaused(true);
    }
}
