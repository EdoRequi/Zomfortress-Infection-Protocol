#include <iostream>
#include <conio.h>
#include <time.h>
#include <thread>
#include <windows.h>
#include <vector>

#include "Gamestuff.h"
using namespace std;
using TP = TypPostaci;
using GW=Globalne;
using namespace std::chrono;
int score=0;
bool debug=false;
void UstawTekst(short width, short height)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//operator kontroli konsola

    CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };
    GetCurrentConsoleFontEx(hOut, FALSE, &cfi);

    cfi.dwFontSize.X = width;
    cfi.dwFontSize.Y = height;

    wcscpy(cfi.FaceName, L"Consolas"); // albo "Lucida Console"

    SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}
void uzyjUTF8(wchar_t znak, int ile){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i=0;i<ile;i++)WriteConsoleW(h,&znak,1,NULL,NULL);
}
void ustawienia(bool &debug,Settings &S)
{
    system("cls");
    char ust;
    while (ust!='x'){
    system("cls");
    koloruj(0,7);
    for (int a=0;a<8;a++){
        cout<<"                                                                                                    "<<endl;
        }
        cout<<S.L.get(Tx::Sw_ENDEBUG)<<setw(10)<<left<<(debug==true?"ENABLED *":"DISABLED *")<<"                          "<<endl<<endl;
        cout<<S.L.get(Tx::Sw_FONTSIZE)<<setw(4)<<left<<S.WCzcionki<<"+/-                       "<<endl<<endl;
        cout<<" PRESS ALT+F4 FOR FREE ROBUX"<<endl;//easter egg
        cout<<"VERSION: INDEV 0.3"<<endl;
        cout<<S.L.get(Tx::X_for_exit)<<"                                     ";
        ust=_getch();
        switch (ust){
        case '1':
            if (debug==false) debug=true;
            else debug=false;
            break;
        case '+':
            if (S.WCzcionki>29){
                S.WCzcionki=30;
                cerr<<"Morbidly obese text!!"<<endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            else {S.WCzcionki++;UstawTekst(0,S.WCzcionki);}
            break;
        case '-':
            if (S.WCzcionki<9){
                S.WCzcionki=8;
                cerr<<"It is so tiny!"<<endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            else {S.WCzcionki--; UstawTekst(0,S.WCzcionki); }
            break;
        }
    }
    koloruj(15,12);
}
void przycisk(string tekst,Settings &S, const short numer_aktyw){
    short miejsce=21;
    cout<<"                                         "<<char(201)<<string(21,(char)205)<<(char)187<<"                                      \n";
    if(tekst.size()<=miejsce){
        short iloscdowypelnienia=miejsce-tekst.size(), jednaczesc,drugaczesc;
        jednaczesc=iloscdowypelnienia/2;
        (iloscdowypelnienia%2==0?drugaczesc=jednaczesc:drugaczesc=jednaczesc+1);
        cout<<"                                         "<<(char)186;(S.IDwybor==numer_aktyw?koloruj(15,3):koloruj(0,15));cout<<string(jednaczesc,(char)176)<<tekst<<string(drugaczesc,(char)176);koloruj(15,12);cout<<(char)186<<"                                      \n";

    }
    else{
        string temp="";
        while (!tekst.empty()){
            for (char c:tekst){
                temp+=c;
                if(temp.size()==miejsce||(temp.size()>=miejsce-4&&c==' ')||(temp.size()==tekst.size()&&temp.size())){usunprzedzial(tekst,temp.size());break;}
            }
            short iloscdowypelnienia=miejsce-temp.size(),jednaczesc,drugaczesc;
            jednaczesc=iloscdowypelnienia/2;
            (iloscdowypelnienia%2==0?drugaczesc=jednaczesc:drugaczesc=jednaczesc+1);
            cout<<"                                         "<<(char)186;(S.IDwybor==numer_aktyw?koloruj(15,3):koloruj(0,15));cout<<string(jednaczesc,(char)176)<<temp<<string(drugaczesc,(char)176);koloruj(15,12);cout<<(char)186<<"                                      \n";
            temp.clear();}
        }
    cout<<"                                         "<<char(200)<<string(21,(char)205)<<(char)188<<"                                      \n";
}
void menu(bool &debug,Settings &S)
{
    koloruj(15,12);
    bool wmenu=false;
    while(!wmenu){
            system("cls");
        cout<<"                                        SELECT LANGUAGE:                                              "<<endl;
        przycisk("POLSKI",S,1);
        cout<<endl;
        przycisk("ENGLISH",S,2);
        char Lt = tolower(_getch());
        switch (Lt){
            case 'w': if(S.IDwybor>1) S.IDwybor--;break;
            case 's': if(S.IDwybor<2) S.IDwybor++;break;
            case 13:
                if(S.IDwybor==1)S.L.setLanguage(Language::POLSKI);
                else if(S.IDwybor==2)S.L.setLanguage(Language::ANGIELSKI);
                wmenu=true;break;
        }
    }
    bool wgrze=false; S.IDwybor=0;
    short los_muzyka=rand()%3;
    if(los_muzyka==0) dzwiek_loop("Audio_RPG\\TF2_Theme_Medley.wav");
    else if(los_muzyka==1) dzwiek_loop("Audio_RPG\\TF2_Doom_remix.wav");
    else dzwiek_loop("Audio_RPG\\TF2_Drunken_Pipe_Bomb.wav");
    while(wgrze!=true)
    {
        system ("cls");
        for (int a=0;a<8;a++){
        cout<<"                                                                                                      "<<endl;
        }
        cout<<"                                 ZOMFORTRESS: INFECTION PROTOCOL                                      "<<endl;
        cout<<"                                           (redesigned)                                               "<<endl;
        cout<<string(102,(char)223)<<endl;
        cout<<"                                                                                                      "<<endl;
        przycisk(L.get(Tx::But_PLAY1),S,1);
        cout<<endl;
        przycisk(L.get(Tx::But_PLAY2),S,2);
        cout<<"                                            ";koloruj(12,15);cout<<"^Not avaliable yet^";koloruj(15,12);cout<<"                           "<<endl;
        przycisk(L.get(Tx::But_Sett),S,3);
        cout<<endl;
        cout<<"Creator: EdoRequi                                                                                     \n"; //credits
        char st = tolower(_getch());
        switch (st)
        {
        case 'w':
            if(S.IDwybor>1) S.IDwybor--;
            break;
        case 's':
            if(S.IDwybor<3) S.IDwybor++;
            break;
        case 13:
            if (S.IDwybor==1)
            {
                koloruj(7,0);
                wgrze=true;
            }
            if (S.IDwybor==3){
                koloruj(0,7);
                ustawienia(debug,S);
            }
            break;
        }
    }
}
void story()//historyjka
{
    system("cls");
    this_thread::sleep_for(chrono::seconds(1));
    char D=' ';
    int str=0;
    while(D!='x'&&str<=1){
    switch (S.L.whatLanguage()){
        case Language::POLSKI:{
        cout << " _____________________________________________________\n";
        cout << "|";koloruj (0,15);cout<<" 13 maja 2012 roku. Dzien, ktory mial przejsc do  \\ ";koloruj(7,0);cout<<"|_\n";
        cout << "|"; koloruj (0,15); cout<<" historii jako poczatek koszmaru.                \\    "; koloruj (7,0); cout<<"|_\n";
        cout << "|"; koloruj (0,15); cout<<"                                                   \\    ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"  W wojskowym laboratorium badawczym Mann Co., gdzie     ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" eksperymenty nad nowoczesnymi technologiami przeplataly ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" sie z rzadowymi tajemnicami (a przynajmniej tak twierdzi";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" ulotka reklamowa), straz nocna miala byc tylko rutyna. _";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"                                                        ";koloruj (7,0);cout<<"|_\n";
        cout << "|";koloruj (0,15);cout<<"  Jednak dla jednego czlowieka - doswiadczonego          ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" zolnierza, sierzanta Demomana - ta noc okazala sie     _";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" brzemienna w skutki.                            _/_   _";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"                                                 /    ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"  Nieco zbyt entuzjastycznie swietujac kolejne zwyciestwa";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" w niezliczonych bitwach, Demoman postanowil ''umocnic'' ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" swoj dyzur czyms bardziej wysokoprocentowym.            ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" Niestety, w stanie lekkiego upojenia, dokonal fatalnej  ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" pomylki - zamiast zwyklej wody destylowanej, wlal do    ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" systemu chlodzenia beczke wysoko skazonych odpadow      ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" radioaktywnych (dlaczego Mann Co. w ogole je mialo?     ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" Lepiej nie pytac).                                      ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"...                                    ==               ";koloruj (7,0);cout<<"|\n";
        cout << " ";koloruj (0,15);cout<<"________________________________________________________";koloruj (7,0);cout<<"\n";
        cout << "WCISNIJ 'X', ABY PRZEJSC DALEJ" << endl;break;}
        case Language::ANGIELSKI:{
        cout << " _____________________________________________________\n";
        cout << "|";koloruj (0,15);cout<<" On May 13th, 2012 year. The day, which happened to \\ ";koloruj(7,0);cout<<"|_\n";
        cout << "|"; koloruj (0,15); cout<<" be the beginning of this nightmare.                 \\   "; koloruj (7,0); cout<<"|\n";
        cout << "|"; koloruj (0,15); cout<<"                                                      \\  ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"  In a military base of Mann Co. , where research        ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" on advanced technologies went hand in hand               ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" with govermental secrets (according to an advertisement ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" leaflet), the night guard was supposed to be only      _";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" a routine.                                             ";koloruj (7,0);cout<<"|_\n";
        cout << "|";koloruj (0,15);cout<<"  However this night for one man - the experienced       ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" soldier, known as a veteran Demoman - had a lot of      _";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" consequences.                                   _/_   _";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"                                                 /    ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"                                                /     ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"  When he had been celebrating too enthusiastically      ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" countless victories in battles, Demoman decided to      ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" 'fortify' his watch with something stiffer.             ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" Unfortunately, in a state of intoxication, he made a    ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" fatal mistake - instead of an ordinary distilled water  ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" used in the facility for cooling system, he poured a    ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" barell of radioactive waste (why Mann Co. had it in ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<" stock? Better not to ask).                              ";koloruj (7,0);cout<<"|\n";
        cout << "|";koloruj (0,15);cout<<"...                                    ==               ";koloruj (7,0);cout<<"|\n";
        cout << " ";koloruj (0,15);cout<<"________________________________________________________";koloruj (7,0);cout<<"\n";
        cout << L.get(Tx::X_for_continue) << endl;break;}
        default: str++; break;
    }
    dzwiek("Audio_RPG\\Undertale_onceuponatime.wav");
    D=tolower(_getch());
    if (D=='x')
    {
        D='l';
        str++;
        system("cls");
        switch (S.L.whatLanguage()){
            case Language::POLSKI:{
            cout << " _________________________________________________________\n";
            cout << "|";koloruj (0,15);cout<<"  Kiedy nad ranem ocknal sie do rzeczywistosci, ktora  ";koloruj(12,15);cout<<"#~";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" sam nieopatrznie stworzyl, bylo juz za pozno.           ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" Wszyscy naukowcy i zolnierze pracujacy w kompleksie     ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" ulegli tajemniczej mutacji. Teraz, zamienieni w zadne   ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" krwi zombie, blakali sie po korytarzach, szukajac     _";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" pierwszej ofiary.                                   _";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<"                                       ^\\           ";koloruj (7,0);cout<<"|_\n";
            cout << "|";koloruj (0,15);cout<<"  Ze swoim mieczem ,Eyelanderem, i wyrzutnikiem granatow";koloruj (7,0);cout<<"|_\n";
            cout << "|";koloruj (0,15);cout<<" samoprzylepnych w drugiej, Demoman musi stawic czola    ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" koszmarowi, ktory nie tylko zagraza jego zyciu, ale moze";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" stac sie miedzynarodowym skandalem. Jesli ten sekret    ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" wyjdzie na jaw, honor garnizonu zostanie splamiony      ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" na zawsze.                                               ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<"                                                         ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<"  Czy podejmiesz sie misji ocalenia bazy i zatrzymania   ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" epidemii, nim bedzie za pozno?                          ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<"_________________________________________________________";koloruj (7,0);cout<<"|\n";
            cout << endl << endl;
            cout << "WCISNIJ 'X', ABY PRZEJSC DALEJ" << endl;break;}
            case Language::ANGIELSKI:{
            cout << " _________________________________________________________\n";
            cout << "|";koloruj (0,15);cout<<"  In the morning, when he regained consciousness, it was";koloruj(12,15);cout<<"#~";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" too late.                                               ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" Every scientist and troop inside the complex had gone   ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" through a mysterious mutation. Being turned into hostile";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" and bloodthirsty zombies, they wandered  around the   _";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" facility, looking for their first prey.             _";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<"                                       ^\\           ";koloruj (7,0);cout<<"|_\n";
            cout << "|";koloruj (0,15);cout<<"  Wielding his sword, Eyelander, in one hand, as well  ";koloruj (7,0);cout<<"|_\n";
            cout << "|";koloruj (0,15);cout<<" as well as the Sticky Bomb Launcher in another one,     ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" Demoman has to stand against the horrifying reality,    ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" being not just a threat to his life, but also a         ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" potential worldwide scandal. If this secret exposes     ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" itself, the honour of his garrison will be stained      ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" permanently.                                            ";koloruj (7,0);cout<<"|_\n";
            cout << "|";koloruj (0,15);cout<<"  Will you take on the mission of saving the base and    ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<" stopping the epidemic before it's too late?             ";koloruj (7,0);cout<<"|\n";
            cout << "|";koloruj (0,15);cout<<"_________________________________________________________";koloruj (7,0);cout<<"|\n";
            cout << endl << endl;
            cout << "PRESS 'X' TO CONTINUE" << endl;break;}
            default: str++; break;
        }
        D=tolower(_getch());
        if (D=='x')
            str++;
            }
    }
}
int main()
{
    debug=false;
    UstawTekst(S.WCzcionki,S.WCzcionki);
    system("mode con cols=102 lines=60");
    srand(static_cast<unsigned>(time(nullptr)));
    menu(debug,S);
    PlaySound(NULL, 0, 0);
    story();
    long x=1;
    short battlecry=rand()%(10-1+1)+1;
            if (battlecry<5)
                dzwiek("Audio_RPG\\Demoman_response_battlecry.wav");
            else
                dzwiek("Audio_RPG\\Demoman_response_battlecry2.wav");
    Player gracz(TP::GRACZ,"DemomanTF2",175,175,20,0,10,1,TypRoli::DEMOMAN,false,0.01,0.08);
    Character* dzialko=new Character(TP::DZIALKO,"Dzialko Straznicze",0,0,0,0,0,0);
    Character* zasobnik=new Character(TP::ZASOBNIK,"Zasobnik",0,0,0,0,0,0);
    vector<Character*> enemies;vector<std::unique_ptr<NonLivingObject>> Obiekty;
    bool wybor=false,dlacase=false;Globalne Wydarzenie=GW::NONE;
    int wskazany=1;
    vector<Character*> affectedT;
    vector<DamageResult> dane;
    ScreenEfekt R;
    chrono::steady_clock::time_point CzasTrwania = std::chrono::steady_clock::now();
    Gamecontent Gc={S,debug,gracz,enemies,Obiekty,dzialko,zasobnik,x,wskazany,smigniecie,Wydarzenie,wybor,dlacase,affectedT,dane,R,kolejComm,CzasTrwania};
    gracz.dodajwyposazeniestartowe(Gc.S.L);
    nowyWrog(Gc,base_HP_wrog);
    ciagla_walka(Gc,Barka_status,CzyBylSklep);
    this_thread::sleep_for(chrono::seconds(1));
    int kodsmierci=rand()%(2-1+1)+1;
    if (kodsmierci==1)
        dzwiek_ciagly("Audio_RPG\\Demoman_response_fail.wav");
    else
        dzwiek_ciagly("Audio_RPG\\Demoman_response_fail2.wav");
    this_thread::sleep_for(chrono::milliseconds(10));
    Gc.Wydarzenie=GW::DEATH;
    screen(Gc);
    cout << "\n" << gracz.Imie << " zostal pokonany! Przegrales!" << endl;
    dzwiek_ciagly("Audio_RPG\\Demoman_response_death.wav");
    for (Character* wrog:enemies){
                delete wrog;
            }
    enemies.clear();
    delete dzialko;
    delete zasobnik;
    return 0;
}
