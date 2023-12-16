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
    // Application and Widget Objects
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://Sprite/Logo/PacMan.ico"));
    MyWidget w;
    w.setFocusPolicy(Qt::StrongFocus);

    // Layout
    QHBoxLayout* hb = new QHBoxLayout;

    // QGraphicsView
    QGraphicsView* gv = new QGraphicsView();
    gv->setFocusPolicy(Qt::NoFocus);
    hb->addWidget(gv);

    // PacMan Object
    PacMan* pm = new PacMan(gv);
    // Connect Keyboard Input Events
    QObject::connect(&w, &MyWidget::keyPressed, pm, &PacMan::handleKeyPress);

    // Add Layout to Widget and Show Widget
    w.setLayout(hb);
    w.show();

    // Setup the frameTimer that triggers the paint loop.
    QTimer frameTimer;
    QObject::connect(&frameTimer, &QTimer::timeout, pm, &PacMan::paint);
    frameTimer.start(0);                            // paint as often as possible but...
    frameTimer.setTimerType(Qt::VeryCoarseTimer);   // make everything else more important.

    // Run the Application and wait for it to stop.
    return a.exec();
}
