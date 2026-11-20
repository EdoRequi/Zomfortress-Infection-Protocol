#ifndef DEMOMAN_H_INCLUDED
#define DEMOMAN_H_INCLUDED
#pragma once
#include "Gamelogic.h"
#include "Player.h"
#include "events.h"
#include "Controls.h"
#include "ItemManagement.h"
#include "SoundManagement.h"
extern short Barka_status;
void panele(Gamecontent &Gc,Przedmiot &flashbang,Przedmiot &tel,Przedmiot &zatyczki);
void kiedy_efekt(Gamecontent &Gc,MultiDamageResult &ew, Character &source);
void przedmioty_wybrane(Gamecontent &Gc, const Przedmiot &flashbang,const Przedmiot &tel,const Przedmiot &zatyczki);
void AkcjaMiecz(Gamecontent &Gc,Character* &cel,Eyelander* &miecz);
void AkcjaGranatySamoprzylepne(Gamecontent &Gc,Character* &Cel,WyrzutnikGranatow* &SBLauncher);
void AkcjaGorzalka(Gamecontent &Gc,Scrumpy* &gorz);
void AkcjaTarcza(Gamecontent &Gc,Shield* &Sh);
void AkcjaEkwipunek(Gamecontent &Gc,bool &validchoice);
#endif // DEMOMAN_H_INCLUDED
