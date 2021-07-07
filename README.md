# Game of Life meets physics

La idea de este proyecto es principalmente crear un juego lo mas desde 0 que pueda. Tambien es una forma de aprender herramientas nuevas que nunca use como lo puede ser OpengGl o Vulkan

El juego consiste de falling sand simulator, pero con el twist que realmente es una simulacion de muchas particulas que despues se va a mostrar como si fuera una matriz. El motivo de esto es que a mi me gusta mucho los falling sand simulators pero me gustaria poder agregarle fisicas mas realistas, pero en el proceso de pensar como hacerlo note lo complicado que se hace estan en una matriz entonces descarte la idea de la matriz para el computo del motivimiento, resultando en lo que quiero hacer actualmente

## Idea de progreso
El primer paso, y en el que estoy, es crear un motor de fisicas que pueda manejar muchas particulas interactuando entre si, y lo divide en lo siguiente
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
En la explicacion se puede esperar ver el motivo por el cual uso ciertas estructuras, o la idea general del porque hago ciertas cosas, todo esto lo pueden ver [aca](explicaciones.md)
