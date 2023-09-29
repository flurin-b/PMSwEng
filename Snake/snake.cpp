#include "snake.h"

Snake::Snake(QGraphicsScene* sc):sc{sc}{
    stepTimer = new QTimer();
    QObject::connect(stepTimer, &QTimer::timeout, this, &Snake::onStep);
}

void Snake::begin(){
    // init Snake
    body = std::vector<QPoint>();
    for(int i = 5; i > 0; i--) {
        body.insert(body.begin(), QPoint(playAreaWidth / 2, playAreaHeight / 2 + i));
    }
    currentDirection = UP;
    nextDirection = UP;
    nextNextDirection = UP;
    // init food
    spawnFood();
    // init Timer
    stepTimer->start(500);
    this->paint();
}

void Snake::spawnFood(){
    if(body.size() % 2)
        stepTimer->setInterval(stepTimer->interval()-stepTimerDecrement);
    do {
        food = QPoint(rand() % playAreaWidth, rand() % playAreaHeight);
    } while(std::find(body.begin(), body.end(), food) != body.end());
}

void Snake::paint(){
    sc->clear();
    int width = sc->width() / playAreaWidth;
    int l = (1.0 - margins) * width;
    int offset = margins * width / 2;
    for(QPoint element : body) {
        sc->addRect(element.x() * width + offset,
                    element.y() * width + offset,
                    l, l);
    }
    sc->addEllipse( food.x() * width + offset,
                    food.y() * width + offset,
                    l, l);
}

void Snake::gameOver() {
    stepTimer->stop();
    sc->addText("Game Over!");
}

void Snake::onStep(){
    // If snake hasnt eaten remove tail and add head
    currentDirection = nextDirection;
    nextDirection = nextNextDirection;
    if(body.front()+currentDirection != food){
        body.pop_back();
    }
    else{
        spawnFood();
    }
    body.insert(body.begin(), body.front()+currentDirection);
    paint();
    // Game Over if crashed into wall
    if(body.front().x() >= 25 || body.front().y() >= 25 || body.front().x() < 0 || body.front().y() < 0) {
        gameOver();
    }
    // Game Over if crashed into self
    if(std::find(body.begin()+1, body.end(), body.front()) != body.end()){
        gameOver();
    }
}

void Snake::onKeyPress(QKeyEvent* event){
    switch(event->key()){
    case Qt::Key_W:
    case Qt::Key_Up:
        if(currentDirection != DOWN && currentDirection != UP) {
            nextDirection = UP;
            nextNextDirection = UP;
        }
        else
            nextNextDirection = UP;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        if(currentDirection != UP && currentDirection != DOWN) {
            nextDirection = DOWN;
            nextNextDirection = DOWN;
        }
        else
            nextNextDirection = DOWN;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        if(currentDirection != RIGHT && currentDirection != LEFT) {
            nextDirection = LEFT;
            nextNextDirection = LEFT;
        }
        else
            nextNextDirection = LEFT;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        if(currentDirection != LEFT && currentDirection != RIGHT){
            nextDirection = RIGHT;
            nextNextDirection = RIGHT;
        }
        else
            nextNextDirection = RIGHT;
        break;
    case Qt::Key_Space:
        if(!stepTimer->isActive())
            begin();
        break;
    case Qt::Key_Escape:
        // TODO: Implement Pause Menu
        emit exit();
        break;
    }
}
