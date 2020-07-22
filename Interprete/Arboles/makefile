flags = -Wall -Werror -Wextra -g -c -std=c99

ITree = ITree1
cola = Cola/cola
intervalos = Intervalos/intervaloE
pila = Pila/pila

.PHONY: all Pila Cola intervalo
all: ITree1.o Pila Cola intervalo


Pila:
	$(MAKE) -C Pila

Cola:
	$(MAKE) -C Cola

intervalo:
	$(MAKE) -C Intervalos

ITree1.o: $(ITree).c $(ITree).h $(pila).h $(intervalos).h $(cola).h
	gcc $(flags) $(ITree).c
