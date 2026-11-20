#include "Gamelogic.h"
#include "SoundManagement.h"
#include <iostream>
#include <windows.h>
#include <random>
#include<cstdlib>
using namespace std;

namespace std{
    namespace ZaWarudo=chrono;
};
bool czy_pudlo(double missrate){
    double los = (double)rand() / RAND_MAX; // Losowa liczba z zakresu 0.0 - 1.0
    return los<missrate;
}
bool czy_crit(double critrate){
    double los=(double)rand()/RAND_MAX;
    return los<critrate;
}
int Los(int M,int m){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(m,M);
    return distrib(gen);
}
void koloruj(int fg,int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD kolor = (bg << 4) | fg; // Tlo przesuniete w lewo o 4 bity
    SetConsoleTextAttribute(hConsole, kolor);
}
void narysujScene(Gamecontent &Gc);
void ReturnToZero(Gamecontent &Gc) //This ability of 'Gold Experience Requiem' Stand is a cause of Diavolo's inifite death loop
{
    Gc.SE.R=ScreenEfekt::NONE;Gc.affectedT.clear();Gc.dane.clear();
    narysujScene(Gc);
}
void aktualizuj_efekt(Gamecontent &Gc){
    if(Gc.SE.R==ScreenEfekt::NONE) return;
    if (ZaWarudo::steady_clock::now()>=Gc.CzasTrwania){
        ReturnToZero(Gc);
    }
}
MultiDamageResult nowyMDR(vector<DamageResult> multi){
    MultiDamageResult MDR;
    MDR.Eksplozja=multi;
    return MDR;
}

