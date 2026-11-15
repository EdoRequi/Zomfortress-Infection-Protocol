#ifndef VISUAL_H_INCLUDED
#define VISUAL_H_INCLUDED
#pragma once
#include "ItemManagement.h"
#include "Player.h"
char electric(int w,int i,int j, Gamecontent &Gc);
char aura(int w, int i, int j, int wskazany, Gamecontent &Gc);
char vomit(int w, int i, int j, Gamecontent &Gc);
char strzalka (bool wybor,int wskazany,int w,int i,int j,int liczba_wrogow);
char efekt_napis(Gamecontent &Gc,Character* &cel, int w,int i,int j,char cyfra);
#endif // VISUAL_H_INCLUDED
