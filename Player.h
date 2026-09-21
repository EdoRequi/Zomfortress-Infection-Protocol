#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#pragma once
#include "Gamelogic.h"
#include "Character.h"
struct Player : Character{
    TypRoli Klasa;
    std::vector<std::unique_ptr<Przedmiot>> Ekwipunek;
    Player(TypPostaci t,const std::string &im,unsigned int hp,unsigned int basehp,int atk,long exp,int sp,int def,TypRoli klasa,bool doubleatk=false,double mr=0.0,double cr=0.0,short cd=-1, TypAkcji oa=AK::NO_ACTION)
    : Character(t,im,hp,basehp,atk,exp,sp,def,doubleatk,mr,cr,cd,oa),Klasa(klasa)
    {
    }
    void dodajwyposazeniestartowe(const Localization &L);
    template<typename T>
    T* znajdz()
    {
        for (auto& E:Ekwipunek)
        {
            if (auto wynik=dynamic_cast<T*>(E.get()))
            return wynik;
        }
    return nullptr;
    }
};
char rzut_granatem(int w,int i,int j,Player &source);
char sword_pulled(int relI,int relJ,Player &source);
char SBL_pulled(int relI,int relJ,Player &source);
char Demo_special_Caber(int relI,int relJ,Player &source);
char rysujgracza(int w, int i, int j,Gamecontent &Gc);


#endif // PLAYER_H_INCLUDED
