flags = -Wall -Werror -Wextra -g -c
cola = Cola/cola
intervalos = Intervalos/intervalos
pila = Pila/pila
ITree = ITree

.PHONY: Colas Pilas Intervalos all
all: Colas Pilas Intervalos ITree.o

Colas:
	$(MAKE) -C Cola

Pilas:
	$(MAKE) -C Pila

Intervalos:
	$(MAKE) -C Intervalos

ITree.o: $(ITree).c $(ITree).h $(pila).h $(intervalos).h $(cola).h
	gcc $(flags) $(ITree).c
