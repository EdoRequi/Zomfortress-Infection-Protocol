#include "Emotes.h"
using namespace std;
char KazotskyKick(int w,int i,int j,const Player &gracz){
    switch(gracz.Klasa){
    case TR::DEMOMAN:{
        switch(gracz.obecna_klatka){
        case 0:case 2:case 4:case 6:case 15:{
                            if(i==w-6){
                                switch (j){
                                    case 5:
                                        koloruj(0,8);
                                        return '_';
                                    case 6:
                                        koloruj(4,8);
                                        return 'O';
                                        break;
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-5){
                                switch (j){
                                    case 4: case 6:
                                        koloruj(12,8);
                                        return '|';
                                    case 7:
                                        koloruj(12,8);
                                        return '\\';
                                        break;
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-4){
                                switch (j){
                                    case 4:
                                        koloruj(15,8);
                                        return 'L';
                                    case 6:
                                        koloruj(12,8);
                                        return '|';
                                    case 8:
                                        koloruj(15,8);
                                        return '\\';
                                        break;
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-3){
                                switch (j){
                                    case 5:case 7:case 8:koloruj(12,8);return '_';
                                        case 9:koloruj(0,8);
                                        return '_';
                                    case 6:
                                        koloruj(12,8);
                                        return '|';
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-2){
                                switch (j){
                                    case 4:
                                        koloruj(12,8);
                                        return '|';
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-1){
                                switch (j){
                                    case 4:
                                        koloruj(0,8);
                                        return '|';
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                    else return ' ';}
                    case 1:case 3:case 5:case 7:case 16:{
                        if(i==w-6){
                            switch (j){
                                case 8:
                                    koloruj(4,8);
                                    return 'O';
                                default:
                                    return ' ';
                                    break;
                                }
                        }
                            if(i==w-5){
                                switch (j){
                                    case 7:
                                        koloruj(12,8);
                                        return '|';
                                    case 8:
                                        koloruj(0,8);
                                        return '|';
                                    case 9:
                                        koloruj(12,8);
                                        return '\\';
                                        break;
                                    case 10:
                                        koloruj(15,8);
                                        return '/';
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-4){
                                switch (j){
                                    case 7:
                                        koloruj(12,8);
                                        return char(192);
                                    case 8:
                                        koloruj(0,8);
                                        return char(136);
                                    case 10:
                                        koloruj(15,8);
                                        return '\\';
                                        break;
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-3){
                                switch (j){
                                    case 6:case 7:case 9:koloruj(12,8);return '_';
                                        case 5:koloruj(0,8);
                                        return '_';
                                    case 8:
                                        koloruj(12,8);
                                        return '|';
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-2){
                                switch (j){
                                    case 10:
                                        koloruj(12,8);
                                        return '|';
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                            if(i==w-1){
                                switch (j){
                                    case 10:
                                        koloruj(0,8);
                                        return '|';
                                    default:
                                        return ' ';
                                        break;
                                }
                            }
                        else return ' ';}
            case 8:case 10:case 12:case 14:{
                if(i==w-5){
                    switch(j){
                        case 7:koloruj(15,8);return '/';case 13:koloruj(0,8);return '/';
                        default: return ' ';
                    }
                }
                if(i==w-4){
                    switch(j){
                        case 6:case 12:koloruj(12,8);return '/';
                        default: return ' ';
                    }
                }
                if(i==w-3){
                    switch(j){
                        case 4:koloruj(4,8);return 'O';
                        case 5:koloruj(0,8);return char(197);
                        case 6:case 7: koloruj(0,8);return char(196);
                        case 8:case 9:koloruj(12,8);return char(196);
                        default: return ' ';
                    }
                }
                if(i==w-2){
                    switch(j){
                        case 6:koloruj(12,8); return '|';
                        case 12:koloruj(12,8);return '\\';
                        default: return ' ';
                    }
                }
                if(i==w-1){
                    switch(j){
                        case 6:koloruj(15,8); return '|';case 12:koloruj(0,8); return '|';
                        default: return ' ';
                    }
                }
                else return ' ';}
                case 9:case 11:case 13:{
                if(i==w-5){
                    switch(j){
                        case 6:koloruj(15,8);return '/';case 12:koloruj(0,8);return '/';
                        default: return ' ';
                    }
                }
                if(i==w-4){
                    switch(j){
                        case 5:case 11:koloruj(12,8);return '/';
                        default: return ' ';
                    }
                }
                if(i==w-3){
                    switch(j){
                        case 4:koloruj(4,8);return 'O';
                        case 5:koloruj(0,8);return char(197);
                        case 6:case 7: koloruj(0,8);return char(196);
                        case 8:case 9:koloruj(12,8);return char(196);
                        default: return ' ';
                    }
                }
                if(i==w-2){
                    switch(j){
                        case 7:koloruj(12,8); return '|';
                        case 12:koloruj(12,8);return '\\';
                        default: return ' ';
                    }
                }
                if(i==w-1){
                    switch(j){
                        case 7:koloruj(15,8); return '|';case 13:koloruj(0,8); return '|';
                        default: return ' ';
                    }
                }
            else return ' ';}
        default: return ' ';
        break;}
        }
    }
}
