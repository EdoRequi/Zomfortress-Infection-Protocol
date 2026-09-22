#include <iostream>
#include <cstdlib>
#include "Player.h"
#include <time.h>
#include <thread>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
using Tx=TextID;
class Localization;
int liczba_wrogow=1;
unsigned int base_HP_wrog=150;
bool czyZyje(const Character* ch){
    return ch!=nullptr&&ch->HP>0;
}
bool czyZyje(const Character &ch){
    return ch.HP>0;
}
void SprawdzZIndeksem(Character* C, const std::vector<Character*>& enemies,int &wskazany){
    for (int r=0;r<enemies.size();r++){
        if (enemies[r]==C&&czyZyje(C)){
            wskazany=r+1;
        }
    }
}
void tag_efektu(const string &napis,int kolor_f,int kolor_b){
    int miejsce=30-napis.size();
    std::cout<<"|";koloruj(kolor_f,kolor_b);std::cout<<napis<<std::setw(miejsce)<<std::right;std::cout<<" ";koloruj(15,0);std::cout<<"|\n";
}
void Player::dodajwyposazeniestartowe(const Localization &L){
    switch(Klasa){
        case TypRoli::DEMOMAN:{
            auto miecz = make_unique<Eyelander>(L.get(Tx::I_Sword),120,1,120,1,"Audio_RPG\\miecz_machniecie.wav","Audio_RPG\\miecz_machniecie.wav",0);
            Ekwipunek.push_back(move(miecz));
            auto wyrzutnik=make_unique<WyrzutnikGranatow>(L.get(Tx::I_SBLauncher),90,1,60,1,"Audio_RPG\\bomba_wyrzut.wav","Audio_RPG\\bomba_wyrzut.wav",5);
            Ekwipunek.push_back(move(wyrzutnik));

            auto Gorzalka = make_unique<Scrumpy>(L.get(Tx::I_Scrumpy),0,1,1,32);
            Ekwipunek.push_back(move(Gorzalka));

            auto Tarcza = make_unique<Shield>(L.get(Tx::I_Shield),55,1,1,2,1);
            Ekwipunek.push_back(move(Tarcza));

            auto flashbang=make_unique<Flashbang>(L.get(Tx::I_flashbang),25,0);
            Ekwipunek.push_back(move(flashbang));

            auto tel=make_unique<Telephone>(L.get(Tx::I_phone),500,0);
            Ekwipunek.push_back(move(tel));

            auto zatyczki=make_unique<Earplugs>(L.get(Tx::I_earplugs),250,0);
            Ekwipunek.push_back(move(zatyczki));
        break;}
    }
}
Character* generujZombie(long x,unsigned int &lok_HP_wrog,const bool CV,const Localization &L){
    Character* jedn=nullptr;
        short losujszablon=Los(100,0);
        unsigned int health;
        switch (x)
        {
        case 1:
            health=lok_HP_wrog;
            jedn = new Character(TP::ZWYKLY,"Zombie", health, health, 20+(x * 2), x * 0.8, 0, 1, false,0.005,0.1);
            //NOTA: TEN TEKST SLUZYL DO TESTOW
            //if(!CV) jedn=new Character(TP::COMMANDER,"Zombie Dowodca",health,health,50+(x*2),x*2,0,2,false,0.02,0.01);
            //jedn = new Character(TP::ZWYKLY,"TEST", health, health, 20+(x * 2), x * 0.8, 0, 1, false,0.005,1);
            //jedn = new Character(TP::TOKSYCZNY,"Toksyczny Zombie", health, health, 20+(x * 2), x * 0.8, 0, 1, false,0.005);
            //jedn=new Character("Zombie Samobojca",health, health,9999, x*1.2, 0,1,false,0.005,3);
            //jedn=new Character(TP::NALADOWANY,"Naladowany Zombie",health, health, 0+(x*1.7), x*1, 5,2,false,0.01);
            break;
        case 2 ... 5:{
            switch (losujszablon){
            case 0 ... 45:
                health = lok_HP_wrog*pow(1.06,x-1);
                jedn = new Character(TP::ZWYKLY,"Zombie", health, health, 20+(x * 2), x * 0.6, 0, 1, false,0.05,0.03);
                break;
            case 46 ... 59:{
                health=lok_HP_wrog*pow(1.05,x-1);
                jedn=new Character(TP::SZYBKI,L.get(Tx::Name_FastZ),health, health, 25+(x*1.1), x*0.6, 0,1,true,0.06,0.05);
                break;}
            case 60 ... 69:{
                health=lok_HP_wrog*pow(1.08,x-1);
                jedn=new Character(TP::NALADOWANY,L.get(Tx::Name_ElecZ),health, health, 20+(x*1.5), x*0.8, 0,2,false,0.03,0.06);
                break;}
            case 70 ... 99:{
                health=lok_HP_wrog*pow(1.09,x-1);
                jedn=new Character(TP::TYTANOWY,L.get(Tx::Name_TitanZ),health, health, 30+(x*2), x*1, 0,3,false,0.05,0.03);
                break;}
            }
        break;}
        case 6 ... 10:{
            switch (losujszablon){
            case 0 ... 19:
                health=lok_HP_wrog*pow(1.02,x-1);
                jedn=new Character(TP::ZWYKLY,"Zombie",health, health, 25+(x*2.3), x*1, 0,1,false,0.04,0.03);
                break;
            case 20 ... 37:{
                health=lok_HP_wrog*pow(1.01,x-1);
                jedn=new Character(TP::SZYBKI,L.get(Tx::Name_FastZ),health, health, 25+(x*1.25), x*1, 0,1,true,0.04,0.05);
                break;}
            case 38 ... 59:{
                health=lok_HP_wrog*pow(1.05,x-1);
                jedn=new Character(TP::NALADOWANY,L.get(Tx::Name_ElecZ),health, health, 25+(x*1.8), x*1, 0,2,false,0.03,0.06);
                break;}
            case 60 ... 85:{
                health=lok_HP_wrog*pow(1.03,x-1);
                jedn=new Character(TP::TYTANOWY,L.get(Tx::Name_TitanZ),health, health, 50+(x*3.4), x*1.5, 0,3,false,0.02,0.02);
                break;}
            case 86 ... 99:{
                health=lok_HP_wrog*pow(1.05,x-1);
                jedn=new Character(TP::TOKSYCZNY,L.get(Tx::Name_ToxicZ),health, health, 20+(x*2.1), x*1.5, 0,1,false,0.03,0.04);
                break;}
            }
        break;}
        default:{
            switch (losujszablon){
            case 0 ... 14:
                health=lok_HP_wrog*pow(1.06,x-1);
                jedn=new Character(TP::ZWYKLY,"Zombie",health, health, 50 + (x * 4.6), x*0.5, 0,1,false,0.02,0.03);
                break;
            case 15 ... 30:{
                health=lok_HP_wrog*pow(1.06,x-1);
                jedn=new Character(TP::SZYBKI,L.get(Tx::Name_FastZ),health, health, 55 + (x * 3.2), x*0.5, 0,1,true,0.04,0.05);
                break;}
            case 31 ... 39:{
                if (CV){ health=lok_HP_wrog*pow(1.1,x-1);
                jedn=new Character(TP::COMMANDER,L.get(Tx::Name_CommandZ),health,health,50+(x*2),x*2,0,2,false,0.02,0.01);}
                else{
                    health=lok_HP_wrog*pow(1.06,x-1);
                jedn=new Character(TP::ZWYKLY,"Zombie",health, health, 50 + (x * 4.6), x*0.5, 0,1,false,0.02,0.03);
                }
                break;}
            case 40 ... 54:{
                health=lok_HP_wrog*pow(1.1,x-1);
                jedn=new Character(TP::NALADOWANY,L.get(Tx::Name_ElecZ),health, health, 50+(x*2.4), x*1, 0,2,false,0.03,0.06);
                break;}
            case 55 ... 64:{
                double tytanowy_mnoznik=x<20?1.2:(x<30?1.1:1.05);
                health=static_cast<unsigned int>(lok_HP_wrog*pow(tytanowy_mnoznik,x-1));
                jedn=new Character(TP::TYTANOWY,L.get(Tx::Name_TitanZ),health, health, 100 + (x * 5), x*1, 0,3,false,0.01,0.02);
                break;
            }
            case 65 ... 75:{
                health=static_cast<unsigned int>(lok_HP_wrog*pow(1.06,x-1));
                unsigned short l_licznika=Los(4,2);
                jedn=new Character(TP::EXPLODER,L.get(Tx::Name_ExplZ),health, health,9999, x*1.2, 0,1,false,0.05,0,l_licznika);
                break;}
            case 76:case 77:case 78:case 79:case 80:case 81:case 82:case 83:case 84:case 85:case 86:case 87:case 88:case 89:
            case 90:case 91:case 92:case 93:case 94:case 95:case 96:case 97:case 98:case 99:{
                health=static_cast<unsigned int>(lok_HP_wrog*pow(1.15,x-1));
                jedn=new Character(TP::TOKSYCZNY,L.get(Tx::Name_ToxicZ),health, health, 50 + (x * 3.5), x*1, 0,1,false,0.03,0.05);
                break;}
            }
        break;}

        }
    return jedn;
}
int gen_l_wrogow(long x){
    switch(x){
    case 1:
        return 1;
    case 2:
        return 2;
        case 3:case 4:case 5:
        return Los(3,1);
    case 6:case 7:case 8:case 9:case 10:
        return Los(3,2);
    case 11 ... 19:
        return Los(5,2);
    default:
        return Los(5,4);
        break;
    }
}
void nowyWrog(Gamecontent &Gc, unsigned int &base_HP_wrog)
{
    Character *jedn=nullptr; int IDX;
    bool Commandervalid=false;
    liczba_wrogow=gen_l_wrogow(Gc.x);
    for (IDX=0;IDX<liczba_wrogow;IDX++) {
            unsigned int lok_HP_wrog=base_HP_wrog;
            jedn=generujZombie(Gc.x,lok_HP_wrog,Commandervalid,Gc.S.L);
        if(!jedn) {cerr<<Gc.S.L.get(Tx::Error_info)<<endl;
        return;}
        if (jedn->typ==TP::COMMANDER) Commandervalid=true;
        Gc.enemies.push_back(jedn);
        if (debug==true){
            cout << "Created enemy[" << IDX << "] | address: " <<jedn<<" | HP: " <<jedn->HP<<" | DEF: "<<jedn->DEF<<" | TYPE: "<<jedn->typ<<'\n';
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        for (const Character* wrog:Gc.enemies){
    // Dostosowanie base_HP_wrog do najnizszego HP wroga(jesli jest)
            if (czyZyje(wrog)&&wrog->HP<base_HP_wrog)
            {
                base_HP_wrog=wrog->HP;
            }
        }
    }
        if (Gc.debug==true){
            cout<<L.get(Tx::Deb_gen)<<Gc.enemies.size()<<" zombie\n";
            cout<<L.get(Tx::Deb_highest_localHP)<< base_HP_wrog<<endl;
            this_thread::sleep_for(chrono::seconds(3));
        }
}
void noweDzialko(long x,Character* &dzialko, const Localization &L)
{
    delete dzialko;
    dzialko=nullptr;
    unsigned int min_hp=110+(x*10);
    unsigned int max_hp=160+(x*25);
    unsigned int base_HP_dzialko = Los(max_hp,min_hp);
    dzialko=new Character(TP::DZIALKO,L.get(Tx::Name_Sentry),base_HP_dzialko,base_HP_dzialko,250+2*(x/5),0,0,2);
}

void nowyZasobnik(long x,Character* &zasobnik,const Localization &L)
{
    delete zasobnik;
    zasobnik=nullptr;
    unsigned int min_hp=80+(x*7);
    unsigned int max_hp=110+(x*20);
    long n=base_HP_wrog*pow(1.21,x-1);
    unsigned int base_HP_zasobnik = Los(max_hp,min_hp);
    zasobnik=new Character(TP::ZASOBNIK,L.get(Tx::Name_Dispenser),base_HP_zasobnik,base_HP_zasobnik,50*(float(x)/4),0,0,3);
}
