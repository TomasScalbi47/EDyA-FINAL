flags = -Wall -Werror -Wextra -g -c -std=c99


intervaloE.o: intervaloE.c intervaloE.h
	gcc $(flags) intervaloE.c

.PHONY: cleanLin, cleanWin
cleanLin:
	rm -rf *.o

cleanWin:
	del /Q /F *.o
