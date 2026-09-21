#ifndef SCREEN_H
#define SCREEN_H
#pragma once
#include "Player.h"
#include "Character.h"
bool EverybodyDEAD_NOT_BIG_SUPRISE(const std::vector<Character*> &enemies);
struct Character;
extern Language Jezyk;
void koloruj(int fg,int bg);
char strzalka (bool wybor,int wskazany,int w,int i,int j,int liczba_wrogow);
char efekt_napis(Gamecontent &Gc,Character* &cel, int w,int i,int j,char cyfra);
char rysuj_dzialko(int w,int i,int j,Gamecontent &Gc);
char rysuj_zasobnik(int w,int i,int j,Gamecontent &Gc);
char aura(int w,int i,int j,short e,int wskazany,std::vector<Character*> &enemies,bool smigniecie);
char vomit(int w, int i, int j, int wskazany, std::vector<Character*> &enemies);
std::vector<int> PozBomby(int relJ,int l_bomb);
char bomby(int w,int i,int j,Gamecontent &Gc);
char rysujwroga(int w, int i, int j,Gamecontent &Gc);
char electric(int w,int i,int j,int wskazany, std::vector<Character*> &enemies);
char Exploder(int w,int i,int j,std::vector<Character*> &enemies);
void pokazStatystyki(const Character* postac,const std::string& etykieta,Gamecontent &Gc);
void przesunKursorNaGore();
void narysujScene(Gamecontent &Gc);
void szybkieCzyszczenie();
void screen(Gamecontent &Gc);
#endif
