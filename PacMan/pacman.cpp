#include "pacman.h"
#include "maze.h"
#include "qevent.h"

#include <stdio.h>


/**
 * @brief PacMan::PacMan Initalize the base needed for a round of Pac-Man
 * @param A Pointer to the GraphicsView in which Pac-Man will be displayed
 */
PacMan::PacMan(QGraphicsView *gvPointer):gv{gvPointer}
{
    //With 20px per field the game is playable from a 1080p display up to a 4k. A scalabe resolution will maybe be implemented later on
    int fieldSize_px = 20;
    menuScene = new QGraphicsScene();
    gameScene = new QGraphicsScene();

    //Set the font for the Text in the game
    int id = QFontDatabase::addApplicationFont(":/Sprite/Font/emulogic.ttf");
    pacManFont      = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 10);
    pacManFontLarge = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 18);

    //Setup the two seprate scene for playing and starting/ending the game
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
    //Hide everything in the Scene before deleting the items for a better expirence
    gameScene->clear();
    menuScene->clear();

    //Remove the old Maze,Player and Ghosts which all contain information from the past game, and create new ones
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

    //Create the Text for playing a new round
    menuText = menuScene->addText("");
    menuText->setDefaultTextColor(Qt::white);
    menuText->setFont(pacManFontLarge);
    menuPrompt = menuScene->addText("Press ENTER to play again.");
    menuPrompt->setDefaultTextColor(Qt::white);
    menuPrompt->setFont(pacManFont);
    scoreText = menuScene->addText("");
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(pacManFont);

    //Create the Text for informing the Player how to start the game
    gameStateText = gameScene->addText("Press ENTER to start playing.");
    gameStateText->setDefaultTextColor(Qt::white);
    gameStateText->setFont(pacManFont);

//Create a new fpsCounter for the new round
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
    //Switch between the diffrent Text that appears depending on the gameState
    switch (gameState)
    {
    case won:
    case lost:
    {
        //Handle the information flow after a game has been won or lost
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
        //Handle the information flow while a game is paused
        if (gv->scene() != gameScene)
            gv->setScene(gameScene);
        if (!gameStateText->isVisible())
        {
            gameStateText->setPlainText("Game Paused, press ENTER to resume.");
            gameStateText->show();
        }
        break;
    case running:
        //Handle the information flow while the game is running
        if (gv->scene() != gameScene)
            gv->setScene(gameScene);
        if (gameStateText->isVisible())
            gameStateText->hide();
        break;
    case start:
        //This will only ever be displayed at the start of a round to inform the Player how to start
        if (gv->scene() != gameScene)
            gv->setScene(gameScene);
        if (!gameStateText->isVisible())
        {
            gameStateText->show();
            gameStateText->setPlainText("Press ENTER to start playing.");
        }
        break;
    }

    //Display all the parts of the game the player actively interacts with
    maze->paint();
    player->paint();
    for(Ghost* ghost : ghosts)
        ghost->paint();

    //Show the current Frames per Second(FPS) aka. how often the Paint functionn of the Objects are called per second
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
    //The Arrow key are only used for controlling the player thus they are forwareded to him
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if (gameState == running || gameState == start)
            player->changeDirection(event);
        break;
    //Both the enter key on the keyboard and on the numpad can be used to start/pause the game
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
