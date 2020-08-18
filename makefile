SUBDIRS = Intervalos Conjuntos AVL HashAVL Interprete

intervalos = Intervalos/intervaloE.o
interprete = Interprete/interprete.o
hashavl = HashAVL/hashavl.o
avl = AVL/avl.o
conjuntos = Conjuntos/conjuntos.o

.PHONY: all
all: subdirs interpretar


.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: interpretar
interpretar: $(intervalos) $(interprete) $(hashavl) $(avl) $(conjuntos)
	gcc -o interprete $(intervalos) $(interprete) $(hashavl) $(avl) $(conjuntos)

cleanLin:
	rm -rf *.out */*.o

cleanWin:
	del /Q /F *.exe *.out Interprete\*.o Intervalos\*.o HashAVL\*.o AVL\*.o Conjuntos\*.o
