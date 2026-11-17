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
using namespace std;
constexpr int w=15,k=100;
int i=0,j=0;
char efekt_napis(Gamecontent &Gc,Character* &cel, int w,int i,int j,const string &obrazenia){
    if(cel!=nullptr){
            switch(cel->typ){
            case GRACZ:{
                switch (Gc.SE.R){
                    case ScreenEfekt::CRITICAL:{
                        int relI=i-(w-8);
                        switch(relI){
                            case 0:{
                                koloruj(10,8);
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
                                    koloruj(10,8);
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
                    case ScreenEfekt::HIT:{
                        int startJ=5;
                        int relI=i-(w-7);
                        if (relI!=0) return ' ';
                        int relJ=j-startJ;
                        if(relJ<0||relJ>=static_cast<int>(obrazenia.size())) return ' ';
                        koloruj(0,12); return obrazenia[relJ];
                        break;}
                    default:break;
                }
                break;}
                case DZIALKO:case ZASOBNIK:{
                    switch (Gc.SE.R){
                    case ScreenEfekt::CRITICAL:{
                        int relI=i-(w-8);
                        switch(relI){
                            case 0:{
                                koloruj(10,8);
                                switch(j){
                                    case 16: return 'C';
                                    case 17: return 'R';
                                    case 18: return 'I';
                                    case 19: return 'T';
                                    case 20: return 'I';
                                    case 21: return 'C';
                                    case 22: return 'A';
                                    case 23: return 'L';
                                    default: return ' ';
                                    }
                                }
                                case 1:{
                                    koloruj(10,8);
                                    switch(j){
                                        case 17: return 'H';
                                        case 18: return 'I';
                                        case 19: return 'T';
                                        case 20: return '!';
                                        case 21: return '!';
                                        case 22: return '!';
                                        default: return ' ';
                                    }
                                }
                                default: return ' ';

                            }
                    break;}
                    case ScreenEfekt::HIT:{
                        int startJ=15;
                        int relI=i-(w-7);
                        if (relI!=0) return ' ';
                        int relJ=j-startJ;
                        if(relJ<0||relJ>=static_cast<int>(obrazenia.size())) return ' ';
                        koloruj(0,12); return obrazenia[relJ];
                        break;}
                    default:break;
                }
                break;}
                default:
                {
                    auto it=find(Gc.enemies.begin(),Gc.enemies.end(),cel);
                    if (it==Gc.enemies.end()) return ' ';
                    size_t idx=distance(Gc.enemies.begin(),it);
                    switch(Gc.SE.R){
                        case ScreenEfekt::CRITICAL:{
                            int basepos_J=40+idx*10;
                            if (j<basepos_J||j>basepos_J+8) return ' ';
                            int relJ=j-basepos_J;
                            int relI=i-(w-8);
                            switch (relI){
                                case 0:
                                switch(relJ){
                                    case 0: koloruj(10,8);return 'C';
                                    case 1: koloruj(10,8);return 'R';
                                    case 2: koloruj(10,8);return 'I';
                                    case 3: koloruj(10,8);return 'T';
                                    case 4: koloruj(10,8);return 'I';
                                    case 5: koloruj(10,8);return 'C';
                                    case 6: koloruj(10,8);return 'A';
                                    case 7: koloruj(10,8);return 'L';
                                    default: return ' ';
                                }
                                case 1:
                                switch(relJ){
                                    case 1: koloruj(10,8);return 'H';
                                    case 2: koloruj(10,8);return 'I';
                                    case 3: koloruj(10,8);return 'T';
                                    case 4: koloruj(10,8);return '!';
                                    case 5: koloruj(10,8);return '!';
                                    case 6: koloruj(10,8);return '!';
                                    default: return ' ';
                                    }
                                 default: return ' ';
                            }
                        break;}
                        case ScreenEfekt::HIT:{
                            int startJ=43+idx*10;
                            if(startJ<40||startJ>90) return ' ';
                            int relJ=j-startJ;
                            if(relJ<0||relJ>=static_cast<int>(obrazenia.size())) return ' ';
                            int relI=i-(w-7);
                            if(relI!=0) return ' ';
                            koloruj(0,12); return obrazenia[relJ];
                        break;}
                    default:break;
                    }
                break;}
                }
    return ' ';}
    return ' ';
}
char rysuj_dzialko(int w,int i,int j,Gamecontent &Gc)
{
    if (!czyZyje(Gc.dzialko)) return ' ';
    switch(Gc.dzialko->ObecnaAkcja){
        default:
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
        break;}
    }
    return ' ';
}
char rysuj_zasobnik(int w,int i,int j,Gamecontent &Gc)
{
    if (!czyZyje(Gc.zasobnik)) return ' ';
    switch(Gc.zasobnik->ObecnaAkcja){
        default:
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
        break;}
    }
    return ' ';
}

vector<int> PozBomby(int relJ,int l_bomb){
    vector<int> poz;
    switch (l_bomb){
        case 1: poz={0}; break;
        case 2: poz={0,4};break;
        case 3: poz={0,4,2};break;
        case 4: poz={0,4,2,6};break;
        case 5: poz={0,4,2,6,3};break;
        case 6: poz={0,2,3,4,6,7};break;
        default: break;
    }
    return poz;
}
char bomby(int w,int i,int j,Gamecontent &Gc)
{
    koloruj(12,8);
    if (i==w-1)
    {
        vector<StickyBomb*> Bomby=znajdzbombyWlasciciela(Gc.Obiekty,&Gc.gracz);
        for(Character* wrog:Gc.enemies){
            if (!czyZyje(*wrog)==true) continue;
            int baseposJ=43+(Gc.wskazany-1)*10;
            int relJ=j-baseposJ;
            if(relJ<0||relJ>7) continue;
            vector<StickyBomb*> bombyPrzyWrogu;
            for (StickyBomb* bomba:Bomby)
            {
                if (bomba->attachedTo==wrog)
                {
                    bombyPrzyWrogu.push_back(bomba);
                }
            }
            for (size_t idx=0;idx<bombyPrzyWrogu.size();idx++){
                vector<int> PB=PozBomby(relJ,bombyPrzyWrogu.size());
                if(relJ==PB[idx]){
                    if(bombyPrzyWrogu[idx]->krytyczna) koloruj(4,12);
                    return 'o';
                }
            }

        }
    }
    return ' ';
}
char rysujwroga(int w, int i, int j,Gamecontent &Gc)
{
    if (!EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies))
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
char Exploder(int w,int i,int j,vector<Character*> &enemies){
    auto it=find_if(enemies.begin(),enemies.end(),[](const auto &enemy){return enemy!=nullptr&&enemy->typ==TP::EXPLODER&&czyZyje(enemy);});
    if(it==enemies.end()) return ' ';
    Character *IT=*it;
    if(IT->ObecnaAkcja==AK::SPECIAL){
        koloruj(4,4);
        return char(176);
    }
    return ' ';
}
char screen_char_at(int i, int j,Gamecontent &Gc) {
    char c;
    if (Gc.wybor==true){
    c = strzalka(Gc.wybor,Gc.wskazany,w,i,j,Gc.enemies.size()); if (c!=' ')return c;}
    if(!Gc.affectedT.empty()){
        for (auto &K:Gc.affectedT){
            int full_damage=0;
            for(auto &DR:Gc.dane){
                if(DR.cel==K)full_damage+=DR.obrazenia;
            }
            string l_o=to_string(full_damage);
            c=efekt_napis(Gc,K,w,i,j,l_o);
                if(c!=' ') return c;
        }
    }
    c = aura(w,i,j,Gc.wskazany,Gc);if(c!=' ') return c;
    c = electric(w,i,j,Gc);if(c!=' ') return c;
    c = vomit(w,i,j,Gc); if (c!=' ') return c;
    c = Exploder(w,i,j,Gc.enemies);if(c!=' ') return c;
    c = rysujgracza(w,i,j,Gc); if (c!=' ') return c;
    c = bomby(w,i,j,Gc); if (c!=' ') return c;
    c = rysuj_dzialko(w,i,j,Gc); if (c!=' ') return c;
    c = rysuj_zasobnik(w,i,j,Gc); if (c!=' ') return c;
    c = rysujwroga(w,i,j,Gc); if (c!=' ') return c;

    return ' ';
}
void przesunKursorNaGore()
{
    COORD coord = {0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void narysujScene(Gamecontent &Gc){
    if (Gc.wskazany < 1 || Gc.wskazany>static_cast<int>(Gc.enemies.size())){
        Gc.wskazany=1;
    }

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
    if (Gc.debug==true){
        for(auto wrog:Gc.enemies)
        {
            cout<<Gc.S.L.get(Tx::Deb_info_EnAdress)<<wrog<<"| ACTION: "<<static_cast<int>(wrog->ObecnaAkcja)<<endl;
        }
    }
    koloruj(0,4);
    cout<<Gc.S.L.get(Tx::Wave_info)<<Gc.x<<" --"<<endl;

     koloruj(7,0);
     cout<<endl;
    ShowStatystyki(Gc);
    if (Gc.wskazany < 1 || Gc.wskazany>static_cast<int>(Gc.enemies.size())) {
        cout <<Gc.S.L.get(Tx::Error_info_IndexOutOfBounds)<< Gc.wskazany << ", Gc.enemies.size() = " << Gc.enemies.size() << endl;
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
    if (Gc.wskazany < 1 || Gc.wskazany>static_cast<int>(Gc.enemies.size())){
        Gc.wskazany=1;
    }
    szybkieCzyszczenie();
    if (Gc.Wydarzenie==Globalne::SHOP){
        koloruj(15,0);
        for (int i=0;i<76;i++) cout<<(char)205;
        cout<<(char)185<<endl;
        koloruj(15,4);
                cout<<"              ___   _    _  _      _____   _____                            ";koloruj(7,0);cout<<(char)186<<endl;koloruj(15,4);
                cout<<"             /";koloruj(15,12);cout<<"   ";koloruj(15,4);cout<<"\\ |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|  /";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"/|";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|    |";koloruj(15,12);cout<<"  ___";koloruj(15,4);cout<<"| |";koloruj(15,12);cout<<"  _  ";koloruj(15,4);cout<<"|                           ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"            |";koloruj(15,12);cout<<"  |_|";koloruj(15,4);cout<<" |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|_/";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"/ |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|    |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|__   |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|_|";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|                           ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"            \\";koloruj(15,12);cout<<"_   ";koloruj(15,4);cout<<"\\ |";koloruj(15,12);cout<<"   _";koloruj(15,4);cout<<"/  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|    |";koloruj(15,12);cout<<"  __";koloruj(15,4);cout<<"|  |";koloruj(15,12);cout<<"  ___";koloruj(15,4);cout<<"|                           ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"            |";koloruj(15,12);cout<<" |  |";koloruj(15,4);cout<<" ";koloruj(15,12);cout<<"| |\\";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"\\  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|__  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|___  |";koloruj(15,12);cout<<" ";koloruj(15,4);cout<<"|                               ";koloruj(15,0);cout<<(char)186<<endl;
                koloruj(15,4);cout<<"             \\";koloruj(15,12);cout<<"___";koloruj(15,4);cout<<"/ |";koloruj(15,12);cout<<"_";koloruj(15,4);cout<<"| \\";koloruj(15,12);cout<<"_";koloruj(15,4);cout<<"\\ |";koloruj(15,12);cout<<"____";koloruj(15,4);cout<<"| |";koloruj(15,12);cout<<"_____";koloruj(15,4);cout<<"| |";koloruj(15,12);cout<<"_";koloruj(15,4);cout<<"|                               ";koloruj(15,0);cout<<(char)186<<endl;
            }
    else if (Gc.Wydarzenie==Globalne::DEATH){ koloruj (15,0);
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
                if (Gc.Wydarzenie==Globalne::NONE){
                char znak = screen_char_at(i,j,Gc);
                cout << znak;
                koloruj(7,0);
                }
                else if (Gc.Wydarzenie==Globalne::FLASH)
                {
                    koloruj(15,15);
                    cout<<" ";
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
        for(auto wrog:Gc.enemies)
        {
            cout<<Gc.S.L.get(Tx::Deb_info_EnAdress)<<wrog<<endl;
        }
    }
    koloruj(0,4);
    cout<<Gc.S.L.get(Tx::Wave_info)<<Gc.x<<" --"<<endl;

     koloruj(7,0);
     cout<<endl;
    ShowStatystyki(Gc);
    if (Gc.wskazany < 1 || Gc.wskazany>static_cast<int>(Gc.enemies.size())) {
        cout <<Gc.S.L.get(Tx::Error_info_IndexOutOfBounds)<< Gc.wskazany << ", Gc.enemies.size() = " << Gc.enemies.size() << endl;
    }
    else{ cout<<endl;}
    cout<<endl;
    }
}
