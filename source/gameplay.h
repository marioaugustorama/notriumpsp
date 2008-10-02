#include "grass.h"
void gameplay() {
    //Mapa ci�g dalszy
	grass = oslCreateMap(
		trawa,						//Tileset
		grass_map,						//Map
		16,16,							//Size of tiles
		32,33,							//Size of Map
		OSL_MF_U16);						//Format of Map
    grass->scrollY += 20;
    MP3_Stop(); 
    MP3_FreeTune();
    MP3_Load("/data/music/bgm1.mp3");
    MP3_Play(); 
    hits = 0;
    while(1) {
             // Rozpocznij rysowanie i odczytaj stan przycisk�w.
             oslStartDrawing();
             oslCls();
             oslReadKeys();
             //"W��cz system �mierci
       if (heroHP == 0) {
       break;
       }
             // Wy��cz gr� przy wci�ni�ciu start.
             if (osl_keys->pressed.start)
               {  MP3_Stop(); MP3_FreeTune(); oslQuit(); }
             // Zresetuj pozycj� gracza przy wci�ni�ciu select.
             if (osl_keys->pressed.select)
               { herox=480; heroy=272; herodirection=0; }
             // Pauzuj/w��czaj muze
             if (osl_keys->pressed.triangle)
                { MP3_Pause(); }
             // Narysuj szary prostok�t na t�o.
             oslDrawMap(grass);
             // Wy�rodkuj ekran na bohaterze.
             view_xview=herox-240;
             view_yview=heroy-136;
             // Akcje zwi�zane z herosem.
             hero_init();
             // "W��cz" obiekty.
             objects_init();
             // Skonfiguruj czcionk�.
             oslSetTextColor(RGBA(0,0,0,255));
             oslSetBkColor(RGBA(0,0,0,0));
             // Narysuj dane na ekranie.
             oslPrintf_xy(8,8,"Press start to exit.");
             oslPrintf_xy(8,16,"Press select to reset your position.");
             oslPrintf_xy(8,24,"Press triangle to pause/resume the music.");
             oslPrintf_xy(8,32,"Player Hp: %d", heroHP);
             // Sko�cz rysowanie.
		     oslEndDrawing();
		     oslSyncFrame();
             }
       oslCls();
       MP3_Stop(); 
       MP3_FreeTune();
       oslDrawImage(death);
       oslSetTextColor(RGBA(255,255,255,255));
       oslSetBkColor(RGBA(0,0,0,0));   
       oslPrintf_xy(3,4,"You are dead.");
       oslPrintf_xy(3,4+8,"Press any key to contiune.");
       oslEndDrawing();
       oslSyncFrame();
       oslWaitKey();
       title_screen();
}

void hero_init() {
    // Je�li gracz trzyma strza�k� w lewo...
    if (osl_keys->held.left) {
                             // ...gracz obraca si� w lewo.
                             herodirection+=5;
                             }
    // Analogicznie w prawo.
    if (osl_keys->held.right) {
                             herodirection-=5;
                             }
    // Je�li gracz trzyma strza�k� w g�r�...
    if (osl_keys->held.up) {
                              // ...idzie do przodu.
                              herox+=cos(herodirection*3.1415/180)*3;
                              heroy-=sin(herodirection*3.1415/180)*3;
                              if(oslGetSoundChannel(steps) == -1) { oslPlaySound(steps, 2);	}
                              }
    // Je�li gracz trzyma strza�k� w d�...
    if (osl_keys->held.down) {
                              // ...cofa si�.
                              herox-=cos(herodirection*3.1415/180)*2;
                              heroy+=sin(herodirection*3.1415/180)*2;
                              if(oslGetSoundChannel(steps) == -1) { oslPlaySound(steps, 2);	}
                              }
    // Je�li gracz wcisn�� X...
    if (osl_keys->held.cross) {
                              // ...strzela z broni (UWAGA! Narazie TYLKO z Tazora i tylko odtwarzany dzwiek.)
        if(oslGetSoundChannel(tazor) == -1) { oslPlaySound(tazor, 3);	}
                              }
    if (osl_keys->held.square) { heroHP=0;}
    // Ograniczenia herodirection.
    if(herodirection<0) herodirection+=360;
    if(herodirection>=360) herodirection-=360;
    // Narysuj bohatera w �rodku ekranu.
    hero->x=240;
    hero->y=136;
    hero->angle=-herodirection+90;
    oslDrawImage(hero);
}

void object_init(int wino) {
    // Je�li obiekt jest blokiem
    if(obj_i[wino]==1) {
                 // Je�li blok nie jest poza ekranem...
                 if(obj_x[wino]-view_xview>-64 && obj_x[wino]-view_xview<480 && obj_y[wino]-view_yview>-64 && obj_y[wino]-view_yview<272) {
                   // Narysuj blok.
                   blok->x=obj_x[wino]-view_xview;
                   blok->y=obj_y[wino]-view_yview;
                   oslDrawImage(blok);
                   }
                 // Je�li gracz dotyka prawej kraw�dzi bloku...
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]+64 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to w ni� nie wejdzie.
                                         herox=obj_x[wino]+76;
                                         }
                 // Analogicznie do innych kraw�dzi.
                 if(herox<obj_x[wino] && herox>obj_x[wino]-12 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to w ni� nie wejdzie.
                                         herox=obj_x[wino]-12;
                                         }
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]-12 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]) {
                                         // ...to w ni� nie wejdzie.
                                         heroy=obj_y[wino]-12;
                                         }
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]-12 && heroy>obj_y[wino]+64 && heroy<obj_y[wino]+76) {
                                         // ...to w ni� nie wejdzie.
                                         heroy=obj_y[wino]+76;
                                         }
                 }
    if(obj_i[wino]==2) {
                 // Je�li kolec nie jest poza ekranem...
                 if(obj_x[wino]-view_xview>-64 && obj_x[wino]-view_xview<480 && obj_y[wino]-view_yview>-64 && obj_y[wino]-view_yview<272) {
                   // Narysuj kolec.
                   lava->x=obj_x[wino]-view_xview;
                   lava->y=obj_y[wino]-view_yview;
                   oslDrawImage(lava);
                   }
                 // Je�li gracz dotyka prawej kraw�dzi kolca...
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]+64 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to dostanie obra�enia.
                         if (heroHP == 0) { 
                                    }else {
                                    heroHP=heroHP-10;
                                    }
                         if(hits == 0) {
                             if(oslGetSoundChannel(boli0) == -1) { oslPlaySound(boli0, 0); }
                             hits=hits+1;            
                         }else if(hits == 1) {
                                             if(oslGetSoundChannel(boli1) == -1) { oslPlaySound(boli1, 0); }
                             hits=hits+1;
                         }else if(hits == 2) {
                                             if(oslGetSoundChannel(boli2) == -1) { oslPlaySound(boli2, 0); }
                             hits=0;
                         }
                             }
                 // Analogicznie do innych kraw�dzi.
                 if(herox<obj_x[wino] && herox>obj_x[wino]-12 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to dostanie obra�enia.
                         if (heroHP == 0) { 
                                    }else {
                                    heroHP=heroHP-10;
                                    }
                         if(hits == 0) {
                             if(oslGetSoundChannel(boli0) == -1) { oslPlaySound(boli0, 0); }
                             hits=hits+1;            
                         }else if(hits == 1) {
                                             if(oslGetSoundChannel(boli1) == -1) { oslPlaySound(boli1, 0); }
                             hits=hits+1;
                         }else if(hits == 2) {
                                             if(oslGetSoundChannel(boli2) == -1) { oslPlaySound(boli2, 0); }
                             hits=0;
                         }
                                         }
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]-12 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]) {
                                         // ...to dostanie obra�enia.
                         if (heroHP == 0) { 
                                    }else {
                                    heroHP=heroHP-10;
                                    }
                         if(hits == 0) {
                             if(oslGetSoundChannel(boli0) == -1) { oslPlaySound(boli0, 0); }
                             hits=hits+1;            
                         }else if(hits == 1) {
                                             if(oslGetSoundChannel(boli1) == -1) { oslPlaySound(boli1, 0); }
                             hits=hits+1;
                         }else if(hits == 2) {
                                             if(oslGetSoundChannel(boli2) == -1) { oslPlaySound(boli2, 0); }
                             hits=0;
                         }
                                         }
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]-12 && heroy>obj_y[wino]+64 && heroy<obj_y[wino]+76) {
                                         // ...to dostanie obra�enia.
                         if (heroHP == 0) { 
                                    }else {
                                    heroHP=heroHP-10;
                                    }
                         if(hits == 0) {
                             if(oslGetSoundChannel(boli0) == -1) { oslPlaySound(boli0, 0); }
                             hits=hits+1;            
                         }else if(hits == 1) {
                                             if(oslGetSoundChannel(boli1) == -1) { oslPlaySound(boli1, 0); }
                             hits=hits+1;
                         }else if(hits == 2) {
                                             if(oslGetSoundChannel(boli2) == -1) { oslPlaySound(boli2, 0); }
                             hits=0;
                         }
                                         }
                 }
}

void objects_init() {
    object_init(0);
    object_init(1);
    object_init(2);
    object_init(3);
    object_init(4);
    object_init(5);
    object_init(6);
    object_init(7);
    object_init(8);
    object_init(9);
    object_init(10);
}
