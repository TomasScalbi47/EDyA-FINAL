flags = -Wall -Werror -Wextra -g -c

ITree = ITree
cola = Cola/cola
intervalos = Intervalos/intervaloE
pila = Pila/pila

.PHONY: all Pila Cola intervalo
all: Itree.o Pila Cola intervalo


Pila:
	$(MAKE) -C Pila

Cola:
	$(MAKE) -C Cola

inetervalo:
	$(MAKE) -C Intervalos

ITree.o: $(ITree).c $(ITree).h $(pila).h $(intervalos).h $(cola).h
	gcc $(flags) $(ITree).c
