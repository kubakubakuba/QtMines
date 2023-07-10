#include "qmenu.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>

#ifndef MINE_H
#define MINE_H

class Mine : public QPushButton
{
    Q_OBJECT

public:
    Mine(QWidget* parent = nullptr) : QPushButton(parent), longPressFlag(false) {
        pressTimer = new QTimer(this);
        pressTimer->setInterval(250); // Adjust the interval as desired (in milliseconds)
        pressTimer->setSingleShot(true);

        connect(pressTimer, &QTimer::timeout, this, &Mine::longPressed);
    }

signals:
    void leftClicked();
    void rightClicked();
    void longPress();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton){
            longPressFlag = false;
            pressTimer->start();
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton){
            if (pressTimer->isActive() && !longPressFlag) {
                emit leftClicked();
                pressTimer->stop();
            }
        }
        else if (event->button() == Qt::RightButton){
            if (pressTimer->isActive() && !longPressFlag) {
                emit rightClicked();
                pressTimer->stop();
            }
        }
    }

private slots:
    void longPressed() {
        longPressFlag = true;
        emit longPress();
    }

private:
    QTimer* pressTimer;
    bool longPressFlag;
};

#endif // MINE_H
