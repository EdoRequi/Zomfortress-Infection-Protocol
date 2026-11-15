#include<iostream>
#include "SoundManagement.h"
using Tx=TextID;
using namespace std;
void dzwiek(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_ASYNC);
}
void dzwiek_loop(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_LOOP | SND_ASYNC);
}
void dzwiek_ciagly(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_SYNC);
}
