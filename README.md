# Game of Life meets physics

La idea de este proyecto es principalmente para que aprenda a usar C++, posiblemente Opengl y en el mejor de los casos Vulkan

Para esto primero estoy aprendiendo C++, con el objetivo de hacer un falling sand simulator, pero mi forma de cambiarlo es que no voy a tener una matriz donde esten los materiales sino que van a ser particulas y en el unico momento que se va a ver como si fuera una matriz es cuando se muestre por pantalla

La idea de usar particulas me parecio mas divertido porque me da situaciones como deteccion de colisiones y como optimizar para muchas particulas, el uso de la fisica newtoniana y como manejar su error en una simulacion discontinua

### Idea de progreso
Creo que el motor de fisicas va a estar dividio en estos sistemas vinculados
* [Cuerpos rigidos](#Cuerpos-rigidos)
* [Sibdivision del espacio](#Subdivision-del-espacio)
* [Deteccion de colisiones](#Deteccion-de-colisiones)
* [Resolucion de colisiones](#Resolucion-de-colisiones)

#### Cuerpos rigidos
Son las representaciones geometricas de cuerpos que van a interactuar en el motor de fisicas, estas van a ser
 * Circulo
 * Linea
 * Rectangulo de tipo AABB
 * Rectangulo 
 * Capsula 

Voy a empezar con el circulo, linea y un rectangulo de tipo AABB, y despues voy a agregar el resto, y si veo la necesidad de alguno mas, entonces se actualizara la lista de elementos
#### Subdivision del espacio
Voy a usar un quadtree, principalmente porque me parece divertido, y porque voy a querer que el motor de fisicas sea capaz de admitir zonas muy densas de particulas y zonas con casi ninguna particula, y creo que un quadtree es la mejor estructura para ese trabajo

Para ser mas especifico, voy a crear un archivo quadtree.cpp, en el que estara la clase QuadTree como tambien Node y Entidad, donde QuadTree es la interfaz con el usuario, Node la estructura real del quadtree, y la Entidad lo minimo para poder tener una particula guardada en el quadtree

#### Deteccion de colisiones
La deteccion de colisiones va a estar dada en combinacion entre el cuerpo rigido y el quadtree, donde el quadtree me va a dar todas las posibles colisiones, y el cuerpo rigido va a dar todas las colisiones validas y que se tienen que resolver

#### Resolucion de colisiones
La resolucion de colisiones todavia no lo tengo muy bien pensado pero la idea que tengo actualmente es de usar un grafo para representar las colisiones, y de ahi poder hacer una resolucion mas eficiente y mas realista, pero como dije no lo tengo muy bien pensado y todavia no se si es posible

### Explicacion de todo el codigo
Voy a estar explicando todo el codigo que escribo, y se puede interpresar como una forma de documentacion, pero realmente es mas una explicacion, todo esto lo pueden ver [aca](explicaciones.md)

### Documentacion 
Por ahora no tengo nada escrito porque estuve haciendo la explicacion, pero cuando lo cambie va a estar [aca](documentation.md)