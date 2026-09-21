#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <vector>
#include <memory>
#include <chrono>
#include <sstream>

namespace std{
    namespace ZaWarudo=chrono;
}
inline short IDwybor=0;
inline short WCzcionki=14;
struct NonLivingObject{
    virtual ~NonLivingObject()=default;
};
enum class Globalne{
    NONE,
    SHOP,
    FLASH,
    DEATH
};
enum class CritMode{
    NONE,
    RANDOM,
    FORCED
};
struct Character;
struct DamageResult{
    Character* cel=nullptr;
    int obrazenia=0;
    bool krytyczne=false;
    bool bitesthedust=false;//JoJo fans will know
};
struct MultiDamageResult{
    std::vector<DamageResult> Eksplozja;
};
enum class TypRoli{
    NONE,

    DEMOMAN
};
enum class TypAkcji{
    NO_ACTION,
    ACTION1,
    ACTION2,
    ACTION3,
    SPECIAL,
    ACTION_USED_ITEM,
    ACTION_EMOTE
};
enum class Language{
    NONE,

    POLSKI,
    ANGIELSKI
};
struct WyboryAkcji{
    std::string napis;
};
enum class TextID{
    UnListed,

    Error_info, Error_info_IndexOutOfBounds,Error_noItem,Error_noFunds,Error_noSP,Error_maxLevel,Error_WrongKey,Error_nope_tf2reference,Error_targetnotvalid,Error_NullPointer,Error_AlreadyHaveIt,
    Wave_info, Turn_info,
    Deb_info_EnAdress, Deb_gen,Deb_highest_localHP,
    Tag_direction_Info,Tag_PLAYER, Tag_BUILD, Tag_ENEMY,
    I_Sword,I_SBLauncher,I_Shield,I_Scrumpy,I_flashbang,I_phone,//16 Pro
    I_earplugs,
    Name_FastZ,Name_TitanZ,Name_ToxicZ,Name_ElecZ,Name_ExplZ,Name_CommandZ,Name_Sentry,Name_Dispenser,
    But_PLAY1, But_PLAY2, But_Sett,
    Sw_ENDEBUG,Sw_FONTSIZE,
    Quantity, Bought_Item, Cost_info,Quantity_info,
    Level_info, Used_info_Sword,Used_info_SBLauncher,Used_info_Shield,Used_info_Scrumpy,Used_info_Flashbang,Used_info_phone,
    Sword_resistance,Sword_info_heads,
    SBL_bomb_info, SBL_nobombs,
    Shield_SPGain,
    Scrumpy_HPGain, Scrumpy_Drunk,Scrumpy_DrunkMaintained,
    Flashbang_stun_info,
    Phone1,Phone2,Phone2_accepted,Phone2_rejected,Phone3,Phone_achievement_wastingSP,
    Caber_result,Caber_SDestroyed,Caber_DDestroyed,Caber_UnTouched,Caber_Touched,

    TurnsRemaining,

    EachAndEveryoneWillBeSentHomeToYourMommaInABox, //Soldier response
    EnemyDefeated,EnemiesDefeated,
    Demo_response_drunk1,Demo_response_drunk2,Demo_response_drunk3,Demo_response_drunk4,Demo_response_drunk5,Demo_response_drunk6,
    Demo_response_Caber1,Demo_response_Caber2,Demo_response_Caber3,
    Demo_response_UsedCaber,Demo_response_win,Demo_response_win2,Demo_response_jeer,Demo_response_jeer2,Demo_response_jeer3,
    Demo_response_dom,Demo_response_dom2,Demo_response_laugh,Demo_response_glue,
    Demo_response_Scrumpy,
    Demo_NoSuffer_CUZ_HE_IS_DRUNK,

    Obj_IsStunned,Obj_Is,Obj_IsDeactivated,Obj_IsPowered,Obj_IsPoisoned,Obj_StoppedWorking,Obj_SufferedStrongAttack,Obj_NoSuffer,Obj_Miss,Obj_Miss2,Obj_DealsCrit,Obj_Destroyed,
    Defeat_info,
    Dispenser_heal,
    Comm_Crits,Comm_response_regroup,
    Elec_StrengthCast,Elec_Attack,Elec_Overdrive,
    Toxic_YOMUMFAT,Toxic_YOMUMSTUPID,Toxic_YOMUMUGLY,
    Toxic_YOMUM1,Toxic_YOMUM2,Toxic_YOMUM3,Toxic_YOMUM3_1,Toxic_YOMUM4,Toxic_YOMUM4_1,Toxic_YOMUM5,Toxic_YOMUM6,Toxic_YOMUM6_1,Toxic_YOMUM6_2,Toxic_YOMUM6_3,Toxic_YOMUM7,Toxic_YOMUM8,
    Toxic_YOMUMDEFAULT1,Toxic_YOMUMDEFAULT2,
    SucceededOffend,FailedOffend,
    DoYouWantToQuit, HolyNumberAcquire,
    Toxic_Spit, Toxic_PoisonSuccess,Toxic_PoisonFails,
    Expl_Counter,Expl_Warning1,Expl_Warning2,Expl_WarningFatal,Expl_Miss1,Expl_Miss1_1,Expl_Miss2,Expl_Miss2_1,
    X_for_exit,X_for_continue,X_for_continue2,
    Eff_info,Eff_Stun,Eff_Drunk,Eff_Powered,Eff_Poisoned,Eff_Weakness,Eff_MoreCritrate,
    Shop_Sh,Shop_SBL,Shop_Sw,Shop_Fl,Shop_Phone,Shop_Ear,
    Action_info_offensive,Action_info_support,Action_info_equipment, Demo_actions_offensive_Sword,Demo_actions_offensive_SBL,Demo_actions_offensive_specialAttack,
    Demo_actions_support_Scrumpy,Demo_actions_support_Shield,
    Name_Engineer,
    GAMEOVER
};
class Localization{
    private://Dominated, private Twinkle Toes!
        Language jezyk;
    public:
        Localization(Language lang):jezyk(lang)
        {}
        void setLanguage(Language lang){
            jezyk=lang;
        }
        Language whatLanguage()const;
        std::string get(TextID id) const;

};
inline Localization L(Language::NONE);
struct Settings{
    short &IDwybor;
    short &WCzcionki;
    Localization &L;
};
inline Settings S={IDwybor,WCzcionki,L};
struct Player;
struct ScreenEfekt
{
    enum Rodzaj
    {
        NONE,
        HIT,
        CRITICAL,
        MISS,
        POISON,
        ELECTRIC,
        HEAL
    };

    Rodzaj R = NONE;
};
struct Gamecontent{
    Settings &S;
    const bool &debug;
    Player &gracz;
    std::vector<Character*> &enemies;
    std::vector<std::unique_ptr<NonLivingObject>> &Obiekty;
    Character* &dzialko;
    Character* &zasobnik;
    long &x; //runda
    int &wskazany;
    bool &smigniecie;
    Globalne &Wydarzenie;
    bool &wybor;
    bool &dlacase;
    std::vector<Character*> &affectedT;
    std::vector<DamageResult> &dane;
    ScreenEfekt SE;
    bool &kolejComm;
    std::chrono::steady_clock::time_point &CzasTrwania;

};
void koloruj(int fg,int bg);
void ReturnToZero(Gamecontent& Gc);
void aktualizuj_efekt(Gamecontent &Gc);
MultiDamageResult nowyMDR(std::vector<DamageResult> multi);
void configureConsoleInput();
#endif // GAMELOGIC_H_INCLUDED
