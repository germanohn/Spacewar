#include "alegro.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *mainFont;
ALLEGRO_BITMAP *background_image;
ALLEGRO_SAMPLE *background_sound;

int allegroInit () {
  if (!al_init ()) {
      fprintf (stderr, "Falha ao inicializar a Allegro.\n");
      return -1;
  }

  /* Inclui bibliotecas da Allegro que permite criar as imagens  */
  if (!al_init_image_addon ()) {
      fprintf (stderr, "Falha ao inicializar add-on allegro_image.\n");
      return -1;
  }

  if (!al_install_audio ()) {
      fprintf(stderr, "Falha ao inicializar audio.\n");
      return -1;
   }

   if (!al_init_acodec_addon ()) {
      fprintf(stderr, "Falha ao inicializar audio codecs.\n");
      return -1;
   }

   if (!al_reserve_samples (1)) {
      fprintf(stderr, "Falha ao reservar samples.\n");
      return -1;
   }

  /* Verifica se o teclado foi inicializado */
  if (!al_install_keyboard ()) {
      fprintf (stderr, "Falha ao iniciar o teclado.\n");
      return -1;
  }

  /* Cria o display que será a imagem mostrada do jogo e que possui duas dimensões
  DISPLAY_W (largura) DISPLAY_H (altura).*/
  display = al_create_display (DISPLAY_W, DISPLAY_H);
  if (!display) {
      fprintf (stderr, "Falha ao criar janela.\n");
      return -1;
  }

  /* Bitmap do fundo */
  background_image = al_load_bitmap ("images/space.jpg");
  if (!background_image) {
      fprintf (stderr, "Falha ao carregar 'images/space.jpg'.\n");
      al_destroy_display (display);
      return -1;
  }

  mainFont = al_load_ttf_font ("fonts/terminator.ttf", 48, 0);
  if (!mainFont) {
    fprintf(stderr, "Falha ao carregar 'fonts/terminator.ttf'.\n");
    al_destroy_display (display);
    al_destroy_bitmap (background_image);
    return -1;
  }

  background_sound = al_load_sample ("audios/background.wav");
  if (!background_sound) {
    fprintf(stderr, "Falha ao carregar 'audios/background.wav'.\n");
    al_destroy_display (display);
    al_destroy_bitmap (background_image);
    al_destroy_sample (background_sound);
    return -1;
  }

  return 0;
}

void allegroDestroy () {
  al_destroy_display (display);
  al_destroy_bitmap (background_image);
  al_destroy_ttf_font (mainFont);
}
