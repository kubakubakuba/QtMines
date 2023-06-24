#include "qtmines.h"
#include "minefield.h"
#include "util.h"

#include <QApplication>
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <algorithm>

void render_board(QtMines & qtm, int mine_size);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMines w;

    w.time = 0;
    w.mines_w = 35;
    w.mines_h = 10;

    int mine_size = 35;

    w.num_active = 10;

    w.smiley = new QPushButton;

    w.mineField = MineField(w.mines_w, w.mines_h, w.num_active);
    w.setFixedSize(w.mines_w * mine_size, w.mines_h * mine_size);
    render_board(w, mine_size);

    w.show();
    return a.exec();
}

void render_board(QtMines & qtm, int mine_size){
    Rsrc r = Rsrc();

    QVBoxLayout* vLayout = new QVBoxLayout(qtm.centralWidget());

    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    QHBoxLayout* header = new QHBoxLayout;
    header->setSpacing(0);

    qtm.digitLeft = Digit();
    qtm.digitRight = Digit();

    qtm.digitRight.update(0, r);
    qtm.digitLeft.update(0, r);

    header->addWidget(qtm.digitLeft.d1);
    header->addWidget(qtm.digitLeft.d2);
    header->addWidget(qtm.digitLeft.d3);


    qtm.smiley->setIcon(r.face[0]);
    header->addWidget(qtm.smiley);

    QObject::connect(qtm.smiley, &QPushButton::clicked, [=, &qtm]() {
        qtm.mineField.win = false;
        qtm.mineField.lost = false;
        qtm.mineField.data = std::vector<int>();
        qtm.mineField.mines_set = false;

        for(auto b : qtm.mineField.buttons){
            b->setDisabled(false);
            b->setIcon(qtm.mineField.rsrc.buttons[0]);
        }

        qtm.smiley->setIcon(qtm.mineField.rsrc.face[0]);

        qtm.time = 0;
    });

    header->addWidget(qtm.digitRight.d1);
    header->addWidget(qtm.digitRight.d2);
    header->addWidget(qtm.digitRight.d3);

    qtm.digitLeft.d1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.digitLeft.d2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.digitLeft.d3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.digitRight.d1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.digitRight.d2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.digitRight.d3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    QTimer* timer = new QTimer();
    timer->setInterval(1000);

    QObject::connect(timer, &QTimer::timeout, [&](){
        qtm.digitRight.update((++qtm.time) % 999, Rsrc());
    });

    timer->start();

    qtm.smiley->setFlat(true);
    qtm.mineField.smiley = qtm.smiley;
    vLayout->addLayout(header);

    for (int i = 0; i < qtm.mines_h; i++) {
        QHBoxLayout* hLayout = new QHBoxLayout;
        hLayout->setContentsMargins(0, 0, 0, 0);
        hLayout->setSpacing(0);
        for (int j = 0; j < qtm.mines_w; j++) {
            QPushButton* btn = new QPushButton;
            qtm.mineField.buttons.push_back(btn);
            //QString name = QString("a");
            //btn->setText(name);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            btn->setIcon(r.buttons[0]);
            btn->setIconSize(QSize(mine_size, mine_size));
            hLayout->addWidget(btn);
            QObject::connect(btn, &QPushButton::clicked, [=, &qtm]() {
                qtm.mineField.field_click(j, i);
            });
        }
        vLayout->addLayout(hLayout);
    }
}
