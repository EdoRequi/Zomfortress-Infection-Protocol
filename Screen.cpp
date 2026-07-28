#include <cstdlib>
#include <iostream>
#include <thread>
#include <string>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <sstream>
#include "Screen.h"
using TP=TypPostaci;
int w=15,k=100,i=0,j=0;
int wskazany=1;
char strzalka (int wskazany,int w,int i,int j,int liczba_wrogow)
{
    if (i == w - 8) {
        int pozycje[] = {46,56,66,76,86};
        if (wskazany >= 1 && wskazany <= liczba_wrogow && j == pozycje[wskazany - 1]&&wybor) {
            koloruj(4,7);
            return 'V';
        }
    }
    return ' ';
}
char efekt_napis(Gamecontent &Gc,Character* &cel, int w,int i,int j){
    if(cel!=nullptr){
        if (Gc.SE.r==ScreenEfekt::CRITICAL){
                koloruj(10,8);
            switch(cel->typ){
            case GRACZ:{
                    int relI=i-(w-9);
                    switch(relI){
                        case 0:{
                            switch(j){
                                case 6: return 'C';
                                case 7: return 'R';
                                case 8: return 'I';
                                case 9: return 'T';
                                case 10: return 'I';
                                case 11: return 'C';
                                case 12: return 'A';
                                case 13: return 'L';
                                default: return ' ';
                                }
                            }
                            case 1:{
                                switch(j){
                                    case 7: return 'H';
                                    case 8: return 'I';
                                    case 9: return 'T';
                                    case 10: return '!';
                                    case 11: return '!';
                                    case 12: return '!';
                                    default: return ' ';
                                }
                            }
                            default: return ' ';

                        }
                break;}
                default:
                {
                    for(size_t idx=0;idx<Gc.enemies.size();idx++){
                    const vector<Character*> wrogowie=static_cast<const vector<Character*>>(Gc.enemies);
                    int basepos_J=37+Gc.wskazany*10;
                    if (j<basepos_J||j>basepos_J+8) continue;
                    int relJ=j-basepos_J;
                    int relI=i-(w-9);
                    koloruj(10,8);
                    switch (relI){
                        case 0:
                        switch(relJ){
                            case 0: return 'C';
                            case 1: return 'R';
                            case 2: return 'I';
                            case 3: return 'T';
                            case 4: return 'I';
                            case 5: return 'C';
                            case 6: return 'A';
                            case 7: return 'L';
                            default: return ' ';
                        }
                        case 1:
                        switch(relJ){
                            case 1: return 'H';
                            case 2: return 'I';
                            case 3: return 'T';
                            case 4: return '!';
                            case 5: return '!';
                            case 6: return '!';
                            default: return ' ';
                            }
                         default: return ' ';
                        }
                    }
                    break;}
           }
    return ' ';}}return ' ';
}
char rysujgracza(int w, int i, int j,Gamecontent &Gc)
{
    if (Gc.gracz.Imie=="DemomanTF2"){
       switch (kodscreen){
           case 2:{
            if(i==w-10){
                    switch(j)
                    {
                        case 11:
                            koloruj(0,7);
                            return '^';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
               else if(i==w-9){
                    switch(j)
                    {
                        case 10:
                        case 12:
                            koloruj(0,7);
                            return '|';
                            break;
                        case 11:
                            koloruj(15,7);
                            return (char)177;
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
               else if(i==w-8){
                    switch(j)
                    {
                        case 10:
                        case 12:
                            koloruj(0,7);
                            return '|';
                            break;
                        case 11:
                            koloruj(15,7);
                            return (char)177;
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-7){
                    switch(j)
                    {
                        case 10:
                        case 12:
                            koloruj(0,7);
                            return '|';
                            break;
                        case 11:
                            koloruj(15,7);
                            return (char)177;
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-6){
                    switch(j)
                    {
                        case 6:
                            koloruj(4,8);
                            return 'O';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '_';
                            break;
                        case 8:
                            koloruj(15,8);
                            return '_';
                            break;
                        case 9:
                            koloruj(4,8);
                            return '_';
                            break;
                        case 10:
                        case 11:
                        case 12:
                            koloruj(7,8);
                            return '-';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        case 11:
                            koloruj(6,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {
                        case 4:
                            koloruj(15,8);
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 6:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                        case 4:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 8:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
                }
            case 3:{
                if(i==w-8){
                    switch(j)
                    {
                        case 11 ... 13:
                            koloruj(0,8);
                            return '_';
                            break;
                        case 14:
                            koloruj(7,8);
                            return 'L';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-7){
                    switch(j)
                    {
                        case 11 ... 14:
                            koloruj(0,7);
                            return '_';
                            break;
                        case 10:
                            koloruj(0,7);
                            return '[';
                            break;
                        case 15:
                            koloruj(0,7);
                            return ']';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-6){
                    switch(j)
                    {
                        case 6:
                            koloruj(4,8);
                            return 'O';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '_';
                            break;
                        case 8:
                            koloruj(15,8);
                            return '_';
                            break;
                        case 9:
                            koloruj(4,8);
                            return '_';
                            break;
                        case 10:
                            koloruj(6,8);
                            return '|';
                            break;
                        case 13:
                            koloruj(0,2);
                            return '|';
                            break;
                        case 15:
                            koloruj(6,8);
                            return '|';
                            break;
                        case 12:
                            koloruj(0,2);
                            return 'E';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {
                        case 4:
                            koloruj(15,8);
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 6:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                        case 4:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 8:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
                }
            case 4:{
               if(i==w-9){
                    switch(j)
                    {
                        case 20:
                        case 21:
                            koloruj(0,8);
                            return '_';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
               else if(i==w-8){
                    switch(j)
                    {
                        case 19:
                        case 22:
                            koloruj(0,8);
                            return '!';
                            break;
                        case 20:
                        case 21:
                            koloruj(0,2);
                            return '_';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-7){
                    switch(j)
                    {
                        case 20:
                        case 21:
                            koloruj(6,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-6){
                    switch(j)
                    {
                    case 10 ... 14:
                        return '_';
                        break;
                        case 16:
                            koloruj(4,8);
                            return 'O';
                            break;
                        case 17:
                            koloruj(12,8);
                            return '_';
                            break;
                        case 18:
                            koloruj(15,8);
                            return '_';
                            break;
                        case 19:
                            koloruj(4,8);
                            return '_';
                            break;
                        case 20 ... 21:
                            koloruj(6,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 11 ... 14:
                            return '_';
                            break;
                        case 15:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 16:
                            koloruj(0,8);
                            return '|';
                            break;
                        case 20:
                        case 21:
                            koloruj(2,8);
                            return '-';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {
                        case 9 ... 12:
                            return '_';
                            break;
                        case 14:
                            koloruj(15,8);
                            return '/';
                            break;
                        case 16:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 11 ... 14:
                            return '_';
                            break;
                        case 16:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 10 ... 14:
                            return '_';
                            break;
                        case 15:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 17:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                        case 10 ... 13:
                            return '_';
                            break;
                        case 14:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 18:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
                }
            case 5:
            case 11:
            case 17:
                {
                if(i==w-12){
                    switch(j)
                    {
                        case 20:
                            koloruj(0,8);
                            return '_';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-11){
                    switch(j)
                    {
                        case 19:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 20:
                            koloruj(15,2);
                            return 'H';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-7){
                    switch(j)
                    {
                        case 8:
                            koloruj(15,8);
                            return '/';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-6){
                    switch(j)
                    {
                        case 6:
                            koloruj(4,8);
                            return 'O';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '/';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {

                        case 4:
                            koloruj(15,8);
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 6:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                        case 4:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 8:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
            }
            case 8:
            case 14:
                { // kiedy dzialko lub zasobnik
            if(i==w-10){
                    switch(j)
                    {
                     case 38:
                         koloruj(0,7);
                            return '^';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
               else if(i==w-9){
                    switch(j)
                    {
                        case 37:
                        case 39:
                            koloruj(0,7);
                            return '|';
                            break;
                        case 38:
                            koloruj(7,7);
                            return ' ';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
               else if(i==w-8){
                    switch(j)
                    {
                        case 37:
                        case 39:
                            koloruj(0,7);
                            return '|';
                            break;
                        case 38:
                            koloruj(7,7);
                            return ' ';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-7){
                    switch(j)
                    {
                        case 37:
                        case 39:
                            koloruj(0,7);
                            return '|';
                            break;
                        case 38:
                            koloruj(7,7);
                            return ' ';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-6){
                    switch(j)
                    {
                        case 33:
                            koloruj(4,8);
                            return 'O';
                            break;
                        case 34:
                            koloruj(12,8);
                            return '_';
                            break;
                        case 35:
                            koloruj(15,8);
                            return '_';
                            break;
                        case 36:
                            koloruj(4,8);
                            return '_';
                            break;
                        case 37:
                        case 38:
                        case 39:
                            koloruj(7,8);
                            return '-';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 32:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 33:
                            koloruj(0,8);
                            return '|';
                            break;
                        case 38:
                            koloruj(6,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {
                        case 31:
                            koloruj(15,8);
                            return '/';
                            break;
                        case 33:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 33:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 32:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 34:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                        case 31:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 35:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
                case 9:
                case 15:
                    { // kiedy dzialko lub zasobnik
                if(i==w-8){
                    switch(j)
                    {
                        case 8 ... 10:
                            koloruj(0,8);
                            return '_';
                            break;
                        case 11:
                            koloruj(7,8);
                            return 'L';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-7){
                    switch(j)
                    {
                        case 8 ... 11:
                            koloruj(0,7);
                            return '_';
                            break;
                        case 7:
                            koloruj(0,7);
                            return '[';
                            break;
                        case 12:
                            koloruj(0,7);
                            return ']';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-6){
                    switch(j)
                    {
                        case 3:
                            koloruj(4,8);
                            return 'O';
                            break;
                        case 4:
                            koloruj(12,8);
                            return '_';
                            break;
                        case 5:
                            koloruj(15,8);
                            return '_';
                            break;
                        case 6:
                            koloruj(4,8);
                            return '_';
                            break;
                        case 7:
                            koloruj(6,8);
                            return '|';
                            break;
                        case 10:
                            koloruj(0,3);
                            return '|';
                            break;
                        case 12:
                            koloruj(6,8);
                            return '|';
                            break;
                        case 9:
                            koloruj(0,3);
                            return 'E';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 2:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 3:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {
                        case 1:
                            koloruj(15,8);
                            return '/';
                            break;
                        case 3:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 3:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 2:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 4:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                        case 1:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 5:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
                }
                case 10:
                case 16:{ // kiedy dzialko lub zasobnik
                if(i==w-9){
                    switch(j)
                    {
                        case 37:
                        case 38:
                            koloruj(2,8);
                            return '_';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
               else if(i==w-8){
                    switch(j)
                    {
                    case 36:
                    case 39:
                        koloruj(0,8);
                        return '!';
                        break;
                    case 37:
                    case 38:
                        koloruj(0,2);
                        return '_';
                        break;
                    default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-7){
                    switch(j)
                    {
                        case 37:
                        case 38:
                            koloruj(6,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-6){
                    switch(j)
                    {
                        case 28 ... 30:
                            return '_';
                            break;
                        case 33:
                            koloruj(4,8);
                            return 'O';
                            break;
                        case 34:
                            koloruj(12,8);
                            return '_';
                            break;
                        case 35:
                            koloruj(15,8);
                            return '_';
                            break;
                        case 36:
                            koloruj(4,8);
                            return '_';
                            break;
                        case 37:
                        case 38:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;

                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 29 ... 31:
                            return '_';
                            break;
                        case 32:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 33:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {
                        case 28 ... 29:
                            return '_';
                            break;
                        case 31:
                            koloruj(15,8);
                            return '/';
                            break;
                        case 33:
                            koloruj(0,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 29 ... 31:
                            return '_';
                            break;
                        case 33:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 28 ... 31:
                            return '_';
                            break;
                        case 32:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 34:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                    case 28 ... 30:
                        return '_';
                        break;
                        case 31:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 35:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
                }
           default:{
                if(i==w-6){
                    switch(j)
                    {
                        case 6:
                            koloruj(4,8);
                            return 'O';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-5){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-4){
                    switch(j)
                    {
                        case 4:
                            return '/';
                            break;
                        case 6:
                            koloruj(0,8);
                            return '|';
                            break;
                        case 8:
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-3){
                    switch(j)
                    {
                        case 6:
                            koloruj(12,8);
                            return '|';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-2){
                    switch(j)
                    {
                        case 5:
                            koloruj(12,8);
                            return '/';
                            break;
                        case 7:
                            koloruj(12,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                else if(i==w-1){
                    switch(j)
                    {
                        case 4:
                            koloruj(0,8);
                            return '/';
                            break;
                        case 8:
                            koloruj(0,8);
                            return '\\';
                            break;
                        default:
                            return ' ';
                            break;
                    }
                }
                break;
            }
        }
    }
}
return ' ';
}
char rysuj_dzialko(int w,int i,int j,Gamecontent &Gc)
{
    if (!czyZyje(Gc.dzialko)) return ' ';
    if (kodscreen==6||kodscreen==7||kodscreen==8||kodscreen==9||kodscreen==10||kodscreen==11||kodscreen==22||kodscreen==23)
    {
        if (i==w-6){
            switch (j){
            case 13:
                koloruj(0,8);
                return '_';
                break;
            case 19 ... 25:
                koloruj(0,8);
                return '_';
                break;
            case 14 ... 18:
                koloruj(7,8);
                return (char)220;
                break;
            default:
                return ' ';
                break;

            }
        }
        else if (i==w-5){
            switch (j){
            case 12:
                koloruj(12,8);
                return '|';
                break;
            case 13 ... 17:
                koloruj(4,4);
                return (char)219;
                break;
            case 18:
                koloruj(0,4);
                return '|';
                break;
            case 19 ... 25:
                koloruj(8,0);
                return '=';
                break;
            case 26:
                koloruj(8,0);
                return ']';
                break;
            default:
                return ' ';
                break;
            }
        }
        else if (i==w-4){
            switch (j){
            case 12:
            case 21:
                koloruj(12,8);
                return '|';
                break;
            case 13 ... 19:
                koloruj(12,4);
                return '_';
                break;
            case 20:
                koloruj(12,0);
                return '_';
                break;
            default:
                return ' ';
                break;
            }
        }
        else if (i==w-3){
            switch (j){
            case 16: case 20:
                koloruj(0,0);
                return (char)219;
                break;
            case 19:
                koloruj(0,8);
                return '|';
                break;
            case 17:
                koloruj(0,8);
                return '\\';
                break;
            default:
                return ' ';
                break;
            }
        }
        else if (i==w-2){
            switch (j){
            case 18:
                koloruj(8,0);
                return '/';
                break;
            case 19:
                koloruj(8,0);
                return '|';
                break;
            case 17:
                koloruj(8,0);
                return '_';
                break;
            case 16:
                koloruj(0,8);
                return '_';
                break;
            default:
                return ' ';
                break;
            }
        }else if (i==w-1){
            switch (j){
            case 15:
                koloruj(0,8);
                return '/';
                break;
            case 19:
                koloruj(0,8);
                return '|';
                break;
            case 20 ... 21:
                koloruj(0,8);
                return '\\';
                break;
            default:
                return ' ';
                break;
            }
        }
    }
    return ' ';
}
char rysuj_zasobnik(int w,int i,int j,Gamecontent &Gc)
{
    if (!czyZyje(Gc.zasobnik)) return ' ';
    if (kodscreen==12||kodscreen==13||kodscreen==14||kodscreen==15||kodscreen==16||kodscreen==17||kodscreen==22||kodscreen==23)
    {
        if (i==w-6){
            switch (j){
            case 16 ... 22:
                koloruj(12,8);
                return '_';
                break;
            case 23:
                koloruj(0,8);
                return '_';
            default:
                return ' ';
                break;
            }
        }
        else if (i==w-5){
            switch (j){
            case 14:
                koloruj(15,8);
                return 'O';
                break;
            case 15:
            case 23:
                koloruj(12,8);
                return '|';
                break;
            case 16 ... 22:
                koloruj(0,4);
                return '_';
                break;
            case 24:
                koloruj(0,8);
                return '\\';
                break;
            default:
                return ' ';
                break;
            }
        }
        else if (i==w-4){
            switch (j){
            case 14:
                koloruj(0,8);
                return '-';
            case 15:
            case 23:
                koloruj(12,0);
                return '|';
                break;
            case 18:
                koloruj(15,12);
                return '\\';
                break;
            case 20:
                koloruj(15,12);
                return '/';
            case 24:
                koloruj(0,8);
                return '/';
                break;
            case 16: case 17: case 19: case 21: case 22:
                koloruj(12,12);
                return (char)219;
            default:
                return ' ';
                break;
            }
        }
        else if (i==w-3){
            switch (j){
            case 13:
                koloruj(14,8);
                return '|';
            case 15:
                koloruj(7,8);
                return '|';
            case 23:
                koloruj(12,8);
                return '|';
                break;
            case 16:
            case 17:
            case 18:
                koloruj(0,12);
                return '_';
            case 20:
            case 21:
            case 22:
                koloruj(15,12);
                return '_';
                break;
            case 19:
                koloruj(15,12);
                return 'V';
                break;
            case 24:
                koloruj(0,8);
                return '\\';
                break;
            case 14:
                koloruj(7,7);
                return (char)219;
            default:
                return ' ';
                break;
            }
        }
        else if (i==w-2){
            switch (j){
            case 13:
                koloruj(14,8);
                return '|';
            case 14:
                koloruj(14,14);
                return (char)219;
            case 15:
                koloruj(7,8);
                return '|';
            case 18:
                koloruj(8,0);
                return '|';
            case 23:
                koloruj(12,8);
                return '|';
            case 24:
                koloruj(0,8);
                return '|';
                break;
            case 17:
                koloruj(0,0);
                return (char)219;
            case 16:
                koloruj(12,0);
                return '.';
                break;
            case 19 ... 21:
            case 22:
                koloruj(8,0);
                return '=';
                break;
            default:
                return ' ';
                break;
            }
        }else if (i==w-1){
            switch (j){
            case 14:
                koloruj(7,8);
                return (char)200;
                break;
            case 15:
            case 23:
                koloruj(12,8);
                return '|';
                break;
            case 16 ... 22:
                koloruj(12,4);
                return '_';
                break;
                default:
                    return ' ';
                    break;
            }
        }
    }
    return ' ';
}
char aura(int w, int i, int j, int wskazany, vector<Character*> enemies, bool smigniecie)
    {
    if (i>=w-11&&i<=w-4&&(kodscreen==2||kodscreen==8||kodscreen==14)&&smigniecie==true)
    {
        switch (wskazany)
        {
        case 1:
            if (i==w-11){
                switch (j){
            case 21:
                koloruj(12,8);
                    return (char)177;
                case 38:
                case 39:
                case 40:
                    koloruj (12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                }
            }
            else if (i==w-10){
                    switch (j){
                case 39:
                case 41:
                    koloruj (12,8);
                    return (char)178;
                case 20:
                case 22:
                    koloruj (12,8);
                    return (char)177;
                    break;
                case 40:
                case 21:
                    koloruj(4,4);
                    return (char)219;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-9){
                    switch (j){
                case 34:
                case 40:
                    koloruj(12,8);
                    return (char)178;
                case 21:
                    koloruj(12,8);
                    return (char)177;
                    break;
                case 41:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 42:
                    koloruj(12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-8){
                    switch (j){
                case 35:
                case 40:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 41:
                case 42:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 43:
                    koloruj(12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-7){
                    switch (j){
                case 41:
                case 35:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 42:
                case 43:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 44:
                    koloruj(12,12);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-6){
                    switch (j){
                case 40:
                case 33:
                case 34:
                    koloruj(12,8);
                    return (char)178;
                break;
                case 41:
                case 42:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 43:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 44:
                    koloruj(0,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-5){
                    switch (j){
                case 39:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 40:
                case 41:
                    koloruj(4,4);
                    return (char)219;
                    break;
                case 42:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 43:
                    koloruj(0,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-4){
                    switch (j){
                case 38:
                case 40:
                case 39:
                    koloruj (12,8);
                    return (char)178;
                    break;
                case 41:
                case 42:
                    koloruj(0,8);
                    return (char)178;
                    break;
                //case 39:
                    //koloruj(4,4);
                    //return (char)219;
                    //break;
                default:
                    return ' ';
                    break;
                    }
                }
                else return ' ';
            break;
            case 2:
            if (i==w-11){
                switch (j){
            case 21:
                koloruj(12,8);
                    return (char)177;
                case 48:
                case 49:
                case 50:
                    koloruj (12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                }
            }
            else if (i==w-10){
                    switch (j){
                case 49:
                case 51:
                    koloruj (12,8);
                    return (char)178;
                case 20:
                case 22:
                    koloruj (12,8);
                    return (char)177;
                    break;
                case 50:
                case 21:
                    koloruj(4,4);
                    return (char)219;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-9){
                    switch (j){
                case 44:
                case 50:
                    koloruj(12,8);
                    return (char)178;
                case 21:
                    koloruj(12,8);
                    return (char)177;
                    break;
                case 51:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 52:
                    koloruj(12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-8){
                    switch (j){
                case 45:
                case 50:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 51:
                case 52:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 53:
                    koloruj(12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-7){
                    switch (j){
                case 51:
                case 45:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 52:
                case 53:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 54:
                    koloruj(12,12);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-6){
                    switch (j){
                case 50:
                case 43:
                case 44:
                    koloruj(12,8);
                    return (char)178;
                break;
                case 51:
                case 52:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 53:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 54:
                    koloruj(0,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-5){
                    switch (j){
                case 49:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 50:
                case 51:
                    koloruj(4,4);
                    return (char)219;
                    break;
                case 52:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 53:
                    koloruj(0,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-4){
                    switch (j){
                case 48:
                case 50:
                case 49:
                    koloruj (12,8);
                    return (char)178;
                    break;
                case 51:
                case 52:
                    koloruj(0,8);
                    return (char)178;
                    break;
                //case 39:
                    //koloruj(4,4);
                    //return (char)219;
                    //break;
                default:
                    return ' ';
                    break;
                    }
                }
                else return ' ';
            break;
            case 3:
            if (i==w-11){
                switch (j){
            case 21:
                koloruj(12,8);
                    return (char)177;
                case 58:
                case 59:
                case 60:
                    koloruj (12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                }
            }
            else if (i==w-10){
                    switch (j){
                case 59:
                case 61:
                    koloruj (12,8);
                    return (char)178;
                case 20:
                case 22:
                    koloruj (12,8);
                    return (char)177;
                    break;
                case 60:
                case 21:
                    koloruj(4,4);
                    return (char)219;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-9){
                    switch (j){
                case 54:
                case 60:
                    koloruj(12,8);
                    return (char)178;
                case 21:
                    koloruj(12,8);
                    return (char)177;
                    break;
                case 61:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 62:
                    koloruj(12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-8){
                    switch (j){
                case 55:
                case 60:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 61:
                case 62:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 63:
                    koloruj(12,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-7){
                    switch (j){
                case 61:
                case 55:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 62:
                case 63:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 64:
                    koloruj(12,12);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-6){
                    switch (j){
                case 60:
                case 53:
                case 54:
                    koloruj(12,8);
                    return (char)178;
                break;
                case 61:
                case 62:
                    koloruj (4,4);
                    return (char)219;
                    break;
                case 63:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 64:
                    koloruj(0,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-5){
                    switch (j){
                case 59:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 60:
                case 61:
                    koloruj(4,4);
                    return (char)219;
                    break;
                case 62:
                    koloruj(12,8);
                    return (char)178;
                    break;
                case 63:
                    koloruj(0,8);
                    return (char)178;
                    break;
                default:
                    return ' ';
                    break;
                    }
                }
                else if (i==w-4){
                    switch (j){
                case 58:
                case 60:
                case 59:
                    koloruj (12,8);
                    return (char)178;
                    break;
                case 61:
                case 62:
                    koloruj(0,8);
                    return (char)178;
                    break;
                //case 39:
                    //koloruj(4,4);
                    //return (char)219;
                    //break;
                default:
                    return ' ';
                    break;
                    }
                }
                else return ' ';
            break;
        default:
            return ' ';
            break;
        }
    }
    return ' ';
}
char vomit(int w, int i, int j, int wskazany, vector<Character*> &enemies)// YOU ARE WALKING VOMIT!!!
{
    if(kodscreen==22)
    {
        for(size_t idx=0;idx<enemies.size();++idx){
                if (idx+1==wskazany){
                Character* wrog=enemies[idx];
            int basepos_J=33+idx*10;
            if (j<basepos_J||j>basepos_J+12) continue;
             // Rysowanie zalezne od pozycji i (wiersza) i j (kolumny)
            int relJ=j-basepos_J;
            int relI=i-(w-11);
            if(relI<=i-(w-6)) continue;
            if (!czyZyje(*wrog)||wrog->Imie!="Toksyczny Zombie") return ' ';
            switch(relI){
                case 0:{
                    switch(relJ){
                    case 1:case 2:case 4:case 5:case 6: koloruj(14,14);return (char)219;
                    case 3: koloruj(10,14);return (char)176;
                    case 8: koloruj(14,8);return (char)176;
                    default: return ' ';
                    }
                    break;}
                case 1:{
                    switch(relJ){
                    case 0: koloruj(14,14);return (char)219;
                    case 1:case 2:koloruj (10,2);return (char)178;
                    case 3:case 4:case 5:case 6:case 7: koloruj(2,10);return (char)177;
                    case 8: koloruj(14,14);return (char)219;
                    case 9: koloruj(14,8);return (char)177;
                    default: return ' ';
                    }
                    break;}
                case 2:{
                    switch(relJ){
                    case 1:case 2:case 3: koloruj(14,14);return (char)219;
                    case 4:case 5: koloruj(2,14);return(char)177;
                    case 6:case 7:case 8:case 9: koloruj(2,10);return (char)177;
                    case 10: koloruj(14,14);return (char)219;
                    case 12: koloruj(14,8);return (char)177;
                    default: return ' ';
                    }
                    break;}
                case 3:{
                    switch(relJ){
                    case 5: koloruj(14,8);return (char)176;
                    case 6:case 7:case 11: koloruj(2,14);return (char)176;
                    case 8:case 9:case 10: koloruj(2,10);return (char)177;
                    default: return ' ';
                    }
                    break;}
                case 4:{
                    switch(relJ){
                    case 8:case 12: koloruj(14,14);return (char)219;
                    case 11:case 9: case 10: koloruj(2,10);return (char)177;
                    default: return ' ';
                    }
                    break;}
                case 5:{
                    switch(relJ){
                    case 10: koloruj(14,14);return (char)219;
                    case 11:case 12: koloruj(2,10);return (char)177;
                    default: return ' ';
                    }
                    break;}
                default: return ' ';
                }
            }
        }
        }

    return ' ';
}
char bomby(int w,int i,int j,short e,int wskazany,vector<Character*> enemies)
{
    koloruj(12,8);
    if (i==w-1&&(kodscreen==3||kodscreen==9||kodscreen==15))
    {
        for(Character* wrog:enemies){
            if (!czyZyje(*wrog)==true) continue;
            int baseposJ=43+(wskazany-1)*10;
            int relJ=j-baseposJ;
            if(relJ<0||relJ>6) continue;
            switch(e){
                case 1:{
                    switch(relJ){
                        case 0: return 'o';
                        default: return ' ';
                    }
                    break;
                }
                case 2:{
                    switch(relJ){
                        case 0:case 4: return 'o';
                        default: return ' ';
                    }
                    break;
                }
                case 3:{
                    switch(relJ){
                        case 0:case 2:case 4: return 'o';
                        default: return ' ';
                    }
                    break;
                }
                case 4:{
                    switch(relJ){
                        case 0:case 2:case 4:case 6: return 'o';
                        default: return ' ';
                    }
                    break;
                }
                case 5:{
                    switch(relJ){
                        case 0:case 2:case 3:case 4:case 6: return 'o';
                        default: return ' ';
                    }
                    break;
                }
                default: return ' ';
            }
        }
    }
    return ' ';
}
char rysujwroga(int w, int i, int j,Gamecontent &Gc)
{
    if (kodscreen != 1 && kodscreen != 7 && kodscreen != 13)
    {
        for(size_t idx=0;idx<Gc.enemies.size();++idx){
                Character* wrog=Gc.enemies[idx];
        // Zakladamy, że kazdy wrog ma swoj przydzielony obszar (43 + idx*10)
        int basepos_J=43+idx*10;
        if (j<basepos_J||j>basepos_J+5) continue;
         // Rysowanie zalezne od pozycji i (wiersza) i j (kolumny)
        int relJ=j-basepos_J;
        int relI=i-(w-7);
        if (!czyZyje(*wrog)) return ' ';
        //mapowanie pozycji znakow (i,j)
        switch (relI){
            case 0:{
                switch (relJ){
                case 1:
                    if (wrog->typ==TP::NALADOWANY) koloruj (14,14);
                    else koloruj(8,8);
                    return (char)219;
                case 2:
                    if(wrog->typ==TP::COMMANDER) koloruj(2,8);
                    else koloruj(8,8);
                    return '_';
                case 3:
                    if (wrog->typ==TP::NALADOWANY) koloruj (14,14);
                    else if(wrog->typ==TP::COMMANDER) {koloruj(2,8); return (char)220; break;}
                    else koloruj(8,8);
                    return (char)219;
            default: return ' '; break;
                }
            break;}
        case 1:{
            switch(relJ){
                case 0:
                    if (wrog->typ==TP::ZWYKLY) koloruj(10,8);
                    else if (wrog->typ==TP::SZYBKI) koloruj(1,8);
                    else if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(2,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(2,14);
                    else if (wrog->typ==TP::EXPLODER) {koloruj(0,8); return 'Ó';}
                    else if(wrog->typ==TP::COMMANDER) koloruj(10,8);
                    return '_';
                case 1:
                    if (wrog->typ==TP::ZWYKLY) koloruj(10,8);
                    else if (wrog->typ==TP::SZYBKI) koloruj(1,8);
                    else if (wrog->typ==TP::TYTANOWY) koloruj(6,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(10,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(2,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(10,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(2,8);
                    return '_';
                case 2:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(14,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(3,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) {koloruj(14,8); return (char)220;}
                    else koloruj(15,8);
                    return '_';
                case 3:
                    if (wrog->typ==TP::ZWYKLY) koloruj(10,8);
                    else if (wrog->typ==TP::SZYBKI) koloruj(3,8);
                    else if (wrog->typ==TP::TYTANOWY) koloruj(6,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(2,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(2,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(10,8);
                    return 'O';
                default: return ' '; break;
            }
            break;}
        case 2:{
            switch(relJ){
                case 0:
                    if (wrog->typ==TP::ZWYKLY) koloruj(10,8);
                    else if (wrog->typ==TP::SZYBKI) koloruj(1,8);
                    else if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(10,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(2,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(10,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(10,8);
                    return '_';
                case 1:
                    if (wrog->typ==TP::ZWYKLY) koloruj(10,8);
                    else if (wrog->typ==TP::SZYBKI) koloruj(1,8);
                    else if (wrog->typ==TP::TYTANOWY) koloruj(6,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(2,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(2,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(2,8);
                    return '_';
                case 2:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(14,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(3,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) {koloruj(14,8); return (char)220;}
                    else koloruj(15,8);
                    return '_';
                case 3:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(14,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(3,14);
                    else if (wrog->typ==TP::EXPLODER) {koloruj(2,0); return 'H';}
                    else if(wrog->typ==TP::COMMANDER) koloruj(10,2);
                    else koloruj(15,8);
                    return '|';
                default: return ' '; break;
            }
            break;}
            case 3:{
            switch(relJ){
                case 1:
                    if (wrog->typ==TP::SZYBKI||wrog->typ==TP::ZWYKLY) koloruj(15,15);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(2,2);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(14,14);
                    else if(wrog->typ==TP::COMMANDER) koloruj(2,2);
                    else koloruj(8,8);
                    return (char) 219;
                case 3:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(14,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(3,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(2,8);
                    else koloruj(15,8);
                    return '|';
                case 2:
                    if (wrog->typ==TP::NALADOWANY){koloruj(14,14);return (char)219;}
                    else {koloruj (8,8); return ' ';}
                default: return ' '; break;
            }
            break;}
            case 4:{
            switch(relJ){
                case 3:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(2,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(5,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(2,8);
                    else koloruj(5,8);
                    return '|';
                case 2:case 4:
                    if (wrog->typ==TP::NALADOWANY){koloruj(14,14);return (char)219;}
                    else {koloruj (8,8); return ' ';}
                default: return ' '; break;
            }
            break;}
            case 5:{
            switch(relJ){
                case 2:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::ZWYKLY||wrog->typ==TP::TOKSYCZNY) koloruj(2,8);
                    else if (wrog->typ==TP::SZYBKI)koloruj(1,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(10,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(2,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(10,8);
                    return '/';
                case 4:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(10,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(5,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(4,8);
                    else koloruj(5,8);
                    return '\\';
                case 1: case 5:
                    if (wrog->typ==TP::NALADOWANY){koloruj(14,14);return (char)219;}
                    else {koloruj (8,8); return ' ';}
                default: return ' '; break;
            }
            break;}
            case 6:{
            switch(relJ){
                case 1:
                    if (wrog->typ==TP::TYTANOWY) koloruj(7,8);
                    else if (wrog->typ==TP::ZWYKLY) koloruj(5,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(10,8);
                    else if (wrog->typ==TP::SZYBKI)koloruj(5,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(5,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(0,8);
                    return '/';
                case 5:
                    if (wrog->typ==TP::TYTANOWY) koloruj(6,8);
                    else if (wrog->typ==TP::TOKSYCZNY) koloruj(14,8);
                    else if (wrog->typ==TP::NALADOWANY) koloruj(5,14);
                    else if (wrog->typ==TP::EXPLODER) koloruj(0,8);
                    else if(wrog->typ==TP::COMMANDER) koloruj(0,8);
                    else koloruj(5,8);
                    return '\\';
                default: return ' '; break;
            }
            break;}
            default: return ' '; break;
        }
        }
    }
        return ' ';
}
char electric(int w,int i,int j,int wskazany, vector<Character*> &enemies)
{
    if(kodscreen==23)
    {
        for(size_t idx=0;idx<enemies.size();++idx){
                if (idx+1==wskazany){
                Character* wrog=enemies[idx];
            int basepos_J=13;
            if (j<basepos_J||j>basepos_J+29+idx*10) continue;
             // Rysowanie zalezne od pozycji i (wiersza) i j (kolumny)
            int relJ=j-basepos_J;
            int relI=i-(w-6);
            if(relI<=i-(w-2)) continue;
            if (!czyZyje(*wrog)||wrog->typ!=TP::NALADOWANY) return ' ';
            switch(relI){
            case 0:{
                switch(relJ){
                    case 2:case 4:case 7:case 13:case 20:case 23:case 31:case 34:case 37:case 40:case 43: case 46:case 49: koloruj(14,8);return (char)220;
                    case 5:case 6:case 11:case 12:case 17:case 22:case 30:case 33:case 36:case 39:case 42: case 45:case 48: koloruj(14,8);return (char)223;
                    case 16:case 21: koloruj(14,8);if (rand()%3==0)return (char)177;
                    else return (char)219;
                    default: koloruj(8,8);return ' ';
                }
            break;}
            case 1:{
                switch(relJ){
                    case 0:case 3:case 8:case 12:case 14:case 17:case 19:case 21:case 24: koloruj(14,8);if (rand()%6==0)return (char)177;
                    else return (char)219;
                    case 9:case 10:case 16:case 18:case 25:case 27:case 30:case 32:case 34:case 36:case 38:case 40:case 42:case 44:case 46:case 48:case 50:case 52: koloruj(14,8);return (char)220;
                    case 28:case 29:case 31:case 33:case 35:case 37:case 39:case 41:case 43:case 45:case 47:case 49:case 51: koloruj(14,8);return (char)223;
                    default: koloruj(8,8);return ' ';
                }
            break;}
            case 2:{
                switch(relJ){
                    case 1:case 2:case 11:case 15: koloruj(14,8);return (char)223;
                    case 7:case 21:case 26: koloruj(14,8);if (rand()%4==0)return (char)177; else return (char)219;
                    default: koloruj(8,8);return ' ';
                }
            break;}
            case 3:{
                switch(relJ){
                    case 5:case 6:case 19:case 24:case 25: koloruj(14,8);return (char)223;
                    case 20: koloruj(14,8);if (rand()%2==0)return (char)177; else return (char)219;
                    case 23: koloruj(14,8);return (char)220;
                    default: koloruj(8,8);return ' ';
                    }
            break;}
            default: koloruj(8,8);return ' ';

            }
                }
        }
    }
    return ' ';
}
char screen_char_at(int i, int j,Gamecontent &Gc) {
    char c;
    if (wybor==true)
    {c = strzalka(wskazany,w,i,j,Gc.enemies.size()); if (c!=' ')return c;}
    c = efekt_napis(Gc,Gc.krytT,w,i,j); if(c!=' ')return c;
    c = aura(w,i,j,wskazany,Gc.enemies,Gc.smigniecie);if(c!=' ') return c;
    c = electric(w,i,j,Gc.wskazany,Gc.enemies);if(c!=' ') return c;
    c = vomit(w,i,j,Gc.wskazany,Gc.enemies); if (c!=' ') return c;
    c = rysujgracza(w,i,j,Gc); if (c!=' ') return c;
    c = bomby(w,i,j,Gc.e,Gc.wskazany,Gc.enemies); if (c!=' ') return c;
    c = rysuj_dzialko(w,i,j,Gc); if (c!=' ') return c;
    c = rysuj_zasobnik(w,i,j,Gc); if (c!=' ') return c;
    c = rysujwroga(w,i,j,Gc); if (c!=' ') return c;

    return ' ';
}
void pokazStatystyki(const Character &postac,const string& etykieta,Gamecontent &Gc) {
    if (!czyZyje(postac)) return;
    koloruj(15,0);
    if (postac.typ==TP::GRACZ) cout << "+" << string(30, '-') << "+" << endl;
    cout << "|";koloruj(15,12);cout<<" " << setw(7) << left << etykieta << ":" << setw(20) << right;
    for(const auto& efekt:postac.efekty){
        if(efekt.aktywny){
            switch(efekt.ID){
                case ZATRUCIE: koloruj(2,4); break;
                case UPICIE: koloruj(8,4); break;
                case OSLABIENIE: koloruj(5,4); break;
                case KRYTOWANIE: koloruj(14,4); break;
            }
        }
     }
    cout<<setw(20)<<postac.Imie<<setw(1)<<" "; koloruj (15,12);
    koloruj(15,0);cout<<"|" << endl;
    cout << "|";koloruj(15,12);cout<<" HP: "<<setw(4)<<(char)176<<setw(4)<<postac.HP<<"/"<<setw(4)<<postac.base_HP<<(char)176<<setw(2);

    cout<<" ";
    cout<<"DEF: ";koloruj(15,12);cout<<(char)176<<setw(2)<<postac.DEF<<(char)176;koloruj(15,0);cout<<"|"<<endl;
    if (postac.typ==TP::GRACZ||postac.typ==TP::NALADOWANY||postac.typ==TP::COMMANDER){
            cout << "|";koloruj(14,12);cout<<(char)176<<" SP: " << setw(4)<<postac.SP<<(char)176<<"                   ";koloruj(15,0);cout<<"|" << endl;
    }
    if (postac.typ==TP::EXPLODER){
            cout << "|";koloruj(0,12);cout<<(char)178<<"R. do wybuchhu: " << setw(1)<<postac.odliczanie<<(char)178<< "           ";koloruj(15,0);cout<<"|" << endl;
    }
    if (!postac.efekty.empty()){
        cout<<"|";koloruj(15,12);cout<<" EFEKTY:"<<setw(22)<<right;koloruj(15,12);cout<<" ";koloruj(15,0);cout<<"|\n";
     postac.wypiszEfekty();
    }
    cout << "+" << string(30, '-') << "+" << endl;
}
void przesunKursorNaGore()
{
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void narysujScene(Gamecontent &Gc){
    przesunKursorNaGore(); // bez migania!

    for (int i=0;i<=w;i++){
        if (i==0)
            cout<<" ";
        else
            cout<<char(179);
        for (int j=0;j<k;j++){
            if(i==0||i==w){//obramowanie gora/dol
                if(i==w) koloruj(15,8);
                cout<<"_";
            }
            else{
                koloruj(15,8);
                char znak = screen_char_at(i,j,Gc);
                if (Gc.kodscreen>=0&&Gc.kodscreen<=17&&i==w-7&&Gc.wybor==true){
                char s = strzalka(Gc.wskazany, w, i, j, Gc.enemies.size());
                if (s != ' ') znak = s;
                }
                cout << znak;
                koloruj(7,0);
            }
        }
        if (i==0)
            cout<<" ";
        else
            cout<<char(179);

        cout<<endl;
    }
    if (debug==true){
        cout<<"DEBUG: Gc.kodscreen="<<Gc.kodscreen<<endl;
        for(auto wrog:Gc.enemies)
        {
            cout<<"DEBUG:ADRES WROGA - "<<wrog<<endl;
        }
    }
    koloruj(4,0);
     cout<<"-- WALKA "<<Gc.x<<"--"<<endl;
     koloruj(7,0);
     cout<<endl;
    pokazStatystyki(Gc.gracz, "GRACZ",Gc);
    if (czyZyje(Gc.dzialko)) pokazStatystyki(*Gc.dzialko, "BUDOWLA",Gc);
    if (czyZyje(Gc.zasobnik)) pokazStatystyki(*Gc.zasobnik, "BUDOWLA",Gc);
    for (const Character* wrog:Gc.enemies){
        if (czyZyje(wrog)==true) pokazStatystyki(*wrog,"WROG",Gc);
    }
    if (wskazany < 1 || static_cast<size_t>(wskazany)>Gc.enemies.size()) {
    cout << "BLAD: wskazany poza zakresem! wskazany = " << wskazany << ", Gc.enemies.size() = " << Gc.enemies.size() << endl;
}
else{ cout<<endl;}
    cout<<endl;
}
void szybkieCzyszczenie() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD n, cells;
    COORD topLeft = { 0, 0 };

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cells = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', cells, topLeft, &n);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, topLeft, &n);
    SetConsoleCursorPosition(hConsole, topLeft);
}

void screen(Gamecontent &Gc)
{
    szybkieCzyszczenie();

    if (Gc.kodscreen==20){
        koloruj(15,0);
        for (int i=0;i<75;i++) cout<<(char)205;
        cout<<(char)185<<endl;
        koloruj(15,4);
                cout<<"              ___   _    _  _      _____   _____                           ";koloruj(7,0);cout<<(char)186<<endl;koloruj(15,4);
                cout<<"             /";koloruj(15,12);cout<<"   ";koloruj(15,4);cout<<"\\ |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|  /";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"/|";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|    |";koloruj(15,12);cout<<"  ___";koloruj(15,4);cout<<"| |";koloruj(15,12);cout<<"  _  ";koloruj(15,4);cout<<"|                          ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"            |";koloruj(15,12);cout<<"  |_|";koloruj(15,4);cout<<" |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|_/";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"/ |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|    |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|__   |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|_|";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|                          ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"            \\";koloruj(15,12);cout<<"_   ";koloruj(15,4);cout<<"\\ |";koloruj(15,12);cout<<"   _";koloruj(15,4);cout<<"/  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|    |";koloruj(15,12);cout<<"  __";koloruj(15,4);cout<<"|  |";koloruj(15,12);cout<<"  ___";koloruj(15,4);cout<<"|                          ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"            |";koloruj(15,12);cout<<" |  |";koloruj(15,4);cout<<" ";koloruj(15,12);cout<<"| |\\";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"\\  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|__  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|___  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|                              ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"             \\";koloruj(15,12);cout<<"___";koloruj(15,4);cout<<"/ |";koloruj(15,12);cout<<"_";koloruj(15,4);cout<<"| \\";koloruj(15,12);cout<<"_";koloruj(15,4);cout<<"\\ |";koloruj(15,12);cout<<"____";koloruj(15,4);cout<<"| |";koloruj(15,12);cout<<"_____";koloruj(15,4);cout<<"| |";koloruj(15,12);cout<<"_";koloruj(15,4);cout<<"|                              ";koloruj(15,0);cout<<(char)186<<endl;
            }
    else if (Gc.kodscreen==69){ koloruj (15,0);
        cout<<(char)201<<string(55,(char)205)<<(char)187<<endl;
        cout<<(char)186<<string(55,(char)176)<<(char)186<<endl;
        cout<<(char)186<<(char)177<<string(4,(char)219)<<string(2,(char)177)<<string(4,(char)219)<<string(2,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<string(2,(char)177)<<string(4,(char)219)<<string(5,(char)177)<<string(4,(char)219)<<string(3,(char)177)<<(char)219<<string(4,(char)177)<<(char)219<<string(2,(char)177)<<string(4,(char)219)<<string(2,(char)177)<<string(4,(char)219)<<(char)177<<(char)186<<endl;
        cout<<(char)186<<(char)219<<string(6,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(2,(char)177)<<string(2,(char)219)<<(char)177<<string(2,(char)219)<<string(2,(char)177)<<(char)219<<string(7,(char)177)<<(char)219<<string(4,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(4,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(5,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<(char)186<<endl;
        cout<<(char)186<<(char)219<<string(2,(char)177)<<string(2,(char)219)<<string(2,(char)177)<<string(4,(char)219)<<string(2,(char)177)<<(char)219<<(char)177<<(char)219<<(char)177<<(char)219<<string(2,(char)177)<<string(3,(char)219)<<string(5,(char)177)<<(char)219<<string(4,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(3,(char)177)<<string(3,(char)219)<<string(3,(char)177)<<string(4,(char)219)<<(char)177<<(char)186<<endl;
        cout<<(char)186<<(char)219<<string(3,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<(char)177<<(char)219<<(char)177<<(char)219<<string(2,(char)177)<<(char)219<<string(7,(char)177)<<(char)219<<string(4,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<string(5,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<(char)186<<endl;
        cout<<(char)186<<(char)177<<string(4,(char)219)<<string(2,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(2,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<string(2,(char)177)<<string(4,(char)219)<<string(5,(char)177)<<string(4,(char)219)<<string(5,(char)177)<<(char)219<<(char)219<<string(4,(char)177)<<string(4,(char)219)<<string(2,(char)177)<<(char)219<<string(3,(char)177)<<(char)219<<(char)186<<endl;
        cout<<(char)186<<string(55,(char)176)<<(char)186<<endl;
        cout<<(char)200<<string(55,(char)205)<<(char)188<<endl;
    }
    else {
    for (i=0;i<=w;i++)//dlugosc obrazu
    {
        if (i==0)
            cout<<" ";
        else
            cout<<char(179);
        for (j=0;j<k;j++)//szerokosc obrazu (60 miejsc na jeden rzad)
        {
            if(i==0||i==w){//obramowanie gora/dol
                if(i==w) koloruj(15,8);
                cout<<"_";
            }
            else //detale
            {
                koloruj(15,8);
                if (Gc.kodscreen>=0&& Gc.kodscreen<=17){
                char znak = screen_char_at(i,j,Gc);
                char s = strzalka(Gc.wskazany, w, i, j,Gc.enemies.size());
                if (s != ' ') znak = s;
                cout << znak;
                koloruj(7,0);
                }
            else if (Gc.kodscreen==19)
            {

                koloruj(15,15);
                cout<<" ";
                koloruj(15,0);
            }
            else if (Gc.kodscreen==21)
            {
                koloruj(4,4);
                cout<<" ";
                koloruj(15,0);
            }
            else if (Gc.kodscreen==24)
            {
                koloruj(14,11);
                cout<<(char)177;
                koloruj(15,0);
            }
            }
        }
        if (i==0)
            cout<<" ";
        else
            cout<<char(179);

        cout<<endl;
    }
    if (debug==true){
        cout<<"DEBUG: Gc.kodscreen="<<Gc.kodscreen<<endl;
        for(auto wrog:Gc.enemies)
        {
            cout<<"DEBUG:ADRES WROGA - "<<wrog<<endl;
        }
    }
    koloruj(0,4);
     cout<<"-- WALKA "<<Gc.x<<"--"<<endl;
     koloruj(7,0);
     cout<<endl;
    pokazStatystyki(Gc.gracz, "GRACZ",Gc);
    if (czyZyje(Gc.dzialko)) pokazStatystyki(*Gc.dzialko, "BUDOWLA",Gc);
    if (czyZyje(Gc.zasobnik)) pokazStatystyki(*Gc.zasobnik, "BUDOWLA",Gc);
    for (const Character* wrog:Gc.enemies){
        if (czyZyje(wrog)==true) pokazStatystyki(*wrog,"WROG",Gc);
    }
    if (Gc.wskazany < 1 || Gc.wskazany >Gc.enemies.size()) {
    cout << "BLAD: wskazany poza zakresem! wskazany = " << wskazany << ", Gc.enemies.size() = " << Gc.enemies.size() << endl;
}
else{ cout<<endl;}
    cout<<endl;
    }
}
