#include <iostream>
#include "Gamestuff.h"
#include <conio.h>
#include <time.h>
#include <thread>
#include <vector>
#include <cmath>
#include <windows.h>
using namespace std;
using TP=TypPostaci;
using TE=TypEfektu;
using Tx=TextID;
bool smigniecie=false;
bool kolejComm=false;
bool ogluszenie=false;//warunek ogluszenia
int czekaj=0; //kolejka ogluszen
//efekt upicia
short otrzezwienie=0;
void kiedy_efekt(Gamecontent &Gc,MultiDamageResult &ew, Character &source){
    bool bylCrit=false;
    for (const DamageResult &dr:ew.Eksplozja){
        if(!dr.cel) continue;
        if(dr.krytyczne){
            Gc.SE.R=ScreenEfekt::CRITICAL;
            Gc.CzasTrwania=std::ZaWarudo::steady_clock::now()+std::ZaWarudo::milliseconds(2000);
            bylCrit=true;
        }
        else{
            Gc.SE.R=ScreenEfekt::HIT;
            Gc.CzasTrwania=std::ZaWarudo::steady_clock::now()+std::ZaWarudo::milliseconds(1000);
        }
        if (find(Gc.affectedT.begin(),Gc.affectedT.end(),dr.cel)==Gc.affectedT.end()) {Gc.affectedT.push_back(dr.cel);}
        Gc.dane.push_back(dr);
        }
        if (Gc.affectedT.empty()||EverybodyDEAD_NOT_BIG_SUPRISE(Gc.affectedT)){
            narysujScene(Gc);
            if(bylCrit) source.skrytowanie();
        }
        else {screen(Gc);if(bylCrit) source.skrytowanie();}
    if(Gc.debug){cout<<endl<<endl;cout<<"Amount of affected enemies: "<<Gc.affectedT.size()<<endl;
    this_thread::sleep_for(ZaWarudo::seconds(2));}
    for (auto &dr:ew.Eksplozja){
        dr.cel=nullptr;
    }
    ew.Eksplozja.clear();
    aktualizuj_efekt(Gc);
}
string fitText(const std::string& text, std::size_t width)
{
    if (text.size() <= width) {
        return text + std::string(width - text.size(), ' ');
    }

    if (width <= 3) {
        return text.substr(0, width);
    }

    return text.substr(0, width - 3) + "...";
}
void tag_sklepu(const std::string& name,const std::string& valueLabel,int price,int value)
{
    // Width before the right-hand border character.
    constexpr std::size_t rowWidth = 76;
    // Change these values to adjust the layout.
    constexpr std::size_t nameWidth = 38;
    constexpr std::size_t gapWidth = 2;
    constexpr std::size_t priceWidth = 5;
    constexpr std::size_t valueLabelWidth = 12;
    constexpr std::size_t valueWidth = 4;
    constexpr std::size_t separatorWidth =
        2 + // "\\ "
        1 + // character 177
        1;  // character 176
    constexpr std::size_t usedWidth =
        nameWidth +
        gapWidth +
        priceWidth +
        separatorWidth +
        valueLabelWidth +
        valueWidth;
    static_assert(usedWidth <= rowWidth);

    const std::size_t trailingwidth = rowWidth - usedWidth;

    std::cout
        << fitText(name, nameWidth)
        << std::string(gapWidth, ' ')
        << std::setw(static_cast<int>(priceWidth))
        << std::right
        << price
        << "\\ "
        << static_cast<char>(177)
        << fitText(valueLabel, valueLabelWidth)
        << std::setw(static_cast<int>(valueWidth))
        << std::right
        << value
        << static_cast<char>(176)
        << std::string(trailingwidth, ' ');
        koloruj (15,0);cout<<char(186)<<endl;
}
void tagi_akcji(vector<string> Napisy){
    short numer=1;
    for (string &N:Napisy){
        cout<<"\\"<<numer<<"."<<N<<"\\"<<" ";
        numer++;
    }
    cout<<"             \n";
    for (string &N:Napisy){
        cout<<" ";uzyjUTF8(L'\u203E',N.size()+3);cout<<" ";
    }
    cout<<"                              "<<endl;
}
void panele(Gamecontent &Gc,Przedmiot &flashbang,Przedmiot &tel, Przedmiot &zatyczki)
{
    if (Gc.Wydarzenie==Globalne::SHOP)
    {
        Eyelander* miecz=Gc.gracz.znajdz<Eyelander>();
        WyrzutnikGranatow* SBLauncher=Gc.gracz.znajdz<WyrzutnikGranatow>();
        Shield* Sh=Gc.gracz.znajdz<Shield>();
        koloruj(15,4);
        for (int i=0;i<76;i++) cout<<(char)176;
        koloruj(15,0);cout<<(char)186<<endl;
        koloruj(15,0);
    for (int i=0;i<76;i++) cout<<(char)205;
    cout<<(char)185<<endl;
    koloruj(14,6);cout<<"EXP: "<<setw(5)<<Gc.gracz.EXP<<"                                                                  ";koloruj(15,0);cout<<(char)186<<endl;koloruj(15,0);

        koloruj(3,1);tag_sklepu(Gc.S.L.get(Tx::Shop_Sh),Gc.S.L.get(Tx::Level_info),Sh->cena,Sh->LVL);koloruj(15,0);
        koloruj(8,15);tag_sklepu(Gc.S.L.get(Tx::Shop_SBL),Gc.S.L.get(Tx::Level_info),SBLauncher->cena,SBLauncher->LVL);koloruj(15,0);
        koloruj(4,7);tag_sklepu(Gc.S.L.get(Tx::Shop_Sw),Gc.S.L.get(Tx::Level_info),miecz->cena,miecz->LVL);koloruj(15,0);
        koloruj(11,2);tag_sklepu(Gc.S.L.get(Tx::Shop_Fl),Gc.S.L.get(Tx::Quantity_info),flashbang.cena,flashbang.quant);koloruj(15,0);
        koloruj(9,0);tag_sklepu(Gc.S.L.get(Tx::Shop_Phone),Gc.S.L.get(Tx::Quantity_info),tel.cena,tel.quant);koloruj(15,0);
        if (Gc.x>=15) tag_sklepu(Gc.S.L.get(Tx::Shop_Ear),Gc.S.L.get(Tx::Quantity_info),zatyczki.cena,zatyczki.quant);

    cout<<string(76,(char)205)<<(char)188<<endl;
    cout<<endl;
    cout<<Gc.S.L.get(Tx::X_for_continue2)<<endl;
    cout<<endl;
    }
    else
    {
        for (const auto& efekt:Gc.gracz.efekty){
            if (efekt.ID==1&&efekt.aktywny==true) return;
        }
        cout<<endl;
        cout<<string(64,char(196))<<endl;

    tagi_akcji({Gc.S.L.get(Tx::Action_info_offensive),Gc.S.L.get(Tx::Action_info_support),Gc.S.L.get(Tx::Action_info_equipment)});
    }
}
void ofensywa_wybrana(Gamecontent &Gc)
{
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
    cout<<"                                                             \n";
    cout<<"                                                             \n";
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
        tagi_akcji({Gc.S.L.get(Tx::Demo_actions_offensive_Sword),Gc.S.L.get(Tx::Demo_actions_offensive_SBL),Gc.S.L.get(Tx::Demo_actions_offensive_specialAttack)});
}
void wsparcie_wybrane(Gamecontent &Gc)
{
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
    cout<<"                                                             \n";
    cout<<"                                                             \n";
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
    tagi_akcji({Gc.S.L.get(Tx::Demo_actions_support_Scrumpy),Gc.S.L.get(Tx::Demo_actions_support_Shield)});
}
void przedmioty_wybrane(Gamecontent &Gc, const Przedmiot &flashbang,const Przedmiot &tel,const Przedmiot &zatyczki)
{
    narysujScene(Gc);
    cout<<endl;
    cout<<string(64,char(196))<<endl;
    //wyswietlanie ekwipunku
    cout<<"\\1. "<<flashbang.nazwa<<"("<<Gc.S.L.get(Tx::Quantity)<<": " <<flashbang.quant<< ")\\                                          "<<endl;
    if (tel.quant!=0)
        cout<<"\\2. "<<tel.nazwa<<" ("<<Gc.S.L.get(Tx::Cost_info)<<"5 SP)\\"<<endl;
    if (zatyczki.quant!=0)
        cout<<zatyczki.nazwa<<" (PASSIVE)"<<endl;
    cout<<Gc.S.L.get(Tx::X_for_exit)<<"                                         \n";
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
    Gc.wybor=true;
    bool validchoice3=false;
    int proby = Gc.enemies.size();
    while (proby-- > 0&&(!czyZyje(Gc.enemies[Gc.wskazany-1]))) {
        Gc.wskazany++;
        if (Gc.wskazany>Gc.enemies.size()) Gc.wskazany = 1;
    }
    if(EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)){
            dzwiek("Audio_RPG\\Kiedy_wszyscy_martwi_w_target.wav");
            cerr<<Gc.S.L.get(Tx::EachAndEveryoneWillBeSentHomeToYourMommaInABox)<<endl;
            this_thread::sleep_for(ZaWarudo::seconds(3));
        }
        while (validchoice3==false)
        {
            dzwiek("Audio_RPG\\menu_choosing.wav");
            narysujScene(Gc);
            cout<<endl;
            cout<<string(64,char(196))<<endl;
            cout<<Gc.S.L.get(Tx::Tag_direction_Info)<<endl;
            for (size_t i = 0; i < Gc.enemies.size(); ++i) {
                if (Gc.enemies[i]&&Gc.enemies[i]->HP > 0) {
                    if ((int)i+1==Gc.wskazany) {
                        koloruj(0,7);
                    }
                    cout << "\\" << i + 1 << ". " << Gc.enemies[i]->Imie << "\\                         \n";
                    koloruj(7,0);
                }
            }
            cout<<"DEBUG:   wskazany="<<Gc.wskazany<<"      liczba wrogow="<<Gc.enemies.size();
            cel=_getch();
                switch (cel)
                {
                case 'w':
                    do{
                    Gc.wskazany--;
                    if (Gc.wskazany<1) Gc.wskazany=Gc.enemies.size();
                    }while (!czyZyje(Gc.enemies[Gc.wskazany-1]));
                    break;
                case 's':
                    do{
                        Gc.wskazany++;
                        if (Gc.wskazany>Gc.enemies.size()) Gc.wskazany=1;
                    }while (!czyZyje(Gc.enemies[Gc.wskazany-1]));
                    break;
                case 13:
                        validchoice3=true;
                        break;
                }
        }
        Gc.wybor=false;
        screen(Gc);
        return Gc.wskazany;
}
void sklep_input(Gamecontent &Gc,Przedmiot &flashbang,Przedmiot &tel,Przedmiot &zatyczki)
{
    Shield* Sh=Gc.gracz.znajdz<Shield>();
    WyrzutnikGranatow* SBLauncher=Gc.gracz.znajdz<WyrzutnikGranatow>();
    Eyelander* miecz=Gc.gracz.znajdz<Eyelander>();
    if(!Sh||!SBLauncher||!miecz){
        cerr<<Gc.S.L.get(Tx::Error_info)<<endl;
        exit(0);
    }
    char choice2;
    bool validchoice2=false;
    while(validchoice2==false)
    {
        choice2=_getch();
        wyczyscBufor();
        switch (choice2)
        {
        case '1': //upgrade tarczy
            {   screen(Gc);
                panele(Gc,flashbang,tel,zatyczki);
            if (Gc.gracz.EXP<Sh->cena) { koloruj (12,0);
                cout<<Gc.S.L.get(Tx::Error_noFunds)<<endl;
                koloruj (15,0);
            }
            else if(Sh->LVL>3)//odpowiednia ilosc exp
            { //limit
                koloruj (12,0);
                cout<<Gc.S.L.get(Tx::Error_maxLevel)<<endl;
                koloruj(15,0);
            }
            else
            {
                koloruj (10,0);
                cout<<Gc.S.L.get(Tx::Bought_Item)<<"upgrade to "<<Sh->nazwa<<endl;
                koloruj (15,0);
                Gc.gracz.EXP-=Sh->cena;
                Sh->cena*=3.2;
                Sh->ulepsz();
                this_thread::sleep_for(ZaWarudo::seconds(1));
                screen(Gc);
                panele(Gc,flashbang,tel,zatyczki);
                validchoice2=true;
            }
            break;}
        case '2': //upgrade wyrzutnika
            {   screen(Gc);
                panele(Gc,flashbang,tel,zatyczki);
                if(Gc.gracz.EXP<SBLauncher->cena) { koloruj (12,0);
                        cout<<Gc.S.L.get(Tx::Error_noFunds)<<endl;
                        koloruj (15,0);
                }
                else
                {
                    koloruj (10,0);
                    cout<<Gc.S.L.get(Tx::Bought_Item)<<"upgrade to "<<SBLauncher->nazwa<<endl;
                    koloruj (15,0);
                    Gc.gracz.EXP-=SBLauncher->cena;
                    SBLauncher->cena*=3;
                    SBLauncher->ulepsz();
                    this_thread::sleep_for(ZaWarudo::seconds(1));
                    screen(Gc);
                    panele(Gc,flashbang,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '3': //upgrade miecza
            {   screen(Gc);
                panele(Gc,flashbang,tel,zatyczki);
                if(Gc.gracz.EXP<miecz->cena) { koloruj (12,0);
                        cout<<Gc.S.L.get(Tx::Error_noFunds)<<endl;
                        koloruj (15,0);
                }
                else
                {
                    koloruj (10,0);
                    cout<<Gc.S.L.get(Tx::Bought_Item)<<"upgrade to "<<miecz->nazwa<<endl;
                    koloruj (15,0);
                    Gc.gracz.EXP-=miecz->cena;
                    miecz->cena*=2.5;
                    miecz->ulepsz();
                    this_thread::sleep_for(ZaWarudo::seconds(1));
                    screen(Gc);
                    panele(Gc,flashbang,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '4': //kupno przedmiotu
            {
                screen(Gc);
                panele(Gc,flashbang,tel,zatyczki);
                if(Gc.gracz.EXP<flashbang.cena) { koloruj (12,0);
                        cout<<Gc.S.L.get(Tx::Error_noFunds)<<endl;
                        koloruj (15,0);
                }
                else
                {
                    koloruj (10,0);
                    cout<<Gc.S.L.get(Tx::Bought_Item)<<flashbang.nazwa<<endl;
                    koloruj (15,0);
                    Gc.gracz.EXP-=flashbang.cena;
                    flashbang.cena+=25;
                    flashbang.quant++;
                    this_thread::sleep_for(ZaWarudo::seconds(1));
                    screen(Gc);
                    panele(Gc,flashbang,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '5': //kupno telefonu
            {
                screen(Gc);
                panele(Gc,flashbang,tel,zatyczki);
                if(Gc.gracz.EXP<tel.cena) { koloruj (12,0);
                        cout<<Gc.S.L.get(Tx::Error_noFunds)<<endl;
                        koloruj (15,0);
                }
                else if(tel.quant!=0) {koloruj (12,0);
                cout<<Gc.S.L.get(Tx::Error_AlreadyHaveIt)<<endl;
                koloruj (15,0);}
                else
                {
                    koloruj (10,0);
                    cout<<Gc.S.L.get(Tx::Bought_Item)<<tel.nazwa<<endl;
                    koloruj (15,0);
                    Gc.gracz.EXP-=tel.cena;
                    tel.quant++;
                    this_thread::sleep_for(ZaWarudo::seconds(1));
                    screen(Gc);
                    panele(Gc,flashbang,tel,zatyczki);
                    validchoice2=true;
                }
            break;}
        case '6': //kupno zatyczek
            {
                if (Gc.x<15) cout<<Gc.S.L.get(Tx::Error_nope_tf2reference);
                else{
                    screen(Gc);
                    panele(Gc,flashbang,tel,zatyczki);
                    if(Gc.gracz.EXP<zatyczki.cena) { koloruj (12,0);
                        cout<<Gc.S.L.get(Tx::Error_noFunds)<<endl;
                        koloruj (15,0);
                }
                    else if(zatyczki.quant!=0) {koloruj (12,0);
                    cout<<Gc.S.L.get(Tx::Error_AlreadyHaveIt)<<endl;
                    koloruj (15,0);}
                    else{
                        koloruj (10,0);
                        cout<<Gc.S.L.get(Tx::Bought_Item)<<zatyczki.nazwa<<endl;
                        koloruj (15,0);
                        Gc.gracz.EXP-=zatyczki.cena;
                        zatyczki.quant++;
                        this_thread::sleep_for(ZaWarudo::seconds(1));
                        screen(Gc);
                        panele(Gc,flashbang,tel,zatyczki);
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
                cout<<Gc.S.L.get(Tx::DoYouWantToQuit)<<endl;
                koloruj(7,0);
                choice2=_getch();
                wyczyscBufor();
                if(choice2=='y')
                {
                    dzwiek("Audio_RPG\\menu_selecting.wav");
                Gc.Wydarzenie=Globalne::NONE;
                validchoice2=true;
                continue;
                }
                else if(choice2=='n')
                {
                    dzwiek("Audio_RPG\\menu_selecting.wav");
                    screen(Gc);
                    panele(Gc,flashbang,tel,zatyczki);
                    dzwiek_loop("Audio_RPG\\Upgradestation_loop.wav");
                    validchoice2=true;
                }
                else cout<<Gc.S.L.get(Tx::Error_nope_tf2reference);
                }while (choice2!='y'&&choice2!='n');
                break;
            }
        default:
            cout<<Gc.S.L.get(Tx::Error_nope_tf2reference);
            wyczyscBufor();
            break;
        }
    }
}
Character* dajCel(size_t numer,const vector<Character*>& enemies) {
    if(numer>=1&&numer<=enemies.size()){
        return enemies[numer-1];
    }
    return nullptr;
}

void Input(short &Barka_status,Gamecontent &Gc,Przedmiot &flashbang,Przedmiot &tel,Przedmiot & zatyczki)
{
    Klawisz choice(' ',NOTARROW);
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
                cout<<Gc.gracz.Imie<<Gc.S.L.get(Tx::Obj_IsStunned)<<endl;
                cout<<Gc.S.L.get(Tx::TurnsRemaining)<<efekt.duration<<endl;
                koloruj(7,0);
                oglus=true;
                this_thread::sleep_for(ZaWarudo::seconds(3));
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
        aktualizuj_efekt(Gc);
        this_thread::sleep_for(ZaWarudo::milliseconds(250));
        if (_kbhit()){
        choice.PressK();
            switch(choice.znak)
            {
            case '1':{
                dzwiek("Audio_RPG\\menu_selecting.wav");
                ofensywa_wybrana(Gc);
                bool ofensywaDone = false;
                while(!ofensywaDone){
                    this_thread::sleep_for(ZaWarudo::milliseconds(250));
                    aktualizuj_efekt(Gc);
                    if(_kbhit()){
                        choice.PressK();
                        switch (choice.znak)
                        {
                        case '1':{ //kiedy '1'
                            Eyelander* miecz=Gc.gracz.znajdz<Eyelander>();
                            if(!miecz){
                                cerr<<Gc.S.L.get(Tx::Error_noItem)<<endl;
                            }
                            else{
                                int celataku=target(Gc);
                                Character* cel=dajCel(celataku,Gc.enemies);
                                if (!cel) {
                                    cerr << Gc.S.L.get(Tx::Error_targetnotvalid) << endl;
                                    break;
                                }
                                AkcjaMiecz(Gc,cel,miecz);
                                ofensywaDone=true;
                                validchoice=true;
                            }
                            break;}

                        case '2':{
                            WyrzutnikGranatow* SBLauncher=Gc.gracz.znajdz<WyrzutnikGranatow>();
                            if(!SBLauncher){
                                cerr<<Gc.S.L.get(Tx::Error_noItem)<<endl;
                            }
                            else{
                                int celataku=target(Gc);
                                Character* cel=dajCel(celataku,Gc.enemies);
                                if (!cel) {
                                    cerr << Gc.S.L.get(Tx::Error_targetnotvalid) << endl;
                                    break;
                                }
                                AkcjaGranatySamoprzylepne(Gc,cel,SBLauncher);
                                ofensywaDone=true;
                                validchoice=true;
                            }
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
                                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_Caber1));
                                    dzwiek_ciagly("Audio_RPG\\Demoman_response_grozba2.wav");
                                    break;
                                case 1:
                                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_Caber2));
                                    dzwiek_ciagly("Audio_RPG\\Demoman_response_grozba.wav");
                                    break;
                                default:
                                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_Caber3));
                                    dzwiek_ciagly("Audio_RPG\\Demoman_response_cross.wav");
                                    break;
                                }
                                Gc.gracz.ObecnaAkcja=AK::SPECIAL;
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
                                this_thread::sleep_for(ZaWarudo::seconds(3));
                                for (Character* wrog:Gc.enemies)
                                    wrog->HP=0;
                               Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                                dzwiek("Audio_RPG\\wiwat_uderzenie.wav");
                                system("cls");
                                if (czyZyje(Gc.dzialko)){
                                    Gc.dzialko->HP=0;
                                    Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                                    screen(Gc);
                                    koloruj(11,8);
                                    cout<<"BOOOOOOOOOOOOOOM!!!"<<endl<<endl;
                                    cout<<Gc.S.L.get(Tx::Caber_SDestroyed)<<endl;
                                }
                                else if (czyZyje(Gc.zasobnik)){
                                    Gc.zasobnik->HP=0;
                                    Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                                    screen(Gc);
                                    koloruj(11,8);
                                    cout<<"BOOOOOOOOOOOOOOM!!!"<<endl<<endl;
                                    cout<<Gc.S.L.get(Tx::Caber_DDestroyed)<<endl;
                                }
                                else{
                                screen(Gc);
                                koloruj(11,8);
                                Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                                cout<<"BOOOOOOOOOOOOOOM!!!"<<endl;}
                                cout<<"\n"<<Gc.gracz.Imie<<Gc.S.L.get(Tx::Caber_result)<<endl;
                                koloruj(7,0);

                                if (pijany==true){
                                    koloruj(11,8);
                                    cout<<Gc.S.L.get(Tx::Caber_UnTouched)<<endl;
                                }
                                else
                                {
                                    Gc.gracz.dodajefekt(OGLUSZENIE,2,Gc.gracz);
                                    koloruj(15,8);
                                    cout<<Gc.S.L.get(Tx::Caber_Touched)<<endl;
                                }
                            koloruj(7,0);
                            this_thread::sleep_for(ZaWarudo::seconds(5));
                            screen(Gc);
                            Gc.dlacase=true;
                            this_thread::sleep_for(ZaWarudo::seconds(1));
                            ofensywaDone=true;
                            validchoice=true;
                            }
                            else cout<<Gc.S.L.get(Tx::Error_noSP)<<endl;
                        }
                        default:{
                            cout<<Gc.S.L.get(Tx::Error_nope_tf2reference)<<endl;
                            break;}
                        }
                    }
                }
            }break;
            case '2': //kiedy '2'
            {
                dzwiek("Audio_RPG\\menu_selecting.wav");
                wsparcie_wybrane(Gc);
                bool wsparcieDone=false;
                while (!wsparcieDone){
                    this_thread::sleep_for(ZaWarudo::milliseconds(250));
                    aktualizuj_efekt(Gc);
                    if(_kbhit()){
                    choice.PressK();
                    switch(choice.znak)
                    {
                    case '1':{
                        Scrumpy* trunek=Gc.gracz.znajdz<Scrumpy>();
                        if(!trunek){
                            cerr<<Gc.S.L.get(Tx::Error_noItem)<<endl;
                        }
                        else{
                        dzwiek("Audio_RPG\\menu_selecting.wav");
                        AkcjaGorzalka(Gc,trunek);
                        wsparcieDone=true;
                        validchoice=true;
                        }
                        break;}
                        case '2':{
                            Shield* Sh=Gc.gracz.znajdz<Shield>();
                            if(!Sh){
                                cerr<<Gc.S.L.get(Tx::Error_noItem)<<endl;
                            }
                            else{
                            dzwiek("Audio_RPG\\menu_selecting.wav");
                            AkcjaTarcza(Gc,Sh);
                            wsparcieDone=true;
                            validchoice=true;
                            }
                            break;}
                    default:{
                        cout<<Gc.S.L.get(Tx::Error_nope_tf2reference)<<endl;
                        break;}
                    }
                    }
                }
            }break;
            case '3':
            {
            aktualizuj_efekt(Gc);
            AkcjaEkwipunek(Gc,validchoice);
            break;}
            default:{ // gdy inny klawisz
                break;}
        }
        wyczyscBufor();}
    }
}
void DzialTURN(Gamecontent &Gc)
{
    aktualizuj_efekt(Gc);
    bool ogl=false;
    if (Gc.dzialko->HP>0)
    {
        koloruj(11,8);
        cout<<Gc.dzialko->Imie<<Gc.S.L.get(Tx::Turn_info)<<endl<<endl;
        koloruj(7,0);
        this_thread::sleep_for(ZaWarudo::seconds(2));
        for (const auto &efekt:Gc.dzialko->efekty){
            if (efekt.aktywny==true)
            {
                switch(efekt.ID){
                case OGLUSZENIE:
                    koloruj(11,8);
                    cout<<Gc.dzialko->Imie<<Gc.S.L.get(Tx::Obj_IsDeactivated)<<endl;
                    cout<<Gc.S.L.get(Tx::TurnsRemaining)<<efekt.duration<<endl;
                    this_thread::sleep_for(ZaWarudo::seconds(2));
                    ogl=true;
                    screen(Gc);
                    break;
                default:break;
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
            cout<<Gc.dzialko->Imie<<Gc.S.L.get(Tx::Defeat_info)<<cel->Imie<<"!"<<endl;
            koloruj(7,0);
        }
        dzwiek_ciagly("Audio_RPG\\sentry_shoot.wav");
        this_thread::sleep_for(ZaWarudo::seconds(1));
    }
}
void ZasobTURN(Gamecontent &Gc)
{
    aktualizuj_efekt(Gc);
    bool ogl=false;
    if (czyZyje(Gc.zasobnik))
    {
        cout<<Gc.zasobnik->Imie<<Gc.S.L.get(Tx::Turn_info)<<"                          "<<endl<<endl;
        this_thread::sleep_for(ZaWarudo::seconds(2));
        for (const auto &efekt:Gc.zasobnik->efekty){
            if (efekt.aktywny==true)
            {
                switch (efekt.ID){
                case OGLUSZENIE:
                    koloruj(15,8);
                    cout<<Gc.zasobnik->Imie<<Gc.S.L.get(Tx::Obj_IsDeactivated)<<endl;
                    cout<<Gc.S.L.get(Tx::TurnsRemaining)<<efekt.duration<<endl;
                    this_thread::sleep_for(ZaWarudo::seconds(2));
                    ogl=true;
                    aktualizuj_efekt(Gc);
                    screen(Gc);
                    break;
                default: break;
                }
            }
        }
        if (ogl==true) return;
        dzwiek("Audio_RPG\\zasobnik_heal.wav");
        Gc.zasobnik->heal(Gc.gracz,Gc.zasobnik->ATK);
        screen(Gc);
        koloruj(11,8);
        cout<<Gc.S.L.get(Tx::Dispenser_heal)<<Gc.zasobnik->Imie<<"!\n";
        koloruj(7,0);
        this_thread::sleep_for(ZaWarudo::seconds(2));
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
                cout<< Leader->Imie<<Gc.S.L.get(Tx::Comm_Crits)<<endl;
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
                DamageResult wl=Leader->damage(Gc.gracz,Leader->ATK,CritMode::RANDOM);
                MultiDamageResult TempMDR=nowyMDR({wl});
                kiedy_efekt(Gc,TempMDR,*Leader);
                if(!wl.bitesthedust){
                    Gc.gracz.PainReact();
                }

            }
        }
        else{
                dzwiek("Audio_RPG\\Commander_order.wav");
                Dialog(Leader->Imie,0,10,Gc.S.L.get(Tx::Comm_response_regroup));
                this_thread::sleep_for(ZaWarudo::seconds(2));
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
void NaLZomTURN(Gamecontent &Gc,Character* energ)
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
        default:break;
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
        energ->ObecnaAkcja=AK::ACTION2;
        narysujScene(Gc);
        koloruj(12,14);cout<<endl;
        cout<<energ->Imie<<Gc.S.L.get(Tx::Elec_StrengthCast);koloruj(7,0);cout<<"\n";
        dzwiek("Audio_RPG\\elektrycznosc1.wav");
        this_thread::sleep_for(ZaWarudo::seconds(3));
        for (Character* wrog:Gc.enemies){
                wrog->dodajefekt(WZMOCNIENIE,3,*wrog);
        }
        energ->SP+=Gc.enemies.size();
        energ->ObecnaAkcja=AK::NO_ACTION;
        screen(Gc);
        koloruj(1,14);
        cout<<Gc.S.L.get(Tx::Obj_IsPowered);koloruj(7,0);cout<<"\n";
    }
    else if(typatak==1&&energ->SP>=10&&!(ogl)){
        energ->SP-=10;
        energ->ObecnaAkcja=AK::SPECIAL;
        screen(Gc);
        koloruj(12,14);
        cout<<energ->Imie<<Gc.S.L.get(Tx::Elec_Overdrive);koloruj(7,0);cout<<"\n";
        dzwiek("Audio_RPG\\elektrycznosc_shockwave.wav");
        this_thread::sleep_for(ZaWarudo::seconds(2));
        energ->ObecnaAkcja=AK::NO_ACTION;
        if(czyZyje(Gc.dzialko)) {
            Gc.dzialko->dodajefekt(OGLUSZENIE,2,*Gc.dzialko);
            screen(Gc);
            koloruj(15,8);
            cout<<Gc.dzialko->Imie<<Gc.S.L.get(Tx::Obj_StoppedWorking)<<endl;
            dzwiek_ciagly("Audio_RPG\\wylaczanko.wav");
            this_thread::sleep_for(ZaWarudo::seconds(1));
        }
        else if(czyZyje(Gc.zasobnik)) {
            Gc.zasobnik->dodajefekt(OGLUSZENIE,2,*Gc.zasobnik);
            screen(Gc);
            koloruj(15,8);
            cout<<Gc.zasobnik->Imie<<Gc.S.L.get(Tx::Obj_StoppedWorking)<<"\n";
            dzwiek_ciagly("Audio_RPG\\wylaczanko.wav");
            this_thread::sleep_for(ZaWarudo::seconds(1));
        }
        else narysujScene(Gc);
            if (graczpijany==true)
            {
                cout<<endl;
                koloruj(8,0);
                cout<<Gc.gracz.Imie<<Gc.S.L.get(Tx::Obj_NoSuffer)<<endl;
               koloruj(7,0);
                this_thread::sleep_for(ZaWarudo::seconds(3));
            }
            else{
                Gc.gracz.dodajefekt(OGLUSZENIE,2,Gc.gracz);
                DamageResult O=energ->damage(Gc.gracz,energ->ATK*2,CritMode::RANDOM);
                MultiDamageResult TempMDR=nowyMDR({O});
                kiedy_efekt(Gc,TempMDR,*energ);
                koloruj(12,8);
                cout<<Gc.S.L.get(Tx::Obj_SufferedStrongAttack)<<Gc.gracz.Imie<<endl;
                cout<<Gc.gracz.Imie<<Gc.S.L.get(Tx::Obj_IsStunned)<<endl;
                cout<<Gc.S.L.get(Tx::TurnsRemaining)<<1<<endl;
                koloruj(7,0);
                this_thread::sleep_for(ZaWarudo::seconds(3));
            }
        }

    else {
        energ->ObecnaAkcja=AK::ACTION1;
        narysujScene(Gc);
        koloruj(12,14);
         cout<<energ->Imie<<Gc.S.L.get(Tx::Elec_Attack)<<endl;
        koloruj(7,0);
        dzwiek_ciagly("Audio_RPG\\elektrycznosc2.wav");
        energ->ObecnaAkcja=AK::NO_ACTION;
        if (czy_pudlo(energ->missrate)){
            energ->spudlowanie();
            screen(Gc);
            return;
        }
        DamageResult w=energ->damage(Gc.gracz,energ->ATK,CritMode::RANDOM);
        MultiDamageResult TempMDR=nowyMDR({w});
        kiedy_efekt(Gc,TempMDR,*energ);
        if (czyZyje(Gc.dzialko)){
                DamageResult w_dzial=energ->damage(*Gc.dzialko,energ->ATK*2,CritMode::RANDOM);
                MultiDamageResult TempMDR=nowyMDR({w_dzial});
                kiedy_efekt(Gc,TempMDR,*energ);
                if (!w_dzial.bitesthedust&&czyZyje(Gc.dzialko))
                {
                    dzwiek("Audio_RPG\\Demo_build_ouch.wav");
                }
                else{
                    dzwiek("Audio_RPG\\Demo_ouch_buildDestroyed.wav");
                    screen(Gc);
                    koloruj(11,8);
                    cout<<energ->Imie<<Gc.S.L.get(Tx::Obj_Destroyed)<<Gc.dzialko->Imie<<"!!!\n";
                    koloruj(7,0);
                    this_thread::sleep_for(ZaWarudo::seconds(3));
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
                DamageResult w_zas=energ->damage(*Gc.zasobnik,energ->ATK*3,CritMode::RANDOM);
                MultiDamageResult TempMDR=nowyMDR({w_zas});
                kiedy_efekt(Gc,TempMDR,*energ);
                if (!w_zas.bitesthedust&&czyZyje(Gc.zasobnik))
                {
                    dzwiek("Audio_RPG\\Demo_build_ouch.wav");
                }
                else{
                    dzwiek("Audio_RPG\\Demo_ouch_buildDestroyed.wav");
                    screen(Gc);
                    koloruj(11,8);
                    cout<<energ->Imie<<Gc.S.L.get(Tx::Obj_Destroyed)<<Gc.zasobnik->Imie<<"!!!\n";
                    koloruj (7,0);
                    this_thread::sleep_for(ZaWarudo::seconds(3));
                }
            }
        }
        else dzwiek("Audio_RPG\\Demoman_response_painsharp01.wav");
        energ->SP+=2;

    }
    energ->ObecnaAkcja=AK::NO_ACTION;
    screen(Gc);
}
void BombyTurn(Gamecontent &Gc,Character* Expld)
{
    Expld->odliczanie--;
    if (Expld->odliczanie!=0&&Expld->odliczanie>=0)
    {
        dzwiek("Audio_RPG\\Det_pack_timer.wav");
        string tekst="";
        tekst+=Gc.S.L.get(Tx::Expl_Warning1);
        tekst+=to_string(Expld->odliczanie);
        tekst+=Gc.S.L.get(Tx::Expl_Warning2);
        tag_notyfikacji(tekst,0,4);
        this_thread::sleep_for(ZaWarudo::seconds(3));
        screen(Gc);
    }
    else{
       tag_notyfikacji(Gc.S.L.get(Tx::Expl_WarningFatal),0,4);
        dzwiek("Audio_RPG\\zaplon_instant_kill.wav");
        if (czy_pudlo(Expld->missrate)){
                Expld->spudlowanie();
                Expld->HP=0;
                    screen(Gc);
                    return;
                }
        this_thread::sleep_for(ZaWarudo::milliseconds(3500));
        Gc.gracz.HP=0;
        Expld->HP=0;
        Gc.dzialko->HP=0;
        Gc.zasobnik->HP=0;
        Expld->ObecnaAkcja=AK::SPECIAL;
        screen(Gc);
        this_thread::sleep_for(ZaWarudo::milliseconds(2500));
    }
}
void ToxZomTURN(Gamecontent &Gc,Character* ToxicZombie,const Przedmiot &zatyczki)
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
                default:break;
            }
        }
    }
        if (typataku>2&&!madepresje)
        {
            unsigned short typobrazy=Los(8,0);
            switch (typobrazy)
            {
            case 0:{
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMFAT),3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM1),5400,"Audio_RPG\\yo_mama_joke01.wav"}});
                break;}
            case 1:{
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMFAT),3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM2),6000,"Audio_RPG\\yo_mama_joke02.wav"}});
                break;}
            case 2:{
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMFAT),3000,"Audio_RPG\\yo_mama_fat.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM3),6500,"Audio_RPG\\yo_mama_joke03.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM3_1),5500,"Audio_RPG\\yo_mama_joke03_1.wav"}});
                break;}
            case 3:
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMUGLY),3000,"Audio_RPG\\yo_mama_ugly.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM4),7000,"Audio_RPG\\yo_mama_joke04_1.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM4_1),4000,"Audio_RPG\\yo_mama_joke04_2.wav"}});
                break;
            case 4:
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMFAT),3000,"Audio_RPG\\yo_mama_fat2.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM5),6000,"Audio_RPG\\yo_mama_joke05.wav"}});
                break;
            case 5:
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMSTUPID),3000,"Audio_RPG\\yo_mama_stupid2.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM6),4000,"Audio_RPG\\yo_mama_joke06.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM6_1),5000,"Audio_RPG\\yo_mama_joke06_1.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM6_2),3000,"Audio_RPG\\yo_mama_joke06_2.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM6_3),7800,"Audio_RPG\\yo_mama_joke06_3.wav"}});
                break;
            case 6:
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMSTUPID),3000,"Audio_RPG\\yo_mama_stupid.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM7),4800,"Audio_RPG\\yo_mama_joke07.wav"}});
                break;
            case 7:
                AdvDialog(ToxicZombie->Imie,10,8,{
                        {Gc.S.L.get(Tx::Toxic_YOMUMSTUPID),3000,"Audio_RPG\\yo_mama_stupid2.wav"},
                        {Gc.S.L.get(Tx::Toxic_YOMUM8),4000,"Audio_RPG\\yo_mama_joke08.wav"}});
                break;
            default:
                AdvDialog(ToxicZombie->Imie,10,8,{
                          {Gc.S.L.get(Tx::Toxic_YOMUMDEFAULT1),4000,"Audio_RPG\\yo_mama_joke_default.wav"},
                          {Gc.S.L.get(Tx::Toxic_YOMUMDEFAULT2),5000,"Audio_RPG\\yo_mama_joke_default2.wav"}});
                break;
            }
            if (zatyczki.quant>0){
                koloruj (7,8);
                cout<<Gc.gracz.Imie<<Gc.S.L.get(Tx::FailedOffend)<<endl;
                this_thread::sleep_for(ZaWarudo::seconds(3));
            }
            else{
            screen(Gc);
            dzwiek("Audio_RPG\\Demo_krytyczny_cios_psychiczny.wav");
            koloruj (14,13);
            cout<<Gc.gracz.Imie<<Gc.S.L.get(Tx::SucceededOffend)<<endl;
            koloruj (7,0);
            Gc.gracz.dodajefekt(OSLABIENIE,3,Gc.gracz);
            this_thread::sleep_for(ZaWarudo::seconds(3));
            dzwiek_ciagly("Audio_RPG\\Demoman_response_smutek.wav");
            screen(Gc);
            }
        }
        else{
            ToxicZombie->ObecnaAkcja=AK::ACTION1;
            narysujScene(Gc);
            dzwiek("Audio_RPG\\rzyg.wav");
            koloruj(11,8);
            cout<<ToxicZombie->Imie<<Gc.S.L.get(Tx::Toxic_Spit)<<Gc.gracz.Imie<< "!                 "<<endl;
            koloruj(7,0);
            this_thread::sleep_for(ZaWarudo::seconds(3));
            ToxicZombie->ObecnaAkcja=AK::NO_ACTION;
            if (czy_pudlo(ToxicZombie->missrate)){
                    ToxicZombie->spudlowanie();
                    screen(Gc);
                    return;
                }
            DamageResult w=ToxicZombie->damage(Gc.gracz,ToxicZombie->ATK,CritMode::RANDOM);
            MultiDamageResult TempMDR=nowyMDR({w});
            kiedy_efekt(Gc,TempMDR,*ToxicZombie);
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
            screen(Gc);
                this_thread::sleep_for(ZaWarudo::seconds(1));
                if (Los(100,0)<70){
                    narysujScene(Gc);
                        if(zatruty==false) {
                            Gc.gracz.dodajefekt(ZATRUCIE,3,Gc.gracz);
                            dzwiek("Audio_RPG\\Demoman_response_hssss.wav");
                            koloruj(10,1);
                            cout<<Gc.S.L.get(Tx::Toxic_PoisonSuccess)<<endl;
                            koloruj(7,0);
                        }
                        else{
                            koloruj(7,8);
                            cout<<Gc.gracz.Imie<<Gc.S.L.get(Tx::Toxic_PoisonFails)<<endl;
                        koloruj(7,0);
                        }
                    this_thread::sleep_for(ZaWarudo::seconds(2));
                    screen(Gc);
                }
            }
        else{
                Gc.gracz.PainReact();
                this_thread::sleep_for(ZaWarudo::seconds(1));
            narysujScene(Gc);}
        }
    ToxicZombie->ObecnaAkcja=AK::NO_ACTION;
}
void ZomTURN(Gamecontent &Gc,short odliczanie,Character* &t, const Przedmiot &zatyczki)
{
    aktualizuj_efekt(Gc);
    Gc.wybor=true;
    SprawdzZIndeksem(t,Gc.enemies,Gc.wskazany);
    koloruj(11,8);
    cout<<t->Imie<<Gc.S.L.get(Tx::Turn_info)<<endl;
    koloruj(7,0);
    this_thread::sleep_for(ZaWarudo::seconds(2));
    aktualizuj_efekt(Gc);
    bool ogl=false;
    for (const auto& efekt:t->efekty){
        if (efekt.ID==1&&efekt.aktywny==true)//jezeli zostal ogluszony
        {
            koloruj(11,8);
            cout<<t->Imie<<Gc.S.L.get(Tx::Obj_IsStunned)<<endl;
            cout<<Gc.S.L.get(Tx::TurnsRemaining)<<efekt.duration<<endl;
            koloruj(7,0);
            this_thread::sleep_for(ZaWarudo::seconds(3));
            ogl=true;
            break; // KONIEC TURY! ZOMBIE NIE ATAKUJE
        }
        if (efekt.ID==3&&efekt.aktywny==true)//jezeli zostal wzmocniony
        {
            t->ATK+=t->ATK*0.3;
        }
    }
    if (ogl==true) {screen(Gc);return;}
    Gc.wybor=false;
    DamageResult w;
    //normalnie
    if (t->typ==TP::TOKSYCZNY) ToxZomTURN(Gc,t,zatyczki);
    else if(t->typ==TP::EXPLODER) BombyTurn(Gc,t);
    else if(t->typ==TP::NALADOWANY) NaLZomTURN(Gc,t);
    else if(t->typ==TP::COMMANDER) {CommanderTURN(Gc,t);
    if (kolejComm){kolejComm=false;ZomTURN(Gc,odliczanie,Gc.enemies[0],zatyczki);}
    }
    else{
        if (czyZyje(Gc.dzialko)){
                if (czy_pudlo(t->missrate)){
                    t->spudlowanie();
                    return;
                }
                w=t->damage(*Gc.dzialko,t->ATK,CritMode::RANDOM);
                MultiDamageResult TempMDR=nowyMDR({w});
                kiedy_efekt(Gc,TempMDR,*t);
                if (!w.bitesthedust)
                {
                    Gc.dzialko->PainReact();
                }
                else{
                    t->ObecnaAkcja=AK::NO_ACTION;
                    dzwiek("Audio_RPG\\build_destroyed.wav");
                    screen(Gc);
                    koloruj(11,8);
                    cout<<t->Imie<<Gc.S.L.get(Tx::Obj_Destroyed)<<Gc.dzialko->Imie<<"!!!\n";
                    koloruj(7,0);
                    this_thread::sleep_for(ZaWarudo::seconds(3));
                }
            return;
        }
        else if(czyZyje(Gc.zasobnik)){
            if (czy_pudlo(t->missrate)){
                t->spudlowanie();
                return;
            }
            w=t->damage(*Gc.zasobnik,t->ATK,CritMode::RANDOM);
            MultiDamageResult TempMDR=nowyMDR({w});
            kiedy_efekt(Gc,TempMDR,*t);
            if (!w.bitesthedust)
            {
                Gc.zasobnik->PainReact();
            }
            else{
                t->ObecnaAkcja=AK::NO_ACTION;
                dzwiek("Audio_RPG\\build_destroyed.wav");
                screen(Gc);
                koloruj(11,8);
                cout<<t->Imie<<Gc.S.L.get(Tx::Obj_Destroyed)<<Gc.zasobnik->Imie<<"!!!\n";
                koloruj (7,0);
                this_thread::sleep_for(ZaWarudo::seconds(3));
            }
            return;
        }
        if (czy_pudlo(t->missrate)){
            t->spudlowanie();
            return;
        }
        w=t->damage(Gc.gracz,t->ATK,CritMode::RANDOM);
        MultiDamageResult TempMDR=nowyMDR({w});
        kiedy_efekt(Gc,TempMDR,*t);
        if (!w.bitesthedust)
        {
            Gc.gracz.PainReact();
        }
        else screen(Gc);

    }
    if(Gc.debug){
                 koloruj(7,0);
                cout<<"DAMAGERESULT: | adress:"<<w.cel<<" bitesthedust:"<<w.bitesthedust<<" | IsCritical: "<<w.krytyczne<<" | damage: "<<w.obrazenia<<endl;
                this_thread::sleep_for(ZaWarudo::seconds(2));
            }
    this_thread::sleep_for(ZaWarudo::milliseconds(250));
}
bool CzyBylSklep=false;
void ciagla_walka(Gamecontent &Gc,short &Barka_status,bool &CzyBylSklep)
{
    Flashbang *flashbang = Gc.gracz.znajdz<Flashbang>();
    Telephone *tel=Gc.gracz.znajdz<Telephone>();
    Earplugs *zatyczki=Gc.gracz.znajdz<Earplugs>();
    if(!flashbang||!tel||!zatyczki)
    {
        cerr<<Gc.S.L.get(Tx::Error_noItem)<<endl;
        exit(0);
    }
    Gc.wybor=false;
    for (const Character* wrog:Gc.enemies){
        if (wrog==nullptr) {
            cout << Gc.S.L.get(Tx::Error_NullPointer) << endl;
            return; // Zakoncz funkcje, jesli wskaznik jest nieprawidlowy
        }
    }

    dzwiek("Audio_RPG\\Demoman_response_battlecry.wav");
    while (czyZyje(Gc.gracz))
    {
        if (Gc.x%5==1&&Gc.x!=1&&!CzyBylSklep)
        {
            Gc.gracz.DEF=1;
            Gc.Wydarzenie=Globalne::SHOP;
            CzyBylSklep=true;
            dzwiek_loop("Audio_RPG\\Upgradestation_loop.wav");
            screen(Gc);
            panele(Gc,*flashbang,*tel,*zatyczki);
            do
            {
                sklep_input(Gc,*flashbang,*tel,*zatyczki);
            }while (Gc.Wydarzenie==Globalne::SHOP);
            cout << "DEBUG: wyszedlem ze sklepu\n";
            this_thread::sleep_for(ZaWarudo::milliseconds(1000));
            short battlecry=Los(10,0);
            if (battlecry<5)
                dzwiek("Audio_RPG\\Demoman_response_battlecry.wav");
            else
                dzwiek("Audio_RPG\\Demoman_response_battlecry2.wav");
        }
        else
        {
        Gc.Wydarzenie=Globalne::NONE;
        Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
        flashbang = Gc.gracz.znajdz<Flashbang>();
        tel=Gc.gracz.znajdz<Telephone>();
        zatyczki=Gc.gracz.znajdz<Earplugs>();
        if(!flashbang||!tel||!zatyczki)
        {
            cerr<<Gc.S.L.get(Tx::Error_noItem)<<endl;
            exit(0);
        }
        for (Character* wrog:Gc.enemies) {
            if (czyZyje(wrog)&&wrog->czy_doubleATK==true) {
                screen(Gc);
                this_thread::sleep_for(ZaWarudo::seconds(1));
                ZomTURN(Gc,wrog->odliczanie,wrog,*zatyczki);
                Gc.wybor=false;
                if (!czyZyje(Gc.gracz)) return;
            }
        }
        screen(Gc);
        panele(Gc,*flashbang,*tel,*zatyczki);
        wyczyscBufor();
        Gc.gracz.missrate=0.07;
        Input(Barka_status,Gc,*flashbang,*tel,*zatyczki);
        aktualizuj_efekt(Gc);
        Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
        if (czyZyje(Gc.dzialko)&&!(EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)))
            DzialTURN(Gc);
        else if (czyZyje(Gc.zasobnik)&&!(EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)))
            ZasobTURN(Gc);
        if (EverybodyDEAD_NOT_BIG_SUPRISE(Gc.enemies)) {
            for (Character* wrog:Gc.enemies){
            Gc.gracz.EXP+=wrog->EXP+(10*Gc.x);
            ogluszenie=false;
            if (czyZyje(wrog)) wrog->updateujEfekty(*wrog);
        }
        screen(Gc);
            Gc.wybor=false;
            CzyBylSklep=false;
            if(liczba_wrogow>1) cout << "\n"<<Gc.S.L.get(Tx::EnemiesDefeated)<< endl;
            else cout<<"\n"<<Gc.enemies[0]->Imie<<Gc.S.L.get(Tx::EnemyDefeated)<<endl;
            czekaj=0;
            int kodwypowiedz=Los(10,0);
            if (Gc.dlacase==true)
                {
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_UsedCaber));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_win.wav");
                    Gc.dlacase=false;
                }
            else{
                switch (kodwypowiedz)
                {
                case 1:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_jeer));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_pogarda.wav");
                    break;
                case 2:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_jeer2));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_pogarda2.wav");
                    break;
                case 3:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_jeer3));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_pogarda3.wav");
                    break;
                case 4:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_laugh));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_laugh.wav");
                    break;
                case 5:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_win2));
                    dzwiek_ciagly("Audio_RPG\\Demoman_reaponse_win2.wav");
                    break;
                case 6:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_dom));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_domination.wav");
                    break;
                case 7:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_win));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_win3.wav");
                    break;
                case 8:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_laugh));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_laugh2.wav");
                    break;
                case 9:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_laugh));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_laugh3.wav");
                    break;
                case 10:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_dom2));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_domination2.wav");
                    break;
                default:
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_glue));
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_glue.wav");
                    break;
                    }
                }
            this_thread::sleep_for(ZaWarudo::seconds(2));
            Gc.x++;
            ReturnToZero(Gc);
            cout<<endl<<endl<<endl<<endl;
            for (Character* wrog:Gc.enemies){
                if (wrog!=nullptr) delete wrog;
            }
            Gc.enemies.clear();
            nowyWrog(Gc,base_HP_wrog);
            Gc.gracz.DEF=1;
            system("cls");
            }
        else {
            screen(Gc);
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
                    Gc.wskazany++;
                if (czyZyje(wrog)==true) {
                    wybor=true;
                    narysujScene(Gc);
                if(wrog->typ==TP::COMMANDER&&kolejComm) continue;
                else {
                    ZomTURN(Gc,wrog->odliczanie,wrog,*zatyczki);
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
                        DamageResult Poisoning=Gc.gracz.damage(Gc.gracz,zatrucie,CritMode::NONE);
                        Gc.gracz.PainReact();
                        screen(Gc);
                        MultiDamageResult TempMDR=nowyMDR({Poisoning});
                        kiedy_efekt(Gc,TempMDR,Gc.gracz);
                        if (Poisoning.bitesthedust) return;
                        cout<<Gc.gracz.Imie<<Gc.S.L.get(Tx::Obj_IsPoisoned)<<endl;
                        this_thread::sleep_for(ZaWarudo::seconds(2));
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
