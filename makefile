flags = -Wall -Werror -Wextra -g -c -std=c99

ITree = Interprete/Arboles/ITree1
pila = Interprete/Arboles/Pila/pila
cola = Interprete/Arboles/Cola/cola
intervalos = Interprete/Arboles/Intervalos/intervaloE
interpretar = Interprete/interpretar
interprete = Interprete/interprete

.PHONY: Interprete interpretar cleanLin cleanWin

interpretar: Interprete
	gcc -o interpretar.out $(ITree).o $(pila).o $(cola).o $(intervalos).o $(interprete).o $(interpretar).o

Interprete:
	$(MAKE) -C Interprete


cleanWin:
	del /Q /F  *.o *.exe *.out Proyecto\*.o Interprete\Arboles\*.o Proyecto\Arboles\Cola\*.o Interprete\Arboles\Pila\*.o Interprete\Arboles\Intervalos\*.o

cleanLin:
	rm -rf *.out *.o */*.o */*/*.o */*/*/*.o
