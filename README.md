# Physics Engine
La intención de este proyecto es crear un motor de físicas, con un método propio, para experimentar con la creación de un proyecto a mayor escala.

## Idea de progreso
* [Cuerpos rigidos](#Cuerpos-rigidos)
* [Deteccion de colisiones](#Deteccion-de-colisiones)
* [Resolucion de interseccion](#Resolucion-de-interseccion)
* [Resolucion de colisiones](#Resolucion-de-colisiones)

### Cuerpos rigidos
Son las representaciones geometricas de cuerpos que van a interactuar en el motor de fisicas, estas van a ser
 * Circulo
 * Linea
 * Rectangulo de tipo AABB
 * Rectangulo 
 * Capsula 

Voy a empezar con el circulo, linea y un rectangulo de tipo AABB, y despues voy a agregar el resto, y si veo la necesidad de alguno mas, entonces se actualizara la lista de elementos

### Deteccion de colisiones
La deteccion de colisiones va a ser una combinacion entre los cuerpos rigidos, y un quadtree que uso para subdividir el espacio haciendo mas eficiente la busqueda de particulas. Usando el metodo de busqueda del quadtree para encontrar las colisiones de cada particula

### Resolucion de interseccion
Esta seccion es la que voy a estar trabajando actualmente por lo que todavia no tengo un plan definido, pero va a estar en combinacion con la siguiente parte del motor de fisicas que es la resolucion de colisiones

### Resolucion de colisiones
La resolucion de colisiones, a diferencia de el metodo mas tradicional, estoy usando grafos como forma en la que las particulas interactuen entre si. Por lo tanto, las particulas son los nodos y las aristas es la direccion que une a dos particulas, y de esta forma transmitir las fuerzas como tambien las velocidades

## Documentacion 
En la documentacion se puede esperar ver los metodos que se tienen que usar para usar correctamente los sistemas que cree para este motor de fisicas, en el caso que se quieran usar por separados, todo esto lo pueden ver [aca](documentation.md)

## Explicacion de todo el codigo
En la explicacion se puede esperar ver el motivo por el cual uso ciertas estructuras, o la idea general del porque hago ciertas cosas, todo esto lo pueden ver [aca](explicaciones.md). Todavia no esta hecho, pero cuando lo este, este mensaje va a desaparecer
