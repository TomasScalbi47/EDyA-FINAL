SUBDIRS = Intervalos Arboles AVL HashAVL Listas Hash Interprete

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

interpretar:
