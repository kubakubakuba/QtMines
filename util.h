#include <algorithm>
#include <QPixmap>
#include <QLabel>

#ifndef UTIL_H
#define UTIL_H

/* Class containing all resource images for the projet. */
class Rsrc{
public:
    std::vector<QPixmap> digits;
    std::vector<QPixmap> buttons;
    std::vector<QPixmap> face;

    Rsrc(){
        for(int i = 0; i <= 9; ++i){
            digits.push_back(QPixmap(QString(":/assets/digit%1.png").arg(i)));
        }
        digits.push_back(QPixmap(":/assets/digit-.png"));

        for(int i = 0; i <= 8; ++i){
            buttons.push_back(QPixmap(QString(":/assets/%1.png").arg(i)));
        }
        buttons.push_back(QPixmap(":/assets/flag.png"));
        buttons.push_back(QPixmap(":/assets/mine.png"));
        buttons.push_back(QPixmap(":/assets/mine-death.png"));
        buttons.push_back(QPixmap(":/assets/misflagged.png"));

        face.push_back(QPixmap(":/assets/smile.png"));
        face.push_back(QPixmap(":/assets/dead.png"));
        face.push_back(QPixmap(":/assets/win.png"));
    }

};

/* Class for rendering 3-wide 7 segment displays. */
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

    /* Re-renders the display by changing the digit images. */
    void update(int num, Rsrc r){
        if(num < 0){
            num = - num;
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
