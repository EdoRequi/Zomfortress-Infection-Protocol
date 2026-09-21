#include "Gamelogic.h"
#include <iostream>

using namespace std;
using Tx=TextID;
Language Localization::whatLanguage() const{
    return jezyk;
}
std::string Localization::get(TextID id)const{
    switch(jezyk)
    {
    case Language::POLSKI:
        switch (id){
            //bledy
            case Tx::Error_info: return "BLAD!";
            case Tx::Error_info_IndexOutOfBounds: return "BLAD: wskazany poza zakresem! wskazany = ";
            case Tx::Error_noItem: return "Nie ma takiego przedmiotu";
            case Tx::Error_noSP: return "Nie mozesz, nie masz wystarczajaco SP.";
            case Tx::Error_WrongKey: return "Zly klawisz";
            case Tx::Error_AlreadyHaveIt: return "Juz masz ten przedmiot!";
            case Tx::Error_nope_tf2reference: return "Nope";
            case Tx::Error_noFunds: return "Nie masz odpowiedniej ilosci exp!";
            case Tx::Error_maxLevel: return "Ten przedmiot jest maksymalnie ulepszony!";
            case Tx::Error_NullPointer: return "BLAD: Wskaznik na wroga jest null!";
            case Tx::Error_targetnotvalid: return "Nie wybrano poprawnego celu!";
            //menu
            case Tx::But_PLAY1: return "GRAJ 1P";
            case Tx::But_PLAY2: return "GRAJ 2P";
            case Tx::But_Sett: return "USTAWIENIA";
            case Tx::Sw_ENDEBUG: return "1. Tryb Debug = ";
            case Tx::Sw_FONTSIZE: return "2. Wielkosc tekstu = ";
            case Tx::X_for_exit: return "X - wyjscie";
            case Tx::X_for_continue: return "WCISNIJ 'X', ABY PRZEJSC DALEJ";
            //sklep
            case Tx::Shop_Sh: return "\\1.Ulepszenie tarczy: ";
            case Tx::Shop_SBL: return "\\2.Ulepszenie wyrzutnika: ";
            case Tx::Shop_Sw: return "\\3.Ulepszenie miecza: ";
            case Tx::Shop_Fl: return "\\4.Przedmiot: flashbang: ";
            case Tx::Shop_Phone: return "\\5.Przedmiot:Pomocna linia u Inzyniera(zuzywa 5 SP): ";
            case Tx::Shop_Ear: return "\\6.Przedmiot: Zatyczki do uszu(pasywne): ";
            case Tx::Level_info: return "obecny poziom: ";
            case Tx::Bought_Item: return "Kupiles ";
            case Tx::X_for_continue2: return "\\Wcisnij X, kiedy bedziesz gotowy\\";
            //Ekwipunek gracza
            case Tx::I_Sword: return "Eyelander";
            case Tx::I_SBLauncher: return "Wyrzutnik Granatow Samoprzylepnych";
            case Tx::I_Shield: return "Tarcza";
            case Tx::I_Scrumpy: return "Gorzalka";
            case Tx::I_flashbang: return "Flashbang";
            case Tx::I_phone: return "Telefon do Inzyniera";
            case Tx::I_earplugs: return "Zatyczki do uszu";
            case Tx::Quantity: return "Ilosc: ";
            case Tx::Quantity_info: return "obecna ilosc: ";
            //informacje stale wyswietlane
            case Tx::Deb_info_EnAdress: return "DEBUG:ADRES WROGA - ";
            case Tx::Deb_gen: return "Wygenerowano ";
            case Tx::Deb_highest_localHP: return "Najnizsze HP:";
            case Tx::Wave_info: return "-- WALKA ";
            case Tx::Name_FastZ: return "Szybki Zombie";
            case Tx::Name_TitanZ: return "Tytanowy Zombie";
            case Tx::Name_ToxicZ: return "Toksyczny Zombie";
            case Tx::Name_ElecZ: return "Naladowany Zombie";
            case Tx::Name_ExplZ: return "Zombie Exploder";
            case Tx::Name_CommandZ: return "Zombie Dowodca";
            case Tx::Name_Sentry: return "Dzialko Straznicze";
            case Tx::Name_Dispenser: return "Zasobnik";
            case Tx::Name_Engineer: return "Inzynier";
            //tagi
            case Tx::Tag_direction_Info: return "Zombie otagowane od lewej do prawej!           ";
            case Tx::Tag_PLAYER: return "GRACZ";
            case Tx::Tag_BUILD: return "BUDOWLA";
            case Tx::Tag_ENEMY: return "WROG";
            //napisy gry
            case Tx::Action_info_offensive:return "OFENSYWA";
            case Tx::Action_info_support: return "SPECJALNE";
            case Tx::Action_info_equipment: return "PRZEDMIOTY";
            case Tx::Demo_actions_offensive_Sword: return "Miecz";
            case Tx::Demo_actions_offensive_SBL: return "Wyrzutnik granatow samoprzylepnych";
            case Tx::Demo_actions_offensive_specialAttack: return "ATAK SPECJALNY (zuzywa 15 SP)";
            case Tx::Demo_actions_support_Scrumpy: return  "Gorzalka";
            case Tx::Demo_actions_support_Shield: return "Tarcza";
            case Tx::Turn_info: return " turn:          ";
            case Tx::TurnsRemaining: return "Liczba kolejek: ";
            case Tx::EachAndEveryoneWillBeSentHomeToYourMommaInABox: return "Wszyscy wrogowie martwi sa martwi, nie ma kogo zabijac...";
            case Tx::Defeat_info: return"  pokonalo ";
            case Tx::Obj_IsStunned: return " jest ogluszony i nie moze sie ruszyc!";
            case Tx::Obj_Miss: return " pudluje!    ";
            case Tx::Obj_Miss2: return "Pudlo!";
            case Tx::Obj_NoSuffer: return " nie zostal zaafektowany tym atakiem... BO TAKI OPRUTY!!!         ";
            case Tx::Obj_DealsCrit: return " zadaje krytyczne obrazenia!    ";
            case Tx::Obj_IsPoisoned: return " doznaje obrazen w wyniku zatrucia.";
            case Tx::Obj_SufferedStrongAttack: return " To byl super efektywny cios dla ";
            case Tx::Obj_Destroyed: return " zniszczyl ";
            case Tx::Obj_IsPowered: return "Atak wszystkich zombie zostaje zwiększony o 30% na 3 rundy!!";
            case Tx::Cost_info: return "zuzywa ";
            case Tx::DoYouWantToQuit: return "Na pewno chcesz wyjsc? (Y/N) ";
            case Tx::Caber_SDestroyed: return "Dzialko zostaje zniszczone z powodu wybuchu!";
            case Tx::Caber_DDestroyed: return "Zasobnik zostaje zniszczony z powodu wybuchu!";
            case Tx::Caber_result: return " przezywa, poniewaz zaslonil sie tarcza ";
            case Tx::Caber_UnTouched: return "Byl tak opruty, ze nawet wybuch go nie ruszyl!!! ";
            case Tx::Caber_Touched: return " Niestety zostaje ogluszony na jedna runde...";
            case Tx::EnemyDefeated: return " zostal pokonany! Wygrywasz!";
            case Tx::EnemiesDefeated: return "Wszyscy wrogowie zostali pokonani! Wygrywasz!";
            //uzycia przedmiotow
            case Tx::Used_info_Sword: return "Uzywasz Eyelander'a                                     ";
            case Tx::Sword_info_heads: return "Za uzycie miecza zyskujesz wiekszy max HP!";
            case Tx::Sword_resistance: return "... Miecz nawet nie drasnal Tytanowego Zombie!!!    ";
            case Tx::SBL_bomb_info: return "Wystrzelone granaty: ";
            case Tx::SBL_nobombs: return "...Demoman ostatecznie nie wystrzeliwuje zadnych bomb...";
            case Tx::Used_info_Scrumpy: return "Pijesz gorzalke";
            case Tx::Scrumpy_HPGain:case Tx::Shield_SPGain: return "Zyskujesz ";
            case Tx::Scrumpy_DrunkMaintained: return "Podtrzymales efekt upicia. Liczba kolejek=";
            case Tx::Scrumpy_Drunk: return " sie upil, od teraz ma 33% wiecej szansy na spudlowanie!";
            case Tx::Used_info_Shield: return "Zaslaniasz sie tarcza";
            case Tx::Used_info_Flashbang: return "Rzucasz granat ogluszajacy (flashgrenade)!";
            case Tx::Flashbang_stun_info: return "Ogluszasz zombiaki (bedziesz mial dodatkowe ruchy)!";
            case Tx::Phone1: return "Dzwonisz do Inzyniera...";
            case Tx::Phone2: return "Odebral!";
            case Tx::Phone2_rejected: return "Nie!";
            case Tx::Phone3: return "Inzynier zrzuca...";
            case Tx::Phone_achievement_wastingSP: return "Widze, ze bardzo uwielbiasz marnowac ruchy i SP.";
            //Wypowiedzi Demomana
            case Tx::Demo_response_Scrumpy: return "Ejj... Czas na popicie Scrumpym!";
            case Tx::Demo_response_drunk1: return "Zaraz was zabije i bede was zabijal i ja nigdy tego nie zrobie, poniewaz i tak bedziecie martwi, wiec nie bede musial was zabijac.";
            case Tx::Demo_response_drunk2: return "(paplanina)... wlasnie chcialem pojechac na stacje BOLOWEGO POCIAGU w Train Town...";
            case Tx::Demo_response_drunk3: return "Ja... kocham takich jak ... ty tutaj... nie was.";
            case Tx::Demo_response_drunk4: return "... A potem wyhodujê ci tylek na tylku, jak ja jestem trawiastym czlowiekiem, durniu, poganie jeden...";
            case Tx::Demo_response_drunk5: return "(Niezrozumialy belkot)";
            case Tx::Demo_response_drunk6: return "Kazdy z was... eee... co mysli, zeee... jest lepszy ode mnie... nastepny dostanie za...";
            case Tx::Demo_response_Caber1: return "Nie boj sie chloptasiu, bede delikatny!";
            case Tx::Demo_response_Caber2: return "O, zbije cie tak mocno, ze dostaniesz dreszczy!";
            case Tx::Demo_response_Caber3: return "A TERAZ WSZYSCY WYBUCHNIECIE!!!";
            case Tx::Demo_response_UsedCaber: return "I oto to zyskujesz, gdy dotkniesz tego!";
            case Tx::Demo_response_dom: return "ZDOMINOWANY! (smiech)";
            case Tx::Demo_response_dom2: return "(spiewajaco) Wszyscy pyszalkowie podskakuja ze swymi lbami pelnym galek [ocznych]!";
            case Tx::Demo_response_glue: return "Ooo, beda was musieli posklejac klejem z powrotem... W PIEKLE!!!";
            case Tx::Demo_response_laugh: return "(smiech)";
            case Tx::Demo_response_win: return "Widzisz? Mowilem, ze sa to niezle sztuki malych sku***elow!";
            case Tx::Demo_response_win2: return "TAK SIE POWINNO TO ROBIC!!!";
            case Tx::Demo_response_jeer: return "Jak ci do tego, balwanie?!";
            case Tx::Demo_response_jeer2: return "Niech to bedzie dla ciebie cho****a nauczka!";
            case Tx::Demo_response_jeer3: return "W waszym jezyku - zryjcie olow, lads'i!";
            //poszczegolne zombie
            case Tx::Toxic_YOMUMFAT: return "Twoja stara jest tak gruba!";
            case Tx::Toxic_YOMUMSTUPID: return "Twoja stara jest tak glupia!";
            case Tx::Toxic_YOMUMUGLY: return "Twoja stara jest tak brzydka!";
            case Tx::Toxic_YOMUM1: return "Donald Trump chce jej uzyc jej JAKO MUR GRANICZNY!!!!!";
            case Tx::Toxic_YOMUM2: return "Gdy dolaczyla do Discorda, SCRASHOWALA CALY SERWER!!!!!";
            case Tx::Toxic_YOMUM3: return "Jej pepek dochodzi do domu 20 min przed nia sama!!!";
            case Tx::Toxic_YOMUM3_1: return "... Pamietam to z jednego filmiku na YT.";
            case Tx::Toxic_YOMUM4: return "To ona jest powodem, dlaczego Herobrine z Minecrafta NIE MA ZRENIC!!!";
            case Tx::Toxic_YOMUM4_1: return "... Ok, to bylo kreatywne powiazanie!";
            case Tx::Toxic_YOMUM5: return "Nie potrzebuje internetu... bo ONA JUZ JEST GLOBALNA!!!!!";
            case Tx::Toxic_YOMUM6: return "Jej splash attack... ZARAZ NIE!";
            case Tx::Toxic_YOMUM6_1: return "Nie chce spalic tej riposty... emmm...";
            case Tx::Toxic_YOMUM6_2: return "O! Juz pamietam!";
            case Tx::Toxic_YOMUM6_3: return "Twoja stara jest tak glupia! Poszla do dentysty... aby OTRZYMAC BLUETOOTH!!!!!";
            case Tx::Toxic_YOMUM7: return "Zwrocila do reklamacji donuta, bo mial DZIURE!!!";
            case Tx::Toxic_YOMUM8: return "Umowila sie na badanie lekarskie do DR. PEPPER'A!!!!";
            case Tx::Toxic_YOMUMDEFAULT1: return "Tak dla wspomnienia... TWOJA STARA!!!";
            case Tx::Toxic_YOMUMDEFAULT2: return "Taa... malo wlozylem w to wysilku, ale to nawet samo zawsze dzialalo!";
            case Tx::SucceededOffend: return " czuje sie upokorzony... jego atak spada o 50%!!";
            case Tx::FailedOffend: return " nosi zatyczki - Oczernianie 'starej' nie przejelo go...";
            case Tx::Toxic_Spit: return " pluje jadem na ";
            case Tx::Toxic_PoisonSuccess: return "Zostales Zatruty! Od teraz przez 3 rundy bedzie ci spadac zdrowie!";
            case Tx::Toxic_PoisonFails: return " juz jest zatruty - zatrucie nie dziala.";
            case Tx::Elec_StrengthCast: return  "przekazuje POZYTYWNY FLUID ENERGETYCZNY pozostalym zombie";
            case Tx::Elec_Overdrive: return " wyladowuje ENERGETYCZNY OVERDRIVE!!";
            case Tx::Elec_Attack: return " oddaje elektryczny atak.";
            case Tx::Expl_Counter: return "R. do wybuchhu: ";
            case Tx::Expl_Warning1: return "ZOMBIE EKSPLODER WYBUCHNIE ZA ";
            case Tx::Expl_Warning2: return " RUNDY!!!";
            case Tx::Expl_WarningFatal: return "ZOMBIE EXPLODER WYBUCHNIE! RATUJ SIE KTO MOZE!!!";
            case Tx::Expl_Miss1: return "Bomba nalezaca do ";
            case Tx::Expl_Miss1_1: return " gasnie!   ";
            case Tx::Expl_Miss2: return "Zdesperowany ";
            case Tx::Expl_Miss2_1: return  "idzie do domu...";
            case Tx::Comm_Crits: return " daje swojemu oddzialowi wieksza szanse na kryty o 15% na 2 rundy!";
            case Tx::Comm_response_regroup: return "Zmienic szyki!!!";
            //Dzialko i Zasobnik
            case Tx::Obj_IsDeactivated: return " zostalo zdeazktywowane!";
            case Tx::Obj_StoppedWorking: return " przestalo dzialac.";
            case Tx::Dispenser_heal: return "Zostales uleczony przez: ";
            //efekty
            case Tx::Eff_info: return " EFEKTY:";
            case Tx::Eff_Stun: return "[OGLUSZENIE]";
            case Tx::Eff_Drunk: return "[UPICIE]";
            case Tx::Eff_Powered: return "[WZMOCNIENIE]";
            case Tx::Eff_Poisoned: return "[ZATRUCIE]";
            case Tx::Eff_Weakness: return "[OSLABIENIE (psychiczne)]";
            case Tx::Eff_MoreCritrate: return "[KRYTOWANIE]";
            //inne
            case Tx::GAMEOVER: return " zostal pokonany! Przegrales!";
            case Tx::HolyNumberAcquire: return "Osiagnales swieta liczbe HP = 2137";
            default: return "BLAD: TEKSTU NIE MA NA LISCIE!";
        }
        break;
    case Language::ANGIELSKI:
        switch (id){
            case Tx::Error_info: return "ERROR!";
            case Tx::Error_info_IndexOutOfBounds: return "ERROR: Selected object is out of scope! wskazany = ";
            case Tx::Error_noItem: return "There is not such an item!";
            case Tx::Error_noSP: return "You can't. You don't have enough SP!";
            case Tx::Error_WrongKey: return "Wrong key";
            case Tx::Error_AlreadyHaveIt: return "You already have this item!";
            case Tx::Error_nope_tf2reference:case Tx::Phone2_rejected: return "Nope";
            case Tx::Error_noFunds: return " You don't have enough EXP points!";
            case Tx::Error_maxLevel: return "This item is already upgraded to the max level!";
            case Tx::Error_NullPointer: return "ERROR: The pointer of an enemy doesn't exist (null)!";
            case Tx::Error_targetnotvalid: return "You haven't selected the valid target!";
            //menu
            case Tx::But_PLAY1: return "PLAY 1P";
            case Tx::But_PLAY2: return "PLAY 2P";
            case Tx::But_Sett: return "SETTINGS";
            case Tx::Sw_ENDEBUG: return "1. Debug Mode = ";
            case Tx::Sw_FONTSIZE: return "2.  Font size = ";
            case Tx::X_for_exit: return "X - exit";
            case Tx::X_for_continue: return "PRESS 'X' TO CONTINUE";
            //sklep
            case Tx::Shop_Sh: return "\\1.Shield upgrade: ";
            case Tx::Shop_SBL: return "\\2.Sticky Launcher upgrade: ";
            case Tx::Shop_Sw: return "\\3.Eyelander upgrade: ";
            case Tx::Shop_Fl: return "\\4.Item: Flashbang: ";
            case Tx::Shop_Phone: return "\\5.Item: Engineer's helping service(costs 5SP): ";
            case Tx::Shop_Ear: return "\\6.Item: Earplugs (PASSIVE): ";
            case Tx::Level_info: return "current level: ";
            case Tx::Bought_Item: return "You bought ";
            case Tx::X_for_continue2: return "\\PRESS 'X' WHEN YOU'RE READY\\";
            //Ekwipunek gracza
            case Tx::I_Sword: return "Eyelander";
            case Tx::I_SBLauncher: return "Sticky Bomb Launcher";
            case Tx::I_Shield: return "Chargin' Targe";
            case Tx::I_Scrumpy: return "Scrumpy";
            case Tx::I_flashbang: return "Flashbang";
            case Tx::I_phone: return "Telephone to Engineer";
            case Tx::I_earplugs: return "Earplugs";
            case Tx::Quantity: return "quant: ";
            case Tx::Quantity_info: return "current quant: ";
            //informacje stale wyswietlane
            case Tx::Deb_info_EnAdress: return "DEBUG:ENEMY'S ADRESS - ";
            case Tx::Deb_gen: return "Generated ";
            case Tx::Deb_highest_localHP: return "The lowest local HP:";
            case Tx::Wave_info: return "-- WAVE ";
            case Tx::Name_FastZ: return "Fast Zombie";
            case Tx::Name_TitanZ: return "Titan Zombie";
            case Tx::Name_ToxicZ: return "Toxic Zombie";
            case Tx::Name_ElecZ: return "Charged Zombie";
            case Tx::Name_ExplZ: return "Zombie Exploder";
            case Tx::Name_CommandZ: return "Commander Zombie";
            case Tx::Name_Sentry: return "Sentry";
            case Tx::Name_Dispenser: return "Dispenser";
            case Tx::Name_Engineer: return "Engineer";
            //tagi
            case Tx::Tag_direction_Info: return "Zombies are tagged from left to right!           ";
            case Tx::Tag_PLAYER: return "PLAYER";
            case Tx::Tag_BUILD: return "BUILDING";
            case Tx::Tag_ENEMY: return "ENEMY";
            //napisy gry
            case Tx::Action_info_offensive:return "OFFENSIVE";
            case Tx::Action_info_support: return "SUPPORT";
            case Tx::Action_info_equipment: return "EQUIPMENT";
            case Tx::Demo_actions_offensive_Sword: return "Eyelander";
            case Tx::Demo_actions_offensive_SBL: return "Sticky Bomb Launcher";
            case Tx::Demo_actions_offensive_specialAttack: return "SPECIAL ATTACK (costs 15 SP)";
            case Tx::Demo_actions_support_Scrumpy: return "Scrumpy";
            case Tx::Demo_actions_support_Shield: return "Shield";
            case Tx::Turn_info: return " turn:          ";
            case Tx::TurnsRemaining: return "Turns remaining: ";
            case Tx::EachAndEveryoneWillBeSentHomeToYourMommaInABox: return "Dead... everyone's dead... ";// Half Life 2 secret easter egg
            case Tx::Defeat_info: return"  pokonalo ";
            case Tx::Obj_IsStunned: return " is stunned and he can't move!";
            case Tx::Obj_Miss: return " misses!    ";
            case Tx::Obj_Miss2: return "Miss!";
            case Tx::Obj_NoSuffer: return " hadn't even been affected by it...BECAUSE HE'S SO DRUNK!!!         ";
            case Tx::Obj_DealsCrit: return " deals a critical damage!    ";
            case Tx::Obj_IsPoisoned: return "  suffers from poison.";
            case Tx::Obj_SufferedStrongAttack: return " This was super effective on ";
            case Tx::Obj_Destroyed: return " has destroyed ";
            case Tx::Obj_IsPowered: return "The attack power of every zombie has increased by 30% for 3 turns!!";
            case Tx::Cost_info: return "costs ";
            case Tx::DoYouWantToQuit: return "Na pewno chcesz wyjsc? (Y/N) ";
            case Tx::Caber_SDestroyed: return "Sentry got destroyed due to explosion!";
            case Tx::Caber_DDestroyed: return "Dispenser got destroyed due to explosion!";
            case Tx::Caber_result: return " survives thanks to the shield ";
            case Tx::Caber_UnTouched: return "He was so drunk, he didn't got affected from the explosion!!!";
            case Tx::Caber_Touched: return " Unfortunately, he gets stunned for 1 turn...";
            case Tx::EnemyDefeated: return " got defeated! You won!";
            case Tx::EnemiesDefeated: return "Every enemy has been defeated! You won!";
            //uzycia przedmiotow
            case Tx::Used_info_Sword: return "You pulled out the Eyelander                                     ";
            case Tx::Sword_info_heads: return "Thanks to sword you gain more max HP!";
            case Tx::Sword_resistance: return "... The sword didn't even leave a mark on Titan Zombie!!!         ";
            case Tx::SBL_bomb_info: return "Amount of bombs: ";
            case Tx::SBL_nobombs: return "...Turns out Demoman didn't put any bombs at all...";
            case Tx::Used_info_Scrumpy: return "You are drinking Scrumpy";
            case Tx::Scrumpy_HPGain:case Tx::Shield_SPGain: return "You gained ";
            case Tx::Scrumpy_DrunkMaintained: return "You have maintained your stiffness. Amount of turns=";
            case Tx::Scrumpy_Drunk: return " got drunk,from now you have a 33% more chance of missing.";
            case Tx::Used_info_Shield: return "You cover yourself with shield";
            case Tx::Used_info_Flashbang: return "You have thrown a flashgreande!";
            case Tx::Flashbang_stun_info: return "You have stunned the zombies (you will have additional turns)!";
            case Tx::Phone1: return "You are calling Engineer...";
            case Tx::Phone2: return "He answered!";
            case Tx::Phone3: return "Engineer drops a... ";
            case Tx::Phone_achievement_wastingSP: return "I see you are really fond of wasting moves and SP.";
            //Wypowiedzi Demomana
            case Tx::Demo_response_Scrumpy: return "Aye, me bottle o'scrumpy!";
            case Tx::Demo_response_drunk1: return "Gonna kill you and I'll keep killin' you and I'll never, cause you're 'onna be dead and I don't gotta kill you.";
            case Tx::Demo_response_drunk2: return "(gibberish)... I was gonna take down to the Pain Train station in Train Town...";
            case Tx::Demo_response_drunk3: return "I love... every... single... one of ye... not you.";
            case Tx::Demo_response_drunk4: return "And then I'll grow yer arse's arse and I'm the grass man, punk yeah heaven's heathen...";
            case Tx::Demo_response_drunk5: return "(Unintelligible gibberish)";
            case Tx::Demo_response_drunk6: return "Any of you that think ye're better 'n me, you're gon' have another thing c-..";
            case Tx::Demo_response_Caber1: return "Don't fret, boyo. I'll be gentle!";
            case Tx::Demo_response_Caber2: return "Ohh, I'm gonna beat ya so hard, you'll have a twitch!";
            case Tx::Demo_response_Caber3: return "And NOW EVERYBODY OF YEH ARE GOIN' TO EXPLODE!!!";
            case Tx::Demo_response_UsedCaber: return "And that's what ya get from touching that!";
            case Tx::Demo_response_dom: return "DOMINATED! (laugh)";
            case Tx::Demo_response_dom2: return "(singing) All yah dandies prancin' aboot with ya heads full of eyeballs!";
            case Tx::Demo_response_glue: return "Oh, they're goin' ta have to glue you back together... IN HELL!!!";
            case Tx::Demo_response_laugh: return "(laugh)";
            case Tx::Demo_response_win: return " See? I told ye they were a buncha' wee lasses!";
            case Tx::Demo_response_win2: return "THAT'S THE WAY YA DO IT!!!";
            case Tx::Demo_response_jeer: return "How's that feel ya, blockhead?!";
            case Tx::Demo_response_jeer2: return "Let that be a bloody lesson to yeh!";
            case Tx::Demo_response_jeer3: return "In your language - eat lead, ladies!";
            //poszczegolne zombie
            case Tx::Toxic_YOMUMFAT: return "Your mother is so fat!";
            case Tx::Toxic_YOMUMSTUPID: return "Your mother is so stupid!";
            case Tx::Toxic_YOMUMUGLY: return "Your momma is so ugly!";
            case Tx::Toxic_YOMUM1: return "Donald Trump used her as a BORDER WALL!!!!!";
            case Tx::Toxic_YOMUM2: return "When she joined Discord, she CRASHED THE ENTIRE SERWER!!!!!";
            case Tx::Toxic_YOMUM3: return "Her belly button gets home 20 min before she does!!!";
            case Tx::Toxic_YOMUM3_1: return "... As I remember, I took that from one YT video.";
            case Tx::Toxic_YOMUM4: return "She is the real reason, why Herobrine from Minecraft DOESN'T HAVE PUPILS!!!";
            case Tx::Toxic_YOMUM4_1: return "... Ok, that was a creative one!";
            case Tx::Toxic_YOMUM5: return "She doesn't need internet... she is ALREADY WORLDWIDE!!!!!";
            case Tx::Toxic_YOMUM6: return "Her splash attack... WAIT, NO!";
            case Tx::Toxic_YOMUM6_1: return "I don't want to spoil the punchline... ummm...";
            case Tx::Toxic_YOMUM6_2: return "Oh! I remember!";
            case Tx::Toxic_YOMUM6_3: return "Your mother is so stupid! She went to the dentist... TO GET A BLUETOOTH!!!!!";
            case Tx::Toxic_YOMUM7: return "She returned the donut because it has A HOLE!!!";
            case Tx::Toxic_YOMUM8: return "She made an appointment with DR. PEPPER!!!!";
            case Tx::Toxic_YOMUMDEFAULT1: return "One important mention... YOUR MOTHER!!!";
            case Tx::Toxic_YOMUMDEFAULT2: return "Yeah... that was a low-effort one, but it always hits the punchline!";
            case Tx::SucceededOffend: return  "feels humiliated... his attack power drops by 50%!!";
            case Tx::FailedOffend: return  "wears earplugs - trashtalk doesn't work here...";
            case Tx::Toxic_Spit: return " spits venom on ";
            case Tx::Toxic_PoisonSuccess: return "You got poisoned! From now for 3 turns your healt will be dropping a little! ";
            case Tx::Toxic_PoisonFails: return " is already poisoned - poison doesn't work here.";
            case Tx::Elec_StrengthCast: return  " gives other zombies the POSITIVE ENERGY FLOW";
            case Tx::Elec_Overdrive: return " releases the ENERGETIC OVERDRIVE!!";
            case Tx::Elec_Attack: return " gives off an electric attack.";
            case Tx::Expl_Counter: return "R. do wybuchhu: ";
            case Tx::Expl_Warning1: return "ZOMBIE EXPLODER WILL EXPLODE IN ";
            case Tx::Expl_Warning2: return " TURNS!!!";
            case Tx::Expl_WarningFatal: return "ZOMBIE EXPLODER IS GOING TO EXPLODE! GOD HELP!!!";
            case Tx::Expl_Miss1: return "Bomb belonging to ";
            case Tx::Expl_Miss1_1: return " has extinguished!   ";
            case Tx::Expl_Miss2: return "Disappointed ";
            case Tx::Expl_Miss2_1: return  "goes back home...";
            case Tx::Comm_Crits: return " gives his army crit boost (15% more chance) for 2 turns!";
            case Tx::Comm_response_regroup: return "Change order!!!";
            //Dzialko i Zasobnik
            case Tx::Obj_IsDeactivated: return " has been disactivated!";
            case Tx::Obj_StoppedWorking: return " has stopped working.";
            case Tx::Dispenser_heal: return "You got healed by: ";
            //efekty
            case Tx::Eff_info: return " EFFECTS:";
            case Tx::Eff_Stun: return "[STUNNED]";
            case Tx::Eff_Drunk: return "[DRUNK]";
            case Tx::Eff_Powered: return "[POWERED]";
            case Tx::Eff_Poisoned: return "[POISONED]";
            case Tx::Eff_Weakness: return "[(psychological) WEAKNESS]";
            case Tx::Eff_MoreCritrate: return "[MORE_CRITRATE]";
            //inne
            case Tx::GAMEOVER: return " got defeated! You lose!";
            case Tx::HolyNumberAcquire: return "You have reached the holy number = 2137";
            default: return "BLAD: The text is not on the list.";
        }
        break;
    default:
        return " ERR";
    }
}
