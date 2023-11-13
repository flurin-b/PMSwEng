#include "MyWidget.h"
#include "PacMan.h"

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

    // QGraphicsView
    QGraphicsView* gv = new QGraphicsView();
    gv->setFocusPolicy(Qt::NoFocus);
    hb->addWidget(gv);

    // PacMan
    PacMan* pm = new PacMan(gv);
    // Keyboard Inputs
    QObject::connect(&w, &MyWidget::keyPressed, pm, &PacMan::handleKeyPress);

    // Show Widget
    w.setLayout(hb);
    w.show();

    return a.exec();
}
