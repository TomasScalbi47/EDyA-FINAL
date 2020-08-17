SUBDIRS = Intervalos Arboles AVL HashAVL Listas Hash Interprete

intervalos = Intervalos/intervaloE.o
interprete = Interprete/interprete.o
hashavl = HashAVL/hashavl.o
hash = Hash/tablahash.o
avl = AVL/avl.o
itree = Arboles/ITree1.o

.PHONY: all
all: subdirs interpretar


.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: interpretar
interpretar: $(intervalos) $(interprete) $(hashavl) $(hash) $(avl) $(itree)
	gcc -o interprete.out $(intervalos) $(interprete) $(hashavl) $(hash) $(avl) $(itree)

cleanLin:
	rm -rf *.out */*.o

cleanWin:
	del /Q /F *.out Interprete\*.o Intervalos\*.o HashAVL\*.o Hash\*.o AVL\*.o Arboles\*.o
