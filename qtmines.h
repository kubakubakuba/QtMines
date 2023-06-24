#ifndef QTMINES_H
#define QTMINES_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <algorithm>
#include <QWidget>
#include <iostream>
#include <minefield.h>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class QtMines; }
QT_END_NAMESPACE

class QtMines : public QMainWindow
{
    Q_OBJECT

public:
    QtMines(QWidget *parent = nullptr);
    ~QtMines();
    MineField mineField = MineField();
    int mines_w, mines_h, time, num_active;
    Digit digitLeft, digitRight;
    QPushButton* smiley;

private:
    Ui::QtMines *ui;
};

#endif // QTMINES_H
