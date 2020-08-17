flags = -Wall -Werror -Wextra -g -c -std=c99


hlist.o: hlist.c hlist.h
	gcc $(flags) hlist.c

.PHONY: cleanLin, cleanWin
cleanLin:
	rm -rf *.o

cleanWin:
	del /Q /F *.o
