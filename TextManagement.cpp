#include <iostream>
#include "TextManagement.h"
#include <string>
#include <vector>
using namespace std;
string LFormat(const string &tekst,size_t szer){
    if(tekst.size()>=szer) return tekst;
    else return tekst+string(szer-tekst.size(),' ');
}
string PFormat(const string &tekst,size_t szer){
    if(tekst.size()>=szer) return tekst;
    else return string(szer-tekst.size(),' ')+tekst;
}
void Dialog(string Nazwa, int kolor_fontu,int kolor_tla, string S){
    bool imiewypowiedziane=false;
    koloruj(kolor_fontu,kolor_tla);cout<<" "<<string(71,'_');koloruj (7,0);cout<<"\n";
        while (!S.empty()){
            string temp="";
            for (char &c:S){
            temp+=c;
            if (temp.size()==60||(temp.size()>=50&&c==' ')||(temp.size()==S.size())) {S.erase(0,temp.size()); break;}
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
    bool imiewypowiedziane=false;
    for (auto k:Kwestie){
        ile++;
        dzwiek(k.path);
        while (!k.S.empty()){
            string temp="";
            for (char c:k.S){
            temp+=c;
            if (temp.size()==65||(temp.size()>=55&&c==' ')||(temp.size()==k.S.size())) {k.S.erase(0,temp.size()); break;}
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
void tag_notyfikacji(const string &napis,int kolor_fontu,int kolor_tla){
    int miejsce=napis.size();
    koloruj(kolor_fontu,kolor_tla);cout<<char(201)<<string(miejsce+4,'=')<<char(187);koloruj(15,0);cout<<"\n";
    koloruj(kolor_fontu,4);cout<<"|  "<<napis<<"  |";koloruj(15,0);cout<<"\n";
    koloruj(kolor_fontu,4);cout<<char(200)<<string(miejsce+4,'=')<<char(188);koloruj(15,0);cout<<"\n";
}
