#include "Snake.h"
#include "MyWidget.h"

#include <QApplication>
#include <QtWidgets>

int     gWidth   = 500;
int     gHeight  = 500;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.setFocusPolicy(Qt::StrongFocus);

    // Layout
    QHBoxLayout* hb = new QHBoxLayout;

    // GraphicsScene
    QGraphicsScene* gs = new QGraphicsScene(0, 0, gWidth, gHeight);
    QGraphicsView* gv = new QGraphicsView(gs);
    gv->setFocusPolicy(Qt::NoFocus);
    hb->addWidget(gv);

    // Snake
    Snake* s = new Snake(gs);
    QObject::connect(s, &Snake::exit, &w, &QWidget::close);
    s->begin();

    // Keyboard Inputs
    QObject::connect(&w, &MyWidget::keyPressed, s, &Snake::onKeyPress);

    // Show Widget
    w.setLayout(hb);
    w.show();
    return a.exec();
}
