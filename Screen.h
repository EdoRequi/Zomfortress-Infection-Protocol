#ifndef SCREEN_H
#define SCREEN_H
#pragma once
#include "Gamestuff.h"

extern int wskazany;
extern bool debug;
void koloruj(int fg,int bg);
char strzalka (int wskazany,int w,int i,int j,int liczba_wrogow);
char kryt(Gamecontent &Gc,const bool &krytyczny,Character &target, int w,int i,int j);
char rysujgracza(int w, int i, int j,Gamecontent &Gc);
char rysuj_dzialko(int w,int i,int j,Gamecontent &Gc);
char rysuj_zasobnik(int w,int i,int j,Gamecontent &Gc);
char aura(int w,int i,int j,short e,int wskazany,vector<Character*> &enemies,bool smigniecie);
char vomit(int w, int i, int j, int wskazany, vector<Character*> &enemies);
char bomby(int w,int i,int j,int wskazany,vector<Character*> &enemies);
char rysujwroga(int w, int i, int j,Gamecontent &Gc);
char electric(int w,int i,int j,int wskazany, vector<Character*> &enemies);
void pokazStatystyki(const Character* postac,const string& etykieta,Gamecontent &Gc);
void przesunKursorNaGore();
void narysujScene(Gamecontent &Gc);
void szybkieCzyszczenie();
void screen(Gamecontent &Gc);
#endif
