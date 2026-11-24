#include "Controls.h"
#include <conio.h>
#include <windows.h>
using namespace std;

void wyczyscBufor(){
    while(_kbhit()){
        _getch();
    }
}
void configureConsoleInput()
{
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    if (!GetConsoleMode(h, &mode)) {
        return;
    }
    mode |= ENABLE_EXTENDED_FLAGS;
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode &= ~ENABLE_MOUSE_INPUT;

    SetConsoleMode(h, mode);
    wyczyscBufor();
}
