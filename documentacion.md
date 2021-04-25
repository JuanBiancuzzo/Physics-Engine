# Documentacion
Aca voy a tener todos (por lo menos mi intento es que sea lo mas posible) los detalles tecnicos de lo que este haciendo, y porque lo estoy haciendo de tal manera

#### Menu:
 * [Vectores](#Vector)
 * [Particulas](#Particula)
    * [Entidad] (#Entidad)
 * [Area] (#Area)
 * [Quadtree](#QuadTree)
 * [Nodo](#Nodo)

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
Una particula va a tener una posicion, una velocidad, masa y un radio. Como ahora agregue un QuadTree como forma de guardar las posiciones de las particulas lo que hice es que la particula herede de la clase Entidad, que mas adelante veremos que tiene.

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

### Entidad
El motivo por el cual hice la clase entidad es para que se pueda usar cualquier tipo de dato para guardarse en el QuadTree, por lo tanto si uno quiere guardar una particula, esa clase particula tiene que heredar de la clase entidad y ya se puede usar en el QuadTree sin problemas

La clase entidad es bastante simple, tiene una posicion, un index, y una referencia de donde esta guardado. Todo esto no lo deberia ver el usuario que uso mi codigo, pero el motivo es interesante. La posicion es necesaria para saber en donde se tiene que insertar, el index es para saber la posicion en un array para que sea mucho mas facil eliminar, y la referencia a donde esta guardado es para saber si se tiene que actualizar despues de moverse. Todo esto se entendera mucho mas al ver QuadTree y por consecuencia sus nodos

## Area
De una forma parecida a los vectores, cree una clase que representa un rectangulo para simplificar el codigo al tener un tipo de dato relativamente simple y que se va a usar razonablemente en los quadtrees

### Constructor 
Para crear un rectangulo si o si tiene que tener una posicion, pero no necesariamente determinar el largo y el alto, ya que se tomaran como que son ambos 1.0f

### Interfaz con el usuario
Tanto la posicion como el largo y el ancho son accesibles para el usuario pero para este proyecto estan publicos porque no quiero crear funciones que me devuelvan esos valores. Los podria hacer constantes pero despues si realmente necesito cambiarlos puede hacerse molesto, entonces los dejo como publicos por eso

#### Tenemos los metodos
 * Si contiene una entidad
 * Si intersecta otra area

Las dos funciones son bastante simples
* Si la entidad (basandonos en su posicion) esta adentro o en alguno de sus bordes entonces la contiene,  
* Si los rectangulos se intersectan devuelve true

Como aclaracion a esto ultimo, yo no estoy tomando que dos rectangulos se intersectan cuando comparten un borde, es decir que si un rectangulo tiene el lado derecho en 3, y otro rectangulo tiene su lado izquierdo en 3, entonces esos dos rectangulos no intersectan, y esto es porque mas adelante con los quadtree cuando se dividen las regiones todos van a compar dos lados con otras divisiones y yo no quiero contar esas divisiones por tienen un borde en comun

## QuadTree
Un quadtree un tipo de arbol que tiene 4 hijos, yo lo estoy usando para dividir un rectangulo (que podria ser la pantalla) en cuatro regiones para tener mas resolucion. La idea de implementar un tipo de dato de este estilo en vez de simplemente almacenar las particulas en un array, es la complejidad computacional que viene en hacer operaciones en un array

Un ejemplo de esto es si tenemos que calcular que particulas estan en una region del espacio, si tenemos n particulas, entonces tenemos que hacer n comparaciones si tenemos un array porque cualquier particula podria estar en esa region del espacio, mientras que seria log(n) en el caso de ser un arbol, porque nos permite eliminar "por defecto" particulas que no esten cerca de esa region

### Constructor
Para crear un quadtree vamos a necesitar si o si el area que se quiera cubrir del espacio, para esto necesitamos una instancia de un rectangulo

### Interfaz con el usuario
Tiene como variable publica el area que ocupa, pero como privada la raiz del arbol, esto lo hice porque todo lo que se necesita hacer con la raiz ya se puede hacer con los metodos que veremos a continuacion. Esto de tenerlo en privado la raiz en una forma de proteger la delicado que es, y es delicado porque yo cuando lo programe asumo que nadie mas puede tocar los valores por lo tanto si se modifican pueden hacer que el arbol se rompa bastante facil

#### Tenemos los metodos
 * Insertar una entidad
 * Eliminar una entidad
 * Actualizar la posicion de una entidad
 * Buscar las entidades en una region

Como mencione parcialmente antes, la clase quadtree es realmente una interfaz entre el arbol y el usuario, entonces
 * Para insertar revisamos si la entidad esta en su area, en caso de ser cierto entonces le pedimos a la raiz que inserte la entidad
 * Para eliminar es igual, verificamos que lo contiene y en el caso de que si entonces le pedimos a la raiz que elimine la  entidad
 * Para buscar primero hacemos que el contador este en 0, siempre facilita las cosas comprobar eso, despues verificamos que el area que estemos buscando intersecte con el area de quadtree, y le pedimos a la raiz para que busque
 * El actualizar hace algo por lo menos mas interesante, la idea es ver si la entidad se movio de subdivision, porque no tiene sentido hacer todo un proceso si ya esta perfecto como esta, entonces para eso le pedimos a la raiz que nos la subdivision (el nodo) en el que estaria con esta nueva poscion (para ver como se hace eso ir [aca](#Buscar-hoja)), si esto es diferente con el que tenia, entonces le pedimos a la raiz que lo actualice
 
 Aca vemos porque la clase entidad necesitaba esa referencia a donde esta guardado, porque no ayuda a optimizar esta situacion

## Nodo
El nodo es la parte principal del quadtree e intento que sea lo mas optimizado posible, por lo que tengo que ir un poco por el lado de que no es tan seguro de usar si tenes acceso a los datos internos, por eso mismo en la clase QuadTree se tiene a la raiz como privado

### Contructor
Al igual que el quadtree para crearlo se necesita una instancia de rectangulo

### Interfaz con el usuario
Cabe aclarar que realmente el usuario no deberia modificar nada, por eso solo tengo como propiedad publica el area (y es publica por los motivos que aclare en la seccion de [area](#Area)) todo lo demas es privado

Lo que esta en privado primero es la capacidad de entidades que puede tener una subdivision, y la capacidad de subdivisiones que siempre va a ser 4 pero es bueno tener una constante en la misma clase. Tenemos un bool que nos aclara que esta subdivido que va a ser util en general porque nos permite saber si esta divido sin tener que comprobar cualquier otra cosa, un array de entidades, la cantidad de entidades que tenemos en ese array, y un array de subdivisiones

Al principio tenia pensado usar la libreria de vector, porque permite hacer arrays que pueden aumentar de tamaño, ya tienen incorporado el contador, y puedo saber el tamaño, pero la forma de trabajar con ese tipo de lista se volvio mas complicado por la forma de eliminar item que no era tan simple como dar un indice, la ineficiencia de tener que copiar la entidad cada vez que se agregaba a la lista. Entonces preferi trabajar simplemente con arrays de puntero que es mucho mas simple

### Tenemos los metodos
 * [Insertar una entidad](#Insertar-una-entidad)
 * [Eliminar una entidad](#Eliminar-una-entidad)
 * [Actualizar la posicion de una entidad](#Actualizar-una-entidad)
 * [Buscar las entidades en una region](#Buscar-en-region)
 * [Buscar una hoja segun una posicion](#Buscar-hoja)
 * [Calcular un indice segun una posicion](#Calcular-un-indice)
 * [Subdividir](#Subdividir)
 * [Juntar](#Juntar)

Los ultimos 3 son metodos privados, pero como tecnicamente todos deberian ser privados decidi mencionarlos a todos

#### Insertar una entidad
El proceso es muy parecido a cualquier arbol, y algo tener en cuenta es que la variable responsable de contar cuantas entidades tiene no se limita a las que tiene en el array de entidades, sino que son todas las entidades que hay en esa area

Lo primero que hacemos es comprobar si tenemos capacidad para agregar una entidad nueva, en el caso que sea asi entonces la agregamos al array, sumamos uno mas a la cantidad de entidades, y la particula ahora va a tener como index la posicion en este array, como tambien una referencia al nodo en que se inserto

En el caso de que no sea asi entonces vamos a calcular el indice (para ver como se calcula el indice ir [aca](#Calcular-un-indice)) que nos va a dar el indice de la subdivision en la que tendria que ser insertado, en el caso que no este divido se lo subdivide (para ver como se hace la subdivison ir [aca](#Subdividir)), usando el indice lo usamos en el array de subdivisiones y le pedimos que inserte esa entidas; por ultimo sumamos uno al contador de entidades

#### Eliminar una entidad
Eliminar es muy parecido al insertar, tenemos dos casos el caso donde no esta dividido por lo tanto usamos el indice que tiene la entidad (para eso era util) y la intercambiamos con el ultimo, y acortamos el array. Entonces esta operacion de eliminar en un array que sin el indice es de O(n) ahora es O(1)

En caso de que este dividida, calculamos el indice para la subdivision (para ver como se calcula el indice ir [aca](#Calcular-un-indice)) con eso le pedimos a la subdivision correspondiente a su indice, que elimine esa entidad, ahora como esta elimina, puede ser que este la posibilidad de juntar (para ver como se juntan ir [aca](#Juntar)), y esta se da cuando la cantidad de entidades en todo su area es menor a la capacidad 

Un ejemplo de esto seria imaginemos que toda la pantalla es la raiz, y tenemos una capacidad de 3 entidades, entonces agregamos 3 entidades y por ahora sigue siendo solo la raiz. Cuando agregamos una cuarta entidad se va a tener que subdividir y tendremos izquierda arriba, derecha arriba, izquierda abajo y derecha abajo. Ahora digamos que eliminamos una entidad entonces la raiz va a tener 3 entidades (porque recordemos que todas las subdivisiones tiene un contador de todas las entidades que tienen y no estan limitadas por la capacidad) por lo tanto tiene capacidad la raiz para tener todas las entidades y las junta en su lista de entidades y elimina las subdivisiones

#### Actualizar una entidad
Este metodo es coinciderablemente mas facil en comparacion a insertar y a eliminar, pero tiene un detalle, al principio yo pensaba que se necesitaba solamente eliminar y despues insertar la entidad que nos pasan, pero eso esta mal porque la forma de eliminar como vimos esta guiada por la posicion de la entidad entonces si esta cambio no vamos a encontrarla, entonces lo unico que vamos a lograr es eliminar una que no deberia ser eliminada y duplicar una que ya teniamos 

Entonces la forma que funciona este metodo es crear una entidad descartable, esta se le copia todas las propiedades de la entidad nueva pero su posicion va a estar dada por la posicion de la subdivision en la que este, esto nos va a asegurar encontrar la entidad, y con su indice va a ser facil eliminarla

Despues simplemente insertamos la entidad con la posicion nueva, y listo

#### Buscar en region
Primero tenemos que ver si el area de la subdivision intersecta con lo que estoy buscando (para ver como se hace la interseccion ir [aca](#Area)) y esto que nos permite buscar de forma mas eficiente que un array porque podemos eliminar zonas enteras por algo tan simple como esta comprobacion. Si esta dividido vamos a todas las subdivisiones y que se busque segun esta region

En el caso de que no este subdividido, entonces verificamos cual de todas las particulas que tiene la subdivision pertenecen a esa region (para ver como comprobar si una entidad pertenece a un area ir [aca](#Area))

Notemos como la operacion de buscar es realmente O(n) pero nos ahorramos revisar todas las particulas por la estructura del arbol que se divide por regiones

#### Buscar hoja
Este metodo esta pensado para comprobar si una entidad cambio de subdivision, entonces vamos a buscar esa hoja basandonos en la posicion de una entidad

Lo primero que hacemos es comprobar si esta dividido, en el caso que no lo este, significa que estamos en una hoja entonces devolvemos esa direccion, pero sino entonces calculamos el indice (para ver como se calcula el indice ir [aca](#Calcular-un-indice)) y con eso vamos a la subdivision siguiente y preguntamos que nos de la hoja

#### Calcular un indice
Lo primero que tenemos que entender es el orden en el que las subdivisiones estan. Las subdivision 0 va a estar a la izquierda arriba, la 1 derecha arriba, la 2 izquierda abajo y la 3 derecha abajo. 

Entonces lo primero es tener un vector de la posicion de la entidad con respecto a la posicion de la subdivision. Ahora veamos que si la x es negativa tenemos 0 o 2, si es positiva entonces es 1 o 3, es decir que aumenta uno, y veamos que si la y es positiva entonces es 0 o 1, si es negativa entonces es 2 o 3, es decir que aumenta dos

Por lo tanto tenemos que mapear el signo de x a 0 o 1, e y a 1 o 0, y despues hacer x + 2y

#### Subdividir
Para subdividir, primero tenemos que crear las subdivisiones por lo tanto tenemos que asignarles sus nuevas posiciones, y como es bastante trivial como se logra eso

Yo lo intente de hacer una forma algo eficiente donde no tengo que escribir tanto codigo, entonces primero calculo los nuevos anchos y alto que es la mitad del actual, y siguiendo el orden que propuse con [calcular el indice](#Calcular-un-indice) voy sumando o restando el ancho y/o el alto como corresponda. Lamentablemente no pude encontrar una forma de lograrlo con un solo for loop pero por lo menos es con dos y bastante corto

Despues tenemos que insertar todas las particulas que tenia este nodo, a las subdivisiones entonces calculamos el indice, y le pedimos a la subdivision correspondiente que lo inserte

Por ultimo ponemos que este nodo si esta dividido

Nota:
Un error que tiene este arbol es que si yo tengo una capacidad de entidades de 4 y pongo 4 entidades en un mismo lugar, y despues agrego una quinta entidad en ese mismo lugar, se va a producir un loop infinito porque los va a subdividir, los va a insertar y como sobrepasa su capacidad se subdivide y asi hasta que se rompa, entonces tengo que implementar una forma en la que no pueda insertar si hay una entidad ya en ese lugar

#### Juntar
Este metodo es relativamente simple, porque usa otros metodos para hacer lo mas complicado. Primero comprobamos que la cantidad de entidades que tiene sea menor que la capacidad, que nos dice que podemos juntar, y para recolectar las entidades de las subdivisiones usamos el metodo buscar en region (para ver como funciona ese metodo ir [aca](#Buscar-en-region)) con el array de las entidades que tiene este nodo

Despues a todas las nuevas entidades le asignamos su nuevo indice y que la referencia de donde vienen es este nodo

Por ultimo ponemos que no esta dividido este nodo y eliminamos las subdivisiones