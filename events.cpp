#include <iostream>
#include <windows.h>
#include <thread>
#include "events.h"

using namespace std;
using Tx=TextID;
void Barka(Gamecontent &Gc)
{
    system("cls");
    tag_notyfikacji(Gc.S.L.get(Tx::HolyNumberAcquire),0,14);
    Beep(260,1000);Beep(440,1000);Beep(440,1000);
    Beep(220,250);
    Beep(440,250);Beep(495,250);Beep(523,250);Beep(495,250);Beep(440,250);
    Beep(390,1100);Beep(390,1100);
    Beep(195,1000);
    Beep(345,750);Beep(320,250);Beep(345,1000);Beep(345,1000);
    Beep(160,250);
    Beep(345,250);Beep(392,250);Beep(440,250);Beep(392,250);Beep(345,250);
    Beep(330,1100);Beep(330,1100);
    this_thread::sleep_for(ZaWarudo::seconds(1));
    Beep(260,1000);Beep(440,1000);Beep(440,1000);
    Beep(220,250);
    Beep(440,250);Beep(495,250);Beep(523,250);Beep(495,250);Beep(440,250);
    Beep(390,1100);Beep(390,1100);
    Beep(195,1000);
    Beep(345,750);Beep(320,250);Beep(345,1000);Beep(345,1000);
    Beep(160,250);
    Beep(292,250);Beep(320,250);Beep(345,250);Beep(320,250);Beep(292,250);Beep(260,2000);
}
