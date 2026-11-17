#include <iostream>
#include "labels.h"
using namespace std;
using TP=TypPostaci;
using Tx=TextID;
void tag_efektu(Gui &g,const string &napis,Kursor &k,int fg, int bg){
    g.naniesTekst(k,15,0,"|");
    g.naniesTekst(k,15,12,LFormat(napis,30));
    g.naniesTekst(k,15,0,"|\n");
}
const void wypiszEfekty(Gui &g,Kursor &k,int fg,int bg,const Character &postac)
{
    bool maefekty=false;
        for (const auto& efekt:postac.efekty) {
            if (efekt.aktywny==true){
                maefekty=true;
                switch (efekt.ID)
                {
                case OGLUSZENIE:{
                    tag_efektu(g,L.get(Tx::Eff_Stun),k,15,12);
                    break;}
                case UPICIE:{
                    tag_efektu(g,L.get(Tx::Eff_Drunk),k,3,12);
                    break;}
                case WZMOCNIENIE:{
                    tag_efektu(g,L.get(Tx::Eff_Powered),k,14,12);
                    break;}
                case ZATRUCIE:{
                    tag_efektu(g,L.get(Tx::Eff_Poisoned),k,10,12);
                    break;}
                case OSLABIENIE:{
                    tag_efektu(g,L.get(Tx::Eff_Weakness),k,13,12);
                    break;}
                case KRYTOWANIE:{
                    tag_efektu(g,L.get(Tx::Eff_MoreCritrate),k,11,12);
                    break;}
                }
        }
    }
    if (!maefekty){

        g.naniesTekst(k,fg,bg,"                            |\n");
    }
}
void pokazStatystyki(Gui &g,Kursor &k,const Character &postac,const string& etykieta) {
    if (!czyZyje(postac)) return;
    int rozmiar=4;
    if (postac.typ==TP::GRACZ||postac.typ==TP::NALADOWANY) rozmiar++;
    if(!postac.efekty.empty()) rozmiar+=postac.efekty.size();
    g.SetHeight(rozmiar);
    string granica_ramki="+"+string(30, (char)196)+"+\n";
    g.naniesTekst(k,15,0,granica_ramki);
    g.naniesTekst(k,15,0,"|");
    g.naniesTekst(k,15,12,LFormat(etykieta,10));
    g.naniesTekst(k,15,12,":");
    g.naniesTekst(k,15,12,PFormat(postac.Imie,18));
    g.naniesTekst(k,15,12," ");
    g.naniesTekst(k,15,0,"|\n");
    g.naniesTekst(k,15,0,"|");
    string zdrowie=" HP: "+string(1,(char)176);
    g.naniesTekst(k,15,12,zdrowie);
    g.naniesTekst(k,15,12,PFormat(to_string(postac.HP),5));
    g.naniesTekst(k,15,12,"/");
    g.naniesTekst(k,15,12,PFormat(to_string(postac.base_HP)+string(1,(char)176),5));
    g.naniesTekst(k,15,12," ");
    g.naniesTekst(k,7,12,"DEF: "+string(1,(char)176));
    g.naniesTekst(k,7,12,PFormat(to_string(postac.DEF)+string(1,(char)176),3));
    g.naniesTekst(k,15,12,"   ");
    g.naniesTekst(k,15,0,"| \n");
    if (postac.typ==TP::GRACZ){
        rozmiar++;
        g.SetHeight(rozmiar);
        g.naniesTekst(k,15,0,"|");
        g.naniesTekst(k,15,12," ");
        string specjalne=string(1,(char)176)+"SP: ";
        g.naniesTekst(k,14,12,specjalne);
        g.naniesTekst(k,14,12,PFormat(to_string(postac.SP)+string(1,(char)176),4));
        string dosw="| EXP: "+string(1,(char)176);
        g.naniesTekst(k,10,12,dosw);
        g.naniesTekst(k,10,12,PFormat(to_string(postac.EXP),9));
        g.naniesTekst(k,10,12,string(2,(char)176));
        g.naniesTekst(k,15,12," ");
        g.naniesTekst(k,15,0,"|\n");
    }
    else if(postac.typ==TP::NALADOWANY){
        rozmiar++;
        g.SetHeight(rozmiar);
        g.naniesTekst(k,15,0,"|");
        g.naniesTekst(k,15,12," ");
        string specjalne=string(1,(char)176)+"SP: ";
        g.naniesTekst(k,14,12,specjalne);
        g.naniesTekst(k,14,12,PFormat(to_string(postac.SP)+string(1,(char)176),4));
        g.naniesTekst(k,15,12,"                    ");
        g.naniesTekst(k,15,0,"|\n");
    }
    else if(postac.typ==TP::EXPLODER){

    }
    if (!postac.efekty.empty()){
        rozmiar+=postac.efekty.size();
        g.SetHeight(rozmiar);
        g.naniesTekst(k,15,0,"|");
        g.naniesTekst(k,15,12," "+L.get(Tx::Eff_info)+":                      ");
        g.naniesTekst(k,15,0,"|\n");
        wypiszEfekty(g,k,15,12,postac);
    }
    g.naniesTekst(k,15,0, granica_ramki);
    cout<<k.x<<";"<<k.x<<endl;
}
void ShowStatystyki(Gamecontent &Gc){
    Gui gui;
    Kursor k(0,0,0);
    if (Gc.Wydarzenie==Globalne::NONE||Gc.Wydarzenie==Globalne::FLASH){
        pokazStatystyki(gui,k,Gc.gracz,L.get(Tx::Tag_PLAYER));
        pokazStatystyki(gui,k,*Gc.dzialko,L.get(Tx::Tag_BUILD));
        pokazStatystyki(gui,k,*Gc.zasobnik,L.get(Tx::Tag_BUILD));
        k.tab(40,0);
        for (const auto &wrog:Gc.enemies){
            pokazStatystyki(gui,k,*wrog,L.get(Tx::Tag_ENEMY));
            k.tab(40,k.y);
        }
        gui.wyswietl();
    }
}
