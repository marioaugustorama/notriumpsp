#include "grass.h"
void gameplay() {
    //Mapa ci¹g dalszy
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
             // Rozpocznij rysowanie i odczytaj stan przycisków.
             oslStartDrawing();
             oslCls();
             oslReadKeys();
             //"W³¹cz system œmierci
       if (heroHP == 0) {
       break;
       }
             // Wy³¹cz grê przy wciœniêciu start.
             if (osl_keys->pressed.start)
               {  MP3_Stop(); MP3_FreeTune(); oslQuit(); }
             // Zresetuj pozycjê gracza przy wciœniêciu select.
             if (osl_keys->pressed.select)
               { herox=480; heroy=272; herodirection=0; }
             // Pauzuj/w³¹czaj muze
             if (osl_keys->pressed.triangle)
                { MP3_Pause(); }
             // Narysuj szary prostok¹t na t³o.
             oslDrawMap(grass);
             // Wyœrodkuj ekran na bohaterze.
             view_xview=herox-240;
             view_yview=heroy-136;
             // Akcje zwi¹zane z herosem.
             hero_init();
             // "W³¹cz" obiekty.
             objects_init();
             // Skonfiguruj czcionkê.
             oslSetTextColor(RGBA(0,0,0,255));
             oslSetBkColor(RGBA(0,0,0,0));
             // Narysuj dane na ekranie.
             oslPrintf_xy(8,8,"Press start to exit.");
             oslPrintf_xy(8,16,"Press select to reset your position.");
             oslPrintf_xy(8,24,"Press triangle to pause/resume the music.");
             oslPrintf_xy(8,32,"Player Hp: %d", heroHP);
             // Skoñcz rysowanie.
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
    // Jeœli gracz trzyma strza³kê w lewo...
    if (osl_keys->held.left) {
                             // ...gracz obraca siê w lewo.
                             herodirection+=5;
                             }
    // Analogicznie w prawo.
    if (osl_keys->held.right) {
                             herodirection-=5;
                             }
    // Jeœli gracz trzyma strza³kê w górê...
    if (osl_keys->held.up) {
                              // ...idzie do przodu.
                              herox+=cos(herodirection*3.1415/180)*3;
                              heroy-=sin(herodirection*3.1415/180)*3;
                              if(oslGetSoundChannel(steps) == -1) { oslPlaySound(steps, 2);	}
                              }
    // Jeœli gracz trzyma strza³kê w dó³...
    if (osl_keys->held.down) {
                              // ...cofa siê.
                              herox-=cos(herodirection*3.1415/180)*2;
                              heroy+=sin(herodirection*3.1415/180)*2;
                              if(oslGetSoundChannel(steps) == -1) { oslPlaySound(steps, 2);	}
                              }
    // Jeœli gracz wcisn¹³ X...
    if (osl_keys->held.cross) {
                              // ...strzela z broni (UWAGA! Narazie TYLKO z Tazora i tylko odtwarzany dzwiek.)
        if(oslGetSoundChannel(tazor) == -1) { oslPlaySound(tazor, 3);	}
                              }
    if (osl_keys->held.square) { heroHP=0;}
    // Ograniczenia herodirection.
    if(herodirection<0) herodirection+=360;
    if(herodirection>=360) herodirection-=360;
    // Narysuj bohatera w œrodku ekranu.
    hero->x=240;
    hero->y=136;
    hero->angle=-herodirection+90;
    oslDrawImage(hero);
}

void object_init(int wino) {
    // Jeœli obiekt jest blokiem
    if(obj_i[wino]==1) {
                 // Jeœli blok nie jest poza ekranem...
                 if(obj_x[wino]-view_xview>-64 && obj_x[wino]-view_xview<480 && obj_y[wino]-view_yview>-64 && obj_y[wino]-view_yview<272) {
                   // Narysuj blok.
                   blok->x=obj_x[wino]-view_xview;
                   blok->y=obj_y[wino]-view_yview;
                   oslDrawImage(blok);
                   }
                 // Jeœli gracz dotyka prawej krawêdzi bloku...
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]+64 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to w ni¹ nie wejdzie.
                                         herox=obj_x[wino]+76;
                                         }
                 // Analogicznie do innych krawêdzi.
                 if(herox<obj_x[wino] && herox>obj_x[wino]-12 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to w ni¹ nie wejdzie.
                                         herox=obj_x[wino]-12;
                                         }
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]-12 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]) {
                                         // ...to w ni¹ nie wejdzie.
                                         heroy=obj_y[wino]-12;
                                         }
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]-12 && heroy>obj_y[wino]+64 && heroy<obj_y[wino]+76) {
                                         // ...to w ni¹ nie wejdzie.
                                         heroy=obj_y[wino]+76;
                                         }
                 }
    if(obj_i[wino]==2) {
                 // Jeœli kolec nie jest poza ekranem...
                 if(obj_x[wino]-view_xview>-64 && obj_x[wino]-view_xview<480 && obj_y[wino]-view_yview>-64 && obj_y[wino]-view_yview<272) {
                   // Narysuj kolec.
                   lava->x=obj_x[wino]-view_xview;
                   lava->y=obj_y[wino]-view_yview;
                   oslDrawImage(lava);
                   }
                 // Jeœli gracz dotyka prawej krawêdzi kolca...
                 if(herox<obj_x[wino]+76 && herox>obj_x[wino]+64 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to dostanie obra¿enia.
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
                 // Analogicznie do innych krawêdzi.
                 if(herox<obj_x[wino] && herox>obj_x[wino]-12 && heroy>obj_y[wino]-12 && heroy<obj_y[wino]+76) {
                                         // ...to dostanie obra¿enia.
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
                                         // ...to dostanie obra¿enia.
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
                                         // ...to dostanie obra¿enia.
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
