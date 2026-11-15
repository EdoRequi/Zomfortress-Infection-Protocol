#ifndef SCREEN_H
#define SCREEN_H
#pragma once
#include "Player.h"
#include "labels.h"
#include "Visual.h"
#include "TextManagement.h"
bool EverybodyDEAD_NOT_BIG_SUPRISE(const std::vector<Character*> &enemies);
extern Language Jezyk;
void koloruj(int fg,int bg);
char rysuj_dzialko(int w,int i,int j,Gamecontent &Gc);
char rysuj_zasobnik(int w,int i,int j,Gamecontent &Gc);
std::vector<int> PozBomby(int relJ,int l_bomb);
char bomby(int w,int i,int j,Gamecontent &Gc);
char rysujwroga(int w, int i, int j,Gamecontent &Gc);
char Exploder(int w,int i,int j,std::vector<Character*> &enemies);
void pokazStatystyki(const Character* postac,const std::string& etykieta,Gamecontent &Gc);
void przesunKursorNaGore();
void narysujScene(Gamecontent &Gc);
void szybkieCzyszczenie();
void screen(Gamecontent &Gc);
#endif
