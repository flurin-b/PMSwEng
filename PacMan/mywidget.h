#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "locallib_global.h"

#include <QWidget>

class LOCALLIB_EXPORT MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
signals:
    void keyPressed(QKeyEvent *event);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYWIDGET_H
