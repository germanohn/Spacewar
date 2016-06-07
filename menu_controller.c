#include <stdio.h>
#include <math.h>
#include "menu_controller.h"

ALLEGRO_EVENT_QUEUE *event_queue;
int cursor;

int menuControllerInit () {
    event_queue = al_create_event_queue ();
    if (!event_queue) {
        fprintf (stderr, "Falha ao criar fila de eventos.\n");
        allegroDestroy ();
        return -1;
    }
    cursor = 0;
    return 0;
}

void menuControllerDraw (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet) {
    int redraw = 1;

    al_register_event_source (event_queue, al_get_display_event_source (display));
    al_register_event_source (event_queue, al_get_keyboard_event_source ());
    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_flip_display ();
    
    while (true) { 
        ALLEGRO_EVENT event;
        al_wait_for_event (event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
           switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    cursor++;
                    cursor = cursor % 2;
                    redraw = 1;
                    break;
                case ALLEGRO_KEY_DOWN:
                    cursor--;
                    cursor = abs (cursor) % 2;
                    redraw = 1;
                    break;
                case ALLEGRO_KEY_ENTER:
                    if (gameControllerInit () != -1)
                        gameControllerDraw (dt, player1, player2, head, planet);
                    redraw = 1;
                    
           }
        }
        if (redraw && al_is_event_queue_empty (event_queue)) {
            redraw = 0;
            /* Agora construímos a próxima imagem a ser exibida */
            al_clear_to_color (al_map_rgb (0, 0, 0));
            al_draw_bitmap (background_image, 0, 0 , 0);
            al_draw_text (mainFont, al_map_rgb (0, 0, 0), DISPLAY_W / 2, DISPLAY_H * 0.45, 0, "Novo Jogo");
            al_draw_text (mainFont, al_map_rgb (0, 0, 0), DISPLAY_W / 2, DISPLAY_H * 0.55, 0, "Sair");
            if (cursor == 0) 
                al_draw_text (mainFont, al_map_rgb (0, 0, 0), DISPLAY_W / 2, DISPLAY_H * 0.45, 0, "->");
            else 
                al_draw_text (mainFont, al_map_rgb (0, 0, 0), DISPLAY_W / 2, DISPLAY_H * 0.55, 0, "->");

            al_flip_display ();
        }

    }
}
