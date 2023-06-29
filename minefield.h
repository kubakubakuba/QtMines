#include <iostream>
#include <algorithm>
#include <QPushButton>
#include <QTimer>
#include <Mine.h>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>
#include <random>
#include <chrono>
#include "util.h"

#ifndef MINEFIELD_H
#define MINEFIELD_H

class MineField{
public:
    int w, h, num_active;
    std::vector<int> data;
    std::vector<Mine*> buttons;
    std::vector<int> flags;
    std::vector<int> clicked_spaces;
    Rsrc rsrc;
    QPushButton *smiley;
    QTimer* timer;
    Digit digitLeft, digitRight;
    int time = 0;

    bool mines_set = false;
    bool lost = false;
    bool win = false;

    MineField(){}

    MineField(int w, int h, int num_active){
        this->w = w;
        this->h = h;
        this->rsrc = Rsrc();
        this->num_active = num_active;
        this->flags = std::vector<int>(w*h, 0);
        this->clicked_spaces = std::vector<int>(w*h, 0);
        this->data = std::vector<int>(w*h, 0);
        this->timer = new QTimer();
    }

    int operator () (int x, int y) const{
        return data[y * w + x];
    }

    /* Resets the game to the initial state. */
    void reset(){
        win = false;
        lost = false;
        flags = std::vector<int>(w *h, 0);
        mines_set = false;

        for(auto b : buttons){
            b->setIcon(rsrc.buttons[0]);
            b->setStyleSheet("QPushButton { border: 1px solid black; }"
                             "QPushButton:hover { background-color: yellow; }");
        }

        clicked_spaces = std::vector<int>(w*h, 0);

        smiley->setIcon(rsrc.face[0]);

        time = 0;
        digitRight.update(0, rsrc);

        digitLeft.update(num_active, rsrc);

        timer->start();
    }

    /* Sets difficulty to the selected level. */
    void set_difficulty(int diff){
        switch(diff){
        case 0:
            num_active = 10;
            w = 9;
            h = 9;
            break;
        case 1:
            num_active = 40;
            w = 16;
            h = 16;
            break;
        case 2:
            num_active = 99;
            w = 30;
            h = 16;
            break;
        case 3:
            num_active = 10;
            w = 10;
            h = 10;
            break;
        }

        reset();
    }

    /* Overload for custom difficulty. */
    void set_difficulty(int x, int y, int m){
        w = x;
        h = y;

        num_active = std::min(x * y - 1, m); //the maximum amount of mines can be x*y - 1

        reset();
    }

    /* Function that calculates the number of mines in each spaces (from adjacent mines). */
    void calculate_field(){
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                int sum = 0;
                if(data[i * w + j] == -1){ //skip mines
                    continue;
                }

                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) { //skip self
                            continue;
                        }

                        int new_i = i + di; //neighbour i
                        int new_j = j + dj; //neighbour j

                        if (new_i >= 0 && new_i < h && new_j >= 0 && new_j < w && data[new_i * w + new_j] == -1) { //is in range
                            sum++;
                        }
                    }
                }

                data[i * w + j] = sum;
            }
        }
    }

    /* Function that fills the minefield with the specified amount of mines, then randomizes the field so the entry-point
     * space is not a mine and invokes a click method on that field.
    */
    void set_mines(int x, int y, int num_mines){
        data = std::vector<int>();
        for(int i = 0; i < w*h; ++i){
            data.push_back(i < num_mines ? -1 : 0);
        }

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);

        std::shuffle(data.begin(), data.end(), rng);
        while(data[y*w+x] != 0){
            std::shuffle(data.begin(), data.end(), rng);
        }

        calculate_field();

        this->field_click(x, y);
    }

    /* Clicks on a mine. */
    void field_click(int x, int y){
        if(!mines_set){ //execute only once at the start of the game
            mines_set = true;
            set_mines(x, y, num_active);

            buttons[y * w + x]->setStyleSheet("QPushButton { border: none; }"
                                "QPushButton:hover { background-color: none; }");
            clicked_spaces[y * w + x] = 1;

            return;
        }

        if(clicked_spaces[y * w + x]){
            return;
        }

        if(data[y * w + x] == 0){ //recursively click on mines
            buttons[y * w + x]->setStyleSheet("QPushButton { border: none; }"
                                              "QPushButton:hover { background-color: none; }");
            clicked_spaces[y * w + x] = 1;
            if (data[y * w + x] == 0) {
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int new_x = x + j;
                        int new_y = y + i;

                        if (i == 0 && j == 0) { //skip self
                            continue;
                        }

                        if (new_x >= 0 && new_x < w && new_y >= 0 && new_y < h){
                            flags[y * w + x] = 0;
                            update_flag_count();

                            buttons[y * w + x]->setIcon(rsrc.buttons[0]);
                            field_click(new_x, new_y);
                        }
                    }
                }
            }

            if(check_win()){
                disable_all();
                smiley->setIcon(rsrc.face[2]);
            }
        }

        else if(data[y * w + x] == -1){
            buttons[y * w + x]->setStyleSheet("QPushButton { border: none; }"
                                              "QPushButton:hover { background-color: none; }");
            clicked_spaces[y * w + x] = 1;
            buttons[y * w + x]->setIcon(rsrc.buttons[11]);

            if(lost){
                return;
            }

            lost = true;

            disable_all();

            smiley->setIcon(rsrc.face[1]);
        }

        else{
            buttons[y * w + x]->setStyleSheet("QPushButton { border: none; }"
                                              "QPushButton:hover { background-color: none; }");
            clicked_spaces[y * w + x] = 1;

            flags[y * w + x] = 0;
            update_flag_count();

            buttons[y * w + x]->setIcon(rsrc.buttons[data[y * w + x]]);

            if(check_win()){
                disable_all();
                smiley->setIcon(rsrc.face[2]);
            }
        }
    }

    /* Check if all mines have been flagged correctly, if yes, win the game. */
    bool check_win(){
        int sum = 0;
        int flag_sum = 0;
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                flag_sum += flags[i * w + j] * data[i * w + j]; //only count flag spaces
                sum += clicked_spaces[i * w + j]; //count all clicked spaces
            }
        }

        return (sum == w * h - num_active) && (flag_sum == -num_active);
    }

    /* Function that destructively disables all spaces, so they are not clickable. */
    void disable_all(){
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                if(!clicked_spaces[i * w + j]){
                    clicked_spaces[i * w + j] = 1;
                    buttons[i * w + j]->setStyleSheet("QPushButton { border: none; }"
                                                      "QPushButton:hover { background-color: none; }");
                    buttons[i * w + j]->setIcon(data[i * w + j] >= 0 ? rsrc.buttons[data[i * w + j]] : rsrc.buttons[10]);

                    if((data[i * w + j] != -1) && flags[i * w + j]){ //misflagged
                        buttons[i * w + j]->setStyleSheet("QPushButton { border: none; }"
                                                          "QPushButton:hover { background-color: none; }");
                        buttons[i * w + j]->setIcon(rsrc.buttons[12]);
                    }
                }
            }
        }

        timer->stop();
    }

    /* Draws a flag icon atop of a mine (right click). */
    void draw_flag(int x, int y){
        buttons[y * w + x]->setIcon(flags[y * w + x] ? rsrc.buttons[9] : rsrc.buttons[0]);
    }

    /* Updates the left mine counter. */
    void update_flag_count(){
        int sum = 0;
        for(auto f : flags){ sum += f; }

        digitLeft.update(num_active - sum, rsrc);
    }

    /* Updates the flag on certain position. */
    void update_flag(int x, int y){
        flags[y * w + x] = !flags[y * w + x];

        draw_flag(x, y);

        update_flag_count();

        if(check_win()){
            disable_all();
            smiley->setIcon(rsrc.face[2]);
        }
    }


private:

};

#endif // MINEFIELD_H
