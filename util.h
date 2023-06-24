#include <algorithm>
#include <QPixmap>
#include <QLabel>

#ifndef UTIL_H
#define UTIL_H

class Rsrc{
public:
    std::vector<QPixmap> digits;
    std::vector<QPixmap> buttons;
    std::vector<QPixmap> face;

    Rsrc(){
        digits.push_back(QPixmap(":/assets/digit0.png"));
        digits.push_back(QPixmap(":/assets/digit1.png"));
        digits.push_back(QPixmap(":/assets/digit2.png"));
        digits.push_back(QPixmap(":/assets/digit3.png"));
        digits.push_back(QPixmap(":/assets/digit4.png"));
        digits.push_back(QPixmap(":/assets/digit5.png"));
        digits.push_back(QPixmap(":/assets/digit6.png"));
        digits.push_back(QPixmap(":/assets/digit7.png"));
        digits.push_back(QPixmap(":/assets/digit8.png"));
        digits.push_back(QPixmap(":/assets/digit9.png"));
        digits.push_back(QPixmap(":/assets/digit-.png"));

        buttons.push_back(QPixmap(":/assets/0.png"));
        buttons.push_back(QPixmap(":/assets/1.png"));
        buttons.push_back(QPixmap(":/assets/2.png"));
        buttons.push_back(QPixmap(":/assets/3.png"));
        buttons.push_back(QPixmap(":/assets/4.png"));
        buttons.push_back(QPixmap(":/assets/5.png"));
        buttons.push_back(QPixmap(":/assets/6.png"));
        buttons.push_back(QPixmap(":/assets/7.png"));
        buttons.push_back(QPixmap(":/assets/8.png"));
        buttons.push_back(QPixmap(":/assets/flag.png"));
        buttons.push_back(QPixmap(":/assets/mine.png"));
        buttons.push_back(QPixmap(":/assets/mine-death.png"));
        buttons.push_back(QPixmap(":/assets/misflagged.png"));

        face.push_back(QPixmap(":/assets/smile.png"));
        face.push_back(QPixmap(":/assets/dead.png"));
    }

};

class Digit{
public:
    QLabel *d1;
    QLabel *d2;
    QLabel *d3;

    Digit(){
        d1 = new QLabel;
        d2 = new QLabel;
        d3 = new QLabel;

        d1->setPixmap(QPixmap(":/assets/0.png"));
        d2->setPixmap(QPixmap(":/assets/0.png"));
        d3->setPixmap(QPixmap(":/assets/0.png"));
    }

    void update(int num, Rsrc r){
        if(num < 0){
            d1->setPixmap(r.digits[10]);
            d2->setPixmap(r.digits[(num / 10) % 10]);
            d3->setPixmap(r.digits[num % 10]);
        }
        else{
            d1->setPixmap(r.digits[(num / 100) % 100]);
            d2->setPixmap(r.digits[(num / 10) % 10]);
            d3->setPixmap(r.digits[num % 10]);
        }
    }
};
#endif // UTIL_H
