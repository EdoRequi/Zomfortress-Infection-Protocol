#ifndef GAMESTUFF_H
#define GAMESTUFF_H
#include <string>
#include <vector>
#pragma once
#include "SoundManagement.h"
#include "Gamelogic.h"
#include "Character.h"
#include "ItemManagement.h"
#include "Screen.h"
struct Przedmiot;
extern bool smigniecie;
extern bool CzyBylSklep;
extern bool kolejComm;

extern bool czy_crit(double critrate);
void uzyjUTF8(wchar_t znak,int ile);
enum class DamageTyp{
    NONE,

    MEELE,
    EXPLOSIVE,
    SHOTGUN,
    HEALING

};
int Los(int M,int m);
struct linijkaD{
    std::string S;
    int czas;
    const char* path;
};
void Barka(Gamecontent &Gc);
void usunprzedzial(std::string &s,int I);
void Dialog(std::string Nazwa, int kolor_fontu,int kolor_tla, std::string S);
void AdvDialog(std::string Nazwa, int kolor_fontu, int kolor_tla, std::vector<linijkaD> Kwestie);
void panele(Gamecontent &Gc,Przedmiot &flashbang,Przedmiot &tel,Przedmiot &zatyczki); //graficzne
void ofensywa_wybrana(Gamecontent &Gc);
void wsparcie_wybrane(Gamecontent &Gc);
void kiedy_efekt(Gamecontent &Gc,MultiDamageResult &ew, Character &source);
void przedmioty_wybrane(Gamecontent &Gc, const Przedmiot &flashbang,const Przedmiot &tel,const Przedmiot &zatyczki);
bool EverybodyDEAD_NOT_BIG_SUPRISE(const std::vector<Character*>& enemies);
short target(Gamecontent &Gc);
//logika wczytywania klawiszy
void sklep_input(Gamecontent &Gc,Przedmiot &flashbang,Przedmiot &tel,Przedmiot &zatyczki);
extern short Barka_status;
void Input(short &Barka_status,Gamecontent &Gc,Przedmiot &fajerwerk,Przedmiot &tel,Przedmiot & zatyczki);
void DzialTURN(Gamecontent &Gc); // runda NPCtow
void ZasobTURN(Gamecontent &Gc);
void NaLZomTURN(Gamecontent &Gc,Character* energ);
void BombyTurn(Gamecontent &Gc,Character* Expld);
void ToxZomTURN(Gamecontent &Gc,Character* ToxicZombie,const Przedmiot &zatyczki);
void ZomTURN(Gamecontent &Gc,short odliczanie,Character* &t,const Przedmiot &zatyczki);
void ciagla_walka(Gamecontent &Gc,short &Barka_status,bool &CzyBylSklep); // scalajacy kod
#endif // GAMESTUFF_H_INCLUDED
