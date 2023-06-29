#include "qmenu.h"
#include <QPushButton>
#include <QMouseEvent>

#ifndef MINE_H
#define MINE_H

class Mine : public QPushButton
{
    Q_OBJECT

public:
    Mine(QWidget* parent = nullptr) : QPushButton(parent) {}

signals:
    void leftClicked();
    void rightClicked();

protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton){
            emit leftClicked();
        }
        else if (event->button() == Qt::RightButton){
            emit rightClicked();
        }
    }


};

#endif // MINE_H
