#ifndef SOUNDMANAGEMENT_H
#define SOUNDMANAGEMENT_H
#include <windows.h>
//dziwekowe
inline void dzwiek(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_ASYNC);
}
inline void dzwiek_loop(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_LOOP | SND_ASYNC);
}
inline void dzwiek_ciagly(const char* sciezka)
{
    PlaySound(TEXT(sciezka),NULL,SND_FILENAME| SND_SYNC);
}

#endif // SOUNDMANAGEMENT_H_INCLUDED
