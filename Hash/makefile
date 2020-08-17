flags = -Wall -Werror -Wextra -g -c -std=c99


tablahash.o: tablahash.c tablahash.h
	gcc $(flags) tablahash.c

.PHONY: cleanLin, cleanWin
cleanLin:
	rm -rf *.o

cleanWin:
	del /Q /F *.o
