.PHONY: proyecto cleanLin cleanWin


	
proyecto:
	$(MAKE) -C Proyecto

cleanWin:
	del /Q /F  *.o *.exe *.out Proyecto\*.o Interprete\ITree\*.o Proyecto\ITree\Cola\*.o Interprete\ITree\Pila\*.o Interprete\ITree\Intervalos\*.o

cleanLin:
	rm -rf *.out *.o */*.o */*/*.o */*/*/*.o
