# Documentacion
Aca voy a tener todos (por lo menos mi intento es que sea lo mas posible) los detalles tecnicos de lo que este haciendo, y porque lo estoy haciendo de tal manera

#### Menu:
 * [Vectores](#Vector)
 * [Particulas](#Particula)

## Vector
La idea es representar los vectores en dos dimensiones. Esta implementado en los archivo vector.h y vector.cpp

### Constructor
Cree dos constructores, uno que tomas los valores de x e y, y otra que no, en el caso de que no entonces se inicializan los valores en .0f y .0f

### Interfaz con el usuario
#### Tenemos los metodos
 * modulo
 * distancia
 * imprimir

En estos casos para modulo y distancia me estoy basando en la forma matematica de calcular estas propiedades, pero en los dos casos estoy usando una raiz cuadrada que es costoso computacionalmente

Entonces puede ser que mas adelante cree mas metodos donde no se calcule la raiz cuadrada, que por ejemplo en el caso de una colision de particulas no es necesario tener la raiz cuadrada por lo que seria mas eficiente

El metodo de imprimir es principalmente para debug

#### Operadores
Hice modificaciones a los operadores para que sea mucho mas limpeo las operaciones entre vectores
 * Suma
 * Resta
 * Multiplicacion por un vector
 * Multiplicacion por un escalar
 * Division por un escalar

Tambien estan las variantes de +=, -=, *=, /= pero hay que tener en cuenta que tanto *= como /= van a ser la multiplicacion y division por un escalar

Nuevamente en esto me estoy basando en las definiciones matematica para trabajar con las operaciones de vectores. Por ejemplo en la multiplicacion entre dos vectores, lo mas comun es multiplicar los componentes x e y, pero matematicamente el resultado seria un escalar (float) que es la suma de la multiplicacion de las componentes

Mi pensamiento detras de hacer asi es que uno pueda usar formulas donde se tiene calculo de vecotres y que sea lo mas parecido a esas cuentas

##### Nota:
No implemente lo que se conoce como producto vectorial, donde se multiplican dos vectores y el resultado es otro vector perpendicular a los otros dos

Esto es porque como estamos en dos dimensiones el producto vectorial siempre va a tener una componente en la direccion z, y como estamos viendo vectores de dos dimensiones no tiene sentido tenerlo. Lo que es probable es que en el futuro agregue un metodo que devuelva un vector que sea perpendicular al que se esta aplicando

## Particula
Una particula va a tener una posicion, una velocidad, masa y un radio. Por ahora eso va a ser la representacion de una particula y posiblemente mas adelante va a ir cambiando para adoptar mas caracteristicas

### Constructor
Tenemos 3 posibilidades para crear una particula
 1. Sin ningun parametro, donde su posicion va a ser en 0, 0 su masa de 1 y su radio de 1.
 2. Con su posicion, pero su masa y radio siguen siendo 1
 3. Con su posicion, con su masa, y su radio

### Interfaz con el usuario
#### Tenemos los metodos
 * Aplicar fuerza
 * Actualizar particula
 * Colision con otra particula

Aplicar fuerza y actualizar la particula estan vinculado de una cierta manera, mas conceptual pero de igual forma conectados. Aplicar fuerza seria la forma de ir acumulando todo lo que se le aplique a la particula, y actualizar la particula es usando todas esas fuerzas acumuladas aplicarlas al movimiento de la particulla y reiniciando las fuerzas ya que no son acumulativas

La colision entre dos particulas usamos a la particula como circulos, por lo tanto si la distancia entre las dos particulas es menor a la suma de sus radios significa que estan chocando

Todavia creo que le faltan cosas a la clase de particula pero todavia no veo que es lo que falta, entonces voy a avanzar e intentar usarla para ver que es lo que me falta para completarla