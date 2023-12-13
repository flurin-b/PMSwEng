#include "MyWidget.h"
#include "PacMan.h"

#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QThread>

/**
 * @brief main Initializes the QApplication as well as the MyWidget and creates the PacMan object.
 *        Also sets up a frame timer and connects all relevant signals (timeout and key pressed event).
 * @param argc char args
 * @param argv keyword args
 * @return 0 on succes, not 0 on error.
 */
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

    QTimer frameTimer;
    QObject::connect(&frameTimer, &QTimer::timeout, pm, &PacMan::paint);
    frameTimer.start(10);

//    QThread *thread = QThread::create([&pm]{
//        while(1)
//            pm->paint();
//    });
//    thread->start();

    return a.exec();
}
