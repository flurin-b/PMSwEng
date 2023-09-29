#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget{parent}
{}

void MyWidget::keyPressEvent(QKeyEvent* event){
    emit keyPressed(event);
}
