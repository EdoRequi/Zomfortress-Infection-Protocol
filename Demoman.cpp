#include <conio.h>
#include <iostream>
#include <thread>
#include "Demoman.h"
using namespace std;

short Barka_status=0;
int glowy=0;
void AkcjaMiecz(Gamecontent &Gc,Character* &cel,Eyelander* &miecz){
        dzwiek_ciagly("Audio_RPG\\menu_selecting.wav");
        aktualizuj_efekt(Gc);
        Gc.gracz.ObecnaAkcja=AK::ACTION1;
        narysujScene(Gc);
        koloruj(11,8);
        cout<<Gc.S.L.get(Tx::Used_info_Sword)<<"             "<<endl;
        koloruj(7,0);
        dzwiek_ciagly("Audio_RPG\\miecz_wyciagniecie.wav");
        this_thread::sleep_for(ZaWarudo::seconds(1));
        if(czy_pudlo(Gc.gracz.missrate)){
            Gc.gracz.spudlowanie();
            return;
        }
        Gc.smigniecie=true;
        narysujScene(Gc);
        dzwiek("Audio_RPG\\miecz_machniecie.wav");
        this_thread::sleep_for(ZaWarudo::milliseconds(400));
        if (cel->typ==TP::TYTANOWY){
            dzwiek("Audio_RPG\\Saxxy_impact.wav");
            cout<<Gc.S.L.get(Tx::Sword_resistance)<<endl;
            this_thread::sleep_for(ZaWarudo::seconds(2));
            Gc.smigniecie=false;
            }
            else{
            DamageResult w=miecz->uzyj(Gc.gracz,*cel);//atak bezposredni, raz sie odbywa
            MultiDamageResult TempMDR=nowyMDR({w});
            if(Gc.debug){
                 koloruj(7,0);
                cout<<"DAMAGERESULT: | adress:"<<w.cel<<" bitesthedust:"<<w.bitesthedust<<" | IsCritical: "<<w.krytyczne<<" | damage: "<<w.obrazenia<<endl;
                this_thread::sleep_for(ZaWarudo::seconds(2));
            }
                if (!w.bitesthedust) //kontrola
                {
                    Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                    Gc.smigniecie=false;
                kiedy_efekt(Gc,TempMDR,Gc.gracz);
                }
                else
                {
                    Gc.wybor=false;
                    glowy++;
                    if(glowy>=12) {
                        Gc.gracz.base_HP=2137; //wspomnienie Jana Pawla II
                        Barka_status++;
                        Gc.gracz.heal(Gc.gracz,333);
                        if(Barka_status==1){
                            dzwiek_ciagly("Audio_RPG\\bip_bip.wav");
                            this_thread::sleep_for(ZaWarudo::milliseconds(1500));
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
                Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                Gc.smigniecie=false;
                screen(Gc);
                koloruj(11,8);
                cout<<Gc.S.L.get(Tx::Sword_info_heads)<<endl;
                koloruj(7,0);
                this_thread::sleep_for(ZaWarudo::milliseconds(1500));
                narysujScene(Gc);
            }
        this_thread::sleep_for(ZaWarudo::seconds(1));
    }
}
void AkcjaGranatySamoprzylepne(Gamecontent &Gc,Character* &Cel,WyrzutnikGranatow* &SBLauncher){
    dzwiek("Audio_RPG\\menu_selecting.wav");
    unsigned int iloscGranatow=Los(5,1);
    Gc.gracz.ObecnaAkcja=AK::ACTION2;
    narysujScene(Gc);
    koloruj(11,8);
    cout<<Gc.S.L.get(Tx::SBL_bomb_info)<<iloscGranatow<<endl;
    koloruj(7,0);
    dzwiek_ciagly("Audio_RPG\\bomba_przeladowanie.wav");
    for (unsigned int i=0;i<iloscGranatow;i++)
    {
        if(czy_pudlo(Gc.gracz.missrate)){
            narysujScene(Gc);
            koloruj(11,8);
            cout<<Gc.S.L.get(Tx::SBL_bomb_info)<<iloscGranatow<<endl;cout<<Gc.S.L.get(Tx::Obj_Miss2)<<endl;
            koloruj(7,0);
            dzwiek("Audio_RPG\\Banana_slip.wav");
            this_thread::sleep_for(ZaWarudo::milliseconds(500));
        }
        else{
            unique_ptr<StickyBomb> wyrzut=SBLauncher->wystrzel(Gc.gracz,*Cel);
            StickyBomb* wWyrzutu=wyrzut.get();
            if(wWyrzutu->krytyczna) dzwiek("Audio_RPG\\StickyBomb_wyrzut_kryt.wav");
            else dzwiek("Audio_RPG\\StickyBomb_wyrzut.wav");
            Gc.Obiekty.push_back(move(wyrzut));
            narysujScene(Gc);
            koloruj(11,8);
            cout<<Gc.S.L.get(Tx::SBL_bomb_info)<<iloscGranatow<<endl<<endl;
            koloruj(7,0);
            this_thread::sleep_for(ZaWarudo::milliseconds(500));
        }
    }
    int i2=0;
    vector<StickyBomb*> Bomby=znajdzbombyWlasciciela(Gc.Obiekty,&Gc.gracz);
                for (StickyBomb* &B:Bomby){
                    if(Gc.debug){
                        koloruj(7,0);
                        cout<<"Created StickyBomb["<<i2<<"] | adress:"<<B<<" | attachedTo:"<<B->attachedTo<<" | IsCritical: "<<B->krytyczna<<" | damage: "<<B->obrazenia<<endl;
                        this_thread::sleep_for(ZaWarudo::milliseconds(500));
                    }
                }
                if(Bomby.empty()){
                    narysujScene(Gc);
                    koloruj(7,0);
                    dzwiek("Audio_RPG\\Demoman_response_nobombs.wav");
                    cout<<Gc.S.L.get(Tx::SBL_nobombs)<<endl;
                    cout<<endl;
                    this_thread::sleep_for(ZaWarudo::seconds(2));
                }
                else{
                this_thread::sleep_for(ZaWarudo::seconds(1));
                dzwiek("Audio_RPG\\bip_bip.wav");
                this_thread::sleep_for(ZaWarudo::milliseconds(500));
                int akt_sciezka=Los(2,1);
                MultiDamageResult Wybuch;
                for (auto &B : Bomby)
                {
                    DamageResult splash;
                    vector<Character*> Wrogowiepozabiciu=Gc.enemies;
                    MultiDamageResult pojedynczyWybuch = B->eksploduj(Gc.enemies);
                    for (auto &DR : pojedynczyWybuch.Eksplozja)
                    {
                        Wybuch.Eksplozja.push_back(DR);
                    }
                }
                //atak posredni, ale ma szanse byc mocniejszy
                switch(akt_sciezka) {
                    case 1:
                    dzwiek("Audio_RPG\\TNT_explosion.wav");
                    break;
                    default:{
                            dzwiek("Audio_RPG\\Demoman_response_KaBOOM2.wav");
                            this_thread::sleep_for(ZaWarudo::milliseconds(500));
                            break;
                    }
                }
                Gc.Obiekty.erase(remove_if(Gc.Obiekty.begin(),Gc.Obiekty.end(),[](const unique_ptr<NonLivingObject> &O){
                    return dynamic_cast<StickyBomb*>(O.get())!=nullptr;
                }),Gc.Obiekty.end());
                Bomby.clear();
                for (DamageResult &pojedynczy:Wybuch.Eksplozja){
                    if (!pojedynczy.bitesthedust) //kontrola
                    {
                        Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                    }
                    else
                    {
                        Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                        switch(pojedynczy.cel->typ){
                            case TP::NALADOWANY: Gc.gracz.SP+=(pojedynczy.cel->SP)/2;
                            default: break;
                        }
                    }
                }
                screen(Gc);
                kiedy_efekt(Gc,Wybuch,Gc.gracz);
    }
    Gc.wybor=false;
    this_thread::sleep_for(ZaWarudo::seconds(2));
    Cel=nullptr;
}
bool pijany=false;
void AkcjaGorzalka(Gamecontent &Gc,Scrumpy* &gorz){
    screen(Gc);
    koloruj(11,8);
    cout<<Gc.S.L.get(Tx::Used_info_Scrumpy)<<endl;
    koloruj(7,0);
    int los_dialog=Los(2,1);
    switch (los_dialog){
    case 1:
        Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_Scrumpy));
        dzwiek_ciagly("Audio_RPG\\Demoman_response_scrumpy.wav");
        break;
    default:
        Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_Scrumpy2));
        dzwiek_ciagly("Audio_RPG\\Demoman_response_scrumpy2.wav");
    }
    this_thread::sleep_for(ZaWarudo::seconds(1));
    short alkoholizm=Los(4,0);//1 na 5 szansy na upojenie-efekt przez ktory zadajesz o 20% mniej ataku
    unsigned int przedHP = Gc.gracz.HP;
    gorz->uzyj(Gc.gracz);
    screen(Gc);
    koloruj(11,8);
    cout<<Gc.S.L.get(Tx::Scrumpy_HPGain)<<Gc.gracz.HP-przedHP<<"HP"<<endl;
    koloruj(7,0);
    this_thread::sleep_for(ZaWarudo::seconds(1));
    if (pijany==true){
        for (auto& efekt:Gc.gracz.efekty){
            if (efekt.ID==2&&efekt.aktywny==true){
                efekt.duration++;
                koloruj(8,0);
                cout<<Gc.S.L.get(Tx::Scrumpy_DrunkMaintained)<<efekt.duration<<endl;
                koloruj(7,0);
            }
        }
    }
    else{
        if (alkoholizm==3)
        {
            cout<<endl<<endl;
            koloruj(8,0);
            cout<<"..."<<Gc.gracz.Imie<<Gc.S.L.get(Tx::Scrumpy_Drunk)<<endl;
            short kolejka=Los(5,2);
            Gc.gracz.dodajefekt(UPICIE,kolejka,Gc.gracz);
            cout<<Gc.S.L.get(Tx::TurnsRemaining)<<kolejka-1;
            koloruj(7,0);
            short wersja_pijanstwa=Los(5,0);
            switch (wersja_pijanstwa)
            {
                case 0:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo.wav");
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_drunk1));
                    this_thread::sleep_for(ZaWarudo::seconds(8));
                    break;
                case 1:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo2.wav");
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_drunk2));
                    this_thread::sleep_for(ZaWarudo::seconds(7));
                    break;
                case 2:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo3.wav");
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_drunk3));
                    this_thread::sleep_for(ZaWarudo::seconds(5));
                    break;
                case 3:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo5.wav");
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_drunk5));
                    this_thread::sleep_for(ZaWarudo::seconds(5));
                    break;
                case 4:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo6.wav");
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_drunk6));
                    this_thread::sleep_for(ZaWarudo::seconds(5));
                    break;

                default:
                    dzwiek("Audio_RPG\\Demoman_response_pijanstwo4.wav");
                    Dialog(Gc.gracz.Imie,12,0,Gc.S.L.get(Tx::Demo_response_drunk4));
                    this_thread::sleep_for(ZaWarudo::seconds(7));
                    break;
            }
        }
    }
}
void AkcjaTarcza(Gamecontent &Gc,Shield* &Sh){
    int przedSP=Gc.gracz.SP;
    Sh->uzyj(Gc.gracz);
    screen(Gc);
    koloruj(11,8);
    cout<<Gc.S.L.get(Tx::Used_info_Shield)<<endl;
    koloruj(7,0);
    koloruj(11,8);
    if (Gc.gracz.SP-przedSP>Sh->dodawaczSP)
        cout<<Gc.S.L.get(Tx::Shield_SPGain)<<Sh->dodawaczSP+1<<" SP!"<<endl;
    else
        cout<<Gc.S.L.get(Tx::Shield_SPGain)<<Sh->dodawaczSP<<" SP!"<<endl;
    koloruj(7,0);
    this_thread::sleep_for(ZaWarudo::seconds(2));
}
void AkcjaEkwipunek(Gamecontent &Gc,bool &validchoice){
    Klawisz choice(' ',NOTARROW);
    Flashbang *flashbang = Gc.gracz.znajdz<Flashbang>();
    Telephone *tel=Gc.gracz.znajdz<Telephone>();
    Earplugs *zatyczki=Gc.gracz.znajdz<Earplugs>();
    if(!flashbang||!tel||!zatyczki)
    {
        cerr<<Gc.S.L.get(Tx::Error_noItem)<<endl;
        exit(0);
    }
    dzwiek("Audio_RPG\\menu_selecting.wav");
    przedmioty_wybrane(Gc,*flashbang,*tel,*zatyczki);
    bool przedmiotyDone=false;
    while (!przedmiotyDone)
    {
        choice.PressK();
        switch(choice.znak)
        {
            case '1':
            {
                if (flashbang->quant!=0)
                {
                    Gc.gracz.ObecnaAkcja=AK::ACTION_USED_ITEM;
                    screen(Gc);
                    koloruj(11,8);
                    cout<<Gc.S.L.get(Tx::Used_info_Flashbang)<<endl;
                    koloruj(7,0);
                    dzwiek_ciagly("Audio_RPG\\rzut.wav");
                    dzwiek("Audio_RPG\\flashbang_throw.wav");
                    this_thread::sleep_for(ZaWarudo::seconds(2));
                    Gc.Wydarzenie=Globalne::FLASH;
                    flashbang->uzyj(Gc.enemies);
                    screen(Gc);
                    dzwiek("Audio_RPG\\flashbang_boom.wav");
                    this_thread::sleep_for(ZaWarudo::milliseconds(2500));
                    Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                    Gc.Wydarzenie=Globalne::NONE;
                    screen(Gc);
                    koloruj(11,8);
                    cout<<Gc.S.L.get(Tx::Flashbang_stun_info)<<endl;
                    koloruj(7,0);
                    this_thread::sleep_for(ZaWarudo::seconds(3));
                    przedmiotyDone=true;
                    validchoice=true;
                }
                        else {
                            cout<<Gc.S.L.get(Tx::Error_noItem)<<endl;
                        }
                        break;}
            case '2':
            {
                if(tel->quant!=0&&Gc.gracz.SP>=5)
                {
                    Gc.gracz.SP-=5;
                    Gc.gracz.ObecnaAkcja=AK::NO_ACTION;
                    screen(Gc);
                    dzwiek("Audio_RPG\\telephone_ring.wav");
                    koloruj(11,8);
                    cout<<Gc.S.L.get(Tx::Phone1)<<endl;
                    this_thread::sleep_for(ZaWarudo::seconds(2));
                    cout<<Gc.S.L.get(Tx::Phone2)<<endl;
                    koloruj(7,0);
                    dzwiek_ciagly("Audio_RPG\\Demoman_response_engineer.wav");//Inzynierze...
                    this_thread::sleep_for(ZaWarudo::milliseconds(500));
                    dzwiek("Audio_RPG\\Engineer_response_yeah.wav");//tak?
                    this_thread::sleep_for(ZaWarudo::milliseconds(1200));
                    dzwiek_ciagly("Audio_RPG\\Demoman_HELP.wav");//POMOZ!:(
                    this_thread::sleep_for(ZaWarudo::milliseconds(500));
                    if (!czyZyje(Gc.dzialko)&&!czyZyje(Gc.zasobnik)){
                        short wersjaodpowiedzi=Los(2,0);
                        if (wersjaodpowiedzi==1) dzwiek_ciagly("Audio_RPG\\Engineer_response01.wav");
                        else if(wersjaodpowiedzi==2) dzwiek_ciagly("Audio_RPG\\Engineer_response02.wav");
                        else dzwiek_ciagly("Audio_RPG\\Engineer_response03.wav");
                        this_thread::sleep_for(ZaWarudo::milliseconds(500));
                        screen(Gc);
                        koloruj(11,8);
                        cout<<Gc.S.L.get(Tx::Phone3);
                        koloruj(7,0);
                        this_thread::sleep_for(ZaWarudo::seconds(1));
                        short zrzut=Los(100,0);
                        if (zrzut>50){
                            noweDzialko(Gc.x,Gc.dzialko,Gc.S.L);
                            screen(Gc);
                            koloruj(11,8);
                            cout<<Gc.dzialko->Imie<<"!"<<endl;
                            koloruj(7,0);
                        }
                                else{
                                    nowyZasobnik(Gc.x,Gc.zasobnik,Gc.S.L);
                                    screen(Gc);
                                    koloruj(11,8);
                                    cout<<Gc.zasobnik->Imie<<"!"<<endl;
                                    koloruj(7,0);
                                    }
                                dzwiek_ciagly("Audio_RPG\\build.wav");
                                this_thread::sleep_for(ZaWarudo::seconds(2));
                            }
                            else
                            {
                                dzwiek("Audio_RPG\\Engineer_nope.wav"); //nie
                                koloruj(14,8);
                                Dialog("Inzynier",14,8,Gc.S.L.get(Tx::Phone2_rejected));
                                this_thread::sleep_for(ZaWarudo::milliseconds(500));
                                dzwiek("Audio_RPG\\telephone_lostcon.wav");
                                 cout<<Gc.S.L.get(Tx::Phone_achievement_wastingSP)<<endl;
                                this_thread::sleep_for(ZaWarudo::milliseconds(2000));
                            }
                            przedmiotyDone=true;
                            validchoice=true;

                            }
                        else if (tel->quant!=0&&Gc.gracz.SP<5) {
                            cout<<Gc.S.L.get(Tx::Error_noSP);
                        }
                        else {
                        cout<<Gc.S.L.get(Tx::Error_noItem);
                        }
                        break;}
        case 'x':
        {
            validchoice=false;
            przedmiotyDone=true;
            dzwiek("Audio_RPG\\menu_back.wav");
            screen(Gc);
            panele(Gc,*flashbang,*tel,*zatyczki);
            break;}
        default:
            cout<<Gc.S.L.get(Tx::Error_WrongKey)<<endl;
            break;
        }
    }
}
