#include "mywidget.h"

/**
 * @brief MyWidget::keyPressEvent Exposes the keyPressEvent event as a signal.
 * @param event The key that was pressed.
 */
void MyWidget::keyPressEvent(QKeyEvent *event){
    emit keyPressed(event);
}
