#include "mywidget.h"
#include "pacman.h"
// temporarly include maze.h in order to debug the direction-array
#include "maze.h"

#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>

// Set sizes of different objects
int fieldSize_px = 10;

int main(int argc, char *argv[])
{
    // Application and Widget
    QApplication a(argc, argv);
    MyWidget w;
    w.setFocusPolicy(Qt::StrongFocus);

    // Layout
    QHBoxLayout* hb = new QHBoxLayout;

    // GraphicsScene
    QGraphicsScene* gs = new QGraphicsScene();
    QGraphicsView* gv = new QGraphicsView(gs);
    gv->setFocusPolicy(Qt::NoFocus);
    hb->addWidget(gv);

    // PacMan
    /*PacMan* pm =*/ new PacMan(gs);
    Maze* m = new Maze(gs);
    gv->setFixedSize(m->width*fieldSize_px, m->height*fieldSize_px);
    std::vector<QPoint> dirs;
    for (int x = 0; x < m->width; x++)
    {
        for (int y = 0; y < m->height; y++)
        {
            dirs = m->getMaze(QPoint(x, y));
            for (QPoint dir : dirs)
            {
                gs->addLine((x+0.5)*fieldSize_px, (y+0.5)*fieldSize_px, dir.x() * fieldSize_px, dir.y() * fieldSize_px);
            }
        }
    }

    // Keyboard Inputs
    // Copied from Snake: QObject::connect(&w, &MyWidget::keyPressed, s, &Snake::onKeyPress);

    // Show Widget
    w.setLayout(hb);
    w.show();
    return a.exec();
}
