#include <iostream>
#include "ItemManagement.h"
#include <vector>
#include <cmath>
#include <thread>
using namespace std;
DamageResult Eyelander::uzyj(Character &source, Character &cel)
{
    cel.PainReact();
    int obrazenia=source.ATK+this->ATK;
    DamageResult wynik=source.damage(cel,obrazenia,CritMode::RANDOM);
    if(wynik.bitesthedust){glowy++;}
    return wynik;
}
MultiDamageResult StickyBomb::eksploduj(vector<Character*> &enemies){
    MultiDamageResult W;
    CritMode CM;
    DamageResult DR;
    if(this->krytyczna) CM=CritMode::FORCED;
    else CM=CritMode::NONE;
    DR=StickyBomb::wlasciciel->damage(*this->attachedTo,StickyBomb::obrazenia,CM);
    W.Eksplozja.push_back(DR);
    if(debug){cout << ">MAIN: cel=" <<DR.cel
     << " crit=" << DR.krytyczne << "| bitesthedust="<<DR.bitesthedust<<endl;
    this_thread::sleep_for(chrono::seconds(4));}
    int obrazenia_splash=StickyBomb::obrazenia/3;
    for (Character* &wrog:enemies){
        if (wrog==attachedTo||!(czyZyje(wrog))) continue;
        DamageResult splash=StickyBomb::wlasciciel->damage(*wrog,obrazenia_splash,CM);
        W.Eksplozja.push_back(splash);
        if(debug){cout << "SPLASH: cel=" << splash.cel<< " crit=" << splash.krytyczne << "| bitesthedust="<<splash.bitesthedust<<endl;
     this_thread::sleep_for(chrono::seconds(4));}
    }
    return W;
}
vector<StickyBomb*> znajdzbombyWlasciciela(const vector<unique_ptr<NonLivingObject>> &Obiekty, const Character* wlasciciel){
    vector<StickyBomb*> WszystkieBomby;
    for (auto &O:Obiekty){
        if(auto bomba = dynamic_cast<StickyBomb*>(O.get())){
            if(bomba->wlasciciel==wlasciciel)
                WszystkieBomby.push_back(bomba);
        }
    }
    return WszystkieBomby;
}
unique_ptr<StickyBomb> WyrzutnikGranatow::wystrzel(Character &source, Character &cel)
{
    int obrazenia=10*((source.ATK+this->ATK)/8);

    return make_unique<StickyBomb>(source,cel,obrazenia,czy_crit(source.critrate));
}
DamageResult WyrzutnikGranatow::uzyj(Character &source,Character &cel){
    return DamageResult{};
}
void Flashbang::uzyj(vector<Character*> &Cele){
    for(auto &cel:Cele){
        cel->dodajefekt(TypEfektu::OGLUSZENIE,3,*cel);
    }
    quant--;
}
void Flashbang::zakup(){
    quant++;
    cena+=25;
}
void Telephone::zakup(){
    quant++;
}
void Earplugs::zakup(){
    quant++;
}
void Eyelander::ulepsz(){
    LVL++;
    ATK+=105;
}
void WyrzutnikGranatow::ulepsz(){
    LVL++;
    if(LVL%2==0){
        magazynek++;
    }
    else ATK+=2.1*LVL;
}
void Shield::uzyj(Character &source)
{
    dodawaczSP=dodawaczSP+Los(1,0);
    source.SP+=dodawaczSP;
    source.DEF+=Ochrona;
}
void Shield::ulepsz(){
    if(Shield::LVL>3) return;
    LVL++;
    Ochrona++;
    dodawaczSP++;
}
void Scrumpy::uzyj(Character &source){
    uzdrawiacz=uzdrawiacz+Los(400,120);
    source.heal(source,uzdrawiacz);
}
void Scrumpy::ulepsz(){
    LVL++;
    uzdrawiacz*=2;
}
