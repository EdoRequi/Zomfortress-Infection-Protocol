#ifndef ITEMMANAGEMENT_H
#define ITEMMANAGEMENT_H
#pragma once
#include "Character.h"
#include <string>
#include <memory>
struct Character;
struct NonLivingObject;
struct Przedmiot
{
    std::string nazwa;
    int cena;
    int quant;
    Przedmiot(std::string n="N/A",int c=0,int q=0):nazwa(n),cena(c),quant(q){}
    virtual ~Przedmiot() = default;
};
struct Flashbang : Przedmiot{
    Flashbang(std::string n,int c=0,int q=0)
    :Przedmiot(n,c,q){}
    void uzyj(std::vector<Character*> &Cele);
    void zakup();
};
struct Telephone : Przedmiot{
    Telephone(std::string n,int c=0,int q=0)
    :Przedmiot(n,c,q){}
    void zakup();
};
struct Earplugs : Przedmiot{
    Earplugs(std::string n,int c=0,int q=0)
    :Przedmiot(n,c,q){}
    void zakup();
};
struct SupportItem : Przedmiot{
    unsigned int LVL;

    SupportItem(std::string n,int c=0,int q=0,unsigned int lvl=0)
    :Przedmiot(n,c,q),LVL(lvl)
    {}
    virtual void uzyj(Character &source)=0;
    virtual void ulepsz()=0;
};
struct DamageResult;
struct Bron : Przedmiot
{
    int ATK;//sila ataku broni
    unsigned int LVL;
    std::string DzwiekUderzenia;
    std::string DzwiekCrita;
    Bron(std::string n,int c=0,int q=0,int atk=0,unsigned int lvl=0,std::string du="",std::string dc="")
    :Przedmiot(n,c,q),ATK(atk),LVL(lvl),DzwiekUderzenia(du),DzwiekCrita(dc)
    {}
    virtual DamageResult uzyj(Character &source,Character &cel)=0;

    virtual void ulepsz()=0;
};
struct Eyelander : Bron
{
    short glowy;
    Eyelander(std::string n="N/A",int c=0,int q=0,int atk=0,unsigned int lvl=0,std::string du="",std::string dc="",int gl=0)
    :Bron(n,c,q,atk,lvl,du,dc),glowy(gl)
    {}
    DamageResult uzyj(Character &source,Character &cel) override;
    void ulepsz() override;
};
struct StickyBomb : NonLivingObject{
    Character* wlasciciel=nullptr;
    Character *attachedTo=nullptr;
    int obrazenia;
    bool krytyczna;
    StickyBomb(Character& wl,Character& aT,int o= 0,bool k=false):wlasciciel(&wl),attachedTo(&aT),obrazenia(o),krytyczna(k){}
    MultiDamageResult eksploduj(std::vector<Character*> &enemies);
};
std::vector<StickyBomb*> znajdzbombyWlasciciela(const std::vector<std::unique_ptr<NonLivingObject>> &Obiekty, const Character* wlasciciel);
struct WyrzutnikGranatow : Bron
{
    short magazynek=5;
     WyrzutnikGranatow(std::string n,int c=0,int q=0,int atk=0,unsigned int lvl=0,std::string du="",std::string dc="",short m=0)
    :Bron(n,c,q,atk,lvl,du,dc),magazynek(m)
    {}

    std::unique_ptr<StickyBomb> wystrzel(Character& source,Character &cel);
    DamageResult uzyj(Character &source,Character &cel) override;
    void ulepsz() override;
};
struct Shield : SupportItem{
    int dodawaczSP;
    int Ochrona;
    Shield(std::string n,int c=0,int q=0,int lvl=0,int addSP=0,int O=1)
    :SupportItem(n,c,q,lvl),dodawaczSP(addSP),Ochrona(O)
    {}
    void uzyj(Character &source);
    void ulepsz() override;
} ;
struct Scrumpy :SupportItem{
    int uzdrawiacz;
    Scrumpy(std::string n,int c=0,int q=0,int lvl=0,int addHP=0)
    :SupportItem(n,c,q,lvl),uzdrawiacz(addHP)
    {}
    void uzyj(Character &source);
    void ulepsz() override;
};
#endif // ITEMMANAGEMENT_H_INCLUDED
