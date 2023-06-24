#include <iostream>
#include <algorithm>
#include <QPushButton>
#include "util.h"

#ifndef MINEFIELD_H
#define MINEFIELD_H

class MineField{
public:
    int w, h, num_active;
    std::vector<int> data;
    std::vector<QPushButton*> buttons;
    Rsrc rsrc;
    QPushButton *smiley;

    bool mines_set = false;
    bool lost = false;
    bool win = false;

    MineField(){}

    MineField(int w, int h, int num_active){
        this->w = w;
        this->h = h;
        this->rsrc = Rsrc();
        this->num_active = num_active;
    }

    int operator () (int x, int y) const{
        return data[y * w + x];
    }

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

                        int ni = i + di; //neighbour i
                        int nj = j + dj; //neighbour j

                        if (ni >= 0 && ni < h && nj >= 0 && nj < w && data[ni * w + nj] == -1) { //is in range
                            sum++;
                        }
                    }
                }

                data[i * w + j] = sum;
            }
        }

        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                std::cout << data[i * w + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void set_mines(int x, int y, int num_mines){
        for(int i = 0; i < w*h; ++i){
            data.push_back(i < num_mines ? -1 : 0);
        }

        std::random_shuffle(data.begin(), data.end());
        while(data[y*w+x] != 0){
            std::random_shuffle(data.begin(), data.end());
        }

        calculate_field();

        this->field_click(x, y);
    }

    void field_click(int x, int y){
        if(!mines_set){
            mines_set = true;
            set_mines(x, y, num_active);
            buttons[y * w + x]->setDisabled(true);
            return;
        }

        if(!buttons[y * w + x]->isEnabled()){
            return;
        }

        if(data[y * w + x] == 0){
            buttons[y * w + x]->setDisabled(true);
            if (data[y * w + x] == 0) {
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) { //skip self
                            continue;
                        }

                        int nx = x + dj;
                        int ny = y + di;

                        if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                            field_click(nx, ny);
                        }
                    }
                }
            }
        }

        else if(data[y * w + x] == -1){
            buttons[y * w + x]->setDisabled(true);
            buttons[y * w + x]->setIcon(rsrc.buttons[11]);

            if(lost){
                return;
            }

            lost = true;

            for(int i = 0; i < h; ++i){
                for(int j = 0; j < w; ++j){
                    if(buttons[i * w + j]->isEnabled()){
                        buttons[i * w + j]->setEnabled(false);
                        buttons[i * w + j]->setIcon(data[i * w + j] >= 0 ? rsrc.buttons[data[i * w + j]] : rsrc.buttons[10]);
                    }
                }
            }

            smiley->setIcon(rsrc.face[1]);
        }

        else{
            buttons[y * w + x]->setDisabled(true);
            buttons[y * w + x]->setIcon(rsrc.buttons[data[y * w + x]]);
        }
    }


private:

};

#endif // MINEFIELD_H
