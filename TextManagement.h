#ifndef TEXTMANAGEMENT_H_INCLUDED
#define TEXTMANAGEMENT_H_INCLUDED
#include <vector>
#include <iostream>
#include <thread>
#include <iomanip>
#pragma once
#include "SoundManagement.h"
std::string LFormat(const std::string &tekst,size_t szer);
std::string PFormat(const std::string &tekst,size_t szer);
void koloruj(int fg,int bg);
struct Character;
struct Gamecontent;
struct linijkaD{
    std::string S;
    int czas;
    const char* path;
};
void Dialog(std::string Nazwa, int kolor_fontu,int kolor_tla, std::string S);
void AdvDialog(std::string Nazwa, int kolor_fontu, int kolor_tla, std::vector<linijkaD> Kwestie);
void tag_notyfikacji(const std::string &napis,int kolor_fontu,int kolor_tla);
#endif // TEXTMANAGEMENT_H_INCLUDED
