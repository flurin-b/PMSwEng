#include "maze.h"
#include "qgraphicsitem.h"
#include <QResource>

/**
 * @brief Maze::Maze Creates a Instace of Maze. It also initializes all the graphics items.
 * @param scPointer A Pointer to the GraphicScene onto which the items will be placed
 */
Maze::Maze(QGraphicsScene *gsPointer, QGraphicsView *gvPointer):gs{gsPointer}, gv{gvPointer}
{
    const float dot_size = 0.15;
    const float fieldSize_px = gv->width() / width;

#ifdef MAZE_DEBUG_ARROWS
    const float arrow_len = 0.45;
    const float arrow_hat = 0.15;
#endif /* MAZE_DEBUG_ARROWS */

    gs->setBackgroundBrush(Qt::black);
    QGraphicsPixmapItem* labyrinth =  gs->addPixmap(QPixmap(":/Sprite/Maze/maze.png").scaledToWidth(gs->width()-2));
    labyrinth->setPos(0,fieldSize_px * 3);

    // Score Display
    int id = QFontDatabase::addApplicationFont(":/Sprite/Font/emulogic.ttf");
    QString pacManFont = QFontDatabase::applicationFontFamilies(id).at(0);

    scoreText = gs->addSimpleText("");
    scoreText->setBrush(Qt::white);
    scoreText->setPos(5, 25);
    scoreText->setFont(QFont(pacManFont, 10));

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {

#ifdef MAZE_DEBUG_ARROWS
            std::vector<QPoint> dirs = getMaze(QPoint(x, y));
            for (QPoint dir : dirs)
            {
                gs->addLine((x+0.5)*fieldSize_px, (y+0.5)*fieldSize_px, (x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px,QPen(Qt::white));
                gs->addLine((x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px, (x+0.5+dir.y()*arrow_hat+dir.x()*arrow_hat) * fieldSize_px, (y+0.5+dir.x()*arrow_hat+dir.y()*arrow_hat) * fieldSize_px,QPen(Qt::white));
                gs->addLine((x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px, (x+0.5-dir.y()*arrow_hat+dir.x()*arrow_hat) * fieldSize_px, (y+0.5-dir.x()*arrow_hat+dir.y()*arrow_hat) * fieldSize_px,QPen(Qt::white));
            }
#endif /* MAZE_DEBUG_ARROWS */

            switch (getItemAt(QPoint(x, y)))
            {
            case noItem:
                dotSprites[x][y] = nullptr;
                break;
            case dot:
                dotSprites[x][y] = gs->addEllipse((x+0.5-dot_size/2) * fieldSize_px, (y+0.5-dot_size/2) * fieldSize_px, dot_size * fieldSize_px, dot_size * fieldSize_px,QPen(Qt::yellow),QBrush(Qt::yellow));
                break;
            case energizer:
                dotSprites[x][y] = gs->addEllipse((x+0.5-dot_size) * fieldSize_px, (y+0.5-dot_size) * fieldSize_px, dot_size * 3 * fieldSize_px, dot_size * 3 * fieldSize_px,QPen(Qt::yellow),QBrush(Qt::yellow));
                break;
            }
        }
    }
}

/**
 * @brief Updates the graphics items to reflect the current game state.
 */
void Maze::paint(){

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if(dotSprites[x][y] != nullptr)
            {
                if(getItemAt(QPoint(x, y)) == noItem) {
                    dotSprites[x][y]->setVisible(false);
                    delete dotSprites[x][y];
                    dotSprites[x][y] = nullptr;
                }
            }
        }
    }

    // Score Display
    char buf[7] = "";
    sprintf(buf, "%06d", this->score);
    scoreText->setText(buf);
}

/**
 * @brief Returns what Item is in the specified field.
 * @param The fields coordinates.
 * @return The item in that field.
 */
Maze::item_t Maze::getItemAt(QPoint position)
{
    return dots[position.y()][position.x()];
}

/**
 * @brief Get the amount of small Dots eaten by the Player.
 * @return The ammount of dots eaten untill now.
 */
int Maze::getDotsEaten(){
    return dotsEaten;
}

/**
 * @brief Set a specific field to contain the specified item.
 * @param The field in the Maze where the item should be placed.
 * @param The new item to ne placed.
 */
void Maze::setItemAt(QPoint position, item_t item)
{
    // If a small dot is eaten, increment dotsEaten
    if(dots[position.y()][position.x()] == dot && item == noItem)
    {
        dotsEaten += 1;
        // Check if the Player has eaten all dots.
        // If he has, end the game.
        if (dotsEaten == dotCount)
        {
            emit gameOver(true);
        }
    }
    dots[position.y()][position.x()] = item;
}

/**
 * @brief Returns all possible directions in wich a Player or Ghost can go starting from the supplied position.
 * @param The position to query.
 * @return A vector of QPoints that contains all possible directions.
 */
std::vector<QPoint> Maze::getMaze(QPoint position)
{
    // Return possible directions if there are any...
    if(maze[position.y()][position.x()].size() > 0)
        return maze[position.y()][position.x()];
    // ... otherwise just stand still.
    else
        return std::vector<QPoint>{QPoint(0, 0)};
}

/**
 * @brief Get the current Width of a Field in the Maze.
 * @return The width of a Field in Pixels.
 */
float Maze::getFieldWidth(void) {
    return gv->width() / width;
}

/**
 * @brief Inclrease the score by a given ammount.
 * @param How many points should be added.
 */
void Maze::increaseScore(int offset)
{
    score += offset;
}

/**
 * @brief Get the current score.
 * @return The current score.
 */
int Maze::getScore(void) {
    return score;
}
