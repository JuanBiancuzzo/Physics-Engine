# Explicacion
Aca voy a tener todos (por lo menos mi intento es que sea lo mas posible) los detalles tecnicos de lo que este haciendo, y porque lo estoy haciendo de tal manera

### Temas
* [Vectores](#Vector)
* [Cuerpos rigidos](#Cuerpos-rigidos)
* [Quadtree](#Quadtree)
* [Sistema de particulas](#Sistema-de-particulas)

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

## Cuerpos rigidos

## Quadtree

## Sistema de particulas


