#include "qtmines.h"
#include "minefield.h"
#include "util.h"

#include <QApplication>
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <algorithm>
#include <QMouseEvent>
#include <QMenuBar>
#include <Mine.h>
#include <QSpinBox>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QApplication>

void render_board(QtMines & qtm, int mine_size);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMines w;

    w.mines_w = 9;
    w.mines_h = 9;

    int mine_size = 40;

    w.num_active = 10;

    QMenuBar *menuBar = new QMenuBar();

    QMenu *difficultyMenu = new QMenu("Difficulty", menuBar);

    QAction *easyAction = new QAction("Easy");
    QObject::connect(easyAction, &QAction::triggered, [=, &w](){
        w.mineField.set_difficulty(0);
        render_board(w, mine_size);
    });

    QAction *normalAction = new QAction("Normal");
    QObject::connect(normalAction, &QAction::triggered, [=, &w](){
        w.mineField.set_difficulty(1);
        render_board(w, mine_size);
    });

    QAction *hardAction = new QAction("Hard");
    QObject::connect(hardAction, &QAction::triggered, [=, &w](){
        w.mineField.set_difficulty(2);
        render_board(w, mine_size);
    });

    QAction *customAction = new QAction("Custom");
    QObject::connect(customAction, &QAction::triggered, [=, &w](){
        QList<QSpinBox *> spinBoxes;
        spinBoxes.append(new QSpinBox());
        spinBoxes.append(new QSpinBox());
        spinBoxes.append(new QSpinBox());

        spinBoxes[0]->setRange(5, 25);
        spinBoxes[1]->setRange(5, 25);
        spinBoxes[0]->setValue(5);
        spinBoxes[1]->setValue(5);
        spinBoxes[2]->setRange(1, 624);
        spinBoxes[2]->setValue(5);

        QDialog dialog;
        QFormLayout formLayout(&dialog);
        formLayout.addRow(QApplication::translate("main", "number of boxes horizontally: "), spinBoxes[0]);
        formLayout.addRow(QApplication::translate("main", "number of boxes vertically: "), spinBoxes[1]);
        formLayout.addRow(QApplication::translate("main", "number of mines: "), spinBoxes[2]);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok);
        formLayout.addRow(&buttonBox);

        QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        if (dialog.exec() == QDialog::Accepted) {
            int size_w = spinBoxes[0]->value();
            int size_h = spinBoxes[1]->value();
            int mines_max = spinBoxes[2]->value();

            w.mineField.set_difficulty(size_w, size_h, mines_max);
            render_board(w, mine_size);
        }
        else{
            w.mineField.set_difficulty(1);
            render_board(w, mine_size);
        }
    });

    difficultyMenu->addAction(easyAction);
    difficultyMenu->addAction(normalAction);
    difficultyMenu->addAction(hardAction);
    difficultyMenu->addAction(customAction);

    menuBar->addMenu(difficultyMenu);

    w.setMenuBar(menuBar);

    w.smiley = new QPushButton;

    w.mineField = MineField(w.mines_w, w.mines_h, w.num_active);

    w.setFixedSize(w.mineField.w * mine_size, w.mineField.h * mine_size);

    w.show();

    render_board(w, mine_size);

    return a.exec();
}

void render_board(QtMines & qtm, int mine_size){
    delete qtm.mineField.timer; //prevent multiple timers

    qtm.mineField = MineField(qtm.mineField.w, qtm.mineField.h, qtm.mineField.num_active);
    qtm.setCentralWidget(new QWidget);

    Rsrc r = Rsrc();

    QVBoxLayout* vLayout = new QVBoxLayout(qtm.centralWidget());

    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    QHBoxLayout* header = new QHBoxLayout;
    header->setSpacing(0);

    qtm.mineField.digitLeft = Digit();
    qtm.mineField.digitRight = Digit();

    qtm.mineField.digitRight.update(0, r);
    qtm.mineField.digitLeft.update(qtm.num_active, r);

    header->addWidget(qtm.mineField.digitLeft.d1);
    header->addWidget(qtm.mineField.digitLeft.d2);
    header->addWidget(qtm.mineField.digitLeft.d3);


    qtm.smiley->setIcon(r.face[0]);
    header->addWidget(qtm.smiley);

    QObject::connect(qtm.smiley, &QPushButton::clicked, [=, &qtm]() {
        qtm.mineField.reset();
    });

    header->addWidget(qtm.mineField.digitRight.d1);
    header->addWidget(qtm.mineField.digitRight.d2);
    header->addWidget(qtm.mineField.digitRight.d3);

    qtm.mineField.digitLeft.d1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.mineField.digitLeft.d2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.mineField.digitLeft.d3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.mineField.digitRight.d1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.mineField.digitRight.d2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    qtm.mineField.digitRight.d3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    qtm.smiley->setFlat(true);
    qtm.mineField.smiley = qtm.smiley;
    vLayout->addLayout(header);

    qtm.mineField.timer->setInterval(1000);

    QObject::connect(qtm.mineField.timer, &QTimer::timeout, [&](){
        qtm.mineField.digitRight.update((++qtm.mineField.time) % 999, Rsrc());
    });

    qtm.mineField.timer->start();

    for (int i = 0; i < qtm.mineField.h; i++) {
        QHBoxLayout* hLayout = new QHBoxLayout;
        hLayout->setContentsMargins(0, 0, 0, 0);
        hLayout->setSpacing(0);
        for (int j = 0; j < qtm.mineField.w; j++) {
            Mine* mine = new Mine;
            qtm.mineField.buttons.push_back(mine);
            //QString name = QString("a");
            //btn->setText(name);
            mine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            mine->setIcon(r.buttons[0]);
            mine->setStyleSheet("QPushButton { border: 1px solid black;}"
                                "QPushButton:hover { background-color: yellow; border-color: rgba(0, 0, 0, 0.2);}");
            mine->setFlat(true);

            mine->setIconSize(QSize(mine_size, mine_size));

            hLayout->addWidget(mine);

            QObject::connect(mine, &Mine::leftClicked, [&qtm, j, i]() {
                if(qtm.mineField.clicked_spaces[qtm.mineField.w * i + j]){ //block already clicked buttons
                    return;
                }

                if(qtm.mineField.flags[qtm.mineField.w * i + j]){ //block flagged buttons
                    return;
                }

                qtm.mineField.field_click(j, i);
            });

            QObject::connect(mine, &Mine::rightClicked, [&qtm, j, i]() {
                if(qtm.mineField.clicked_spaces[qtm.mineField.w * i + j]){
                    return;
                }

                qtm.mineField.update_flag(j, i);
            });
        }

        vLayout->addLayout(hLayout);
    }

    qtm.centralWidget()->setLayout(vLayout);
    qtm.setFixedSize(qtm.mineField.w * mine_size, qtm.mineField.h * mine_size);
}
