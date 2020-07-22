flags = -Wall -Werror -Wextra -g -c -std=c99

.PHONY: all arboles
all: arboles interprete.o interpretar.o

interpretar.o: interpretar.c
	gcc $(flags) interpretar.c

interprete.o: interprete.c interprete.h
	gcc $(flags) interprete.c

arboles:
	$(MAKE) -C Arboles
