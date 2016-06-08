#include <stdio.h>
#include <math.h>
#include "menu_controller.h"

static ALLEGRO_EVENT_QUEUE *menuEventQueue;
int cursor;

void initObjects (Body **planet, Ship **player1, Ship **player2) {
    *planet = createBody (9e06, 2.02e24, 0, 0, 0, 0);
    *player1 = createShip ("Nave1", 1.6e6, 7.4e04, -3.5786e07, 0, 0, 0);
    *player2 = createShip ("Nave2", 1.6e6, 7.4e04, 3.5786e07, 0, 0, 0);
}

int menuControllerInit () {
    menuEventQueue = al_create_event_queue ();
    if (!menuEventQueue) {
        fprintf (stderr, "Falha ao criar fila de eventos.\n");
        allegroDestroy ();
        return -1;
    }
    al_register_event_source (menuEventQueue, al_get_display_event_source (display));
    al_register_event_source (menuEventQueue, al_get_keyboard_event_source ());
    al_play_sample (background_sound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    cursor = 0;

    return 0;
}

void menuControllerDestroy () {
    al_destroy_event_queue (menuEventQueue);
}

void menuControllerDraw (double dt) {
    int redraw = 1;

    ALLEGRO_COLOR selected_color = al_map_rgb (255, 255, 255);
    ALLEGRO_COLOR unselected_color = al_map_rgb (145, 145, 145);

    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_draw_bitmap (background_image, 0, 0, 0);
    al_draw_text (mainFont, cursor == 0 ? selected_color : unselected_color, DISPLAY_W / 2, DISPLAY_H * 0.45, ALLEGRO_ALIGN_CENTRE, "Novo Jogo");
    al_draw_text (mainFont, cursor == 1 ? selected_color : unselected_color, DISPLAY_W / 2, DISPLAY_H * 0.55, ALLEGRO_ALIGN_CENTRE, "Sair");
    al_flip_display ();

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event (menuEventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;

        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
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
                default:
                    break;
            }
        } if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            if (cursor == 0) {
                if (gameControllerInit (dt) != -1) {
                    Body *planet;
                    Ship *player1;
                    Ship *player2;
                    Celula *head  = createCelula (NULL, NULL);

                    initObjects (&planet, &player1, &player2);
                    gameControllerDraw (dt, player1, player2, head, planet);
                    gameControllerDestroy ();

                    destroyBody (planet);
                    destroyShip (player1);
                    destroyShip (player2);
                    destroyAllCelulas (head);
                }
                redraw = 1;
            }
            else
                break;
        }
        if (redraw) {
            redraw = 0;

            /* Agora construímos a próxima imagem a ser exibida */
            al_clear_to_color (al_map_rgb (0, 0, 0));
            al_draw_bitmap (background_image, 0, 0, 0);
            al_draw_text (mainFont, cursor == 0 ? selected_color : unselected_color, DISPLAY_W / 2, DISPLAY_H * 0.45, ALLEGRO_ALIGN_CENTRE, "Novo Jogo");
            al_draw_text (mainFont, cursor == 1 ? selected_color : unselected_color, DISPLAY_W / 2, DISPLAY_H * 0.55, ALLEGRO_ALIGN_CENTRE, "Sair");
            al_flip_display ();
        }
    }

    menuControllerDestroy ();
}
