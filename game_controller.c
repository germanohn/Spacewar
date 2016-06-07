#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "game_controller.h"

ALLEGRO_BITMAP *planet_im;
ALLEGRO_BITMAP *player1_im;
ALLEGRO_BITMAP *player2_im;
ALLEGRO_BITMAP *projectile_im;
ALLEGRO_BITMAP *heart;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue;

int keys_1[4] = {false, false, false, false};
int keys_2[4] = {false, false, false, false};

int gameControllerInit (double dt) {
    /* Cria fila em que colocamos todos os eventos que vão servir como fonte
    para "alimentar" a imagem e assim alterá-la. Nesse caso, os eventos são:
    timer (flag que avisa quando a imagem deve ser refeita); Keyboard
    com KEY_DOWN (ativado quando tecla está pressionada) e KEY_UP (ativado
    quando a tecla está despressionada); display (Carrega imagem a ser impressa) */
    event_queue = al_create_event_queue ();
    if (!event_queue) {
        fprintf (stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display (display);
        return -1;
    }

    /* Agora inicializamos as imagens que usaremos para cada elemento da
    imagem, que são planeta, player1, player2, projectile e background
    (espaço sideral) */
    planet_im = al_load_bitmap ("images/planet.png");
    if (!planet_im) {
        fprintf (stderr, "Falha ao iniciar a imagem do Planeta\n");
        al_destroy_display (display);
        al_destroy_event_queue (event_queue);
        return -1;
    }

    player1_im = al_load_bitmap ("images/player1.png");
    if (!player1_im) {
        fprintf (stderr, "Falha ao iniciar a imagem do Player 1\n");
        al_destroy_display (display);
        al_destroy_event_queue (event_queue);
        al_destroy_bitmap (planet_im);

        return -1;
    }

    player2_im = al_load_bitmap ("images/player2.png");
    if (!player2_im) {
        fprintf (stderr, "Falha ao iniciar a imagem do Player 2\n");
        al_destroy_display (display);
        al_destroy_event_queue (event_queue);
        al_destroy_bitmap (planet_im);
        al_destroy_bitmap (player1_im);

        return -1;
    }

    projectile_im = al_load_bitmap ("images/projectile.png");
    if (!projectile_im) {
        fprintf (stderr, "Falha ao iniciar a imagem dos Projeteis\n");
        al_destroy_display (display);
        al_destroy_event_queue (event_queue);
        al_destroy_bitmap (planet_im);
        al_destroy_bitmap (player1_im);
        al_destroy_bitmap (player2_im);

        return -1;
    }

    timer = al_create_timer (1.0 / dt);
    if (!timer) {
        fprintf (stderr, "Erro ao inicalizar timer\n");
        al_destroy_display (display);
        al_destroy_event_queue (event_queue);
        al_destroy_bitmap (planet_im);
        al_destroy_bitmap (player1_im);
        al_destroy_bitmap (player2_im);
        al_destroy_bitmap (projectile_im);

        return -1;
    }

    // coracao
    heart = al_load_bitmap ("images/heart.png");
    if (!heart) {
        fprintf (stderr, "Falha ao iniciar a imagem de vida\n");
        al_destroy_display (display);
        al_destroy_event_queue (event_queue);
        al_destroy_bitmap (planet_im);
        al_destroy_bitmap (player1_im);
        al_destroy_bitmap (player2_im);
        al_destroy_bitmap (projectile_im);
    }
    /* Popula as fontes do event queue */
    al_register_event_source (event_queue, al_get_display_event_source (display));
    al_register_event_source (event_queue, al_get_timer_event_source (timer));
    al_register_event_source (event_queue, al_get_keyboard_event_source ());

    return 0;
}

/* Função que destroi os elementos da cena depois que o jogo acabou */
void gameControllerDestroy () {
    al_destroy_timer (timer);
    al_destroy_display (display);
    al_destroy_event_queue (event_queue);
    al_destroy_bitmap (planet_im);
    al_destroy_bitmap (player1_im);
    al_destroy_bitmap (player2_im);
    al_destroy_bitmap (projectile_im);
    al_destroy_bitmap (heart);
}

/* Função que imprime na tela a imagem correspondente ao objeto recebido */
static void drawBody (ALLEGRO_BITMAP *image, Body *body) {
    /* Posicoes em escala */
    double sx = body->position->x * SCALE_X + DISPLAY_W / 2.0;
    double sy = body->position->y * SCALE_Y + DISPLAY_H / 2.0;

    /* Pixels da imagem: retorna a largura do bitmap em pixels */
    double pw = al_get_bitmap_width (image) / 2.0;
    double ph = al_get_bitmap_height (image) / 2.0;

    /* Constante de Escala */
    double cteX = body->radius * SCALE_X / pw;
    double cteY = body->radius * SCALE_Y / ph;

    al_draw_scaled_rotated_bitmap (image, pw, ph, sx, sy, cteX, cteY, body->angle, 0);
}

static void drawLifes (Ship *player, int dx, int dy, int kind) {
    double pw, ph;
    for (int i = 0; i < player->body->qtdLives; i++) {
        //dx = body->position->x * SCALE_X + DISPLAY_W / 2.0;
        //dy = body->position->y * SCALE_Y + DISPLAY_H / 2.0;
        
        pw = al_get_bitmap_width (heart);
        ph = al_get_bitmap_height (heart);
        
        al_draw_scaled_bitmap (heart, 0, 0, pw, ph, dx, dy, pw/45, ph/45, 0);
        //dx += kind ? 10 : -10;
        if (kind)
            dx += 28;
        else 
            dx -= 28;
    } 
}

/* função que encapsula a draw e faz todos os objetos serem impressos na tela */
static void draw (Ship *player1, Ship *player2, Celula *head, Body *planet) {
    /* Desenho do fundo de tela */
    al_draw_bitmap (background_image, 0, 0, 0);

    /* Desenho dos objetos do jogo */
    drawBody (player1_im, player1->body);
    drawBody (player2_im, player2->body);
    drawBody (planet_im, planet);

    /* Desenho das vidas de cara nave */
    double dx, dy;
    dx = 10, dy = DISPLAY_H - 120;
    drawLifes (player1, dx, dy, 1);
    dx = DISPLAY_W - 100, dy = DISPLAY_H - 120;
    drawLifes (player2, dx, dy, 2);

    Celula *aux = head->next;
    while (aux != NULL) {
        drawBody (projectile_im, aux->proj->body);
        aux = aux->next;
    }
}

void gameControllerDraw (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet) {
    /* Indica quando a imagem seve ser refeita */
    int redraw = 1;

    /* Indica quais eventos que serão usados na event_queue, isto é, os tipos
    de eventos que irão "alimentar" a event_queue. No caso, são display, timer
    e teclado */
    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_flip_display ();
    al_start_timer (timer);

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event (event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            /* Indica quando a imagem deve ser redesenhada */
            redraw = 1;

        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            /* Permite que feche a tela da imagem, mas termine de executar o programa,
            isto é, ele termina de destroir os objetos (dar free) antes de fechar o
            programa*/
            break;
        }

        /* Evento que indica que uma tecla do teclado foi pressionada. Então, a flag
        correspondente a tecla pressionada é ativada, para o player1, ou para o player2
        ou para ambos conforme o caso */
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                // Player 1 (W, A, TAB, D)
                case ALLEGRO_KEY_W:
                    keys_1[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_TAB:
                    keys_1[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_A:
                    keys_1[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_D:
                    keys_1[KEY_RIGHT] = true;
                    break;

                // Player 2 (UP, DOWN, COMMA, RIGHT)
                case ALLEGRO_KEY_UP:
                    keys_2[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_COMMA:
                    keys_2[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys_2[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys_2[KEY_RIGHT] = true;
                    break;

                default:
                    break;
            }
        }
        /* Evento que indica que uma tecla do teclado foi despressionada. Então, a flag
        correspondente a tecla despressionada é desativada para o player1, ou para o player2
        ou para ambos conforme o caso. */
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                // Player 1 (W, A, TAB, D)
                case ALLEGRO_KEY_W:
                    keys_1[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_TAB:
                    keys_1[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_A:
                    keys_1[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_D:
                    keys_1[KEY_RIGHT] = false;
                    break;

                // Player 2 (UP, DOWN, COMMA, RIGHT)
                case ALLEGRO_KEY_UP:
                    keys_2[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_COMMA:
                    keys_2[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys_2[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys_2[KEY_RIGHT] = false;
                    break;

                default:
                    break;
            }
        }
        /* Irá redesenhar a imagem se a flag redraw estiver ativada, isto é, o timer
        indicou que é o momento de redesenhar, e se não tiver um evento na event_queue. */
        if (redraw && al_is_event_queue_empty (event_queue)) {
            redraw = 0;

            /* Agora construímos a próxima imagem a ser exibida */
            al_clear_to_color (al_map_rgb (0, 0, 0));

            /* Função que altera o elementos de cada nave (aceleração, ângulo)
            e cria projéteis, se as teclas correspondentes estiverem ativadas. */
            updateKeys (keys_1, player1->body, head);
            updateKeys (keys_2, player2->body, head);

            /* Função que computa as novas posições de cada objeto de acordo
            com atributos atualizados pela updateKeys (velocidade e ângulo em
            relação ao eixo x) de cada objeto*/
            int endGame = updatePositions (dt, player1, player2, head, planet);

            /* Imprime na tela a imagem resultante construída */
            draw (player1, player2, head, planet);
            al_flip_display ();

            if (endGame)
                break;
        }
    }

    gameControllerDestroy ();
}
