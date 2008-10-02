// Notrium by Herby, 2008
// Jaklub kolizje, Herby reszta rzeczy zaprogramowali

#include <oslib/oslib.h>
#include <pspcallbacks.h>

PSP_MODULE_INFO("Notrium", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// Floaty potrzebne do dzia³ania gry.
// herox - pozycja x bohatera
// heroy - pozycja y bohatera
// herodirection - k¹t obrócenia bohatera
// obj_x[10] - pozycja x obiektu
// obj_y[10] - pozycja y obiektu
// obj_i[10] - id rodzaju objektu (1 - blok, ka¿de mniejsze lub wiêksze - nic)
// view_xview - dla wygody (scroll x)
float herox, heroy, herodirection, obj_x[10], obj_y[10], obj_i[10], view_xview, view_yview;
int heroHP;
// Obrazki (sprity) do gry.
// menu - ekran tytu³owy
// blok - symboliczny blok do testowania kolizji
// hero - bohater
OSL_IMAGE *menu, *blok, *hero, *trawa, *death, *lava;
//Muzyka do gry - pliki mp3, ³adowane z mp3playera
//Dzwieki do gry - pliki wav, ³adowane z osliba
OSL_SOUND *steps, *tazor, *boli0, *boli1, *boli2;
// Mapaa!!!
OSL_MAP *grass;
#include <oslib/oslib.h>
#include "mp3player.h"
int hits;
#include "menu.h"
#include "gameplay.h"
int main(int argc, char* argv[])
{
    // Standardowe procedury OSliba.
	oslInit(OSL_IF_USEOWNCALLBACKS);
	SetupCallbacks();
	oslInitGfx(OSL_PF_8888, 1);
	oslInitConsole();
    oslInitAudio();
    pspAudioInit();
    MP3_Init(1);
	//Narysuj napis "Notrium Loading" w kolorze jaskrawo¿ó³tym (RGB 255, 255 ,0) i wczytaj potrzebne pliki.
	oslStartDrawing();
	oslSetTextColor(RGBA(255,255,255,255));
	oslSetBkColor(RGBA(0,0,0,0));
	oslPrintf("Notrium Loading...");
	oslPrintf("Loading Graphics...");
	oslSyncFrame();
	oslSetQuitOnLoadFailure(1);
    
    menu = oslLoadImageFile("/data/menu.png", OSL_IN_RAM, OSL_PF_5551);
    hero = oslLoadImageFile("/data/texture/hero.png", OSL_IN_RAM, OSL_PF_5551);
    blok = oslLoadImageFile("/data/texture/blok.png", OSL_IN_RAM, OSL_PF_5551);
    trawa = oslLoadImageFile("/data/texture/grasstileset.png", OSL_IN_RAM, OSL_PF_5551);
    death = oslLoadImageFile("/data/death.png", OSL_IN_RAM, OSL_PF_5551);
    lava = oslLoadImageFile("/data/texture/lava.png", OSL_IN_RAM, OSL_PF_5551);
    
    oslPrintf("Loading Sounds...");
    steps = oslLoadSoundFile("/data/music/steps.wav", OSL_FMT_NONE);
    tazor = oslLoadSoundFile("/data/music/tazor.wav", OSL_FMT_NONE);
    boli0 = oslLoadSoundFile("/data/music/grunt0.wav", OSL_FMT_NONE);
    boli1 = oslLoadSoundFile("/data/music/grunt1.wav", OSL_FMT_NONE);
    boli2 = oslLoadSoundFile("/data/music/grunt2.wav", OSL_FMT_NONE);
    
    oslPrintf("Done. Starting game...");
    //Skonfiguruj obrazek hero do swobodnego obracania.
    
    hero->centerX = hero->sizeX / 2;
    hero->centerY = hero->sizeY / 2;
    
    //W³¹cz ekran tytu³owy.
    title_screen();
    
    //Koniec aplikacji.
	oslQuit();
	return 0;
}
