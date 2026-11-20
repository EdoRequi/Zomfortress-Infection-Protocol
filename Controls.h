#ifndef CONTROLS_H_INCLUDED
#define CONTROLS_H_INCLUDED
#pragma once
#include "Gamelogic.h"
#include <conio.h>
#include <iostream>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
enum Strzalka{
    NOTARROW,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
void wyczyscBufor();
struct Klawisz{
    char znak;
    Strzalka arrow;
    Klawisz(char z=' ',Strzalka ar=NOTARROW):znak(z),arrow(ar){}
    void PressK(){
            char one=_getch();
            if(one==0||one==-32){
                char two=_getch();
                switch (two){
                    case KEY_UP: arrow=UP; break;
                    case KEY_DOWN: arrow=DOWN; break;
                    case KEY_LEFT: arrow=LEFT; break;
                    case KEY_RIGHT: arrow=RIGHT; break;
                    default: arrow= NOTARROW; break;
                }
                znak=' ';
            }
            else{
                znak=one; arrow=NOTARROW;
            }
        wyczyscBufor();
    }
    virtual ~Klawisz()=default;
};
void configureConsoleInput();
#endif // CONTROLS_H_INCLUDED
