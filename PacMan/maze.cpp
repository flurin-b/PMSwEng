#include "maze.h"
#include "qgraphicsitem.h"
#include <QResource>

/**
 * @brief Maze::Maze Creates a Instace of Maze which contains all the eatables and the paths that can be taken from a certain position
 * @param scPointer A Pointer to the GraphicScene onto which the items will be placed
 */
Maze::Maze(QGraphicsScene *gsPointer, QGraphicsView *gvPointer):gs{gsPointer}, gv{gvPointer}
{}

void Maze::paint(){

    const float arrow_len = 0.45;
    const float arrow_hat = 0.15;
    const float dot_size = 0.15;
    const float fieldSize_px = gv->width() / width;
    static bool mazeDisplayed = false;
    static QGraphicsEllipseItem* dots[width][height];

    if(!mazeDisplayed){
        gs->setBackgroundBrush(Qt::black);
        QGraphicsPixmapItem* labyrinth =  gs->addPixmap(QPixmap(":/Sprite/Maze/maze.png").scaledToWidth(gs->width()-2));
        labyrinth->setPos(0,fieldSize_px * 3);

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                /*std::vector<QPoint> dirs = getMaze(QPoint(x, y));
                for (QPoint dir : dirs)
                {
                    gs->addLine((x+0.5)*fieldSize_px, (y+0.5)*fieldSize_px, (x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px,QPen(Qt::white));
                    gs->addLine((x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px, (x+0.5+dir.y()*arrow_hat+dir.x()*arrow_hat) * fieldSize_px, (y+0.5+dir.x()*arrow_hat+dir.y()*arrow_hat) * fieldSize_px,QPen(Qt::white));
                    gs->addLine((x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px, (x+0.5-dir.y()*arrow_hat+dir.x()*arrow_hat) * fieldSize_px, (y+0.5-dir.x()*arrow_hat+dir.y()*arrow_hat) * fieldSize_px,QPen(Qt::white));
                }*/
                switch (getDots(QPoint(x, y)))
                {
                case noItem:
                    dots[x][y] = nullptr;
                    break;
                case smallPoint:
                    dots[x][y] = gs->addEllipse((x+0.5-dot_size/2) * fieldSize_px, (y+0.5-dot_size/2) * fieldSize_px, dot_size * fieldSize_px, dot_size * fieldSize_px,QPen(Qt::yellow),QBrush(Qt::yellow));
                    break;
                case bigPoint:
                    dots[x][y] = gs->addEllipse((x+0.5-dot_size) * fieldSize_px, (y+0.5-dot_size) * fieldSize_px, dot_size * 3 * fieldSize_px, dot_size * 3 * fieldSize_px,QPen(Qt::yellow),QBrush(Qt::yellow));
                    break;
                }
            }
        }
        mazeDisplayed = true;
    }
    else {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                if(dots[x][y] != nullptr && getDots(QPoint(x, y)) == noItem) {
                    dots[x][y]->setVisible(false);
                    delete dots[x][y];
                    dots[x][y] = nullptr;
                }
            }
        }
    }


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
        dotsEaten += 1;

    dots[position.y()][position.x()] = item;
}

/**
 * @brief Maze::getMaze Gives back all the Points on to which a character can be moved
 * @param position The position in the maze the directions want to be known from
 * @return A vector of QPoint which are located around the specified posistion
 */
std::vector<QPoint> Maze::getMaze(QPoint position)
{
    ///If the requested Position doesn't exist No Offset willb be given back
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

float Maze::getFieldWidth(void) {
    return gv->width() / width;
}

void Maze::increaseScore(int offset)
{
    if(offset > 0)
    {
        score += offset;
    }
}
