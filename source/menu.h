void title_screen() {
      MP3_Load("/data/music/menu.mp3");
      MP3_Play();
      // Rozpocznij rysowanie i odczytaj stan przycisków.
      oslStartDrawing();
      oslReadKeys();
      // Narysuj ekran tytu³owy.
      oslDrawImage(menu);
      // Skonfiguruj czcionkê.
      oslSetTextColor(RGBA(255,255,255,255));
      oslSetBkColor(RGBA(0,0,0,0));
      // Napisz na ekranie napisy.
      oslPrintf_xy(53,90,"Notrium 0.1");
      oslPrintf_xy(53,90+8,"2008");
      oslPrintf_xy(53,90+16,"Authors:");
      oslPrintf_xy(53,90+24,"Herby - programming");
      oslPrintf_xy(53,90+32,"Jaklub - collisions");
      oslPrintf_xy(53,90+40,"Press cross to play.");
      oslPrintf_xy(53,90+48,"Press triangle to exit.");
      // Skoñcz rysowanie.
      oslEndDrawing();
      oslSyncFrame();
      oslWaitKey();
             // Jeœli gracz wcisn¹³ trójk¹t...
             if (osl_keys->pressed.triangle)
               {
               // ...wy³¹cz grê.
               oslQuit();
               }
             // Jeœli gracz wcisn¹³ krzy¿yk...
             if (osl_keys->pressed.cross)
               {
               // ustaw pozycjê herosa.
               herox=480;
               heroy=272;
               // ustaw obiekty.
               obj_x[0]=256;
               obj_y[0]=256;
               obj_i[0]=1;
               obj_x[1]=512;
               obj_y[1]=512;
               obj_i[1]=1;
               obj_x[2]=512;
               obj_y[2]=256;
               obj_i[2]=1;
               obj_x[3]=256;
               obj_y[3]=512;
               obj_i[3]=1;
               obj_x[4]=320;
               obj_y[4]=576;
               obj_i[4]=2;
               heroHP=100;
               // w³¹cz grê.
               gameplay();
               }
               
}
