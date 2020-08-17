flags = -Wall -Werror -Wextra -g -c -std=c99


hashavl.o: hashavl.c hashavl.h
	gcc $(flags) hashavl.c

.PHONY: cleanLin, cleanWin
cleanLin:
	rm -rf *.o

cleanWin:
	del /Q /F *.o
