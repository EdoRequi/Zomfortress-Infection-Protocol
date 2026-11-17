#include <iostream>
#include "Visual.h"
#include <cstdlib>
using namespace std;
char strzalka (bool wybor,int wskazany,int w,int i,int j,int liczba_wrogow)
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
//char wybuch(int w,int i,int j,Gamecontent &Gc){
//    for (const auto &wrog:Gc.enemies){
  //      int poinnowator=0;
    //    if(!czyZyje(wrog)) {continue;}
      //  int pozycja=distance(Gc.enemies.begin(),wrog)
        //vector<StickyBomb*> Bomby=znajdzbombyWlasciciela(Gc.Obiekty,Gc.gracz);
        //for (const auto &b:Bomby){
          //  if(wrog==b.attachedTo)

        //}
    //}
//}
char aura(int w, int i, int j, int wskazany, Gamecontent &Gc)
{
    if (Gc.gracz.ObecnaAkcja==AK::ACTION1&&Gc.smigniecie==true)
    {
        int relI=i-(w-11);
        if(relI<0) return ' ';
        int baseposJ=20+(wskazany-1)*10;
        int relJ=j-baseposJ;
        switch (relI)
        {
        case 0:{
            switch (relJ){
            case 1:
                koloruj(12,8);
                return (char)177;
            case 18:
            case 19:
            case 20:
                koloruj (12,8);
                return (char)178;
            default:
                return ' ';
                }
        break;}
        case 1:{
            switch (relJ){
                case 19:
                case 21:
                    koloruj (12,8);
                    return (char)178;
                case 0:
                case 2:
                    koloruj (12,8);
                    return (char)177;
                case 20:
                case 1:
                    koloruj(4,4);
                    return (char)219;
                default:
                    return ' ';
            }
        break;}
        case 2:{
            switch (relJ){
                case 14:
                case 20:
                    koloruj(12,8);
                    return (char)178;
                case 1:
                    koloruj(12,8);
                    return (char)177;
                case 21:
                    koloruj (4,4);
                    return (char)219;
                case 22:
                    koloruj(12,8);
                    return (char)178;
                default:
                    return ' ';
            }
        break;}
        case 3:{
            switch (relJ){
                case 15:
                case 20:
                    koloruj(12,8);
                    return (char)178;
                case 21:
                case 22:
                    koloruj (4,4);
                    return (char)219;
                case 23:
                    koloruj(12,8);
                    return (char)178;
                default:
                    return ' ';
            }
        break;}
        case 4:{
            switch (relJ){
                case 21:
                case 15:
                    koloruj(12,8);
                    return (char)178;
                case 22:
                case 23:
                    koloruj (4,4);
                    return (char)219;
                case 24:
                    koloruj(12,12);
                    return (char)178;
                default:
                    return ' ';
            }
        break;}
        case 5:{
            switch (relJ){
                case 20:
                case 13:
                case 14:
                    koloruj(12,8);
                    return (char)178;
                case 21:
                case 22:
                    koloruj (4,4);
                    return (char)219;
                case 23:
                    koloruj(12,8);
                    return (char)178;
                case 24:
                    koloruj(0,8);
                    return (char)178;
                default:
                    return ' ';
            }
        break;}
        case 6:{
            switch (relJ){
                case 19:
                    koloruj(12,8);
                    return (char)178;
                case 20:
                case 21:
                    koloruj(4,4);
                    return (char)219;
                case 22:
                    koloruj(12,8);
                    return (char)178;
                case 23:
                    koloruj(0,8);
                    return (char)178;
                default:
                    return ' ';
            }
        break;}
        case 7:{
            switch (relJ){
                case 18:
                case 20:
                case 19:
                    koloruj (12,8);
                    return (char)178;
                case 21:
                case 22:
                    koloruj(0,8);
                    return (char)178;
                //case 19:
                    //koloruj(4,4);
                    //return (char)219;
                    //break;
                default:
                    return ' ';
            }
        break;}
        default:
            return ' ';
            break;
        }
    }
    return ' ';
}
char vomit(int w, int i, int j, Gamecontent &Gc)// YOU ARE WALKING VOMIT!!!
{
        for (int idx=0;idx<Gc.enemies.size();idx++){
        if(Gc.enemies[idx]==nullptr||Gc.enemies[idx]->typ!=TP::TOKSYCZNY||!czyZyje(Gc.enemies[idx])) continue;
        if(Gc.enemies[idx]->ObecnaAkcja!=AK::ACTION1) continue;
        int basepos_J=20+idx*10;
             // Rysowanie zalezne od pozycji i (wiersza) i j (kolumny)
        int relJ=j-basepos_J;
        if(relJ<0||relJ>30) continue;
        int relI=i-(w-12);
        if(relI<0||relI>6) continue;
        switch(relI){
                case 0:{
                    switch(relJ){
                    case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13: koloruj(14,14);return (char)219;
                    case 3:case 4:case 5: koloruj(10,14);return (char)176;
                    case 14: koloruj(14,8);return (char)176;
                    default: return ' ';
                    }
                    break;}
                case 1:{
                    switch(relJ){
                    case 1:case 2:case 13:case 14:case 15:case 16:case 17: koloruj(14,14);return (char)219;
                    case 3:case 4:case 5: koloruj (10,2);return (char)178;
                    case 6:case 7:case 8:case 9:case 10:case 11:case 12: koloruj(2,10);return (char)177;
                    case 18: koloruj(14,8);return (char)177;
                    default: return ' ';
                    }
                    break;}
                case 2:{
                    switch(relJ){
                    case 17:case 18:case 19:koloruj(14,14);return (char)219;
                    case 0:case 1: koloruj(2,14);return(char)177;
                    case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16: koloruj(2,10);return (char)177;
                    case 20: koloruj(14,8);return (char)177;
                    default: return ' ';
                    }
                    break;}
                case 3:{
                    switch(relJ){

                    case 0: koloruj(2,14);return (char)176;
                    case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13:
                    case 14:case 15:case 16:case 17: case 18:case 19:koloruj(2,10);return (char)177;
                    case 20:case 21: koloruj(14,14); return (char)219;
                    case 22: koloruj(14,8);return (char)176;
                    default: return ' ';
                    }
                    break;}
                case 4:{
                    switch(relJ){
                    case 0:case 5:case 6:case 13: koloruj(2,14);return (char)176;
                    case 1:case 2:case 3:case 4:
                    case 14:case 15:case 16:case 17:case 18:case 19:case 20:case 21: koloruj(2,10);return (char)177;
                    case 22:case 23: koloruj(14,14);return (char)219;
                    case 24: koloruj(14,8);return (char)177;
                    default: return ' ';
                    }
                    break;}
                case 5:{
                    switch(relJ){
                    case 1:case 2:case 3:case 4: case 13 ... 19: koloruj(2,14);return (char)176;
                    case 20 ... 23: koloruj(2,10);return (char)177;
                    case 24: koloruj(14,14);return (char)219;
                    }
                    break;}
                case 6:{
                    switch(relJ){
                    case 20:case 21: koloruj(14,14);return (char)219;
                    case 22:case 23:case 24:case 25: koloruj(2,10);return (char)177;
                    default: return ' ';
                    }
                    break;}
                default: return ' ';
        }
    }
    return ' ';
}
char electric(int w,int i,int j, Gamecontent &Gc)
{
    for (size_t idx=0;idx<Gc.enemies.size();idx++){
        if(Gc.enemies[idx]==nullptr||Gc.enemies[idx]->typ!=TP::NALADOWANY) continue;
        switch(Gc.enemies[idx]->ObecnaAkcja){
        case AK::ACTION1:
            {
                int basepos=13;
                int endpos=29+(idx*10);
                int relJ=j-basepos;
                int relI=i-(w-7);
                if(relI<0||relI>7||relJ<0||relJ>endpos) continue;
                switch(relI){
                case 0:{
                    switch(relJ){
                    case 0:case 1: case 18:
                        koloruj(14,8);
                        return (rand()%3==0)?static_cast<char>(177):static_cast<char>(219);
                    case 14: case 15:
                        koloruj(14,8);
                        return char(220);
                    default: return ' ';
                    }
                break;}
                case 1:{
                    switch(relJ){
                    case 4:case 7:
                    case 13: case 20: case 24:
                    case 26:case 27:
                    case 31:case 32:case 37:case 38:case 43:case 44:case 49:case 50:case 55:case 56:case 61:case 62:case 67:case 68:
                    case 40:case 46:case 52:
                        koloruj(14,8);
                    return char(220);
                    case 1:case 5:case 6:case 11:case 12:
                    case 17:case 23:case 30:
                        koloruj(14,8);
                        return char(223);
                    case 2:case 16:case 21:case 22:case 33:case 60:
                        koloruj(14,8);
                        return (rand()%3==0)?static_cast<char>(177):static_cast<char>(219);
                    default:
                        return ' ';
                    }
                    break;}
                case 2:{
                    switch (relJ){
                    case 0:case 3:case 8:case 12:case 14:case 17:case 19:case 21:case 24:case 27:
                    case 29:case 30:case 33:case 36:case 39:case 42:case 45:case 48:case 51:case 54:case 57:case 60:case 63:case 66:case 69:case 72:
                        koloruj(14,8);
                        return char(219);
                    case 9:case 10:case 16:case 18:case 25:
                        koloruj(14,8);
                    return char(220);
                    default: return ' ';
                    }
                break;}
                case 3:{
                    switch(relJ){
                    case 1:case 2:case 11:case 15:case 34:case 35:case 40:case 41:case 46:case 47:case 52:case 53:case 58:case 59:case 64:case 65:case 70:case 71:
                    case 61:
                        koloruj(14,8);
                        return char(223);
                    case 7:case 21: case 26: case 28:
                        koloruj (14,8);
                        return char(219);
                    default: return ' ';
                    }
                break;}
                case 4:{
                    switch(relJ){
                    case 5: case 20:
                        koloruj(14,8);
                        return (rand()%3==0)?static_cast<char>(177):static_cast<char>(219);
                    case 6:case 19:case 24:case 25:case 28:
                        koloruj(14,8);
                    return char(223);
                    case 23:case 29:
                        koloruj(14,8);
                        return char(220);
                    default: return ' ';
                    }
                break;}
                }

            break;}
            default:break;
        }
    }
    return ' ';
}
