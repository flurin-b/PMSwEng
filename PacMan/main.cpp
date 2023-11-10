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
int fieldSize_px = 30;

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

    for (int x = 0; x < m->width; x++)
    {
        for (int y = 0; y < m->height; y++)
        {
            float arrow_len = 0.45;
            float arrow_hat = 0.15;
            float dot_size = 0.15;
            std::vector<QPoint> dirs = m->getMaze(QPoint(x, y));
            for (QPoint dir : dirs)
            {
                gs->addLine((x+0.5)*fieldSize_px, (y+0.5)*fieldSize_px, (x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px);
                gs->addLine((x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px, (x+0.5+dir.y()*arrow_hat+dir.x()*arrow_hat) * fieldSize_px, (y+0.5+dir.x()*arrow_hat+dir.y()*arrow_hat) * fieldSize_px);
                gs->addLine((x+0.5+dir.x()*arrow_len) * fieldSize_px, (y+0.5+dir.y()*arrow_len) * fieldSize_px, (x+0.5-dir.y()*arrow_hat+dir.x()*arrow_hat) * fieldSize_px, (y+0.5-dir.x()*arrow_hat+dir.y()*arrow_hat) * fieldSize_px);
            }
            int dot = m->getDots(QPoint(x, y));
            switch (dot)
            {
            case noItem:
                break;
            case smallPoint:
                gs->addEllipse((x+0.5-dot_size/2) * fieldSize_px, (y+0.5-dot_size/2) * fieldSize_px, dot_size * fieldSize_px, dot_size * fieldSize_px);
                break;
            case bigPoint:
                gs->addEllipse((x+0.5-dot_size) * fieldSize_px, (y+0.5-dot_size) * fieldSize_px, dot_size * 2 * fieldSize_px, dot_size * 2 * fieldSize_px);
                break;
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
