# EDyA-FINAL
Trabajo final EDyA I Mesas Julio/Agosto.

Implementacion de intérprete para operar con cojuntos numéricos,
soportando operaciones como la unión, intersección, resta y complemento.


Progreso con el trabajo:

13/07.
  Creación del repositorio. Añadido de README, informe y carpeta proyecto.
  Archivos makefile. Recordar comentar el uso de los .PHONY

  Pensamientos:
    Los conjuntos numéricos son de numeros enteros. Los conjuntos pueden ser
    dados por extensión o por compresión. Sea cual sea el método de entrada,
    los conjuntos se pueden representar como un árbol de intervalos donde
    cada intervalo es un conjunto.

    Para esto tengo que importar los intervals tree.
15/07
  Decision de implementar un conjunto como array de intervalos enteros.
  Implementacion de intervalos, y sets.
  Intento de implementar de función insertar un intervalo en un set.
  Realmente es conveniente implementar esto con arrays y no con arboles avl??

21/07
  La forma mas facil de implementar los conjuntos parece ser arboles, y es la
  que mas entiendo. Asi que lo voy a hacer primeramente de esa forma.

  Funciones que hay que modificar para AVLTree conjuntos.
    Se tiene que insertar intervalos de forma inteligente, es decir que los
    intervalos del ITree sean disjuntos.
      Si el arbol esta vacio, se inserta trivialmente.
      Si el arbol es no vacio, hay que primero eliminar todas las coliciones
      y luego hay que insertar la union de todas estas.
