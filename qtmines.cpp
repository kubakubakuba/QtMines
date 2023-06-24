#include "qtmines.h"
#include "ui_qtmines.h"

QtMines::QtMines(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtMines)
{
    ui->setupUi(this);
}

QtMines::~QtMines()
{
    delete ui;
}

