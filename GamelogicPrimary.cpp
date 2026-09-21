#include "Gamelogic.h"
#include "SoundManagement.h"
#include <iostream>
#include <windows.h>
using namespace std;

namespace std{
    namespace ZaWarudo=chrono;
};
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
void configureConsoleInput()
{
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode = 0;
    if (!GetConsoleMode(input, &mode)) {
        return;
    }

    mode |= ENABLE_EXTENDED_FLAGS;
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode &= ~ENABLE_MOUSE_INPUT;

    SetConsoleMode(input, mode);

    FlushConsoleInputBuffer(input);
}
