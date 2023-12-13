#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "locallib_global.h"

#include <QWidget>

/**
 * @brief The MyWidget class is used to redirect keyboard inputs to the PacMan class.
 */
class LOCALLIB_EXPORT MyWidget : public QWidget
{
    Q_OBJECT
signals:
    void keyPressed(QKeyEvent *event);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYWIDGET_H
