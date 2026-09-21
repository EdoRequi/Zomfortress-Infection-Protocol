#include <iostream>
#include "Player.h"
using namespace std;
using AK=TypAkcji;
using GW=Globalne;
char sword_pulled(int relI,int relJ,Player &source){
    switch (relI){
    case 0:{
        switch(relJ){
        case 7:
            koloruj(0,7);
            return '^';
        default: return ' ';
        }
    break;}
    case 1:case 2:case 3:{
        switch(relJ){
            case 6:
            case 8:
                koloruj(0,7);
                return '|';
                break;
            case 7:
                koloruj(15,7);
                return (char)177;
            default:
                return ' ';
        }
    break;}
    case 4:{
        switch(relJ)
        {
        case 2:
            koloruj(4,8);
            return 'O';
        case 3:
            koloruj(12,8);
            return '_';
        case 4:
            koloruj(15,8);
            return '_';
        case 5:
            koloruj(4,8);
            return '_';
        case 6:
        case 7:
        case 8:
            koloruj(7,8);
            return '-';
        default:
            return ' ';
        }
    break;}
    case 5:{
        switch(relJ)
        {
        case 1:
            koloruj(12,8);
            return '/';
        case 2:
            koloruj(0,8);
            return '|';
        case 7:
            koloruj(6,8);
            return '|';
        default:
            return ' ';
                    }

    break;}
    case 6:{
    switch(relJ)
    {
    case 0:
        koloruj(15,8);
        return '/';
    case 2:
        koloruj(0,8);
        return '|';
    default:
        return ' ';
    }
    break;}
    case 7:{
        switch(relJ)
        {
        case 2:
            koloruj(12,8);
            return '|';
        default:
            return ' ';
        }
    break;}
    case 8:{
        switch(relJ)
        {
        case 1:
            koloruj(12,8);
            return '/';
        case 3:
            koloruj(12,8);
            return '\\';
        default:
            return ' ';
        }
    break;}
    case 9:{
    switch(relJ)
    {
        case 0:
            koloruj(0,8);
            return '/';
        case 4:
            koloruj(0,8);
            return '\\';
        default:
            return ' ';
    }
    break;}
    }
return ' ';
}
char rzut_granatem(int w,int i,int j,Player &source){
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
    return ' ';
}
char SBL_pulled(int relI,int relJ,Player &source){
    switch(relI){
        case 0:{
        switch(relJ)
        {
            case 7 ... 9:
                koloruj(0,8);
                return '_';
            case 10:
                koloruj(7,8);
                return 'L';
            default:
                return ' ';
        }
        break;}
        case 1:{
            switch(relJ)
            {
                case 7 ... 10:
                    koloruj(0,7);
                    return '_';
                case 6:
                    koloruj(0,7);
                    return '[';
                case 11:
                    koloruj(0,7);
                    return ']';
                default:
                    return ' ';
            }
        break;}
        case 2:{
            switch(relJ)
            {
                case 2:
                    koloruj(4,8);
                    return 'O';
                case 3:
                    koloruj(12,8);
                    return '_';
                case 4:
                    koloruj(15,8);
                    return '_';
                case 5:
                    koloruj(4,8);
                    return '_';
                case 6:
                    koloruj(6,8);
                    return '|';
                    break;\
                case 8:
                    koloruj(0,2);
                    return 'E';
                    break;
                case 9:
                    koloruj(0,2);
                    return '|';
                case 11:
                    koloruj(6,8);
                    return '|';
                default:
                    return ' ';
            }
        break;}
        case 3:{
            switch(relJ)
            {
                case 1:
                    koloruj(12,8);
                    return '/';
                case 2:
                    koloruj(0,8);
                    return '|';
                default:
                    return ' ';
            }
        break;}
        case 4:{
            switch(relJ)
            {
            case 0:
                koloruj(15,8);
                return '/';
            case 2:
                koloruj(0,8);
                return '|';
            default:
                return ' ';
            }
        break;}
        case 5:{
            switch(relJ)
            {
            case 2:
                koloruj(12,8);
                return '|';
            default:
                return ' ';
            }
        break;}
        case 6:{
            switch(relJ)
            {
                case 1:
                    koloruj(12,8);
                    return '/';
                case 3:
                    koloruj(12,8);
                    return '\\';
                default:
                return ' ';
            }
        break;}
        case 7:{
            switch(relJ)
            {
                case 0:
                    koloruj(0,8);
                    return '/';
                case 4:
                    koloruj(0,8);
                    return '\\';
                default:
                    return ' ';
            }
        break;}
        default: return ' ';
    }
    return ' ';
}
char Demo_special_Caber(int relI,int relJ,Player &source){
    switch (relI){
    case 0:{
        switch(relJ)
        {
            case 11:case 12:
                koloruj(0,8);
                return '_';
            default:
                return ' ';
        }
    break;}
    case 1:{
        switch(relJ)
        {
            case 10:
            case 13:
                koloruj(0,8);
                return '!';
            case 11:
            case 12:
                koloruj(0,2);
                return '_';
            default:
                return ' ';
        }
    break;}
    case 2:{
        switch(relJ)
        {
        case 11:
        case 12:
            koloruj(6,8);
            return '|';
        default:
            return ' ';
        }
    break;}
            case 3:{
                switch(relJ)
                {
                case 0 ... 3:
                    return '_';
                case 7:
                    koloruj(4,8);
                    return 'O';
                case 8:
                    koloruj(12,8);
                    return '_';
                case 9:
                    koloruj(15,8);
                    return '_';
                case 10:
                    koloruj(4,8);
                    return '_';
                case 11:case 12:
                    koloruj(6,8);
                    return '|';
                default:
                    return ' ';
                }
            break;}
            case 4:{
                switch(relJ)
                {
                    case 1 ... 4:
                    return '_';
                case 6:
                    koloruj(12,8);
                    return '/';
                case 7:
                    koloruj(0,8);
                    return '|';
                case 8:
                case 9:
                    koloruj(2,8);
                    return '-';
                default:
                    return ' ';
                }
            break;}
            case 5:{
                switch(relJ)
                {
                case 0 ... 3:
                    return '_';
                case 5:
                    koloruj(15,8);
                    return '/';
                case 7:
                    koloruj(0,8);
                    return '|';
                default:
                    return ' ';
                }
            break;}
           case 6:{
            switch(relJ)
            {
                case 1 ... 4:
                    return '_';
                case 7:
                    koloruj(12,8);
                    return '|';
                default:
                    return ' ';
            }
            break;}
            case 7:{
                switch(relJ)
                {
                case 1 ... 4:
                    return '_';
                case 6:
                    koloruj(12,8);
                    return '/';
                case 8:
                    koloruj(12,8);
                    return '\\';
                default:
                    return ' ';
                }
            break;}
            case 8:{
                switch(relJ)
                {
                    case 0 ... 3:
                        return '_';
                    case 5:
                        koloruj(0,8);
                        return '/';
                    case 9:
                        koloruj(0,8);
                        return '\\';
                    default:
                        return ' ';
                }
            break;}
        default: return ' ';
    }
    return ' ';
}
char rysujgracza(int w, int i, int j,Gamecontent &Gc)
{
       switch (Gc.gracz.ObecnaAkcja){
           case AK::ACTION1:{
               if (Gc.gracz.Klasa==TypRoli::DEMOMAN){
                int relI=i-(w-10); if(relI<0||relI>=10) return ' ';
                int relJ=j-4;
                if(czyZyje(Gc.dzialko)||czyZyje(Gc.zasobnik)) relJ-=27;
                char c=sword_pulled(relI,relJ,Gc.gracz);
                return c;
               }
           }
            case AK::ACTION2:{
                if (Gc.gracz.Klasa==TypRoli::DEMOMAN){
                int relI=i-(w-8); if(relI<0||relI>=8) return ' ';
                int relJ=j-4;
                if(czyZyje(Gc.dzialko)||czyZyje(Gc.zasobnik)) relJ+=3;
                char c=SBL_pulled(relI,relJ,Gc.gracz);
                return c;
                }
            }
            case AK::SPECIAL:{
                if (Gc.gracz.Klasa==TypRoli::DEMOMAN){
                int relI=i-(w-9); if(relI<0||relI>=9) return ' ';
                int relJ=j-30;
                char c=Demo_special_Caber(relI,relJ,Gc.gracz);
                return c;
                }
            }
            case AK::ACTION_USED_ITEM:
            {
                return rzut_granatem(w,i,j,Gc.gracz);
            }
            case AK::NO_ACTION:{
                if (Gc.gracz.Klasa==TypRoli::DEMOMAN){
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
            }
            break;}
            default: return ' ';
        }
    return ' ';
}
