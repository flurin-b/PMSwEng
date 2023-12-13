#include "maze.h"
#include "qgraphicsitem.h"
#include <QResource>

/**
 * @brief Maze::Maze Creates a Instace of Maze which contains all the eatables and the paths that can be taken from a certain position
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

            switch (getDots(QPoint(x, y)))
            {
            case noItem:
                dotSprites[x][y] = nullptr;
                break;
            case smallPoint:
                dotSprites[x][y] = gs->addEllipse((x+0.5-dot_size/2) * fieldSize_px, (y+0.5-dot_size/2) * fieldSize_px, dot_size * fieldSize_px, dot_size * fieldSize_px,QPen(Qt::yellow),QBrush(Qt::yellow));
                break;
            case bigPoint:
                dotSprites[x][y] = gs->addEllipse((x+0.5-dot_size) * fieldSize_px, (y+0.5-dot_size) * fieldSize_px, dot_size * 3 * fieldSize_px, dot_size * 3 * fieldSize_px,QPen(Qt::yellow),QBrush(Qt::yellow));
                break;
            }
        }
    }
}

void Maze::paint(){

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if(dotSprites[x][y] != nullptr && getDots(QPoint(x, y)) == noItem) {
                dotSprites[x][y]->setVisible(false);
                delete dotSprites[x][y];
                dotSprites[x][y] = nullptr;
            }
        }
    }

    // Score Display
    char buf[7] = "";
    sprintf(buf, "%06d", this->score);
    scoreText->setText(buf);
}

/**
 * @brief Maze::getDots A function for getting the Item contained in a field
 * @param position The field in the maze from which the item want to be known
 * @return Returns the Item that is conatined in posistion of the maze
 */
int Maze::getDots(QPoint position)
{
    ///If the requested position is outside of the border from the maze an error is returned otherwise the item contained in the field
    int contend = error;

    if(position.x() >= 0 && position.x() <= width-1)
    {
        if(position.y() >= 0 && position.y() <= height-1)
        {
            contend = dots[position.y()][position.x()];
        }
    }

    return contend;
}

/**
 * @brief Maze::getDotsEaten Get the amount of small Dots eaten by the Player
 * @return 0-244
 */
int Maze::getDotsEaten(){
    return dotsEaten;
}

/**
 * @brief Maze::setDots Change the Item a specific field in the maze contains
 * @param position The point in the maze where the item should be changed
 * @param item The new item that should be placed at the defined position
 */
void Maze::setDots(QPoint position, item_t item)
{
    // If a small dot is eaten, increment dotsEaten
    if(dots[position.y()][position.x()] == smallPoint && item == noItem)
    {
        dotsEaten += 1;
        if (dotsEaten == dotCount)
        {
            emit gameOver(true);
        }
    }

    dots[position.y()][position.x()] = item;
}

/**
 * @brief Maze::getMaze Gives back all the Points on to which a character can be moved
 * @param position The position in the maze the directions want to be known from
 * @return A vector of QPoint which are located around the specified posistion
 */
std::vector<QPoint> Maze::getMaze(QPoint position)
{
    ///If the requested Position doesn't exist No Offset will be given back
    QPoint errorPosition(0,0);
    std::vector<QPoint> directions = {errorPosition};

    if(position.x() >= 0 && position.x() <= width-1)
    {
        if(position.y() >= 0 && position.y() <= height-1)
        {
            directions = maze[position.y()][position.x()];
        }
    }

    return directions;
}

/**
 * @brief Maze::getFieldWidth Get the current Width of a Field in the Maze
 * @return The width of a Field in Pixel
 */
float Maze::getFieldWidth(void) {
    return gv->width() / width;
}

/**
 * @brief Maze::increaseScore Update the score made by the Player
 * @param offset The amount the score should be changed
 */
void Maze::increaseScore(int offset)
{
    //The score can only ever be increased never decreased
    if(offset > 0)
    {
        score += offset;
    }
}


/**
 * @brief Maze::getScore Get the current score.
 * @return The current score.
 */
int Maze::getScore(void) {
    return score;
}
