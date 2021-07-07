# Documentacion

En esta seccion voy a normal los objetos creados, cual son los metodos que tiene y se puedan llamar, y una breve explicacion de para que sirven. En caso de ver en mas en detalle las estructuras, y como se logra todo, ir [aca](explicaciones.md)

## Vista general

* [Vectores](#Vectores)
* [QuadTree](#QuadTree)
* [Sistema De Particulas](#Sistema-de-particulas)

## Vectores

Los vectores que implemente son de dos dimensiones, por lo que su constructor va a ser de esas dos variables, o se puede dejar vacio y seran .0f por defecto

```c++
Vector2 vector(1.0f, -2.0f);
```

Las operaciones que tienen son las suma, resta, multiplicacion por un escalar, multiplicacion escalar, y division.

```c++
// ejemplos
Vector2 vector1(1.0f, -2.0f), vector2(-3.0f, 1.0f);
float alpha = 2.0f;

Vector2 respuesta = vector1 + vector2;
respuesta *= alpha;
```

Tambien esta implementado el operador de igualdad, donde se tiene un rango de desfase de .01f

Tenemos los metodos:
* [Modulo](#Modulo)
* [Distancia](#Distancia)
* [Proyeccion](#Proyeccion)
* [Normal](#Normal)
* [Nulo](#Nulo)

### Modulo
El modulo, tambien su version cuadrada, es la definicion matematica de modulo, donde es la raiz cuadrada de los componente al cuadrado.
```c++
Vector2 vector(3.0f, 4.0f);

float res = vector.modulo(); // 5.0f
float res = vector.modulo_cuadrado(); // 25.0f
```

### Distancia
La distancia, tambien su version cuadrada, es la definicion matematica, donde es el modulo de la diferencia de los vectores
```c++
Vector2 vector1(3.0f, 4.0f), vector2(3.0f, 6.0f);

float res = vector1.distancia(vector2); // 2.0f
float res = vector1.distancia_cuadrada(vector2); // 4.0f
```

### Proyeccion
La proyeccion es la definicion matematica, donde es descompone el vector en la direccion dada
```c++
Vector2 vector(3.0f, 4.0f), dir(1.0f, .0f);

Vector2 res = vector.proyeccion(dir); // Vector2(3.0f, .0f)
```

### Normal
La normal es la definicion matematica, donde se divide el vector por su modulo
```c++
Vector2 vector(3.0f, 4.0f);

Vector2 res = vector.normal(); // Vector2(.6f, .8f)
```

### Nulo
Es una comprobacion si el vector es el vector nulo
```c++
Vector2 vector(3.0f, 4.0f);

bool res = vector.nulo(); // false
```

## QuadTree

La idea general de un quadtree es la forma de guardar y retornar valores, repartidos por un espacio, y en este caso un espacio bidimensional. Entonces primero tenemos un constructor que esta dado por su posicion, un ancho y un alto, de esta forma

```c++
QuadTree qt(Vector2(), 64.0f, 128.0f);
```

Y sus metodos estan dados por:
* [Insertar](#Insertar)
* [Actualizar](#Actualizar)
* [Eliminar](#Eliminar)
* [Buscar](#Buscar)

### Insertar
Es la forma de agregar una entidad al quadtree, donde la clase entidad son los requisitos minimos para poder ser insertados. La forma es la siguiente
```c++
Entidad *entidad = new Entidad();

bool logro_insertar = qt.insertar(entidad);
```

Va a devolver true si pudo insertarlo, es decir que si la entidad esta dentro de la region que pertenece el quadtree

### Actualizar
Cada vez que se mueva la entidad, esta se tiene que actualizar de la siguiente forma,
```c++
qt.actualizar(entidad);
```

Esto se va a encargar de mover lo necesario para despues encontrarlo

### Eliminar
Para poder sacarlo, podemos usar este metodo, y devuelve si pudo sacarlo. En el caso que no lo pudiera sacar, es forma de indicar que esa entidad no esta en el quadtree
```c++
qt.eliminar(entidad);
```

### Buscar
Es un metodo para encontrar todas las entidades que insersecta la region que se pase
```c++
AABB *region_de_busqueda = new AABB(Vector(), 20.0f, 20.0f);

std::vector<Entidad *> entidades = qt.buscar(region_de_busqueda);
```

## Sistema de particulas

