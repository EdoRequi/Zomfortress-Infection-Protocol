#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <iomanip>
#pragma once
#include "Gamelogic.h"
void UstawTekst(short width, short height);
void uzyjUTF8(wchar_t znak, int ile);
void ustawienia(bool &debug,Settings &S);
void przycisk(std::string tekst,Settings &S, const short numer_aktyw);
void menu(bool &debug,Settings &S);


#endif // MENU_H_INCLUDED
