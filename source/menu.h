void menu(int value) {
     // Rozpocznij rysowanie i odczytaj stan przycisk�w.
      oslStartDrawing();
      oslReadKeys();
      // Narysuj ekran tytu�owy.
      oslDrawImage(menuimg);
      
      if (value == 0) {
      // Skonfiguruj czcionk�.
      oslSetTextColor(RGBA(255,255,255,255));
      oslSetBkColor(RGBA(0,0,0,0));
      // Napisz na ekranie napisy.
      oslPrintf_xy(53,90,"Notrium");
      oslPrintf_xy(53,90+16,"Credits");
      oslPrintf_xy(53,90+24,"Exit");
      oslSetTextColor(RGBA(239,221,19,255));
      oslSetBkColor(RGBA(0,0,0,0));
      oslPrintf_xy(53,90+8,"New Game");
      // Sko�cz rysowanie.
      oslEndDrawing();
      oslSyncFrame();
      oslWaitKey();
      // Je�li gracz wcisn�� tr�jk�t...
      if (osl_keys->pressed.down)
      {
      menu(1);                           
      }
      if (osl_keys->pressed.up)
      {
      menu(2);
      }
      // Je�li gracz wcisn�� krzy�yk...
      if (osl_keys->pressed.cross)
      {
      yourchoice(0);
      } else {}
      
      
      } else if (value == 1) {
      // Skonfiguruj czcionk�.
      oslSetTextColor(RGBA(255,255,255,255));
      oslSetBkColor(RGBA(0,0,0,0));
      // Napisz na ekranie napisy.
      oslPrintf_xy(53,90,"Notrium");
      oslPrintf_xy(53,90+8,"New Game");
      oslPrintf_xy(53,90+24,"Exit");
      oslSetTextColor(RGBA(239,221,19,255));
      oslSetBkColor(RGBA(0,0,0,0));
      oslPrintf_xy(53,90+16,"Credits");
      // Sko�cz rysowanie.
      oslEndDrawing();
      oslSyncFrame();
      oslWaitKey();
      // Je�li gracz wcisn�� tr�jk�t...
      if (osl_keys->pressed.down)
      {
      menu(2);                           
      }
      if (osl_keys->pressed.up)
      {
      menu(0);
      }
      // Je�li gracz wcisn�� krzy�yk...
      if (osl_keys->pressed.cross)
      {
      yourchoice(1);
      } else {}
      
      
      
      
      } else if (value == 2) {
      // Skonfiguruj czcionk�.
      oslSetTextColor(RGBA(255,255,255,255));
      oslSetBkColor(RGBA(0,0,0,0));
      // Napisz na ekranie napisy.
      oslPrintf_xy(53,90,"Notrium");
      oslPrintf_xy(53,90+8,"New Game");
      oslPrintf_xy(53,90+16,"Credits");
      oslSetTextColor(RGBA(239,221,19,255));
      oslSetBkColor(RGBA(0,0,0,0));
      oslPrintf_xy(53,90+24,"Exit");
      // Sko�cz rysowanie.
      oslEndDrawing();
      oslSyncFrame();
      oslWaitKey();
      // Je�li gracz wcisn�� tr�jk�t...
      if (osl_keys->pressed.down)
      {
      menu(0);                           
      }
      if (osl_keys->pressed.up)
      {
      menu(1);
      }
      // Je�li gracz wcisn�� krzy�yk...
      if (osl_keys->pressed.cross)
      {
      yourchoice(2);
      } else {}
      
      
      } else if (value == 3) {
             // Skonfiguruj czcionk�.
      oslSetTextColor(RGBA(255,255,255,255));
      oslSetBkColor(RGBA(0,0,0,0));
      // Napisz na ekranie napisy.
      oslPrintf_xy(53,90,"Authors:");
      oslPrintf_xy(53,90+8,"Herby - programming");
      oslPrintf_xy(53,90+16,"Jaklub - collisions");
      oslPrintf_xy(53,90+24,"Sky - help");
      oslSetTextColor(RGBA(239,221,19,255));
      oslSetBkColor(RGBA(0,0,0,0));
      oslPrintf_xy(53,90+32,"Back");
      // Sko�cz rysowanie.
      oslEndDrawing();
      oslSyncFrame();
      oslWaitKey();
      if (osl_keys->pressed.cross) { menu(0); }
      } else {}
      }






void title_screen() {
      MP3_Load("/data/music/menu.mp3");
      MP3_Play();
      // Rozpocznij rysowanie i odczytaj stan przycisk�w.
      oslStartDrawing();
      oslReadKeys();
      menu(0);               
}

void yourchoice(int choice) {
     if (choice == 0) {
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
      obj_x[4]=320;
      obj_y[4]=576;
      obj_i[4]=2;
      heroHP=100;
      // w��cz gr�.
      gameplay();
      } else if (choice == 1) {
             menu(3);
             
             } else if (choice == 2) {
                    oslQuit();
                    }
}
      
