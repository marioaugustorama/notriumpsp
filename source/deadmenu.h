void dead_menu() {
      int option = 0;
      MP3_Load("/data/music/menu.mp3");
      MP3_Play();
    while(option == 0) {
             // Rozpocznij rysowanie i odczytaj stan przycisk�w.
             oslStartDrawing();
             oslReadKeys();
             // Narysuj ekran tytu�owy.
             oslDrawImage(death);
             // Je�li gracz wcisn�� tr�jk�t...
             if (osl_keys->pressed.triangle)
               {
               // ...wy��cz gr�.
               oslQuit();
               }
             // Je�li gracz wcisn�� krzy�yk...
             if (osl_keys->pressed.cross)
               {
               option = 1;
               // ustaw pozycj� herosa.
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
               obj_x[4]=288;
               obj_y[4]=544;
               obj_i[4]=2;
               // w��cz gr�.
               gameplay();
               }
               // Skonfiguruj czcionk�.
	           oslSetTextColor(RGBA(255,255,255,255));
	           oslSetBkColor(RGBA(0,0,0,0));
	           // Napisz na ekranie napisy.
	           oslPrintf_xy(53,90,"Notrium 0.1");
	           oslPrintf_xy(53,90+8,"2008");
	           oslPrintf_xy(53,90+40,"Press cross to restart game.");
	           oslPrintf_xy(53,90+48,"Press triangle to exit.");
             // Sko�cz rysowanie.
		     oslEndDrawing();
		     oslSyncFrame();
             }
}
