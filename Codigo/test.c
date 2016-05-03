#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

int main (int argc, char *argv[]) {
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_BITMAP *image = NULL;

    if (!al_init ()) {
        fprintf (stderr, "Falha ao inicializar a Allegro");
        return -1;
    }
    janela = al_create_display (680, 680);
    if (!janela) {
        fprintf (stderr, "Falha ao inicializar a janela");
        return -1;
    }
    image = al_load_bitmap ("milleniumTop.png");
    /*if (!image) {
        fprintf (stderr, "Falha ao inicializar a imagem");
        return -1;
    }*/
    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_draw_bitmap (image, 0, 0, 0);
    al_flip_display ();
    al_rest (10.0);

    al_destroy_display (janela);

    return 0;
}
