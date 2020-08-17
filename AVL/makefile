flags = -Wall -Werror -Wextra -g -c -std=c99
ITree1 = ../Arboles/ITree1.h

avl.o: avl.c avl.h $(ITree1)
	gcc $(flags) avl.c

.PHONY: cleanLin, cleanWin
cleanLin:
	rm -rf *.o

cleanWin:
	del /Q /F *.o
