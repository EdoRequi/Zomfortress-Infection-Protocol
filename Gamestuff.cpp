#include <iostream>
#include "Gamestuff.h"
#include "Screen.h"
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <thread>
#include <string>
#include <vector>
#include <cmath>
#include <windows.h>
using namespace std;
using TP=TypPostaci;
using TE=TypEfektu;
int liczba_wrogow=1;
short IDwybor=0;
short WCzcionki=14;
Language Jezyk=Language::NONE;
unsigned int base_HP_wrog=150;
int kodscreen=0;
int glowy=0;
bool dlacase=false;
short e=0;
bool smigniecie=false;
short tarcza=2;
short WATK=20;
short MATK=20;
bool kolejComm=false;
bool ogluszenie=false;//warunek ogluszenia
int czekaj=0; //kolejka ogluszen
bool pijany=false;//efekt upicia
bool czyZyje(const Character* ch){
    return ch!=nullptr&&ch->HP>0;
}
bool czyZyje(const Character &ch){
    return ch.HP>0;
}
void dzwiek(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_ASYNC);
}
void dzwiek_loop(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_LOOP | SND_ASYNC);
}
void dzwiek_ciagly(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_SYNC);
}
struct Settings{
    short &IDwybor;
    short &WCzcionki;
    Language &Jezyk;
};
Settings S={IDwybor,WCzcionki,Jezyk};
Przedmiot ult= {"Ulepszenie tarczy",55,1}; //NOTA: w 3 pierwszych przypadkach wartosc quant oznacza poziom ulepszenia (domyslnie 1)
Przedmiot ulw= {"Ulepszenie wyrzutnika",90,1};
Przedmiot ulm= {"Ulepszenie miecza",120,1};
Przedmiot fajerwerk={"Flashbang",25,0};
Przedmiot tel={"Telefon do Inzyniera",500,0};
Przedmiot zatyczki={"Zatyczki do uszu",250,0};
void Barka(Gamecontent &Gc)
{
    system("cls");
    switch (Gc.S.Jezyk){
    case POLSKI:
        koloruj(0,14);cout<<"+======================================+";koloruj(15,0);cout<<"\n";
        koloruj(0,14);cout<<"|  Osiagnales swieta liczbe HP = 2137  |";koloruj(15,0);cout<<"\n";
        koloruj(0,14);cout<<"+======================================+";koloruj(15,0);cout<<"\n";
        break;
    case ANGIELSKI:
        koloruj(0,14);cout<<"+=========================================+";koloruj(15,0);cout<<"\n";
        koloruj(0,14);cout<<"| You have reached the holy number = 2137 |";koloruj(15,0);cout<<"\n";
        koloruj(0,14);cout<<"+=========================================+";koloruj(15,0);cout<<"\n";\
        break;
    default: break;
    }
    Beep(260,1000);Beep(440,1000);Beep(440,1000);
    Beep(220,250);
    Beep(440,250);Beep(495,250);Beep(523,250);Beep(495,250);Beep(440,250);
    Beep(390,1100);Beep(390,1100);
    Beep(195,1000);
    Beep(345,750);Beep(320,250);Beep(345,1000);Beep(345,1000);
    Beep(160,250);
    Beep(345,250);Beep(392,250);Beep(440,250);Beep(392,250);Beep(345,250);
    Beep(330,1100);Beep(330,1100);
    this_thread::sleep_for(chrono::seconds(1));
    Beep(260,1000);Beep(440,1000);Beep(440,1000);
    Beep(220,250);
    Beep(440,250);Beep(495,250);Beep(523,250);Beep(495,250);Beep(440,250);
    Beep(390,1100);Beep(390,1100);
    Beep(195,1000);
    Beep(345,750);Beep(320,250);Beep(345,1000);Beep(345,1000);
    Beep(160,250);
    Beep(292,250);Beep(320,250);Beep(345,250);Beep(320,250);Beep(292,250);Beep(260,2000);
}
bool czy_pudlo(double missrate){
    double los = (double)rand() / RAND_MAX; // Losowa liczba z zakresu 0.0 - 1.0
    return los<missrate;
}
bool czy_crit(double critrate){
    double los=(double)rand()/RAND_MAX;
    return los<critrate;
}
int Los(int M,int m){
    if (m==0) return rand()%M;
    return rand()%(M-m+1)+m;
}
void usunprzedzial(string &s,int I){
    reverse(s.begin(),s.end());
    for (int i=0;i<I;i++) s.pop_back();
    reverse(s.begin(),s.end());
}
void Dialog(string Nazwa, int kolor_fontu,int kolor_tla, string S){
    bool imiewypowiedziane=false;
    koloruj(kolor_fontu,kolor_tla);cout<<" "<<string(71,'_');koloruj (7,0);cout<<"\n";
        while (!S.empty()){
            string temp="";
            for (char &c:S){
            temp+=c;
            if (temp.size()==60||(temp.size()>=50&&c==' ')||(temp.size()==S.size())) {usunprzedzial(S,temp.size()); break;}
            }
            if (imiewypowiedziane){
                koloruj(kolor_fontu,kolor_tla);cout<<"| "<<setw(70)<<left<<temp<<"|";koloruj (7,0);cout<<"\n";
            }
            else {
                string razem=Nazwa+": "+temp;
                koloruj(kolor_fontu,kolor_tla);cout<<"| "<<setw(70)<<left<<razem<<"|";koloruj (7,0);cout<<"\n";
                imiewypowiedziane=true;
            }
        }
        koloruj(kolor_fontu,kolor_tla);cout<<" "<<string(71,char(196));koloruj (7,0);cout<<"\n";
}
void AdvDialog(string Nazwa, int kolor_fontu, int kolor_tla, vector<linijkaD> Kwestie){
    koloruj(kolor_fontu,kolor_tla);cout<<" "<<string(71,'_');koloruj (7,0);cout<<"\n";
    int ile=0;
    bool imiewypowiedziane=false,koniec=false;
    for (auto k:Kwestie){
        ile++;
        dzwiek(k.path);
        while (!k.S.empty()){
            string temp="";
            for (char c:k.S){
            temp+=c;
            if (temp.size()==65||(temp.size()>=55&&c==' ')||(temp.size()==k.S.size())) {usunprzedzial(k.S,temp.size()); break;}
            }
            if (imiewypowiedziane){
                koloruj(kolor_fontu,kolor_tla);cout<<"| "<<setw(70)<<left<<temp<<"|";koloruj (7,0);cout<<"\n";
            }
            else {
                string razem=Nazwa+": "+temp;
                koloruj(kolor_fontu,kolor_tla);cout<<"| "<<setw(70)<<left<<razem<<"|";koloruj (7,0);cout<<"\n";
                imiewypowiedziane=true;
            }
        }
        if (ile==Kwestie.size()){koloruj(kolor_fontu,kolor_tla);cout<<" "<<string(71,char(196));koloruj (7,0);cout<<"\n";}
        this_thread::sleep_for(chrono::milliseconds(k.czas));
    }
}

short otrzezwienie=0;
Character* generujZombie(long x,unsigned int &lok_HP_wrog,const bool CV,const Language &J){
    Character* jedn=nullptr;
        short losujszablon=Los(100,0);
        unsigned int health;
        unsigned short L;
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
            //jedn=new Character("Naladowany Zombie",health, health, 25+(x*1.7), x*1, 10,2,false,0.01);
            break;
        case 2 ... 5:{
            switch (losujszablon){
            case 0 ... 45:
                health = lok_HP_wrog*pow(1.06,x-1);
                jedn = new Character(TP::ZWYKLY,"Zombie", health, health, 20+(x * 2), x * 0.6, 0, 1, false,0.05,0.03);
                break;
            case 46 ... 59:{
                health=lok_HP_wrog*pow(1.05,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Szybki Zombie";break;
                default: NameZ="Fast Zombie";break;
                }
                jedn=new Character(TP::SZYBKI,NameZ,health, health, 25+(x*1.1), x*0.6, 0,1,true,0.06,0.05);
                break;}
            case 60 ... 69:{
                health=lok_HP_wrog*pow(1.08,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Naladowany Zombie";break;
                default: NameZ="Charged Zombie";break;
                }
                jedn=new Character(TP::NALADOWANY,NameZ,health, health, 20+(x*1.5), x*0.8, 0,2,false,0.03,0.06);
                break;}
            case 70 ... 99:{
                health=lok_HP_wrog*pow(1.09,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Tytanowy Zombie";break;
                default: NameZ="Titan Zombie";break;
                }
                jedn=new Character(TP::TYTANOWY,NameZ,health, health, 40+(x*2), x*1, 0,3,false,0.05,0.03);
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
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Szybki Zombie";break;
                default: NameZ="Fast Zombie";break;
                }
                jedn=new Character(TP::SZYBKI,NameZ,health, health, 25+(x*1.25), x*1, 0,1,true,0.04,0.05);
                break;}
            case 38 ... 59:{
                health=lok_HP_wrog*pow(1.05,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Naladowany Zombie";break;
                default: NameZ="Charged Zombie";break;
                }
                jedn=new Character(TP::NALADOWANY,NameZ,health, health, 25+(x*1.8), x*1, 0,2,false,0.03,0.06);
                break;}
            case 60 ... 85:{
                health=lok_HP_wrog*pow(1.03,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Tytanowy Zombie";break;
                default: NameZ="Titan Zombie";break;
                }
                jedn=new Character(TP::TYTANOWY,NameZ,health, health, 50+(x*3.4), x*1.5, 0,3,false,0.02,0.02);
                break;}
            case 86 ... 99:{
                health=lok_HP_wrog*pow(1.05,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Toksyczny Zombie";break;
                default: NameZ="Toxic Zombie";break;
                }
                jedn=new Character(TP::TOKSYCZNY,NameZ,health, health, 20+(x*2.1), x*1.5, 0,1,false,0.03,0.04);
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
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Szybki Zombie";break;
                default: NameZ="Fast Zombie";break;
                }
                jedn=new Character(TP::SZYBKI,NameZ,health, health, 55 + (x * 3.2), x*0.5, 0,1,true,0.04,0.05);
                break;}
            case 31 ... 39:{
                if (CV) health=lok_HP_wrog*pow(1.1,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Zombie Dowodca";break;
                default: NameZ="Commander Zombie";break;
                }
                jedn=new Character(TP::COMMANDER,NameZ,health,health,50+(x*2),x*2,0,2,false,0.02,0.01);
                break;}
            case 40 ... 54:{
                health=lok_HP_wrog*pow(1.1,x-1);
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Naladowany Zombie";break;
                default: NameZ="Charged Zombie";break;
                }
                jedn=new Character(TP::NALADOWANY,NameZ,health, health, 50+(x*2.4), x*1, 0,2,false,0.03,0.06);
                break;}
            case 55 ... 64:{
                double tytanowy_mnoznik=x<20?1.2:(x<30?1.12:1.05);
                health=static_cast<unsigned int>(lok_HP_wrog*pow(tytanowy_mnoznik,x-1));
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Tytanowy Zombie";break;
                default: NameZ="Titan Zombie";break;
                }
                jedn=new Character(TP::TYTANOWY,NameZ,health, health, 100 + (x * 5), x*1, 0,3,false,0.01,0.02);
                break;
            }
            case 65 ... 75:
                health=static_cast<unsigned int>(lok_HP_wrog*pow(1.06,x-1));
                L=Los(4,2);
                jedn=new Character(TP::EXPLODER,"Zombie Exploder",health, health,9999, x*1.2, 0,1,false,0.05,0,L);
                break;
            case 76:case 77:case 78:case 79:case 80:case 81:case 82:case 83:case 84:case 85:case 86:case 87:case 88:case 89:
            case 90:case 91:case 92:case 93:case 94:case 95:case 96:case 97:case 98:case 99:{
                health=static_cast<unsigned int>(lok_HP_wrog*pow(1.15,x-1));
                string NameZ;
                switch (J){
                case POLSKI: NameZ="Toksyczny Zombie";break;
                default: NameZ="Toxic Zombie";break;
                }
                jedn=new Character(TP::TOKSYCZNY,"Toksyczny Zombie",health, health, 50 + (x * 3.5), x*1, 0,1,false,0.03,0.05);
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
    case 2:case 3:case 4:case 5:
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
void kiedy_crit(Gamecontent &Gc,AttackResult &w,Character &source,Character &cel){
    if(w.krytyczne){
        Gc.SE.r=ScreenEfekt::CRITICAL;
        if (czyZyje(cel)) {Gc.krytT=&cel;narysujScene(Gc);}
        else screen(Gc);
        source.skrytowanie();
        Gc.SE.r = ScreenEfekt::NONE;
        Gc.krytT=nullptr;
    }
}
void nowyWrog(Gamecontent &Gc, unsigned int &base_HP_wrog)
{
    bool Commandervalid=false;
    liczba_wrogow=gen_l_wrogow(Gc.x);
    for (int r=0;r<liczba_wrogow;++r) {
            unsigned int lok_HP_wrog=base_HP_wrog;
            Character* jedn=generujZombie(Gc.x,lok_HP_wrog,Commandervalid,Gc.S.Jezyk);
        if (!jedn) {
            switch (Gc.S.Jezyk){
                case POLSKI: cerr<<"BLAD!"<<endl;break;
                default: cerr<<"ERROR!"<<endl;break;
            }
        return;}
        if (jedn->typ==TP::COMMANDER) Commandervalid=true;
        Gc.enemies.push_back(jedn);
        if (debug==true){
            switch(Gc.S.Jezyk){
            case POLSKI:
                cout << "Wrog[" << r << "] utworzony | adres: " <<jedn<<" | HP: " <<jedn->HP<<" | DEF: "<<jedn->DEF<<'\n';
                break;
            default:
                cout << "Created enemy[" << r << "] | address: " <<jedn<<" | HP: " <<jedn->HP<<" | DEF: "<<jedn->DEF<<'\n';
                break;
                  }
                  this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
        for (const Character* wrog:Gc.enemies){
    // Dostosowanie base_HP_wrog do najnizszego HP wroga(jesli jest)
            if (czyZyje(wrog)&&wrog->HP<base_HP_wrog)
            {
                base_HP_wrog=wrog->HP;
            }
        }
        if (Gc.debug==true){
            switch(Gc.S.Jezyk){
            case POLSKI:
            cout<<"Wygenerowano "<<Gc.enemies.size()<<" zombie\n";
            cout<<"Najnizsze HP:"<< base_HP_wrog<<endl;break;
            default:
            cout<<"Generated "<<Gc.enemies.size()<<" zombie\n";
            cout<<"The lowest HP:"<< base_HP_wrog<<endl;break;
        }
            this_thread::sleep_for(chrono::seconds(3));
        }
}
void noweDzialko(long x,Character* &dzialko, const Language &J)
{
    delete dzialko;
    dzialko=nullptr;
    unsigned int min_hp=110+(x*10);
    unsigned int max_hp=160+(x*25);
    unsigned int base_HP_dzialko = Los(max_hp,min_hp);
    string NameS;
        switch (J){
        case POLSKI: NameS="Dzialko Straznicze";break;
        default: NameS="Sentry Gun";break;
        }
    dzialko=new Character(TP::DZIALKO,NameS,base_HP_dzialko,base_HP_dzialko,250+2*(x/5),0,0,2);
}

void nowyZasobnik(long x,Character* &zasobnik,const Language &J)
{
    delete zasobnik;
    zasobnik=nullptr;
    unsigned int min_hp=80+(x*7);
    unsigned int max_hp=110+(x*20);
    long n=base_HP_wrog*pow(1.21,x-1);
    unsigned int base_HP_zasobnik = Los(max_hp,min_hp);
    string NameD;
        switch (J){
        case POLSKI: NameD="Zasobnik";break;
        default: NameD="Dispenser";break;
        }
    zasobnik=new Character(TP::ZASOBNIK,NameD,base_HP_zasobnik,base_HP_zasobnik,50*(float(x)/4),0,0,3);
}

void panele(Gamecontent &Gc,Przedmiot ult,Przedmiot ulw,Przedmiot ulm,Przedmiot fajerwerk,Przedmiot tel,Przedmiot zatyczki)
{
    if (Gc.kodscreen==20)
    {
        koloruj(15,4);
        for (int i=0;i<75;i++) cout<<(char)176;
        koloruj(15,0);cout<<(char)186<<endl;
        koloruj(15,0);
    for (int i=0;i<75;i++) cout<<(char)205;
    cout<<(char)185<<endl;
    koloruj(14,6);cout<<"EXP: "<<setw(5)<<Gc.gracz.EXP<<"                                                                 ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
    switch (Gc.S.Jezyk){
    case POLSKI:{
        koloruj(3,1);cout<<"\\1.Ulepszenie tarczy: "<<setw(5)<<right<<ult.cena<<"\\ "<<(char)177<<setw(7)<<left<<"obecny poziom: "<<ult.quant<<(char)176<<"                            ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(8,15);cout<<"\\2.Ulepszenie wyrzutnika: "<<setw(5)<<right<<ulw.cena<<"\\ "<<(char)177<<setw(7)<<left<<"obecny poziom: "<<ulw.quant<<(char)176<<"                        ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(4,7);cout<<"\\3.Ulepszenie miecza: "<<setw(5)<<right<<ulm.cena<<"\\ "<<(char)177<<setw(7)<<left<<"obecny poziom: "<<ulm.quant<<(char)176<<"                            ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(11,2);cout<<"\\4.Przedmiot: flashbang: "<<setw(5)<<right<<fajerwerk.cena<<"\\ "<<(char)177<<setw(7)<<left<<"obecna ilosc: "<<fajerwerk.quant<<(char)176<<"                          ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(9,0);cout<<"\\5.Przedmiot:Pomocna linia u Inzyniera(zuzywa 5 SP): "<<setw(3)<<tel.cena<<"\\ "<<(char)177<<setw(7)<<left<<"obecna ilosc: "<<tel.quant<<(char)176;koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        if (Gc.x>=15) cout<<"\\6.Przedmiot: Zatyczki do uszu(pasywne): "<<setw(3)<<right<<zatyczki.cena<<"\\ "<<(char)177<<setw(7)<<left<<"obecna ilosc: "<<zatyczki.quant<<(char)176<<"            "<<(char)186<<"\n";
        break;}
    default:{
        koloruj(3,1);cout<<"\\1.Shield upgrade: "<<setw(8)<<right<<ult.cena<<"\\ "<<(char)177<<setw(7)<<left<<"current level: "<<ult.quant<<(char)176<<"                            ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(8,15);cout<<"\\2.Sticky Launcher upgrade: "<<setw(3)<<right<<ulw.cena<<"\\ "<<(char)177<<setw(7)<<left<<"current level: "<<ulw.quant<<(char)176<<"                        ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(4,7);cout<<"\\3.Sword upgrade: "<<setw(9)<<right<<ulm.cena<<"\\ "<<(char)177<<setw(7)<<left<<"current level: "<<ulm.quant<<(char)176<<"                            ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(11,2);cout<<"\\4.Item: flashbang: "<<setw(9)<<right<<fajerwerk.cena<<"\\ "<<(char)177<<setw(7)<<left<<"current quant: "<<fajerwerk.quant<<(char)176<<"                          ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        koloruj(9,0);cout<<"\\5.Item:Telephone to Engineer(costs 5 SP): "<<setw(12)<<tel.cena<<"\\ "<<(char)177<<setw(7)<<left<<"current quant: "<<tel.quant<<(char)176;koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);
        if (Gc.x>=15) cout<<"\\6.Item: Earplugs(passive): "<<setw(15)<<right<<zatyczki.cena<<"\\ "<<(char)177<<setw(7)<<left<<"current quant: "<<zatyczki.quant<<(char)176<<"            "<<(char)186<<"\n";
    break;}
    }
    cout<<string(75,(char)205)<<(char)188<<endl;
    cout<<endl;
    switch(Gc.S.Jezyk){
        case POLSKI: cout<<"\\Wcisnij X, kiedy bedziesz gotowy\\"<<endl; break;
        default: cout<<"\\Press X, when you are ready\\"<<endl; break;
    }
    cout<<endl;}
    else
    {
        for (const auto& efekt:Gc.gracz.efekty){
            if (efekt.ID==1&&efekt.aktywny==true) return;
        }
        cout<<endl;
        cout<<string(64,char(196))<<endl;
        switch(Gc.S.Jezyk){
        case POLSKI:{
            cout<<"\\1. OFENSYWA\\"<<" "<<"\\2. SPECJALNE\\"<<" "<<"\\3. PRZEDMIOTY\\ \n";
            cout<<" ";uzyjUTF8(L'\u203E',12);cout<<"  ";uzyjUTF8(L'\u203E',13);cout<<"  ";uzyjUTF8(L'\u203E',14);cout<<endl;
            break;}
        default:
            cout<<"\\1. OFFENSIVE\\"<<" "<<"\\2. SPECIAL\\"<<" "<<"\\3. ITEMS\\ \n";
            cout<<" ";uzyjUTF8(L'\u203E',13);cout<<"  ";uzyjUTF8(L'\u203E',11);cout<<"  ";uzyjUTF8(L'\u203E',9);cout<<endl;
            break;}
        }
}
void ofensywa_wybrana(Gamecontent &Gc)
{
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
    switch(Gc.S.Jezyk){
    case POLSKI:{
        cout<<"\\1. Miecz\\"<<' '<<"\\2. Wyrzutnik granatow samoprzylepnych\\"<<' '<<"\\3.ATAK SPECJALNY (zuzywa 15 SP)\\ \n";
        cout<<" ";uzyjUTF8(L'\u203E',9);cout<<"  ";uzyjUTF8(L'\u203E',38);cout<<"  ";uzyjUTF8(L'\u203E',32);cout<<endl;
        break;}
    default:{
        cout<<"\\1. Sword\\"<<' '<<"\\2. Sticky Bomb Launcher\\"<<' '<<"\\3.SPECIAL ATTACK (zuzywa 15 SP)\\ \n";
        cout<<" ";uzyjUTF8(L'\u203E',9);cout<<"  ";uzyjUTF8(L'\u203E',25);cout<<"  ";uzyjUTF8(L'\u203E',32);cout<<endl;
        break;}
    }
}
void wsparcie_wybrane(Gamecontent &Gc)
{
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
    switch(Gc.S.Jezyk){
    case POLSKI:{
        cout<<"\\1. Gorzalka\\"<<"  "<<"\\2. Tarcza\\                                                            \n";
        cout<<" ";uzyjUTF8(L'\u203E',12);cout<<"   ";uzyjUTF8(L'\u203E',10);cout<<"                                   "<<endl;
        break;}
    default:{
        cout<<"\\1. Scrumpy\\"<<"  "<<"\\2. Shield\\                                                            \n";
        cout<<" ";uzyjUTF8(L'\u203E',11);cout<<"   ";uzyjUTF8(L'\u203E',10);cout<<"                                   "<<endl;
        break;}
    }
}
void przedmioty_wybrane(Gamecontent &Gc,Przedmiot fajerwerk,Przedmiot tel,Przedmiot zatyczki)
{
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
    //wyswietlanie ekwipunku
    switch(Gc.S.Jezyk){
    case POLSKI:{
        cout<<"\\1. "<<fajerwerk.nazwa<<"(Ilosc: " <<fajerwerk.quant<< ")\\                                          "<<endl;
        if (tel.quant!=0)
            cout<<"\\2. "<<tel.nazwa<<" (zuzywa 5 SP)\\"<<endl;
        if (zatyczki.quant!=0)
            cout<<"ZATYCZKI (PASYWNE)"<<endl;
        cout<<"X - wyjscie                                         \n";
        break;}
    default:{
        cout<<"\\1. "<<fajerwerk.nazwa<<"(quant: " <<fajerwerk.quant<< ")\\                                          "<<endl;
        if (tel.quant!=0)
            cout<<"\\2. "<<tel.nazwa<<" (costs 5 SP)\\"<<endl;
        if (zatyczki.quant!=0)
            cout<<"EARPLUGS (PASSIVE)"<<endl;
        cout<<"X - exit                                            \n";
        break;}
    }
}
bool wybor=false;
bool EverybodyDEAD_NOT_BIG_SUPRISE(const vector<Character*>& enemies){
    for (const Character* wrog:enemies) //kazdy element z wektora enemies jest sprawdzany
    {
        if (wrog&&czyZyje(wrog))
            return false; // jesli ktorys z wrogow nadal zyje, zwroc falsz
    }
    return true;
}
short target(Gamecontent &Gc)
{
    screen(Gc);
    char cel;
    wybor=true;
    bool validchoice3=false;
    int proby = Gc.enemies.size();
    while (proby-- > 0&&(!czyZyje(Gc.enemies[Gc.wskazany-1]))) {
        Gc.wskazany++;
        if (Gc.wskazany>Gc.enemies.size()) Gc.wskazany = 1;
    }
    if(EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)){
            dzwiek("Audio_RPG\\Kiedy_wszyscy_martwi_w_target.wav");
            cerr<<"Wszyscy wrogowie martwi sa martwi, nie ma kogo zabijac...\n";
            this_thread::sleep_for(chrono::seconds(3));
        }
        while (validchoice3==false)
        {
            dzwiek("Audio_RPG\\menu_choosing.wav");
            narysujScene(Gc);
            cout<<endl;
            cout<<string(64,char(196))<<endl;
            switch(Gc.S.Jezyk){
            case POLSKI: cout<<"Zombie otagowane od lewej do prawej!           \n";break;
            default: cout<<"Zombies are tagged from left to right!             \n";break;
            }
            for (size_t i = 0; i < Gc.enemies.size(); ++i) {
                if (Gc.enemies[i]&&Gc.enemies[i]->HP > 0) {
                    if ((int)i+1==Gc.wskazany) {
                        koloruj(0,7);
                    }
                    cout << "\\" << i + 1 << ". " << Gc.enemies[i]->Imie << "\\                         \n";
                    koloruj(7,0);
                }
            }
            cout<<"DEBUG:   wskazany="<<wskazany<<"      liczba wrogow="<<Gc.enemies.size();
            cel=_getch();
                switch (cel)
                {
                case 'w':
                    do{
                    wskazany--;
                    if (wskazany<1) wskazany=Gc.enemies.size();
                    }while (!czyZyje(Gc.enemies[wskazany-1]));
                    break;
                case 's':
                    do{
                        wskazany++;
                        if (wskazany>Gc.enemies.size()) wskazany=1;
                    }while (!czyZyje(Gc.enemies[wskazany-1]));
                    break;
                case 13:
                        validchoice3=true;
                        break;
                }
        }
        wybor=false;
        screen(Gc);
        return wskazany;
}
void sklep_input(Gamecontent &Gc,short &tarcza, short &WATK, short &MATK, Przedmiot &ult,Przedmiot &ulw,Przedmiot &ulm,Przedmiot &fajerwerk,Przedmiot &tel,Przedmiot &zatyczki)
{
    char choice2;
    bool validchoice2=false;
    while(validchoice2==false)
    {
        choice2=_getch();
        switch (choice2)
        {
        case '1': //upgrade tarczy
            {   screen(Gc);
                panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
            if (Gc.gracz.EXP<ult.cena) { koloruj (12,0);
                        switch(Gc.S.Jezyk){
                            case POLSKI: cout<<"Nie masz odpowiedniej ilosci exp!"<<endl;break;
                            case ANGIELSKI: cout<<"You don't have enough exp!"<<endl;break;
                            default: cout<<"NEVER GONNA GIVE YOU UP"<<endl;break;//easter egg
                        }
                        koloruj (15,0);
                }
            else if(ult.quant>3)//odpowiednia ilosc exp
            { //limit
                koloruj (12,0);
                switch (Gc.S.Jezyk){
                    case POLSKI: cout<<"Twoja tarcza jest maksymalnie ulepszona!\n";break;
                    default: cout<<"Your shield is already upgraded to the max level!\n";break;
                }
                koloruj(15,0);
            }
            else
            {
                koloruj (10,0);
                switch(Gc.S.Jezyk){
                        case POLSKI: cout<<"Kupiles "<<ult.nazwa<<endl;break;
                        default: cout<<"You bought "<<ult.nazwa<<endl;break;
                        }
                koloruj (15,0);
                Gc.gracz.EXP-=ult.cena;
                ult.cena*=3.2;
                tarcza+=ult.quant;
                ult.quant++;
                this_thread::sleep_for(chrono::seconds(1));
                screen(Gc);
                panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                validchoice2=true;
            }
            break;}
        case '2': //upgrade wyrzutnika
            {   screen(Gc);
                panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                if(Gc.gracz.EXP<ulw.cena) { koloruj (12,0);
                        switch(Gc.S.Jezyk){
                            case POLSKI: cout<<"Nie masz odpowiedniej ilosci exp!"<<endl;break;
                            case ANGIELSKI: cout<<"You don't have enough exp!"<<endl;break;
                            default: cout<<"NEVER GONNA LET YOU DOWN"<<endl;break;//easter egg
                        }
                        koloruj (15,0);
                }
                else
                {
                    koloruj (10,0);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<"Kupiles "<<ulw.nazwa<<endl;break;
                        default: cout<<"You bought "<<ulw.nazwa<<endl;break;
                        }
                    koloruj (15,0);
                    Gc.gracz.EXP-=ulw.cena;
                    ulw.cena*=3;
                    WATK+=2.1*ulw.quant;
                    ulw.quant++;
                    this_thread::sleep_for(chrono::seconds(1));
                    screen(Gc);
                    panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '3': //upgrade miecza
            {   screen(Gc);
                panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                if(Gc.gracz.EXP<ulm.cena) { koloruj (12,0);
                        switch(Gc.S.Jezyk){
                            case POLSKI: cout<<"Nie masz odpowiedniej ilosci exp!"<<endl;break;
                            case ANGIELSKI: cout<<"You don't have enough exp!"<<endl;break;
                            default: cout<<"NEVER GONNA RUN AROUND AND DESERT YOU"<<endl;break;//easter egg
                        }
                        koloruj (15,0);
                }
                else
                {
                    koloruj (10,0);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<"Kupiles "<<ulm.nazwa<<endl;break;
                        default: cout<<"You bought "<<ulm.nazwa<<endl;break;
                        }
                    koloruj (15,0);
                    Gc.gracz.EXP-=ulm.cena;
                    ulm.cena*=2.5;
                    MATK+=105;
                    ulm.quant++;
                    this_thread::sleep_for(chrono::seconds(1));
                    screen(Gc);
                    panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '4': //kupno przedmiotu
            {
                screen(Gc);
                panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                if(Gc.gracz.EXP<fajerwerk.cena) { koloruj (12,0);
                        switch(Gc.S.Jezyk){
                            case POLSKI: cout<<"Nie masz odpowiedniej ilosci exp!"<<endl;break;
                            case ANGIELSKI: cout<<"You don't have enough exp!"<<endl;break;
                            default: cout<<"NEVER GONNA MAKE YOU CRY"<<endl;break;//easter egg
                        }
                        koloruj (15,0);
                }
                else
                {
                    koloruj (10,0);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<"Kupiles "<<fajerwerk.nazwa<<"x 1"<<endl;break;
                        default: cout<<"You bought "<<fajerwerk.nazwa<<"x 1"<<endl;break;
                        }
                    koloruj (15,0);
                    Gc.gracz.EXP-=fajerwerk.cena;
                    fajerwerk.cena+=25;
                    fajerwerk.quant++;
                    this_thread::sleep_for(chrono::seconds(1));
                    screen(Gc);
                    panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '5': //kupno telefonu
            {
                screen(Gc);
                panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                if(Gc.gracz.EXP<tel.cena) { koloruj (12,0);
                        switch(Gc.S.Jezyk){
                            case POLSKI: cout<<"Nie masz odpowiedniej ilosci exp!"<<endl;break;
                            case ANGIELSKI: cout<<"You don't have enough exp!"<<endl;break;
                            default: cout<<"NEVER GONNA SAY GOODBYE"<<endl;break;//easter egg
                        }
                        koloruj (15,0);
                }
                else if(tel.quant!=0) {koloruj (12,0);
                switch (Gc.S.Jezyk){
                    case POLSKI: cout<<"Juz masz ten przedmiot!\n";break;
                    default: cout<<"You have already bought this item!\n";break;
                }
                koloruj (15,0);}
                else
                {
                    koloruj (10,0);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<"Kupiles "<<tel.nazwa<<endl;break;
                        default: cout<<"You bought "<<tel.nazwa<<endl;break;
                        }
                    koloruj (15,0);
                    Gc.gracz.EXP-=tel.cena;
                    tel.quant++;
                    this_thread::sleep_for(chrono::seconds(1));
                    screen(Gc);
                    panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '6': //kupno zatyczek
            {
                if (Gc.x<15) cout<<"Nope";
                else{
                    screen(Gc);
                    panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                    if(Gc.gracz.EXP<zatyczki.cena) { koloruj (12,0);
                        switch(Gc.S.Jezyk){
                            case POLSKI: cout<<"Nie masz odpowiedniej ilosci exp!"<<endl;break;
                            case ANGIELSKI: cout<<"You don't have enough exp!"<<endl;break;
                            default: cout<<"NEVER GONNA TELL A LIE AND HURT YOU"<<endl;break;//easter egg
                        }
                        koloruj (15,0);
                }
                    else if(zatyczki.quant!=0) {koloruj (12,0);
                    switch (Gc.S.Jezyk){
                        case POLSKI: cout<<"Juz masz ten przedmiot!\n";break;
                        default: cout<<"You have already bought this item!\n";break;
                    }
                    koloruj (15,0);}
                    else{
                        koloruj (10,0);
                        switch(Gc.S.Jezyk){
                        case POLSKI: cout<<"Kupiles "<<zatyczki.nazwa<<endl;break;
                        default: cout<<"You bought "<<zatyczki.nazwa<<endl;break;
                        }
                        koloruj (15,0);
                        Gc.gracz.EXP-=zatyczki.cena;
                        zatyczki.quant++;
                        this_thread::sleep_for(chrono::seconds(1));
                        screen(Gc);
                        panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                        validchoice2=true;
                    }
                }
            break;}
        case 'x': //wyjscie
            {
                PlaySound(NULL, 0, 0);
                dzwiek("Audio_RPG\\menu_choosing.wav");
                do
                {system("cls");
                koloruj(11,8);
                switch(Gc.S.Jezyk){
                case POLSKI:cout<<"Na pewno chcesz wyjsc? (Y/N) ";break;
                case ANGIELSKI: cout<<"Are you sure you want to leave? (Y/N) ";break;
                default: "(Y/N)?";break;
                }
                koloruj(7,0);
                choice2=_getch();
                if(choice2=='y')
                {
                    dzwiek("Audio_RPG\\menu_selecting.wav");
                if (czyZyje(Gc.dzialko))
                    Gc.kodscreen=6;
                else if (czyZyje(Gc.zasobnik))
                    Gc.kodscreen=12;
                else
                    Gc.kodscreen=0;//powrot do gry
                validchoice2=true;
                continue;
                }
                else if(choice2=='n')
                {
                    dzwiek("Audio_RPG\\menu_selecting.wav");
                    screen(Gc);
                    panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
                    dzwiek_loop("Audio_RPG\\Upgradestation_loop.wav");
                    validchoice2=true;
                }
                else cout<<"NOPE";
                }while (choice2!='y'&&choice2!='n');
                break;
            }
        default:
            cout<<"Nope";
            break;
    }
}
}
Character* dajCel(int numer,const vector<Character*>& enemies) {
    if(numer>=1&&numer<=enemies.size())
        return enemies[numer-1];
    return nullptr;
}
void SprawdzZIndeksem(Character* &C, const vector<Character*>& enemies,int &wskazany){
    for (int r=0;r<enemies.size();r++){
        if (enemies[r]==C&&czyZyje(C)){
            wskazany==r+1;
        }
    }
}
short Barka_status=0;
void AkcjaMiecz(Gamecontent &Gc,Character* &cel){
        dzwiek_ciagly("Audio_RPG\\menu_selecting.wav");
        Gc.gracz.ATK=MATK;
        Gc.kodscreen=2;
        if (czyZyje(Gc.dzialko))
            Gc.kodscreen+=6;
        else if (czyZyje(Gc.zasobnik))
            Gc.kodscreen+=12;
        narysujScene(Gc);
        koloruj(11,8);
        switch(Gc.S.Jezyk){
            case POLSKI: cout<<"Uzywasz Eyelander'a                                     "<<endl;break;
            default:  cout<<"You pulled out the Eyelander                                     "<<endl;
        }
        koloruj(7,0);
        dzwiek_ciagly("Audio_RPG\\miecz_wyciagniecie.wav");
        this_thread::sleep_for(chrono::seconds(1));
        if(czy_pudlo(Gc.gracz.missrate)){
            Gc.gracz.spudlowanie();
            return;
        }
        Gc.smigniecie=true;
        narysujScene(Gc);
        dzwiek("Audio_RPG\\miecz_machniecie.wav");
        this_thread::sleep_for(chrono::milliseconds(400));
        if (cel->typ==TP::TYTANOWY){
            dzwiek("Audio_RPG\\Saxxy_impact.wav");
            switch(Gc.S.Jezyk){
                case POLSKI: cout<<"... Miecz nawet nie drasnal Tytanowego Zombie!!!    \n";break;
                default:  cout<<"... The sword didn't even leave a mark on Titan Zombie!!!         "<<endl;break;
            }
            this_thread::sleep_for(chrono::seconds(2));
            Gc.smigniecie=false;
            }
            else{
            cel->PainReact();
            int obrazenia=Gc.gracz.ATK+120;
            AttackResult w=Gc.gracz.damage(*cel,obrazenia);//atak bezposredni, raz sie odbywa
            kiedy_crit(Gc,w,Gc.gracz,*cel);
                if (!w.bitesthedust) //kontrola
                {
                    Gc.kodscreen=0;
                    if (czyZyje(Gc.dzialko))
                        Gc.kodscreen+=6;
                    else if (czyZyje(Gc.zasobnik))
                        Gc.kodscreen+=12;
                    Gc.smigniecie=false;
                    screen(Gc);
                }
                else
                {
                    glowy++;
                    if(glowy>=12) {
                        Gc.gracz.base_HP=2137; //wspomnienie Jana Pawla II
                        Barka_status++;
                        Gc.gracz.heal(Gc.gracz,333);
                        if(Barka_status==1){
                            dzwiek_ciagly("Audio_RPG\\bip_bip.wav");
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            Barka(Gc);
                            Gc.gracz.SP+=10;
                            screen(Gc);
                            Barka_status++;
                        }
                    }
                    else {Gc.gracz.base_HP*=1.25;
                    Gc.gracz.heal(Gc.gracz,Gc.gracz.base_HP);}
                    switch (cel->typ){
                    case TP::NALADOWANY:
                        Gc.gracz.SP+=(cel->SP)/2;
                    default: break;
                }
                Gc.kodscreen=0;
                if (czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
                else if (czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
                Gc.smigniecie=false;
                screen(Gc);
                koloruj(11,8);
                switch(Gc.S.Jezyk){
                    case POLSKI: cout<<"Za uzycie miecza zyskujesz wiekszy max HP!"<<endl;break;
                    default:  cout<<"Thanks to sword you gain more max HP!"<<endl;break;
                }
                koloruj(7,0);
                this_thread::sleep_for(chrono::milliseconds(1500));
                narysujScene(Gc);
            }
            if (EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)){
            Gc.kodscreen=1;
            if (czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
            else if (czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
    Gc.gracz.ATK=20;
}
void AkcjaGranatySamoprzylepne(Gamecontent &Gc,Character* &cel){
            dzwiek("Audio_RPG\\menu_selecting.wav");
                        Gc.gracz.ATK=WATK;
                        unsigned int iloscGranatow=Los(5,1);
                        Gc.kodscreen=3;
                        if (czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
                        else if (czyZyje(Gc.zasobnik))Gc.kodscreen+=12;
                        narysujScene(Gc);
                        koloruj(11,8);
                        switch(Gc.S.Jezyk){
                            case POLSKI:cout<<"Wystrzelone granaty: "<<iloscGranatow<<endl;break;
                            default: cout<<"Amount of bombs: "<<iloscGranatow<<endl;break;
                        }
                        koloruj(7,0);
                        dzwiek_ciagly("Audio_RPG\\bomba_przeladowanie.wav");
                        for (unsigned int i=1;i<=iloscGranatow;i++)
                        {
                            if(czy_pudlo(Gc.gracz.missrate)){
                            narysujScene(Gc);
                            koloruj(11,8);
                            switch(Gc.S.Jezyk){
                                case POLSKI:cout<<"Wystrzelone granaty: "<<iloscGranatow<<endl;cout<<"Pudlo!\n";break;
                                default: cout<<"Amount of bombs: "<<iloscGranatow<<endl;cout<<"Miss!\n";break;
                            }
                            koloruj(7,0);
                            dzwiek("Audio_RPG\\Banana_slip.wav");
                            this_thread::sleep_for(chrono::milliseconds(500));
                            }
                            else{
                            Gc.e++;
                            narysujScene(Gc);
                            koloruj(11,8);
                            switch(Gc.S.Jezyk){
                                case POLSKI:cout<<"Wystrzelone granaty: "<<iloscGranatow<<endl<<endl;break;
                                default: cout<<"Amount of bombs: "<<iloscGranatow<<endl<<endl;break;
                            }
                            koloruj(7,0);
                            dzwiek("Audio_RPG\\bomba_wyrzut.wav");
                            this_thread::sleep_for(chrono::milliseconds(500));
                            }
                        }
                        this_thread::sleep_for(chrono::seconds(1));
                        dzwiek("Audio_RPG\\bip_bip.wav");
                        this_thread::sleep_for(chrono::milliseconds(500));
                        int akt_sciezka=Los(1,0);
                        int obrazenia =10*iloscGranatow*(Gc.gracz.ATK/2.5); // Obliczenie obrazen
                        AttackResult w=Gc.gracz.damage(*cel,obrazenia);//atak posredni, ale ma szanse byc mocniejszy
                        switch(akt_sciezka) {
                        case 1:
                        if (w.krytyczne) dzwiek("Audio_RPG\\TNT_explosion.wav");
                        else dzwiek("Audio_RPG\\TNT_explosion.wav");
                        break;
                        default:
                            {
                                if (w.krytyczne) dzwiek("Audio_RPG\\Demoman_response_KaBOOM2.wav");
                                else dzwiek("Audio_RPG\\Demoman_response_KaBOOM2.wav");
                                this_thread::sleep_for(chrono::milliseconds(500));
                                break;
                            }
                        }
                        kiedy_crit(Gc,w,Gc.gracz,*cel);
                        if (!w.bitesthedust) //kontrola
                        {
                            Gc.kodscreen=0;
                            if (czyZyje(Gc.dzialko))
                                Gc.kodscreen+=6;
                            else if (czyZyje(Gc.zasobnik))
                                Gc.kodscreen+=12;
                        }
                        else
                        {
                            cel->HP=0;
                            switch(cel->typ){
                                case TP::NALADOWANY: Gc.gracz.SP+=(cel->SP)/2;
                                default: break;;
                            }
                        }
                        for (Character* wrog:Gc.enemies) {
                        if (wrog==cel||!(czyZyje(wrog))) continue;
                        int splash=obrazenia/3;
                        AttackResult w_splash=Gc.gracz.damage(*wrog,splash);
                        if(!w_splash.bitesthedust&&w_splash.krytyczne) wskazany++;
                        kiedy_crit(Gc,w_splash,Gc.gracz,*wrog);
                        if (w_splash.bitesthedust) wrog->HP=0;
                        switch(wrog->typ){
                            case TP::NALADOWANY: Gc.gracz.SP++; break;
                            default: break;
                        }
                                }
    if (EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)){
        Gc.kodscreen=1;
        if (czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
        else if (czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
    }
    Gc.e=0;
    screen(Gc);
    this_thread::sleep_for(chrono::seconds(2));
    Gc.gracz.ATK=20;
}
void AkcjaGorzalka(Gamecontent &Gc){
    screen(Gc);
    koloruj(11,8);
    switch(Gc.S.Jezyk){
        case POLSKI:{cout<<"Pijesz gorzalke"<<endl;
            koloruj(7,0);
            Dialog(Gc.gracz.Imie,12,0,"Ejj... Czas na popicie Scrumpym!");
            break;}
        default:{cout<<"You are drinking Scrumpy"<<endl;
            koloruj(7,0);
            Dialog(Gc.gracz.Imie,12,0,"Aye, me bottle o'scrumpy!");
            break;}
    }
    dzwiek_ciagly("Audio_RPG\\Demoman_response_scrumpy.wav");
    this_thread::sleep_for(chrono::seconds(1));
    int iloscZdrowkadoZycka=Los(400,120);
    short alkoholizm=Los(4,0);//1 na 5 szansy na upojenie-efekt przez ktory zadajesz o 20% mniej ataku
    int przedHP = Gc.gracz.HP;
    Gc.gracz.heal(Gc.gracz,iloscZdrowkadoZycka);
    screen(Gc);
    koloruj(11,8);
    switch(Gc.S.Jezyk){
        case POLSKI:cout<<"Zyskujesz "<<Gc.gracz.HP-przedHP<<"HP"<<endl;break;
        default:cout<<"You gained "<<Gc.gracz.HP-przedHP<<"HP"<<endl;break;
    }
    koloruj(7,0);
    this_thread::sleep_for(chrono::seconds(1));
    if (pijany==true){
        for (auto& efekt:Gc.gracz.efekty){
            if (efekt.ID==2&&efekt.aktywny==true){
                efekt.duration++;
                koloruj(8,0);
                switch(Gc.S.Jezyk){
                    case POLSKI:cout<<"Podtrzymales efekt upicia. Liczba kolejek="<<efekt.duration;break;
                    default:cout<<"You maintained the stiffness. Number of turns="<<efekt.duration;break;
                }
                koloruj(7,0);
            }
        }
    }
    else{
        if (alkoholizm==4)
        {
            cout<<endl<<endl;
            koloruj(8,0);
            switch(Gc.S.Jezyk){
                case POLSKI:cout<<"..."<<Gc.gracz.Imie<<" sie upil, od teraz ma 33% wiecej szansy na spudlowanie!\n";break;
                default:cout<<"..."<<Gc.gracz.Imie<<" has got drunked, from now he has 33% more chance of missing!\n";break;
            }
            short kolejka=Los(5,2);
            Gc.gracz.dodajefekt(UPICIE,kolejka,Gc.gracz);
            cout<<"L kolejek="<<kolejka-1;
            koloruj(7,0);
            short wersja_pijanstwa=Los(5,0);
            switch (wersja_pijanstwa)
            {
                case 0:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo.wav");
                    switch(Gc.S.Jezyk){
                        case POLSKI: Dialog(Gc.gracz.Imie,12,0,"Zaraz was zabije i bede was zabijal i ja nigdy tego nie zrobie, poniewaz i tak bedziecie martwi, wiec nie bede musial was zabijac.");break;
                        default: Dialog(Gc.gracz.Imie,12,0,"Gonna kill you and I'll keep killin' you and I'll never, cause you're 'onna be dead and I don't gotta kill you.");break;
                    }
                    this_thread::sleep_for(chrono::seconds(8));
                    break;
                case 1:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo2.wav");
                    switch(Gc.S.Jezyk){
                        case POLSKI: Dialog(Gc.gracz.Imie,12,0,"(paplanina)... wlasnie chcialem pojechac na stacje BOLOWEGO POCIAGU w Train Town...");break;
                        default: Dialog(Gc.gracz.Imie,12,0,"(gibberish)... I was gonna take down to the Pain Train station in Train Town...");break;
                    }
                    this_thread::sleep_for(chrono::seconds(7));
                    break;
                case 2:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo3.wav");
                    switch(Gc.S.Jezyk){
                        case POLSKI: Dialog(Gc.gracz.Imie,12,0,"Ja... kocham takich jak ... ty tutaj... nie was.");break;
                        default: Dialog(Gc.gracz.Imie,12,0,"I love... every... single... one of ye... not you.");break;
                    }
                    Dialog(Gc.gracz.Imie,12,0,"Aoch, jestes singlem... jeden z was... nie ty.");
                    this_thread::sleep_for(chrono::seconds(5));
                    break;
                case 3:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo5.wav");
                    switch(Gc.S.Jezyk){
                        case POLSKI: Dialog(Gc.gracz.Imie,12,0,"(Niezrozumialy belkot)");break;
                        default: Dialog(Gc.gracz.Imie,12,0,"(Unintelligible gibberish)");break;
                    }
                    this_thread::sleep_for(chrono::seconds(5));
                    break;
                case 4:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo6.wav");
                    switch(Gc.S.Jezyk){
                        case POLSKI: Dialog(Gc.gracz.Imie,12,0,"Kazdy z was... eee... co mysli, zeee... jest lepszy ode mnie... nastepny dostanie za...");break;
                        default: Dialog(Gc.gracz.Imie,12,0,"Any of you that think ye're better 'n me, you're gon' have another thing c-..");break;
                    }
                    this_thread::sleep_for(chrono::seconds(5));
                    break;

                default:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo4.wav");
                    switch(Gc.S.Jezyk){
                        case POLSKI: Dialog(Gc.gracz.Imie,12,0,"... A potem wyhoduję ci tylek na tylku, jak ja jestem trawiastym czlowiekiem, durniu, poganie jeden...");break;
                        default: Dialog(Gc.gracz.Imie,12,0,"And then I'll grow yer arse's arse and I'm the grass man, punk yeah heaven's heathen...");break;
                    }
                    this_thread::sleep_for(chrono::seconds(7));
                    break;
            }
        }
    }
}
void AkcjaTarcza(Gamecontent &Gc){
    int Specjalnepunkciki=Los(100,0);
    if (Specjalnepunkciki>=75)
        Gc.gracz.SP+=tarcza+1;
    else
        Gc.gracz.SP+=tarcza;
    Gc.gracz.DEF=tarcza;
    screen(Gc);
    koloruj(11,8);
    switch(Gc.S.Jezyk){
        case POLSKI:cout<<"Zaslaniasz sie tarcza"<<endl;break;
        default:cout<<"You cover yourself with shield"<<endl;break;
    }
    koloruj(7,0);
    koloruj(11,8);
    if (Specjalnepunkciki>=75){
        switch(Gc.S.Jezyk){
        case POLSKI:cout<<"Zyskujesz "<<tarcza+1<<" SP!"<<endl;break;
        default:cout<<"You gained "<<tarcza+1<<" SP!"<<endl;break;
        }
    }
    else{
        switch(Gc.S.Jezyk){
        case POLSKI:cout<<"Zyskujesz "<<tarcza<<" SP!"<<endl;break;
        default:cout<<"You gained "<<tarcza<<" SP!"<<endl;break;
        }
    }
    koloruj(7,0);
    this_thread::sleep_for(chrono::seconds(2));
}
void AkcjaEkwipunek(Gamecontent &Gc,Przedmiot &fajerwerk,Przedmiot &tel,Przedmiot &zatyczki,bool &validchoice){
    char choice;
    dzwiek("Audio_RPG\\menu_selecting.wav");
    przedmioty_wybrane(Gc,fajerwerk,tel,zatyczki);
    bool przedmiotyDone=false;
    while (!przedmiotyDone)
    {
        choice=_getch();
        switch(choice)
        {
            case '1':
            {
                if (fajerwerk.quant!=0)
                {
                    Gc.kodscreen=5;
                    if (czyZyje(Gc.dzialko))
                        Gc.kodscreen=10;
                    else if (czyZyje(Gc.zasobnik))
                        Gc.kodscreen+=12;
                    screen(Gc);
                    koloruj(11,8);
                    switch(Gc.S.Jezyk){
                        case POLSKI:cout<<"Rzucasz granat ogluszajacy (flashgrenade)!\n";break;
                        default:cout<<"You have thrown a flashbang!\n";break;
                    }
                    koloruj(7,0);
                    dzwiek_ciagly("Audio_RPG\\rzut.wav");
                    dzwiek("Audio_RPG\\flashbang_throw.wav");
                    this_thread::sleep_for(chrono::seconds(2));
                    fajerwerk.quant--;
                    Gc.kodscreen=19;
                    screen(Gc);
                    dzwiek("Audio_RPG\\flashbang_boom.wav");
                    this_thread::sleep_for(chrono::milliseconds(2500));
                    for (Character* wrog:Gc.enemies){
                    if (czyZyje(wrog)==true) wrog->dodajefekt(OGLUSZENIE,3,*wrog);
                    }
                    Gc.kodscreen=0;
                    if (czyZyje(Gc.dzialko))
                        Gc.kodscreen+=6;
                    else if (czyZyje(Gc.zasobnik))
                        Gc.kodscreen+=12;
                    screen(Gc);
                    koloruj(11,8);
                    switch(Gc.S.Jezyk){
                        case POLSKI:cout<<"Ogluszasz zombiaki (bedziesz mial dodatkowe ruchy)!"<<endl;break;
                        default:cout<<"You have stunned the zombies (you will have additional turns)!"<<endl;break;
                    }
                    koloruj(7,0);
                    this_thread::sleep_for(chrono::seconds(3));
                    przedmiotyDone=true;
                    validchoice=true;
                }
                        else {
                            switch(Gc.S.Jezyk){
                            case POLSKI:cout<<"Nie ma takiego przedmiotu\n";break;
                            default:cout<<"There's no such an item\n";break;
                            }
                        }
                        break;}
            case '2':
            {
                if(tel.quant!=0&&Gc.gracz.SP>=5)
                {
                    Gc.gracz.SP-=5;
                    Gc.kodscreen=0;
                    if (czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
                    if (czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
                    screen(Gc);
                    dzwiek("Audio_RPG\\telephone_ring.wav");
                    koloruj(11,8);
                    switch(Gc.S.Jezyk){
                    case POLSKI:
                        cout<<"Dzwonisz do inzyniera...!"<<endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout<<"Odebral!\n"; break;
                    default:
                        cout<<"You are calling Engineer!"<<endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout<<"He answered!\n"; break;

                    }
                    koloruj(7,0);
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_engineer.wav");//Inzynierze...
                    this_thread::sleep_for(chrono::milliseconds(500));
                    dzwiek("Audio_RPG\\Engineer_response_yeah.wav");//tak?
                    this_thread::sleep_for(chrono::milliseconds(1200));
                    dzwiek_ciagly("Audio_RPG\\Demoman_HELP.wav");//POMOZ!:(
                    this_thread::sleep_for(chrono::milliseconds(500));
                    if (!czyZyje(Gc.dzialko)&&!czyZyje(Gc.zasobnik)){
                        short wersjaodpowiedzi=Los(2,0);
                        if (wersjaodpowiedzi==1) dzwiek_ciagly("Audio_RPG\\Engineer_response01.wav");
                        else if(wersjaodpowiedzi==2) dzwiek_ciagly("Audio_RPG\\Engineer_response02.wav");
                        else dzwiek_ciagly("Audio_RPG\\Engineer_response03.wav");
                        this_thread::sleep_for(chrono::milliseconds(500));
                        screen(Gc);
                        koloruj(11,8);
                        switch (Gc.S.Jezyk){
                            case POLSKI: cout<<"Inzynier zrzuca...";break;
                            default: cout<<"Engineer drops a... ";break;
                        }
                        koloruj(7,0);
                        this_thread::sleep_for(chrono::seconds(1));
                        short zrzut=Los(100,0);
                        if (zrzut>50){
                            Gc.kodscreen=6;
                            noweDzialko(Gc.x,Gc.dzialko,Gc.S.Jezyk);
                            screen(Gc);
                            koloruj(11,8);
                            cout<<Gc.dzialko->Imie<<"!"<<endl;
                            koloruj(7,0);
                        }
                                else{
                                    Gc.kodscreen=12;
                                    nowyZasobnik(Gc.x,Gc.zasobnik,Gc.S.Jezyk);
                                    screen(Gc);
                                    koloruj(11,8);
                                    cout<<Gc.zasobnik->Imie<<"!"<<endl;
                                    koloruj(7,0);
                                    }
                                dzwiek_ciagly("Audio_RPG\\build.wav");
                                this_thread::sleep_for(chrono::seconds(2));
                            }
                            else
                            {
                                dzwiek("Audio_RPG\\Engineer_nope.wav"); //nie
                                koloruj(14,8);
                                switch (Gc.S.Jezyk){
                                    case POLSKI: Dialog("Inzynier",14,8,"Nie!");break;
                                    default: Dialog("Inzynier",14,8,"Nope!");break;
                                }
                                Dialog("Inzynier",14,8,"Nie!");
                                this_thread::sleep_for(chrono::milliseconds(500));
                                dzwiek("Audio_RPG\\telephone_lostcon.wav");
                                switch (Gc.S.Jezyk){
                                    case POLSKI: cout<<"Widze, ze bardzo uwielbiasz marnowac ruchy i SP.\n";break;
                                    default: cout<<"I see you are really fond of wasting moves and SP.\n";break;
                                }
                                this_thread::sleep_for(chrono::milliseconds(2000));
                            }
                            przedmiotyDone=true;
                            validchoice=true;

                            }
                        else if (tel.quant!=0&&Gc.gracz.SP<5) {
                                switch(Gc.S.Jezyk){
                            case POLSKI:cout<<"Nie mozesz, nie masz wystarczajaco SP.";break;
                            default:cout<<"You can't, you don't have enough SP.\n";break;
                            }
                        }
                        else {
                            switch(Gc.S.Jezyk){
                            case POLSKI:cout<<"Nie ma takiego przedmiotu\n";break;
                            default:cout<<"There's no such an item\n";break;
                            }
                        }
                            break;
                        }
        case 'x':
        {
            validchoice=false;
            przedmiotyDone=true;
            dzwiek("Audio_RPG\\menu_back.wav");
            screen(Gc);
            panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
            break;}
        default:
            switch(Gc.S.Jezyk){
                case POLSKI:cout<<"Zly klawisz"<<endl;break;
                default:cout<<"Wrong button"<<endl;break;
            }
            break;
        }
    }
}
void Input(short &Barka_status,Gamecontent &Gc,Przedmiot &fajerwerk,Przedmiot &tel,Przedmiot & zatyczki)
{
    char choice;
    Gc.wybor=false;
    bool validchoice=false;
    bool oglus=false;
    bool pijany=false;
    for (const auto& efekt:Gc.gracz.efekty){
    if (efekt.aktywny==true)//jezeli zostal ogluszony
        {
            switch(efekt.ID){
            case OGLUSZENIE:
                koloruj(15,8);
                switch(Gc.S.Jezyk){
                case POLSKI:
                    cout<<Gc.gracz.Imie<<" jest ogluszony i nie moze sie ruszyc!"<<endl;
                    cout<<"Kolejka: "<<efekt.duration<<endl;
                    break;
                default:
                    cout<<Gc.gracz.Imie<<" is stunned and he can't move!"<<endl;
                    cout<<"Remains for: "<<efekt.duration<<" turns."<<endl;
                    break;
                }
                koloruj(7,0);
                oglus=true;
                this_thread::sleep_for(chrono::seconds(3));
                break;
            case UPICIE:
                Gc.gracz.missrate=0.333;
                pijany=true;
                break;
            case OSLABIENIE:
                Gc.gracz.ATK*=0.5;
                break;
            default:
                break;
            }
            break;
        }
    }
    if (oglus==true) return;
    while (!validchoice)
    {
        choice=_getch();


            switch (choice)
            {
            case '1':{
                dzwiek("Audio_RPG\\menu_selecting.wav");
                ofensywa_wybrana(Gc);
                bool ofensywaDone = false;
                while(!ofensywaDone){
                    choice=_getch();
                    switch (choice)
                    {
                    case '1':{ //kiedy '1'
                        int celataku=target(Gc);
                        Character* cel=dajCel(celataku,Gc.enemies);
                        if (!cel) {
                            cerr << "Nie wybrano poprawnego celu!" << endl;
                            break;
                        }
                        AkcjaMiecz(Gc,cel);
                        ofensywaDone=true;
                        validchoice=true;
                        break;}

                    case '2':{
                        int celataku=target(Gc);
                        Character* cel=dajCel(celataku,Gc.enemies);
                        if (!cel) {
                            cerr << "Nie wybrano poprawnego celu!" << endl;
                            break;
                        }
                        AkcjaGranatySamoprzylepne(Gc,cel);
                        ofensywaDone=true;
                        validchoice=true;
                        break;}
                    case '3':{
                        dzwiek("Audio_RPG\\menu_selecting.wav");
                        if (Gc.gracz.SP>=15)
                        {
                            Gc.gracz.SP-=15;
                            int wersjaTekstu=Los(2,0);
                            int wersjadzwieku=Los(4,1);
                            screen(Gc);
                            switch (wersjaTekstu)
                            {
                            case 0:
                                switch(Gc.S.Jezyk){
                                case POLSKI:Dialog(Gc.gracz.Imie,12,0,"Nie boj sie chloptasiu, bede delikatny!");break;
                                default: Dialog(Gc.gracz.Imie,12,0,"Don't fret, boyo. I'll be gentle!");break;
                                }
                                dzwiek_ciagly("Audio_RPG\\Demoman_response_grozba2.wav");
                                break;
                            case 1:
                                switch(Gc.S.Jezyk){
                                case POLSKI:Dialog(Gc.gracz.Imie,12,0,"O, zbije cie tak mocno, ze dostaniesz dreszczy!");break;
                                default: Dialog(Gc.gracz.Imie,12,0,"Ohh, I'm gonna beat ya so hard, you'll have a twitch!");break;
                                }
                                dzwiek_ciagly("Audio_RPG\\Demoman_response_grozba.wav");
                                break;
                            default:
                                switch(Gc.S.Jezyk){
                                case POLSKI:Dialog(Gc.gracz.Imie,12,0,"A TERAZ WSZYSCY WYBUCHNIECIE!!!");break;
                                default: Dialog(Gc.gracz.Imie,12,0,"And NOW EVERYBODY OF YEH ARE GOIN' TO EXPLODE!!!");break;
                                }
                                this_thread::sleep_for(chrono::seconds(3));
                                break;
                            }
                            Gc.kodscreen=4;
                            if (czyZyje(Gc.dzialko))
                                Gc.kodscreen+=6;
                            else if (czyZyje(Gc.zasobnik))
                                Gc.kodscreen+=12;
                            screen(Gc);
                            switch (wersjadzwieku)
                            {
                            case 1:
                                dzwiek("Audio_RPG\\chargeatack1.wav");
                                break;
                            case 2:
                                dzwiek("Audio_RPG\\chargeatack2.wav");
                                break;
                            case 3:
                                dzwiek("Audio_RPG\\chargeatack3.wav");
                                break;
                            default:
                                dzwiek("Audio_RPG\\chargeatack3.wav");
                                break;
                            }
                            this_thread::sleep_for(chrono::seconds(3));
                            for (Character* wrog:Gc.enemies)
                                wrog->HP=0;
                            Gc.kodscreen=0;
                            if (czyZyje(Gc.dzialko))
                                Gc.kodscreen+=6;
                            else if (czyZyje(Gc.zasobnik))
                                Gc.kodscreen+=12;
                            dzwiek("Audio_RPG\\wiwat_uderzenie.wav");
                            system("cls");
                            if (czyZyje(Gc.dzialko)){
                                Gc.dzialko->HP=0;
                                Gc.kodscreen=1;
                                screen(Gc);
                                koloruj(11,8);
                                cout<<"BOOOOOOOOOOOOOOM!!!"<<endl<<endl;
                                switch(Gc.S.Jezyk){
                                case POLSKI:cout<<"Dzialko zostaje zniszczone z powodu wybuchu!\n";break;
                                default:cout<<"Sentry got destroyed due to explosion!\n";break;
                                }
                            }
                            else if (czyZyje(Gc.zasobnik)){
                                Gc.zasobnik->HP=0;
                                Gc.kodscreen=1;
                                screen(Gc);
                                koloruj(11,8);
                                cout<<"BOOOOOOOOOOOOOOM!!!"<<endl<<endl;
                                switch(Gc.S.Jezyk){
                                case POLSKI:cout<<"Zasobnik zostaje zniszczony z powodu wybuchu!\n";break;
                                default:cout<<"Dispenser got destroyed due to explosion!\n";break;
                                }
                            }
                            else{
                            screen(Gc);
                            koloruj(11,8);
                            cout<<"BOOOOOOOOOOOOOOM!!!"<<endl;}
                            switch(Gc.S.Jezyk){
                                case POLSKI:cout<<"\n"<<Gc.gracz.Imie<<" przezywa, poniewaz zaslonil sie tarcza "<<endl;break;
                                default:cout<<"\n"<<Gc.gracz.Imie<<" survives thanks to the shield "<<endl;break;
                                }
                            koloruj(7,0);

                            if (pijany==true){
                                koloruj(11,8);
                                switch(Gc.S.Jezyk){
                                case POLSKI:cout<<"Byl tak opruty, ze nawet wybuch go nie ruszyl!!! "<<endl;break;
                                default:cout<<"\n"<<"He was so drunk, he didn't got affected from the explosion!!!"<<endl;break;
                                }
                            }
                            else
                            {
                                Gc.gracz.dodajefekt(OGLUSZENIE,2,Gc.gracz);
                                koloruj(15,8);
                                switch(Gc.S.Jezyk){
                                case POLSKI:cout<<" Niestety zostaje ogluszony na jedna runde...\n";break;
                                default:cout<<" Unfortunately, he gets stunned for 1 turn...\n";break;
                                }
                                koloruj(7,0);
                            }

                        this_thread::sleep_for(chrono::seconds(5));
                        screen(Gc);
                        dlacase=true;
                        this_thread::sleep_for(chrono::seconds(1));
                        ofensywaDone=true;
                        validchoice=true;
                        }
                        else
                        switch(Gc.S.Jezyk){
                            case POLSKI:cout<<"Nie mozesz, nie masz wystarczajaco SP"<<endl;break;
                            default:cout<<"You can't, you don't have enough SP"<<endl; break;
                        }
                        break;}
                    default:{
                        cout<<"Nope"<<endl;
                        break;}
                    }
                    }
                }break;
            case '2': //kiedy '2'
            {
                dzwiek("Audio_RPG\\menu_selecting.wav");
                wsparcie_wybrane(Gc);
                bool wsparcieDone=false;
                while (!wsparcieDone){
                    choice=_getch();
                    switch(choice)
                    {
                    case '1':{
                        dzwiek("Audio_RPG\\menu_selecting.wav");
                        AkcjaGorzalka(Gc);
                        wsparcieDone=true;
                        validchoice=true;
                        break;}
                        case '2':{
                            dzwiek("Audio_RPG\\menu_selecting.wav");
                            AkcjaTarcza(Gc);
                            wsparcieDone=true;
                            validchoice=true;
                            break;}
                    default:{
                        cout<<"Nope"<<endl;
                        break;}
                    }
                }
            }break;
            case '3':
            {
            AkcjaEkwipunek(Gc,fajerwerk,tel,zatyczki,validchoice);
            break;}
            default:{ // gdy inny klawisz
                break;}
        }
    }
}
void DzialTURN(Gamecontent &Gc)
{
    bool ogl=false;
    if (Gc.dzialko->HP>0)
    {
        koloruj(11,8);
        cout<<Gc.dzialko->Imie<<" turn:                   "<<endl<<endl;
        koloruj(7,0);
        this_thread::sleep_for(chrono::seconds(2));
        for (const auto &efekt:Gc.dzialko->efekty){
            if (efekt.aktywny==true)
            {
                switch(efekt.ID){
                case OGLUSZENIE:
                    koloruj(11,8);
                    switch (Gc.S.Jezyk){
                        case POLSKI:cout<<Gc.dzialko->Imie<<" zostalo zdeazktywowane!"<<endl;
                        cout<<"Kolejka: "<<efekt.duration<<endl;
                        break;
                        default:cout<<Gc.dzialko->Imie<<" has turned off!"<<endl;
                        cout<<"Lasts till: "<<efekt.duration<<"turns."<<endl;
                        break;
                    }
                    this_thread::sleep_for(chrono::seconds(2));
                    ogl=true;
                    screen(Gc);
                    break;
                }
            }
        }
        if (ogl==true) return;
        dzwiek_ciagly("Audio_RPG\\sentry_spot.wav");
        Character* cel=nullptr;
        for (Character* wrog:Gc.enemies)
        {
            if (czyZyje(wrog)) {cel=wrog; break;}
        }
        unsigned int obrazenia=Gc.dzialko->ATK/cel->DEF;
        if (cel->HP>obrazenia)
            {
                cel->HP-=obrazenia;
                screen(Gc);
            }
        else
        {
            cel->HP=0;
            system("cls");
            screen(Gc);
            koloruj(11,8);
            switch (Gc.S.Jezyk){
                case POLSKI:
                cout<<Gc.dzialko->Imie<<" pokonalo "<<cel->Imie<<"!"<<endl; break;
                default:
                cout<<Gc.dzialko->Imie<<" has defeated "<<cel->Imie<<"!"<<endl; break;
            }
            koloruj(7,0);
        }
        dzwiek_ciagly("Audio_RPG\\sentry_shoot.wav");
        this_thread::sleep_for(chrono::seconds(1));
    }
}
void ZasobTURN(Gamecontent &Gc)
{
    bool ogl=false;
    if (czyZyje(Gc.zasobnik))
    {
        cout<<Gc.zasobnik->Imie<<" turn:                               "<<endl<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        for (const auto &efekt:Gc.zasobnik->efekty){
            if (efekt.aktywny==true)
            {
                switch (efekt.ID){
                case OGLUSZENIE:
                    koloruj(15,8);
                    switch (Gc.S.Jezyk){
                        case POLSKI:cout<<Gc.zasobnik->Imie<<" zostalo zdeazktywowane!"<<endl;
                        cout<<"Kolejka: "<<efekt.duration<<endl;
                        break;
                        default:cout<<Gc.zasobnik->Imie<<" has turned off!"<<endl;
                        cout<<"Lasts till: "<<efekt.duration<<"turns."<<endl;
                        break;
                    }
                    this_thread::sleep_for(chrono::seconds(2));
                    ogl=true;
                    screen(Gc);
                    break;
                }
            }
        }
        if (ogl==true) return;
        dzwiek("Audio_RPG\\zasobnik_heal.wav");
        Gc.zasobnik->heal(Gc.gracz,Gc.zasobnik->ATK);
        screen(Gc);
        koloruj(11,8);
        switch (Gc.S.Jezyk){
                case POLSKI:
                cout<<"Zostales uleczony przez: "<<Gc.zasobnik->Imie<<"!\n"; break;
                default:
                cout<<"You got healed by: "<<Gc.zasobnik->Imie<<"!\n"; break;
            }
        koloruj(7,0);
        this_thread::sleep_for(chrono::seconds(2));
    }
}
bool preferencja_commandera(vector<Character*> &enemies,short id,short Tytanowe){

    for (int T=0;T<enemies.size();T++){
        if (Tytanowe!=0&&enemies[T]->typ==TP::TYTANOWY&&T>id) return false;
        else if(Tytanowe==0&&id!=((enemies.size()+1)/2)-1) return false;
    }
    return true;
}
void CommanderTURN(Gamecontent &Gc,Character *Leader){
    unsigned short typatak=Los(1,0);
    short id_leadera=0;
    bool L;
    bool krytowanie_aktywne=false;
    short Tytanowe=0;
    for (const Character* wrog:Gc.enemies){
        if(wrog==Leader) L=true;
        else if (!L) id_leadera++;
        if(wrog->typ==TP::TYTANOWY) Tytanowe++;
        for(const auto& efekt:wrog->efekty){

        if(efekt.aktywny){
            switch(efekt.ID){
            case KRYTOWANIE: krytowanie_aktywne=true; break;
            default: break;}
            }
        }
    }
        int p=0,k=Gc.enemies.size(), sr=(Gc.enemies.size()+1)/2;
        if(preferencja_commandera(Gc.enemies,id_leadera,Tytanowe)){
            if (typatak==0&&Leader->SP>=3&&!krytowanie_aktywne){
                narysujScene(Gc);koloruj(0,10);
                switch (Gc.S.Jezyk){
                case POLSKI:
                cout<< Leader->Imie<<" daje swojemu oddzialowi wieksza szanse na kryty o 15% na 2 rundy!"<<endl; break;
                default:
                cout<< Leader->Imie<<" gives his army crit boost (15% more chance) for 2 turns!"<<endl; break;
            }
            koloruj(7,0);
                Leader->SP=0;
                for (Character* &wrog:Gc.enemies){
                    Leader->dodajefekt(KRYTOWANIE,2,*wrog);
                }
            }
            else{
                if(czy_pudlo(Leader->missrate)){
                    Leader->spudlowanie();
                    screen(Gc);
                    return;
                }
                AttackResult wl=Leader->damage(Gc.gracz,Leader->ATK);
                kiedy_crit(Gc,wl,*Leader,Gc.gracz);
                if(!wl.bitesthedust){
                    Gc.gracz.PainReact();
                }

            }
        }
        else{
                dzwiek("Audio_RPG\\Commander_order.wav");
                switch(Gc.S.Jezyk){
                case POLSKI:Dialog(Leader->Imie,0,10,"Zmienic szyki!!!");break;
                default:Dialog(Leader->Imie,0,10,"Change order!!!");break;
                }
                this_thread::sleep_for(chrono::seconds(2));
                vector<pair<Character*,int>> temp;
                dzwiek("Audio_RPG\\marsz.wav");
                for(auto &wrog:Gc.enemies){
                    switch (wrog->typ){
                        case TYTANOWY: {temp.push_back({wrog,0});break;}
                        case COMMANDER: {temp.push_back({wrog,1});break;}
                        default: {temp.push_back({wrog,2});break;}
                        }
                }
                if (Tytanowe==0){
                    temp.clear();
                    swap(Gc.enemies[id_leadera],Gc.enemies[sr-1]);
                }
                else{ sort(temp.begin(),temp.end(),[](pair<Character*,int> A,pair<Character*,int> B){
                     return A.second<B.second;});
                    for (int Z=p;Z<k;Z++){
                        Gc.enemies[Z]=temp[Z].first;
                    }
                }
            kolejComm=true;
            screen(Gc);

        }
}
void NaLZomTURN(Gamecontent &Gc,Character* energ,Przedmiot zatyczki)
{
    unsigned short typatak=Los(3,0);
    bool wzmocnienie_istnieje=false;
    bool graczpijany=false;
    bool ogl=false;
    for(const auto& efekt:Gc.gracz.efekty){
        if (efekt.aktywny==true)
        switch(efekt.ID){
            case OGLUSZENIE: ogl=true; break;
        case UPICIE: graczpijany=true; break;
        }
    }
    for (const Character* wrog:Gc.enemies){
        for(const auto& efekt:wrog->efekty){
            if (efekt.ID==TE::WZMOCNIENIE&&efekt.aktywny==true) wzmocnienie_istnieje=true;
        }
    }
    for (const auto& efekt:Gc.dzialko->efekty){
        if (efekt.ID==TE::OGLUSZENIE&&efekt.aktywny==true) ogl=true;
    }
    for (const auto& efekt:Gc.zasobnik->efekty){
        if (efekt.ID==TE::OGLUSZENIE&&efekt.aktywny==true) ogl=true;
    }
    if (typatak==0&&!(wzmocnienie_istnieje))
    {
        koloruj(12,14);
        switch(Gc.S.Jezyk){
        case POLSKI: cout<<energ->Imie<<" przekazuje POZYTYWNY FLUID ENERGETYCZNY pozostalym zombie";koloruj(7,0);cout<<"\n";break;
        default: cout<<energ->Imie<<" gives other zombies the POSITIVE ENERGY FLOW";koloruj(7,0);cout<<"\n";break;
        }
        dzwiek("Audio_RPG\\elektrycznosc1.wav");
        this_thread::sleep_for(chrono::seconds(3));
        for (Character* wrog:Gc.enemies){
                wrog->dodajefekt(WZMOCNIENIE,3,*wrog);
        }
        energ->SP+=Gc.enemies.size();
        screen(Gc);
        koloruj(1,14);
        switch(Gc.S.Jezyk){
            case POLSKI:cout<<"Atak wszystkich zombie zostaje zwiększony o 30% na 3 rundy!!";koloruj(7,0);cout<<"\n";break;
            default:cout<<"The attack power of every zombie has increased by 30% for 3 turns!!";koloruj(7,0);cout<<"\n";break;
        }
    }
    else if(typatak==1&&energ->SP>=10&&!(ogl)){
        energ->SP-=10;
        Gc.kodscreen=24;
        screen(Gc);
        koloruj(12,14);
        switch(Gc.S.Jezyk){
            case POLSKI:cout<<energ->Imie<<" wyladowuje ENERGETYCZNY OVERDRIVE!!";koloruj(7,0);cout<<"\n";break;
            default:cout<<energ->Imie<<" releases the ENERGETIC OVERDRIVE!!";koloruj(7,0);cout<<"\n";break;
        }
        dzwiek("Audio_RPG\\elektrycznosc_shockwave.wav");
        this_thread::sleep_for(chrono::seconds(2));
        Gc.kodscreen=0;
        if(czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
        else if(czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
        if(czyZyje(Gc.dzialko)) {
            Gc.dzialko->dodajefekt(OGLUSZENIE,2,*Gc.dzialko);
            screen(Gc);
            koloruj(15,8);
            switch(Gc.S.Jezyk){
                case POLSKI:cout<<Gc.dzialko->Imie<<" przestalo dzialac.\n";break;
                default:cout<<Gc.dzialko->Imie<<" has stopped working.\n";break;
            }
            dzwiek_ciagly("Audio_RPG\\wylaczanko.wav");
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if(czyZyje(Gc.zasobnik)) {
            Gc.zasobnik->dodajefekt(OGLUSZENIE,2,*Gc.zasobnik);
            screen(Gc);
            koloruj(15,8);switch(Gc.S.Jezyk){
                case POLSKI:cout<<Gc.zasobnik->Imie<<" przestalo dzialac.\n";break;
                default:cout<<Gc.zasobnik->Imie<<" has stopped working.\n";break;
            }
            dzwiek_ciagly("Audio_RPG\\wylaczanko.wav");
            this_thread::sleep_for(chrono::seconds(1));
        }
        else narysujScene(Gc);
            if (graczpijany==true)
            {
                cout<<endl;
                koloruj(8,0);
                switch(Gc.S.Jezyk){
                    case POLSKI: cout<<" To nawet nie drasnelo "<<Gc.gracz.Imie<<" ... BO TAKI OPRUTY!!!       \n";break;
                    default: cout<<" This hasn't even affected "<<Gc.gracz.Imie<<" ... BECAUSE HE'S SO DRUNK!!!       \n";break;
                }
               koloruj(7,0);
                this_thread::sleep_for(chrono::seconds(3));
            }
            else{
                Gc.gracz.dodajefekt(OGLUSZENIE,2,Gc.gracz);
                AttackResult O=energ->damage(Gc.gracz,energ->ATK*2);
                kiedy_crit(Gc,O,*energ,Gc.gracz);
                koloruj(12,8);
                switch(Gc.S.Jezyk){
                    case POLSKI: cout<<" To byl super efektywny cios na "<<Gc.gracz.Imie<<" ... zostaje ogluszony na 1 runde!\n";break;
                    default: cout<<" This was super effective on "<<Gc.gracz.Imie<<" ... he got stunned for 1 round!\n";break;
                }
                koloruj(7,0);
                this_thread::sleep_for(chrono::seconds(3));
            }
        }

    else {
        Gc.kodscreen=23;
        narysujScene(Gc);
        koloruj(12,14);
        switch(Gc.S.Jezyk){
                    case POLSKI: cout<<energ->Imie<<" oddaje elektryczny atak.\n";break;
                    default:cout<<energ->Imie<<" gives off an electric attack.\n";break;
                }
                koloruj(7,0);
        dzwiek_ciagly("Audio_RPG\\elektrycznosc2.wav");
        if (czy_pudlo(energ->missrate)){
            energ->spudlowanie();
            kodscreen=0;
            if(czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
            else if(czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
            screen(Gc);
            return;
        }
        AttackResult w=energ->damage(Gc.gracz,energ->ATK);
        kiedy_crit(Gc,w,*energ,Gc.gracz);
        if (czyZyje(Gc.dzialko)){
                AttackResult w_dzial=energ->damage(*Gc.dzialko,energ->ATK*2);
                kiedy_crit(Gc,w_dzial,*energ,*Gc.dzialko);
                if (!w_dzial.bitesthedust&&czyZyje(Gc.dzialko))
                {
                    dzwiek("Audio_RPG\\Demo_build_ouch.wav");
                }
                else{
                    Gc.kodscreen=0;
                    dzwiek("Audio_RPG\\Demo_ouch_buildDestroyed.wav");
                    screen(Gc);
                    koloruj(11,8);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<energ->Imie<<" zniszyl "<<Gc.dzialko->Imie<<"!!!\n";break;
                        default:cout<<energ->Imie<<" has destroyed "<<Gc.dzialko->Imie<<"!!!\n";break;
                    }
                    koloruj(7,0);
                    this_thread::sleep_for(chrono::seconds(3));
                }
        }
        else if(czyZyje(Gc.zasobnik)){
            short los_cel=Los(2,0);
            if (czy_pudlo(energ->missrate)){
                    energ->spudlowanie();
                    screen(Gc);
                    return;
                }
            if (los_cel==1){
                AttackResult w_zas=energ->damage(*Gc.zasobnik,energ->ATK*3);
                kiedy_crit(Gc,w_zas,*energ,*Gc.zasobnik);
                if (!w_zas.bitesthedust&&czyZyje(Gc.zasobnik))
                {
                    dzwiek("Audio_RPG\\Demo_build_ouch.wav");
                }
                else{
                    Gc.kodscreen=0;
                    dzwiek("Audio_RPG\\Demo_ouch_buildDestroyed.wav");
                    screen(Gc);
                    koloruj(11,8);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<energ->Imie<<" zniszyl "<<Gc.zasobnik->Imie<<"!!!\n";break;
                        default:cout<<energ->Imie<<" has destroyed "<<Gc.zasobnik->Imie<<"!!!\n";break;
                    }
                    koloruj (7,0);
                    this_thread::sleep_for(chrono::seconds(3));
                }
            }
        }
        else dzwiek("Audio_RPG\\Demoman_response_painsharp01.wav");
        energ->SP+=2;

    }
    Gc.kodscreen=0;
    if(czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
    else if(czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
    screen(Gc);
}
void BombyTurn(Gamecontent &Gc,Character* Expld,short odliczanie,Przedmiot zatyczki)
{
    Expld->odliczanie--;
    if (Expld->odliczanie!=0&&Expld->odliczanie>=0)
    {
        dzwiek("Audio_RPG\\Det_pack_timer.wav");
        switch(Gc.S.Jezyk){
        case POLSKI:{
            koloruj(0,4);cout<<" ____________________________________________________________";koloruj (7,0);cout<<"\n";
            koloruj(0,4);cout<<"|"<<string(10,(char)177)<<"ZOMBIE EKSPLODER WYBUCHNIE ZA "<<Expld->odliczanie<<" RUNDY!!!"<<string(10,(char)177)<<"|";koloruj (7,0);cout<<"\n";
            koloruj(0,4);cout<<" ------------------------------------------------------------";koloruj (7,0);cout<<"\n";
            break;}
        default:{
            koloruj(0,4);cout<<" _______________________________________________________________";koloruj (7,0);cout<<"\n";
            koloruj(0,4);cout<<"|"<<string(10,(char)177)<<"ZOMBIE EKSPLODER WILL EXPLODE IN "<<Expld->odliczanie<<" ROUNDS!!!"<<string(10,(char)177)<<"|";koloruj (7,0);cout<<"\n";
            koloruj(0,4);cout<<" ---------------------------------------------------------------";koloruj (7,0);cout<<"\n";
            break;}
        }
        this_thread::sleep_for(chrono::seconds(3));
        screen(Gc);
    }
    else{
            switch(Gc.S.Jezyk){
        case POLSKI:{
             koloruj(0,12);cout<<" _____________________________________________________________";koloruj (7,0);cout<<"\n";
        koloruj(0,12);cout<<"|"<<string(6,(char)177)<<"ZOMBIE EXPLODER WYBUCHNIE! RATUJ SIE KTO MOZE!!!"<<string(6,(char)177)<<"|";koloruj (7,0);cout<<"\n";
        koloruj(0,12);cout<<" -------------------------------------------------------------";koloruj (7,0);cout<<"\n";
            break;}
        default:{
             koloruj(0,12);cout<<" _____________________________________________________________";koloruj (7,0);cout<<"\n";
        koloruj(0,12);cout<<"|"<<string(6,(char)177)<<"ZOMBIE EXPLODER IS GOING TO EXPLODE! GOD HELP!!!"<<string(6,(char)177)<<"|";koloruj (7,0);cout<<"\n";
        koloruj(0,12);cout<<" -------------------------------------------------------------";koloruj (7,0);cout<<"\n";
            break;}
        }
        dzwiek("Audio_RPG\\zaplon_instant_kill.wav");
        if (czy_pudlo(Expld->missrate)){
                Expld->spudlowanie();
                Expld->HP=0;
                    screen(Gc);
                    return;
                }
        this_thread::sleep_for(chrono::milliseconds(3500));
        Gc.gracz.HP=0;
        Expld->HP=0;
        Gc.dzialko->HP=0;
        Gc.zasobnik->HP=0;
        Gc.kodscreen=21;
        screen(Gc);
        this_thread::sleep_for(chrono::milliseconds(2500));
    }
}
void ToxZomTURN(Gamecontent &Gc,Character* ToxicZombie,Przedmiot zatyczki)
{
    unsigned short typataku=Los(9,0);
    bool madepresje=false;
    bool zatruty=false;
    for (const auto& efekt : Gc.gracz.efekty) {
        if (efekt.aktywny==true){
            switch(efekt.ID){
                case OSLABIENIE:
                    madepresje=true;
                    break;
                case ZATRUCIE:
                    zatruty=true;
                    break;
            }
        }
    }
        if (typataku>2&&!madepresje)
        {
            unsigned short typobrazy=Los(8,0);
            switch (typobrazy)
            {
            case 0:{
                switch(Gc.S.Jezyk){
                    case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak gruba!",3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {"Donald Trump chce jej uzyc jej JAKO MUR GRANICZNY!!!!!",5400,"Audio_RPG\\yo_mama_joke01.wav"}});
                        break;
                    default:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Yo mama's so fat!",3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {"Donald Trump used her as a BORDER WALL!!!!!",5400,"Audio_RPG\\yo_mama_joke01.wav"}});
                        break;
                }
                break;}
            case 1:{
                switch(Gc.S.Jezyk){
                    case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak gruba!",3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {"Gdy dolaczyla do Discorda, SCRASHOWALA CALY SERWER!!!!!",6000,"Audio_RPG\\yo_mama_joke02.wav"}});
                        break;
                    default:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Your mother is so fat!",3000,"Audio_RPG\\yo_mama_fat.wav"},
                        {"When she joined Discord, she CRASHED THE ENTIRE SERVER!!!!!",6000,"Audio_RPG\\yo_mama_joke02.wav"}});
                        break;
                }
                break;}
            case 2:{
                switch(Gc.S.Jezyk){
                    case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak gruba!",3000,"Audio_RPG\\yo_mama_fat.wav"},
                        {"Jej pepek dochodzi do domu 20 min przed nia sama!!!",6500,"Audio_RPG\\yo_mama_joke03.wav"},
                        {"... Pamietam to z jednego filmiku na YT.",5500,"Audio_RPG\\yo_mama_joke03_1.wav"}});
                        break;
                    default:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Your mama is so fat!",3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {"Her belly button gets home 20 min before she does!!!",6500,"Audio_RPG\\yo_mama_joke03.wav"},
                        {"... As I remember, I took that from one YT video.",5500,"Audio_RPG\\yo_mama_joke03_1.wav"}});
                        break;
                    }
                break;}
            case 3:
                switch(Gc.S.Jezyk){
                    case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak brzydka!",3000,"Audio_RPG\\yo_mama_ugly.wav"},
                        {"To ona jest powodem, dlaczego Herobrine z Minecrafta NIE MA ZRENIC!!!",7000,"Audio_RPG\\yo_mama_joke04_1.wav"},
                        {"... Ok, to bylo kreatywne powiazanie!",4000,"Audio_RPG\\yo_mama_joke04_2.wav"}});
                        break;
                    default:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Your mother is so ugly!",3000,"Audio_RPG\\yo_mama_ugly.wav"},
                        {"She is the real reason, why Herobrine from Minecraft DOESN'T HAVE PUPILS!!!",7000,"Audio_RPG\\yo_mama_joke04_1.wav"},
                        {"... Ok, that was a creative one!",4000,"Audio_RPG\\yo_mama_joke04_2.wav"}});
                        break;
                }
                break;
            case 4:
                switch(Gc.S.Jezyk){
                case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak gruba!",3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {"Nie potrzebuje internetu... bo ONA JUZ JEST GLOBALNA!!!!!",6000,"Audio_RPG\\yo_mama_joke05.wav"}});
                        break;
                default:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Your mama is so fat!",3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {"She doesn't need internet... she is ALREADY WORLDWIDE!!!!!",6000,"Audio_RPG\\yo_mama_joke05.wav"}});
                        break;
                }
                break;
            case 5:
                switch(Gc.S.Jezyk){
                case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak glupia!",3000,"Audio_RPG\\yo_mama_stupid2.wav"},
                        {"Jej splash attack... ZARAZ NIE!",4000,"Audio_RPG\\yo_mama_joke06.wav"},
                        {"Nie chce spalic tej riposty... emmm...",5000,"Audio_RPG\\yo_mama_joke06_1.wav"},
                        {"O! Juz pamietam!",3000,"Audio_RPG\\yo_mama_joke06_2.wav"},
                        {"Twoja stara jest tak glupia! Poszla do dentysty... aby OTRZYMAC BLUETOOTH!!!!!",7800,"Audio_RPG\\yo_mama_joke06_3.wav"}});
                        break;
                default:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Your mother is so stupid!",3000,"Audio_RPG\\yo_mama_stupid2.wav"},
                        {"Her splash attack... WAIT, NO!",4000,"Audio_RPG\\yo_mama_joke06.wav"},
                        {"I don't want to spoil the punchline... ummm...",5000,"Audio_RPG\\yo_mama_joke06_1.wav"},
                        {"Oh! I remember!",3000,"Audio_RPG\\yo_mama_joke06_2.wav"},
                        {"Your mother is so stupid! She went to the dentist... TO GET A BLUETOOTH!!!!!",7800,"Audio_RPG\\yo_mama_joke06_3.wav"}});
                        break;
                }
                break;
            case 6:
                switch(Gc.S.Jezyk){
                case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak glupia!",3000,"Audio_RPG\\yo_mama_stupid.wav"},
                        {"Zwrocila do reklamacji donuta, bo mial DZIURE!!!",4800,"Audio_RPG\\yo_mama_joke07.wav"}});
                        break;
                default:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Your mother is so stupid!",3000,"Audio_RPG\\yo_mama_stupid.wav"},
                        {"She returned the donut because it has A HOLE!!!",4800,"Audio_RPG\\yo_mama_joke07.wav"}});
                        break;
                }
                break;
            case 7:
                switch(Gc.S.Jezyk){
                case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Twoja stara jest tak glupia!",3000,"Audio_RPG\\yo_mama_stupid2.wav"},
                        {"Umowila sie na badanie lekarskie do DR. PEPPER'A!!!!",4000,"Audio_RPG\\yo_mama_joke08.wav"}});
                        break;
                default: AdvDialog(ToxicZombie->Imie,10,8,{
                        {"Your mother is so stupid!",3000,"Audio_RPG\\yo_mama_stupid2.wav"},
                        {"She made an appointment with DR. PEPPER!!!!",4000,"Audio_RPG\\yo_mama_joke08.wav"}});
                        break;
                }
                break;
            default:
                switch(Gc.S.Jezyk){
            case POLSKI:AdvDialog(ToxicZombie->Imie,10,8,{
                          {"Tak dla wspomnienia... TWOJA STARA!!!",4000,"Audio_RPG\\yo_mama_joke_default.wav"},
                          {"Taa... malo wlozylem w to wysilku, ale to nawet samo zawsze dzialalo!",5000,"Audio_RPG\\yo_mama_joke_default2.wav"}});
                            break;
                default:AdvDialog(ToxicZombie->Imie,10,8,{
                          {"One important mention... YOUR MOTHER!!!",4000,"Audio_RPG\\yo_mama_joke_default.wav"},
                          {"Yeah... that was a low-effort one, but it always hits the punchline!",5000,"Audio_RPG\\yo_mama_joke_default2.wav"}});
                          break;
                }
                break;
            }
            if (zatyczki.quant>0){
                koloruj (7,8);
                switch(Gc.S.Jezyk){
                    case POLSKI: cout<<Gc.gracz.Imie<<" nosi zatyczki - Oczernianie 'starej' nie przejelo gracza...\n"; break;
                    default: cout<<Gc.gracz.Imie<<" wears earplugs - trashtalk doesn't work here...\n"; break;
                }
                this_thread::sleep_for(chrono::seconds(3));
            }
            else{
            screen(Gc);
            dzwiek("Audio_RPG\\Demo_krytyczny_cios_psychiczny.wav");
            koloruj (14,13);
            switch(Gc.S.Jezyk){
                    case POLSKI: cout<<Gc.gracz.Imie<<" czuje sie upokorzony... jego atak spada o 50%!!\n"; break;
                    default: cout<<Gc.gracz.Imie<<" feels humiliated... his attack power drops by 50%!!\n"; break;
                }
            koloruj (7,0);
            Gc.gracz.dodajefekt(OSLABIENIE,3,Gc.gracz);
            this_thread::sleep_for(chrono::seconds(3));
            dzwiek_ciagly("Audio_RPG\\Demoman_response_smutek.wav");
            screen(Gc);
            }
        }
        else{
                Gc.kodscreen=22;
            narysujScene(Gc);
            dzwiek("Audio_RPG\\rzyg.wav");
            koloruj(11,8);
            switch(Gc.S.Jezyk){
                    case POLSKI: cout<<ToxicZombie->Imie<<" pluje na "<<Gc.gracz.Imie<< " jadem!            "<<endl; break;
                    default: cout<<ToxicZombie->Imie<<" spits venom on "<<Gc.gracz.Imie<< "                 "<<endl; break;
                }
            koloruj(7,0);
            this_thread::sleep_for(chrono::seconds(3));
            if (czy_pudlo(ToxicZombie->missrate)){
                    ToxicZombie->spudlowanie();
                    screen(Gc);
                    return;
                }
            AttackResult w=ToxicZombie->damage(Gc.gracz,ToxicZombie->ATK);
            kiedy_crit(Gc,w,*ToxicZombie,Gc.gracz);
            if (!w.bitesthedust)
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
            Gc.kodscreen=0;
            if(czyZyje(Gc.dzialko))
                Gc.kodscreen+=6;
            else if(czyZyje(Gc.zasobnik))
                Gc.kodscreen+=12;
                screen(Gc);
                this_thread::sleep_for(chrono::seconds(1));
                if (Los(100,0)<70){
                    narysujScene(Gc);
                        if(zatruty==false) {
                            Gc.gracz.dodajefekt(ZATRUCIE,3,Gc.gracz);
                            dzwiek("Audio_RPG\\Demoman_response_hssss.wav");
                            koloruj(10,1);
                            switch(Gc.S.Jezyk){
                                case POLSKI: cout<<"Zostales Zatruty! Od teraz przez 3 rundy bedzie ci spadac zdrowie!\n"; break;
                                default: cout<<"You got poisoned! From now for 3 turns your healt will be dropping a little!\n"; break;
                            }
                            koloruj(7,0);
                        }
                        else{
                            koloruj(7,8);
                            switch(Gc.S.Jezyk){
                                case POLSKI: cout<<"Zatrucie nie dziala - "<<Gc.gracz.Imie<<" juz jest zatruty.\n";break;
                                default: cout<<"Poisoning doesn't work here - "<<Gc.gracz.Imie<<" is already poisoned.\n"; break;
                            }
                        koloruj(7,0);
                        }
                    this_thread::sleep_for(chrono::seconds(2));
                    screen(Gc);
                }
            }
        else{
                Gc.gracz.PainReact();
                this_thread::sleep_for(chrono::seconds(1));
            narysujScene(Gc);}
        }

}
void ZomTURN(Gamecontent &Gc,short odliczanie,Character* &t)
{
    wybor=true;
    SprawdzZIndeksem(t,Gc.enemies,wskazany);
    koloruj(11,8);
    cout<<t->Imie<<" turn:          "<<endl;
    koloruj(7,0);
    this_thread::sleep_for(chrono::seconds(2));
    bool ogl=false;
    for (const auto& efekt:t->efekty){
        if (efekt.ID==1&&efekt.aktywny==true)//jezeli zostal ogluszony
        {
            koloruj(11,8);
            switch(Gc.S.Jezyk){
                case POLSKI:
                    cout<<t->Imie<<" jest ogluszony i nie moze sie ruszyc!"<<endl;
                    cout<<"Kolejka: "<<efekt.duration<<endl;
                    break;
                default:
                    cout<<t->Imie<<" is stunned and he can't move!"<<endl;
                    cout<<"Remains for: "<<efekt.duration<<" turns."<<endl;
                    break;
                }
            koloruj(7,0);
            this_thread::sleep_for(chrono::seconds(3));
            ogl=true;
            screen(Gc);
            break; // KONIEC TURY! ZOMBIE NIE ATAKUJE
        }
        if (efekt.ID==3&&efekt.aktywny==true)//jezeli zostal wzmocniony
        {
            t->ATK+=t->ATK*0.3;
        }
    }
    if (ogl==true) return;
    //normalnie
    if (t->typ==TP::TOKSYCZNY) ToxZomTURN(Gc,t,zatyczki);
    else if(t->typ==TP::EXPLODER) BombyTurn(Gc,t,odliczanie,zatyczki);
    else if(t->typ==TP::NALADOWANY) NaLZomTURN(Gc,t,zatyczki);
    else if(t->typ==TP::COMMANDER) {CommanderTURN(Gc,t);
    if (kolejComm){kolejComm=false;ZomTURN(Gc,odliczanie,Gc.enemies[0]);}
    }
    else{

        if (czyZyje(Gc.dzialko)){
                if (czy_pudlo(t->missrate)){
                    t->spudlowanie();
                    return;
                }
                AttackResult w=t->damage(*Gc.dzialko,t->ATK);
                kiedy_crit(Gc,w,*t,*Gc.dzialko);
                if (!w.bitesthedust)
                {
                    Gc.dzialko->PainReact();
                }
                else{
                    Gc.kodscreen=0;
                    dzwiek("Audio_RPG\\build_destroyed.wav");
                    screen(Gc);
                    koloruj(11,8);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<t->Imie<<" zniszyl "<<Gc.dzialko->Imie<<"!!!\n";break;
                        default:cout<<t->Imie<<" has destroyed "<<Gc.dzialko->Imie<<"!!!\n";break;
                    }
                    koloruj(7,0);
                    this_thread::sleep_for(chrono::seconds(3));
                }
            return;
        }
        else if(czyZyje(Gc.zasobnik)){
            if (czy_pudlo(t->missrate)){
                    if (czy_pudlo(t->missrate)){
                    t->spudlowanie();
                    return;
                }
                AttackResult w=t->damage(*Gc.zasobnik,t->ATK);
                kiedy_crit(Gc,w,*t,*Gc.zasobnik);
                if (!w.bitesthedust)
                {
                    Gc.zasobnik->PainReact();
                }
                else{
                    Gc.kodscreen=0;
                    dzwiek("Audio_RPG\\build_destroyed.wav");
                    screen(Gc);
                    koloruj(11,8);
                    switch(Gc.S.Jezyk){
                        case POLSKI: cout<<t->Imie<<" zniszyl "<<Gc.zasobnik->Imie<<"!!!\n";break;
                        default:cout<<t->Imie<<" has destroyed "<<Gc.zasobnik->Imie<<"!!!\n";break;
                    }
                    koloruj (7,0);
                    this_thread::sleep_for(chrono::seconds(3));
                }
                return;
            }
        }
        if (czy_pudlo(t->missrate)){
            t->spudlowanie();
            return;
        }
        AttackResult w1=t->damage(Gc.gracz,t->ATK);
        kiedy_crit(Gc,w1,*t,Gc.gracz);
        if (!w1.bitesthedust)
            {
                Gc.gracz.PainReact();
            }
        else screen(Gc);

        Gc.wybor=false;
    }
}
bool CzyBylSklep=false;
void ciagla_walka(Gamecontent &Gc,short &Barka_status,bool &CzyBylSklep)
{

    Gc.wybor=false;
    for (const Character* wrog:Gc.enemies){
        if (wrog==nullptr) {
            switch(Gc.S.Jezyk){
            case POLSKI: cout << "Blad: Wskaznik na wroga jest null!" << endl;break;
            default: cout << "Error: The pointer of an enemy doesn't exist (null)!" << endl;break;
            }
            return; // Zakoncz funkcje, jesli wskaznik jest nieprawidlowy
        }
    }

    dzwiek("Audio_RPG\\Demoman_response_battlecry.wav");
    while (czyZyje(Gc.gracz))
    {
        if (Gc.x%5==1&&Gc.x!=1&&!CzyBylSklep)
        {
            Gc.gracz.DEF=1;
            Gc.kodscreen=20;
            CzyBylSklep=true;
            dzwiek_loop("Audio_RPG\\Upgradestation_loop.wav");
            screen(Gc);
            panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
            do
            {
                sklep_input(Gc,tarcza,WATK,MATK,ult,ulw,ulm,fajerwerk,tel,zatyczki);
            }while (Gc.kodscreen==20);
            short battlecry=Los(10,0);
            if (battlecry<5)
                dzwiek("Audio_RPG\\Demoman_response_battlecry.wav");
            else
                dzwiek("Audio_RPG\\Demoman_response_battlecry2.wav");
        }
        else
        {
        if (czyZyje(Gc.dzialko))
            Gc.kodscreen=6;
        else if (czyZyje(Gc.zasobnik))
            Gc.kodscreen=12;
        else
            Gc.kodscreen=0;
        for (Character* wrog:Gc.enemies) {
            if (czyZyje(wrog)&&wrog->czy_doubleATK==true) {
                screen(Gc);
                this_thread::sleep_for(chrono::seconds(1));
                ZomTURN(Gc,wrog->odliczanie,wrog);
                wybor=false;
                if (!czyZyje(Gc.gracz)) return;
            }
        }
        screen(Gc);
        panele(Gc,ult,ulw,ulm,fajerwerk,tel,zatyczki);
        Gc.gracz.missrate=0.08;
        Gc.gracz.ATK=20;
        Input(Barka_status,Gc,fajerwerk,tel,zatyczki);
        Gc.kodscreen=0;
        if (czyZyje(Gc.dzialko)) Gc.kodscreen+=6;
        else if (czyZyje(Gc.zasobnik)) Gc.kodscreen+=12;
        if (czyZyje(Gc.dzialko)&&!(EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)))
            DzialTURN(Gc);
        else if (czyZyje(Gc.zasobnik)&&!(EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)))
            ZasobTURN(Gc);
        screen(Gc);
        if (EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)==true) {
            CzyBylSklep=false;
            for (Character* wrog:Gc.enemies){
            if (czyZyje(wrog)) wrog->updateujEfekty(*wrog);
            Gc.gracz.EXP+=wrog->EXP+(10*Gc.x);
            ogluszenie=false;
            if (czyZyje(wrog)) wrog->updateujEfekty(*wrog);
            }
            switch(Gc.S.Jezyk){
            case POLSKI:{
                for (const Character* wrog:Gc.enemies){
                if (liczba_wrogow==1){cout << "\n" << wrog->Imie << " zostal pokonany! Wygrywasz!" << endl;}
                else cout << "\n Wszyscy wrogowie zostali pokonani! Wygrywasz!" << endl;break;
                }
                break;}
            default:{
                for (const Character* wrog:Gc.enemies){
                if (liczba_wrogow==1){ cout << "\n" << wrog->Imie << " has been defeated! You win!" << endl;}
                else cout << "\n Every enemy here has been defeated! You win!" << endl;break;
                }
                break;}
            }
            czekaj=0;
            int kodwypowiedz=Los(10,0);
            if (dlacase==true)
                {
                    switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"I oto to zyskujesz, gdy dotkniesz tego!");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"And that's what ya get for touching that!");break;
                    }
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_win.wav");
                    dlacase=false;
                }
            else{
            switch (kodwypowiedz)
            {
            case 1:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"Jak ci do tego, balwanie?!");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"How's that feel ya, blockhead?!");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_pogarda.wav");
                break;
            case 2:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"Niech to bedzie dla ciebie cho****a nauczka!");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"Let that be a bloody lesson to yeh!");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_pogarda2.wav");
                break;
            case 3:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"W waszym jezyku - zryjcie olow, lads'i!");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"In your language - eat lead, ladies!");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_pogarda3.wav");
                break;
            case 4:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"(smiech)");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"(laugh)");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_laugh.wav");
                break;
            case 5:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"TAK SIE POWINNO TO ROBIC!!!");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"THAT'S THE WAY YA DO IT!!!");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_reaponse_win2.wav");
                break;
            case 6:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"ZDOMINOWANY! (smiech)");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"DOMINATED! (laugh)");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_domination.wav");
                break;
            case 7:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"Widzisz? Mowilem, ze sa to niezle sztuki malych sku***elow!");break;
                    default: Dialog(Gc.gracz.Imie,12,0," See? I told ye they were a buncha' wee lasses!");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_win3.wav");
                break;
            case 8:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"(smiech)");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"(laugh)");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_laugh2.wav");
                break;
            case 9:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"(smiech)");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"(laugh)");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_laugh3.wav");
                break;
            case 10:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"(spiewajaco) Wszyscy pyszalkowie podskakuja ze swymi lbami pelnym galek [ocznych]!");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"(singing) All yah dandies prancin' aboot with ya heads full of eyeballs!");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_domination2.wav");
                break;
            default:
                switch(Gc.S.Jezyk){
                    case POLSKI: Dialog(Gc.gracz.Imie,12,0,"Ooo, beda was musieli posklejac klejem z powrotem... W PIEKLE!!!");break;
                    default: Dialog(Gc.gracz.Imie,12,0,"Oh, they're goin' ta have to glue you back together... IN HELL!!!");break;
                }
                dzwiek_ciagly("Audio_RPG\\Demoman_response_glue.wav");
                break;
            }
            }
            this_thread::sleep_for(chrono::seconds(2));
            Gc.x++;
            for (Character* wrog:Gc.enemies){
                if (wrog!=nullptr) delete wrog;
            }
            Gc.enemies.clear();
            nowyWrog(Gc,base_HP_wrog);
            Gc.gracz.DEF=1;
            system("cls");
            }
        else {
            bool kolejComm=false;
                short chark=Los(2,0);
            switch (chark)
            {
            case 0:
                dzwiek("Audio_RPG\\Zombie_charczy1.wav");
                break;
            case 1:
                dzwiek("Audio_RPG\\Zombie_charczy2.wav");
                break;
            default:
                dzwiek("Audio_RPG\\Zombie_charczy3.wav");
                break;
            }
            Gc.wskazany=0;
            for (Character* wrog:Gc.enemies) {
                    wskazany++;
                if (czyZyje(wrog)==true) {
                    wybor=true;

                    narysujScene(Gc);
                if(wrog->typ==TP::COMMANDER&&kolejComm) continue;
                else {
                    ZomTURN(Gc,wrog->odliczanie,wrog);
                    if(wrog->typ==TP::COMMANDER&&!kolejComm) kolejComm=true;
                }
                wybor=false;
            }
        }
        Gc.gracz.DEF=1;
        }
        for (const auto& efekt:Gc.gracz.efekty)
        {
            if (efekt.aktywny==true){
                    switch(efekt.ID){
                    case ZATRUCIE:{
                        int zatrucie=3+(pow(2,Gc.x-1));
                        int maks_zatrucie=Gc.gracz.base_HP*0.1; // maksymalnie 10% HP
                        zatrucie=min(zatrucie, maks_zatrucie);
                        if (Gc.gracz.HP>=zatrucie) Gc.gracz.HP-=zatrucie;
                        else Gc.gracz.HP=0;
                        dzwiek("Audio_RPG\\damage_taken.wav");
                        screen(Gc);
                        switch(Gc.S.Jezyk){
                            case POLSKI:cout<<Gc.gracz.Imie<<" doznaje obrazen w wyniku zatrucia.\n";break;
                            default:cout<<Gc.gracz.Imie<<" suffers from poison.\n";break;
                        }
                        this_thread::sleep_for(chrono::seconds(2));
                        break;}
                    default: break;
                    }
            }
        }
        Gc.gracz.updateujEfekty(Gc.gracz);
        if (czyZyje(Gc.dzialko)) Gc.dzialko->updateujEfekty(*Gc.dzialko);
        if (czyZyje(Gc.zasobnik)) Gc.zasobnik->updateujEfekty(*Gc.zasobnik);
        for (Character* wrog:Gc.enemies) {
            if (czyZyje(wrog)) wrog->updateujEfekty(*wrog);
        }
        }

    }
}
