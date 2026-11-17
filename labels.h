#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED
#include <vector>
#include <iomanip>
#pragma once
#include "Gamelogic.h"
#include "Player.h"
#include "TextManagement.h"

struct Kursor{
    short x;
    short y;
    short startX;
    Kursor(short X,short Y,short stX):x(X),y(Y),startX(stX){}
    void newLine(){y++; x=startX;}
    void resetujx(){if(startX!=x)x=startX;}
    void tab(short pozx,short pozy){
        x=pozx;y=pozy;startX=pozx;
    }
};
struct Piksel{
    char znak=' ';
    int fg_kolor=0;
    int bg_kolor=0;
    Piksel(char z,int fg,int bg):znak(z),fg_kolor(fg),bg_kolor(bg){}
};
class Gui{
    private:
        std::vector<std::vector<Piksel>> ekran;
        int WYS=0;
        int SZER=100;
    public:
        Gui() {
            wyczysc();
        }
        void wyczysc() {
            ekran.assign(WYS, std::vector<Piksel>(SZER, Piksel(' ',15,0)));
        }
    // Wpisuje tekst w strukturze siatki bez ruszania kursora konsoli
    void SetHeight(int newWys){
        WYS+=newWys;
        ekran.resize(WYS,std::vector<Piksel>(SZER,Piksel(' ',15,0)));
    }
    void naniesTekst(Kursor &k,int fg,int bg,const std::string& tekst){

        bool zmianalinii=false;
        for (char ch:tekst) {
            if (ch=='\n') {
                k.newLine();
                zmianalinii=true;
                continue;
            }
            // Zabezpieczenie przed wyjsciem poza ekran
            if (k.y>=0&&k.y<WYS&&k.x>=0&&k.x<SZER) {
                ekran[k.y][k.x].znak=ch;
                ekran[k.y][k.x].fg_kolor=fg;
                ekran[k.y][k.x].bg_kolor=bg;
                k.x++;
            }
        }
        if(zmianalinii) k.resetujx();
    }
    void wyswietl(){
        COORD topleft={0,18};
        int curfg=-1,curbg=-1;
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(h, topleft);
        for (int y=0;y<WYS;y++){
            for(int x=0;x<SZER;x++){
                const Piksel& p=ekran[y][x];
                if (curfg!=p.fg_kolor||curbg!=p.bg_kolor){
                    curfg=p.fg_kolor;curbg=p.bg_kolor;
                }
                koloruj(curfg,curbg);
                std::cout<<p.znak;
            }
            std::cout<<std::endl;
        }
    }
};
void pokazStatystyki(Gui &g,Kursor &k,const Character &postac,const std::string& etykieta);
void ShowStatystyki(Gamecontent &Gc);
#endif // LABELS_H_INCLUDED
