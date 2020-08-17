flags = -Wall -Werror -Wextra -g -c -std=c99
intervalo = ../Intervalos/intervaloE.h

ITree.o: ITree1.c ITree1.h $(intervalo)
	gcc $(flags) ITree1.c

.PHONY: cleanLin, cleanWin
cleanLin:
	rm -rf *.o

cleanWin:
	del /Q /F *.o
