#include <windows.h>
#include <time.h>
#include <thread>
#include <iostream>
#include <conio.h>
#include "menu.h"
#include "SoundManagement.h"

using namespace std;
using TP = TypPostaci;
using Tx=TextID;
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
        cout<<"VERSION: INDEV 0.3.1"<<endl;
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
                if(temp.size()==miejsce||(temp.size()>=miejsce-4&&c==' ')||(temp.size()==tekst.size()&&temp.size())){tekst.erase(0,temp.size());break;}
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
