#ifndef GAMESTUFF_H
#define GAMESTUFF_H
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <thread>
#pragma once
using namespace std;
extern short IDwybor;
extern short WCzcionki;
extern unsigned int base_HP_wrog;
extern bool debug;
extern int kodscreen;
extern int glowy;
extern bool dlacase;
extern short e;
extern bool smigniecie;
extern short tarcza;
extern short WATK;
extern short MATK;
extern bool CzyBylSklep;
extern int liczba_wrogow;
extern bool wybor;
extern bool kolejComm;
struct Character;
extern bool czyZyje(const Character* ch);
extern bool czyZyje(const Character &ch);
extern bool czy_crit(double critrate);
void koloruj(int fg,int bg);
void uzyjUTF8(wchar_t znak,int ile);
void dzwiek(const char* sciezka); //dziwekowe
void dzwiek_ciagly(const char* sciezka);
void dzwiek_loop(const char*sciezka);
struct Settings;
extern Settings S;

enum Language{
    NONE,

    POLSKI,
    ANGIELSKI
};
extern Language Jezyk;
int Los(int M,int m);
struct linijkaD{
    string S;
    int czas;
    const char* path;
};
struct Przedmiot
{
    string nazwa;
    int cena;
    int quant;
};
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
struct ScreenEfekt
{
    enum Rodzaj
    {
        NONE,
        CRITICAL,
        MISS,
        POISON,
        ELECTRIC,
        HEAL
    };

    Rodzaj r = NONE;
    Character* target = nullptr;
};
using TP=TypPostaci;
using TE=TypEfektu;
struct AttackResult{
    int obrazenia=0;
    bool krytyczne=false;
    bool bitesthedust=false;//JoJo fans will know
};
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
struct StatusEfekt;
struct Character
{
    TypPostaci typ;
    string Imie;
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
    Character()
    : typ(TP::None), Imie(""), HP(0), base_HP(0), ATK(0), EXP(0), SP(0), DEF(0), czy_doubleATK(false), missrate(0.0),critrate(0.0),odliczanie(-1) {}
    Character(TypPostaci t, const std::string& im, unsigned int hp, unsigned int basehp, int atk, long exp,int sp, int def, bool doubleAtk=false, double mr=0.0,double cr=0.0,short cd=-1)
        : typ(t),Imie(im), HP(hp),base_HP(basehp), ATK(atk), EXP(exp), SP(sp), DEF(def), czy_doubleATK(doubleAtk),missrate(mr),critrate(cr),odliczanie(cd) {}
    vector<StatusEfekt> efekty;
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
                    switch(Jezyk){
                    case POLSKI:cout<<"|";koloruj(15,12);cout<<"[OGLUSZENIE]"<<setw(18)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    default:cout<<"|";koloruj(15,12);cout<<"[STUNNED]"<<setw(21)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    }
                    break;}
                case UPICIE:{
                    switch(Jezyk){
                    case POLSKI:cout<<"|";koloruj(15,12);cout<<"[UPICIE]"<<setw(22)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    default:cout<<"|";koloruj(15,12);cout<<"[DRUNK]"<<setw(23)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    }
                    break;}
                case WZMOCNIENIE:{
                    switch(Jezyk){
                    case POLSKI:cout<<"|";koloruj(15,12);cout<<"[WZMOCNIENIE]"<<setw(17)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    default:cout<<"|";koloruj(15,12);cout<<"[POWERED]"<<setw(21)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    }
                    break;}
                case ZATRUCIE:{
                    switch(Jezyk){
                    case POLSKI:cout<<"|";koloruj(15,12);cout<<"[ZATRUCIE]"<<setw(20)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    default:cout<<"|";koloruj(15,12);cout<<"[POISONING]"<<setw(19)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    }
                    break;}
                case OSLABIENIE:{
                    switch(Jezyk){
                    case POLSKI:cout<<"|";koloruj(15,12);cout<<"[OSLABIENIE (psychiczne)]"<<setw(5)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    default:cout<<"|";koloruj(15,12);cout<<"[(psychological) WEAKNESS]"<<setw(4)<<right;cout<<" ";koloruj(15,0);cout<<"|\n";break;
                    }
                    break;}
                case KRYTOWANIE:{
                    switch(Jezyk){
                        case POLSKI:cout<<"|";koloruj(5,12);cout<<"[KRYTOWANIE]"<<setw(18)<<right;cout<<" ";koloruj(15,12);koloruj(15,0);cout<<"|\n";\
                        default:cout<<"|";koloruj(5,12);cout<<"[CRITS]"<<setw(23)<<right;cout<<" ";koloruj(15,12);koloruj(15,0);cout<<"|\n";
                    }
                    break;}
                default:
                    cout<<"BLAD\n";

                }
                }
            }
            if (!maefekty)
            cout<<endl;
        }

    void heal(Character &target,int ilosc){
        if(target.HP+ilosc<=target.base_HP) target.HP+=ilosc;
        else target.HP=target.base_HP;
    }
    void skrytowanie()const{
        dzwiek("Audio_RPG\\krytyczny_cios.wav");
        koloruj(10,0);
        switch (Jezyk){
            case POLSKI:cout<<Imie<<" zadaje krytyczne obrazenia!    \n"; break;
            default: cout<<Imie<<" deals critical damage!    \n"; break;
            }
        koloruj(7,0);
        this_thread::sleep_for(chrono::seconds(2));
    }
    AttackResult damage(Character &target,int ilosc){
        AttackResult wynik;
        wynik.krytyczne=czy_crit(this->critrate);
        int obrazenia=ilosc/target.DEF;
        if(wynik.krytyczne) obrazenia*=2;
        if(obrazenia>=target.HP){
            target.HP=0;
            wynik.bitesthedust=true;
        }
        else
            target.HP-=obrazenia;
        return wynik;
    }
    void spudlowanie()const{
        switch(typ){
        case EXPLODER:{
            this_thread::sleep_for(chrono::seconds(3));
        dzwiek("Audio_RPG\\extinguish.wav");
        koloruj(11,8);
        switch (Jezyk){
            case POLSKI:
                cout<<"Bomba nalezaca do "<<Imie<<" gasnie!\n";koloruj(7,0);
                this_thread::sleep_for(chrono::seconds(2));
                cout<<"Zdesperowany "<<Imie<<" idzie do domu...\n";
                break;
            default:
                cout<<"The bomb belonging to "<<Imie<<" has extinguished!\n";koloruj(7,0);
                this_thread::sleep_for(chrono::seconds(2));
                cout<<"Disappointed "<<Imie<<" goes back home...\n";
                break;
            }
        this_thread::sleep_for(chrono::seconds(2));
        break;
        }
        default:{
            dzwiek("Audio_RPG\\Banana_slip.wav");
            koloruj(11,8);
            switch (Jezyk){
            case POLSKI:cout<<Imie<<" pudluje!    \n"; break;
            default: cout<<Imie<<" misses!     \n"; break;
            }
            koloruj(7,0);
            this_thread::sleep_for(chrono::seconds(2));
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
};
struct Gamecontent{
    Settings &S;
    const bool &debug;
    Character &gracz;
    vector<Character*> &enemies;
    Character* &dzialko;
    Character* &zasobnik;
    long &x; //runda
    int &kodscreen;
    short e;//ile bomb ma pokazac w screen;
    int &wskazany;
    bool &smigniecie;
    bool &wybor;
    bool &dlacase;
    Character* &krytT;
    ScreenEfekt SE;
    bool &kolejComm;
};
void Barka(Gamecontent &Gc);
void usunprzedzial(string &s,int I);
void Dialog(string Nazwa, int kolor_fontu,int kolor_tla, string S);
void AdvDialog(string Nazwa, int kolor_fontu, int kolor_tla, vector<linijkaD> Kwestie);
void nowyWrog(Gamecontent &Gc, unsigned int &base_HP_wrog); //wywolanie nowych obiektow
void noweDzialko(long x,Character* &dzialko,const Language& J);
void nowyZasobnik(long x,Character* &zasobnik,const Language &J);
void panele(Gamecontent &Gc,Przedmiot ult,Przedmiot ulw,Przedmiot ulm,Przedmiot fajerwerk,Przedmiot tel,Przedmiot zatyczki); //graficzne
void ofensywa_wybrana(Gamecontent &Gc);
void wsparcie_wybrane(Gamecontent &Gc);
void przedmioty_wybrane(Gamecontent &Gc, Przedmiot fajerwerk,Przedmiot tel,Przedmiot zatyczki);
bool EverybodyDEAD_NOT_BIG_SUPRISE(const vector<Character*>& enemies);
short target(Gamecontent &Gc);
//logika wczytywania klawiszy
void sklep_input(Gamecontent &Gc,short &tarcza, short &WATK, short &MATK, Przedmiot &ult,Przedmiot &ulw,Przedmiot &ulm,Przedmiot &fajerwerk,Przedmiot &tel,Przedmiot &zatyczki);
extern short Barka_status;
void SprawdzZIndeksem(Character* &C, const vector<Character*>& enemies,int &wskazany);
void Input(short &Barka_status,Gamecontent &Gc,Przedmiot &fajerwerk,Przedmiot &tel,Przedmiot & zatyczki);
void DzialTURN(Gamecontent &Gc); // runda NPCtow
void ZasobTURN(Gamecontent &Gc);
void NaLZomTURN(Gamecontent &Gc,Character* energ,Przedmiot zatyczki);
void BombyTurn(Gamecontent &Gc,Character* Expld,short odliczanie,Przedmiot zatyczki);
void ToxZomTURN(Gamecontent &Gc,Character* ToxicZombie,Przedmiot zatyczki);
void ZomTURN(Gamecontent &Gc,short odliczanie,Character* &t);
void ciagla_walka(Gamecontent &Gc,short &Barka_status,bool &CzyBylSklep); // scalajacy kod
#endif // GAMESTUFF_H_INCLUDED
