CFLAGS = -Wall -Wextra -ansi -pedantic -O2 --std=c99
LIBS = -lallegro -lallegro_main -lallegro_image -lm
OSNAME := $(shell uname -s)

ifeq ($(OSNAME), Linux)
    CC = gcc
else
    CC = gcc-5
endif

Spacewar: main.o body.o ship.o vector.o projectile.o draw.o simulation.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

main.o: main.c body.h ship.h projectile.h draw.h vector.h

simulation.o: simulation.c body.h vector.h ship.h projectile.h

body.o: body.c vector.h body.h

ship.o: ship.c body.h ship.h

vector.o: vector.c vector.h

projectile.o: projectile.c projectile.h body.h

draw.o: draw.c simulation.h draw.h

test:
	./Spacewar 60 < Samples/Teste.txt

doc: Relatorio.tex
	pdflatex Relatorio.tex

clear:
	rm -f *.o
