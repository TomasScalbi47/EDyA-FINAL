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

  Insercion de intervalos completada.

24/07
  Comienzo implementacion de operaciones de conjuntos.
  Union: Para unir dos sets implementados como árboles, la opción más coherente
    que se me ocurre es ingresar los nodos de un árbol a otro.
    Pero la union tiene que devolver un arbol nuevo, asi que la idea entonces
    seria insertar todos los de uno y despus los de otros, hay que recorrer los
    2 arboles, por ejemplo con dfs.

  Interseccion: la interseccion de dos conjuntos es los que estan en ambos.
  Por lo tanto tengo que recorrer ambos arboles a la ves e ir haciendo Interseccion
  de cada nodo con el arbol.

  Terminado union =).
  Se hizo itree_copia.

25/07
  Objetivo de hoy, implementar la interseccion entre 2 conjuntos.
    La interseccion es un nuevo conjunto que contiene los elementos que
    pertenecen a ambos.

    La idea seria recorrer ambos arboles

  TAMBIEN ME DOY CUENTA QUE HABRIA QUE REHACER LA FUNCION DE INTERSECCION,
  en este tipo de arboles deberia ser menos costoso buscar intersecciones.

26/07
  Terminada la interseccion entre 2 conjuntos.
  
 7/8
    No logee los avances, pero basicamente ya esta terminada la
    implementacion de conjuntos con arboles AVL, tendria que ver si se
    pueden añadir algunas mejoras, pero lo dudo y ya es funcional.
    
    Comienzo de implementacion del interprete.
    
    https://stackoverflow.com/questions/7666509/hash-function-for-string
