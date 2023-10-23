#include "mywidget.h"
#include "pacman.h"

#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    // Application and Widget
    QApplication a(argc, argv);
    MyWidget w;
    w.setFocusPolicy(Qt::StrongFocus);

    // Layout
    QHBoxLayout* hb = new QHBoxLayout;

    // GraphicsScene
    QGraphicsScene* gs = new QGraphicsScene(0, 0, 200, 200);
    QGraphicsView* gv = new QGraphicsView(gs);
    gv->setFocusPolicy(Qt::NoFocus);
    hb->addWidget(gv);

    // PacMan
    /*PacMan* pm =*/ new PacMan(gs);

    // Keyboard Inputs
    // Copied from Snake: QObject::connect(&w, &MyWidget::keyPressed, s, &Snake::onKeyPress);

    // Show Widget
    w.setLayout(hb);
    w.show();
    return a.exec();
}
