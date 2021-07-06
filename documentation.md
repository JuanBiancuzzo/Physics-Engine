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

## Sistema de particulas

