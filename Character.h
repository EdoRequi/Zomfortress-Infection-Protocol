#ifndef CHARACTER_H
#define CHARACTER_H
#pragma once
#include "Gamelogic.h"
#include "SoundManagement.h"
#include "ItemManagement.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <thread>
using Tx=TextID;
using AK=TypAkcji;
extern int liczba_wrogow;
extern unsigned int base_HP_wrog;
struct Przedmiot;
extern bool debug;
void koloruj(int fg,int bg);
extern bool czy_crit(double critrate);
int Los(int M,int m);
extern bool czyZyje(const Character* ch);
extern bool czyZyje(const Character &ch);
void SprawdzZIndeksem(Character* C, const std::vector<Character*>& enemies,int &wskazany);
enum TypPostaci {
    None,

    GRACZ,
    DZIALKO,
    ZASOBNIK,

    ZWYKLY,
    SZYBKI,
    TYTANOWY,
    TOKSYCZNY,
    NALADOWANY,
    EXPLODER,
    COMMANDER
};
enum TypEfektu{
    NA,

    OGLUSZENIE,
    UPICIE,
    WZMOCNIENIE,
    ZATRUCIE,
    OSLABIENIE,
    KRYTOWANIE
};

using TP=TypPostaci;
using TE=TypEfektu;

struct StatusEfekt
{
    bool aktywny=false; //sprawdza, czy efekt jest aktywny
    TypEfektu ID=NA; // ID efektu
    short duration=0; //tury trwania efektu
    Character* target=nullptr; //wskaznik na postac

    void nalozEfekt(Character& postac){
        if (!target){
    aktywny=true;
    target=&postac;
        }
    }

    void updateEfekt(){ //sprawdza, czy efekt nadal powinien trwac
        if (aktywny&&target){
            if (duration>0) duration--;
            if (duration==0) aktywny=false;
        }
    }
};
void tag_efektu(const std::string &napis,int kolor_f,int kolor_b);
struct Character
{
    TypPostaci typ;
    std::string Imie;
    unsigned int HP;//domyslne hp
    unsigned int base_HP;//stala hp
    int ATK;// domyslny atak(dla zasobnika:domyslne leczone HP)
    long EXP; //doswiadczenie gracza (w opracowaniu)
    int SP;//punkty specjalne
    int DEF;//punkty obrony
    bool czy_doubleATK;
    double missrate;
    double critrate;
    short odliczanie;
    TypAkcji ObecnaAkcja;
    Character()
    : typ(TP::None), Imie(""), HP(0), base_HP(0), ATK(0), EXP(0), SP(0), DEF(0), czy_doubleATK(false), missrate(0.0),critrate(0.0),odliczanie(-1),ObecnaAkcja(AK::NO_ACTION) {}
    Character(TypPostaci t, const std::string& im, unsigned int hp, unsigned int basehp, int atk, long exp,int sp, int def, bool doubleAtk=false, double mr=0.0,double cr=0.0,short cd=-1,TypAkcji oa=AK::NO_ACTION)
        : typ(t),Imie(im), HP(hp),base_HP(basehp), ATK(atk), EXP(exp), SP(sp), DEF(def), czy_doubleATK(doubleAtk),missrate(mr),critrate(cr),odliczanie(cd),ObecnaAkcja(oa) {}
    std::vector<StatusEfekt> efekty;
    void dodajefekt(TypEfektu ID,short duration,Character& target)
    {
        StatusEfekt efekt;
        efekt.ID=ID;
        efekt.duration=duration;
        efekt.nalozEfekt(target);
        target.efekty.push_back(efekt);
    }
    void updateujEfekty(Character &target){
        for (auto& efekt:efekty){
                if (!(czyZyje(*&target))) efekt.aktywny=false;
                efekt.updateEfekt();
        }
        //jezeli ktorykolwiek z nalozonych efektow przyjmie wartosc aktywny==false, ustaw na sam koniec i usun
        efekty.erase(std::remove_if(efekty.begin(),efekty.end(),[](const StatusEfekt& e) {return!e.aktywny;}),efekty.end());
    }
    void wypiszEfekty()const
    {
        bool maefekty=false;
        for (const auto& efekt:efekty) {
            if (efekt.aktywny==true){
                maefekty=true;
                switch (efekt.ID)
                {
                case OGLUSZENIE:{
                    tag_efektu(L.get(Tx::Eff_Stun),15,12);
                    break;}
                case UPICIE:{
                    tag_efektu(L.get(Tx::Eff_Drunk),3,12);
                    break;}
                case WZMOCNIENIE:{
                    tag_efektu(L.get(Tx::Eff_Powered),14,12);
                    break;}
                case ZATRUCIE:{
                    tag_efektu(L.get(Tx::Eff_Poisoned),10,12);
                    break;}
                case OSLABIENIE:{
                    tag_efektu(L.get(Tx::Eff_Weakness),13,12);
                    break;}
                case KRYTOWANIE:{
                    tag_efektu(L.get(Tx::Eff_MoreCritrate),11,12);
                    break;}
                default:
                    std::cout<<L.get(Tx::Error_info);break;

                }
                }
            }
            if (!maefekty)
            std::cout<<std::endl;
        }

    void heal(Character &target,int ilosc){
        if(target.HP+ilosc<=target.base_HP) target.HP+=ilosc;
        else target.HP=target.base_HP;
    }
    void skrytowanie()const{
        dzwiek("Audio_RPG\\krytyczny_cios.wav");
        koloruj(10,0);
        std::cout<<Imie<<L.get(Tx::Obj_DealsCrit)<<std::endl;
        koloruj(7,0);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    DamageResult damage(Character &target,int ilosc,CritMode CM){
        DamageResult wynik;
        wynik.cel=&target;
        switch(CM){
            case CritMode::RANDOM: wynik.krytyczne=czy_crit(this->critrate); break;
            case CritMode::FORCED: wynik.krytyczne=true; break;
            default:wynik.krytyczne=false; break;
        }
        unsigned int obrazenia=ilosc/target.DEF;
        if(wynik.krytyczne) obrazenia*=2;
        if(obrazenia>=target.HP){
            target.HP=0;
            wynik.bitesthedust=true;
        }
        else
            target.HP-=obrazenia;
        wynik.obrazenia=obrazenia;
        return wynik;
    }
    void spudlowanie()const{
        switch(typ){
        case EXPLODER:{
            std::this_thread::sleep_for(std::ZaWarudo::seconds(3));
        dzwiek("Audio_RPG\\extinguish.wav");
        koloruj(11,8);
        std::cout<<L.get(Tx::Expl_Miss1)<<Imie<<L.get(Tx::Expl_Miss1_1)<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout<<L.get(Tx::Expl_Miss2)<<Imie<<L.get(Tx::Expl_Miss2_1)<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        default:{
            dzwiek("Audio_RPG\\Banana_slip.wav");
            koloruj(11,8);
            std::cout<<Imie<<L.get(Tx::Obj_Miss)<<"\n";
            koloruj(7,0);
            std::this_thread::sleep_for(std::ZaWarudo::seconds(2));
            break;
            }
        }
    }
    void PainReact()const{
        switch (typ)
        {
            case GRACZ:
                {

                int demo_ouch=Los(1,0);
                switch (demo_ouch)
                {
                case 1:
                    dzwiek("Audio_RPG\\Demoman_response_painsharp01.wav");
                    break;
                default:
                    dzwiek("Audio_RPG\\damage_taken.wav");
                    break;
                }
                break;
                }
                case DZIALKO:
                case ZASOBNIK:
                    {
                    dzwiek("Audio_RPG\\sentry_ouch.wav");
                    break;
                    }
                default:
                    {
                    dzwiek("Audio_RPG\\damage_taken.wav");
                    break;
                    }

        }
    }
    virtual ~Character() = default;
};
void nowyWrog(Gamecontent &Gc, unsigned int &base_HP_wrog); //wywolanie nowych obiektow
void noweDzialko(long x,Character* &dzialko,const Localization &L);
void nowyZasobnik(long x,Character* &zasobnik,const Localization &L);
#endif // CHARACTER_H_INCLUDED
