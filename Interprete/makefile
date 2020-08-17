flags = -Wall -Werror -Wextra -g -c -std=c99
ITree1 = ../Arboles/ITree1.h

tablahash = ../Hash/tablahash.h
hashavl = ../HashAVL/hashavl.h

interprete.o: interprete.c interprete.h $(tablahash) $(hashavl)
	gcc $(flags) interprete.c

.PHONY: cleanLin, cleanWin
cleanLin:
	rm -rf *.o

cleanWin:
	del /Q /F *.o
