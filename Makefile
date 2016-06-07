CFLAGS = -Wall -Wextra -ansi -pedantic -O2 --std=c99
LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf -lm
OSNAME := $(shell uname -s)

ifeq ($(OSNAME), Linux)
    CC = gcc
else
    CC = gcc-5
endif

Spacewar: main.o body.o ship.o vector.o projectile.o simulation.o allegro.o menu_controller.o game_controller.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

main.o: main.c body.h ship.h projectile.h allegro.h vector.h

simulation.o: simulation.c body.h vector.h ship.h projectile.h

body.o: body.c vector.h body.h

ship.o: ship.c body.h ship.h

vector.o: vector.c vector.h

projectile.o: projectile.c projectile.h body.h

allegro.o: allegro.c simulation.h allegro.h

menu_controller.o: menu_controller.c allegro.h menu_controller.h

game_controller.o: game_controller.c allegro.h menu_controller.h game_controller.h

play: Spacewar
	./Spacewar 60

doc: Relatorio.tex
	pdflatex Relatorio.tex

zip: *.c *.h images/*.* Relatorio.pdf Makefile Spacewar
	zip spacewar.zip $^

clear:
	rm -f *.o

clear_all:
	rm -f *.o Spacewar spacewar.zip Relatorio.aux Relatorio.out Relatorio.log Relatorio.pdf
