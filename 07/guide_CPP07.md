# CPP07 — Templates en C++98

Guia de estudio y defensa para el modulo CPP07 de la escuela 42.

---

## Indice

1. [Que son las Templates](#1-que-son-las-templates)
2. [Por que las Templates van en el header](#2-por-que-las-templates-van-en-el-header)
3. [Deduccion de tipos (Type Deduction)](#3-deduccion-de-tipos-type-deduction)
4. [ex00 — whatever.hpp: funciones template](#4-ex00--whateverhpp-funciones-template)
5. [ex01 — iter.hpp: funcion template con funcion como parametro](#5-ex01--iterhpp-funcion-template-con-funcion-como-parametro)
6. [ex02 — Array.hpp: clase template](#6-ex02--arrayhpp-clase-template)
7. [Template de funcion vs Template de clase](#7-template-de-funcion-vs-template-de-clase)
8. [Deep copy: por que es necesaria en Array](#8-deep-copy-por-que-es-necesaria-en-array)
9. [Requisitos del tipo T en cada ejercicio](#9-requisitos-del-tipo-t-en-cada-ejercicio)
10. [Preguntas de defensa con respuestas](#10-preguntas-de-defensa-con-respuestas)
11. [Compilacion rapida](#11-compilacion-rapida)

---

## 1. Que son las Templates

Una **template** (plantilla) es un mecanismo del lenguaje C++ que permite escribir codigo generico: codigo que funciona con cualquier tipo de dato sin duplicar la implementacion.

```cpp
// Sin templates: hay que repetir para cada tipo
void swap(int& a, int& b)     { int tmp = a; a = b; b = tmp; }
void swap(float& a, float& b) { float tmp = a; a = b; b = tmp; }

// Con templates: una sola definicion vale para todos los tipos
template <typename T>
void swap(T& a, T& b) { T tmp = a; a = b; b = tmp; }
```

El compilador **instancia** la template en tiempo de compilacion: cuando ve `swap(x, y)` con `x` e `y` de tipo `int`, genera internamente el codigo `swap<int>`.

---

## 2. Por que las Templates van en el header

El compilador necesita ver la implementacion completa de la template en el momento en que la instancia. Si la implementacion esta en un .cpp separado ya compilado, el compilador no puede generar el codigo especifico para `T = int` o `T = std::string`.

**La solucion**: todo el codigo de la template — declaracion e implementacion — debe estar en el header:

```
main.cpp  -->  #include "whatever.hpp"
               El compilador ve la implementacion completa de swap<T>
               Puede generar swap<int>, swap<std::string>, etc.
```

---

## 3. Deduccion de tipos (Type Deduction)

Cuando llamas a una funcion template, el compilador puede deducir automaticamente el tipo `T` a partir de los argumentos:

```cpp
int a = 2, b = 3;
::swap(a, b);        // T se deduce como int automaticamente

std::string c = "hola", d = "mundo";
::swap(c, d);        // T se deduce como std::string
```

Si hay varios parametros con el mismo `T`, todos deben deducir el mismo tipo:

```cpp
// Esto falla: T no puede ser int y double a la vez
// ::min(1, 2.0);

// Correcto: ambos del mismo tipo
::min(1, 2);         // T = int
::min(1.0, 2.0);     // T = double
```

---

## 4. ex00 — whatever.hpp: funciones template

### Codigo completo

```cpp
#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template <typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
const T& min(const T& a, const T& b)
{
    return (b < a) ? b : a;
}

template <typename T>
const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

#endif
```

### Analisis

**`swap`**: intercambia los valores usando una variable temporal. Requiere que `T` sea copiable.

**`min`**: `return (b < a) ? b : a` — si `b` es estrictamente menor que `a`, retorna `b`; en caso de igualdad retorna `a`.

**`max`**: `return (a < b) ? b : a` — si `a` es menor que `b`, retorna `b`; en caso de igualdad retorna `a`.

**Por que `const T&` y no `T`?** Devuelve una referencia a uno de los argumentos originales, evitando una copia innecesaria. Seguro porque `a` y `b` son referencias a variables del llamador, no variables locales.

### Por que `::swap` en lugar de `swap`

`::` delante de un nombre indica "busca en el namespace global". Sin `::`, el ADL (Argument Dependent Lookup) podria encontrar `std::swap`, `std::min`, `std::max` y crear ambiguedad. Con `::swap` se llama obligatoriamente a la version del namespace global.

### Salida esperada

```
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```

---

## 5. ex01 — iter.hpp: funcion template con funcion como parametro

### Codigo completo

```cpp
#ifndef ITER_HPP
# define ITER_HPP

# include <cstddef>

template <typename T, typename F>
void iter(T* array, std::size_t length, F func)
{
    for (std::size_t i = 0; i < length; i++)
        func(array[i]);
}

#endif
```

### Analisis

`iter` recibe tres parametros:
- `T* array`: puntero al primer elemento del array.
- `std::size_t length`: numero de elementos (tipo correcto para tamanios e indices).
- `F func`: la funcion (o functor) a aplicar a cada elemento.

### Por que dos parametros de tipo: T y F?

Tener `F` como parametro de tipo independiente permite que `func` sea:
- Una funcion ordinaria: `void print(int x)`
- Un functor: objeto de una clase que sobrecarga `operator()`
- Una funcion template instanciada: `print<int>`

### Ejemplo de uso

```cpp
template <typename T>
void print(const T& x)
{
    std::cout << x << std::endl;
}

int arr[] = {1, 2, 3, 4, 5};
::iter(arr, 5, print<int>);
```

Nota: se escribe `print<int>` porque `print` es una funcion template y el compilador necesita saber que instanciacion usar al pasarla como argumento.

### Functores en C++98

Un **functor** es un objeto de una clase que define `operator()`. Permite pasar "funciones" con estado:

```cpp
struct Multiplier
{
    int factor;
    Multiplier(int f) : factor(f) {}
    void operator()(int& x) const { x *= factor; }
};

int arr[] = {1, 2, 3, 4, 5};
Multiplier times3(3);
::iter(arr, 5, times3);  // cada elemento se multiplica por 3
```

Los functores son el equivalente C++98 de los lambdas de C++11.

---

## 6. ex02 — Array.hpp: clase template

### Codigo completo

```cpp
#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>
# include <cstddef>

template <typename T>
class Array
{
public:
    Array() : _data(new T[0]()), _size(0) {}

    Array(unsigned int n) : _data(new T[n]()), _size(n) {}

    Array(const Array& other) : _data(new T[other._size]()), _size(other._size)
    {
        for (std::size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }

    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            delete[] _data;
            _size = other._size;
            _data = new T[_size]();
            for (std::size_t i = 0; i < _size; i++)
                _data[i] = other._data[i];
        }
        return *this;
    }

    ~Array() { delete[] _data; }

    T& operator[](std::size_t index)
    {
        if (index >= _size)
            throw std::out_of_range("Index out of bounds");
        return _data[index];
    }

    const T& operator[](std::size_t index) const
    {
        if (index >= _size)
            throw std::out_of_range("Index out of bounds");
        return _data[index];
    }

    unsigned int size() const { return static_cast<unsigned int>(_size); }

private:
    T*          _data;
    std::size_t _size;
};

#endif
```

### `new T[n]` vs `new T[n]()`

| Expresion | Tipos primitivos | Tipos con constructor |
|---|---|---|
| `new T[n]` | Valores indeterminados (basura) | Llama al constructor por defecto |
| `new T[n]()` | Inicializados a cero | Llama al constructor por defecto |

Para tipos primitivos, `new int[5]` deja basura; `new int[5]()` inicializa a 0.

### `operator[]` — por que devuelve referencia

Devolver `T&` permite:

```cpp
arr[0] = 42;   // Modifica directamente el elemento en memoria
               // Si devolviera T (copia), esta asignacion no tendria efecto
```

### Las dos versiones de `operator[]`

```cpp
T& operator[](std::size_t index);        // para objetos no-const: lectura y escritura
const T& operator[](std::size_t index) const;  // para objetos const: solo lectura
```

Sin la version const, no podrias usar `operator[]` sobre un `const Array<T>`.

### Destructor

```cpp
~Array() { delete[] _data; }
```

Es fundamental usar `delete[]` (con corchetes) para arrays. `delete` sin corchetes sobre un array es comportamiento indefinido.

---

## 7. Template de funcion vs Template de clase

| Aspecto | Template de funcion | Template de clase |
|---|---|---|
| Instanciacion | Automatica por deduccion de tipos | Manual: `Foo<int> obj` |
| Donde va el codigo | Todo en el header | Todo en el header |
| Ejemplo en CPP07 | `swap`, `min`, `max`, `iter` | `Array` |

```cpp
// Funcion template: T se deduce
::swap(a, b);            // T = int (deducido)

// Clase template: T siempre se especifica
Array<int> arr(5);       // T = int
Array<std::string> s(3); // T = std::string
```

---

## 8. Deep copy: por que es necesaria en Array

`Array` gestiona memoria dinamica: `_data` es un puntero al heap. La copia superficial (shallow copy) solo copiaria el valor del puntero, no los datos:

```cpp
Array<int> a(5);
a[0] = 42;

Array<int> b = a;   // shallow copy: b._data == a._data (misma memoria!)

b[0] = 99;          // modifica la memoria compartida
// a[0] tambien es 99 ahora (no esperado)

// Al destruir b: delete[] b._data
// Al destruir a: delete[] a._data  -> DOBLE LIBERACION -> undefined behavior
```

La deep copy soluciona esto asignando nueva memoria y copiando datos:

```cpp
Array(const Array& other) : _data(new T[other._size]()), _size(other._size)
{
    for (std::size_t i = 0; i < _size; i++)
        _data[i] = other._data[i];
}
```

**La regla de los tres (Rule of Three) en C++98**: si una clase necesita definir cualquiera de estos tres metodos, probablemente necesita los tres:
1. Destructor
2. Constructor de copia
3. Operador de asignacion

**Proteccion contra auto-asignacion**:

```cpp
Array& operator=(const Array& other)
{
    if (this != &other)  // evita "arr = arr"
    {
        delete[] _data;
        // ...
    }
    return *this;
}
```

Sin esta comprobacion, `arr = arr` haria `delete[] _data` y luego intentaria copiar datos de memoria ya liberada.

---

## 9. Requisitos del tipo T en cada ejercicio

### ex00 — `swap`, `min`, `max`

| Funcion | Requisitos de T |
|---|---|
| `swap` | Constructor de copia, operador de asignacion |
| `min` | Operador `<` |
| `max` | Operador `<` |

### ex01 — `iter`

`T` no tiene requisitos directos. Los requisitos dependen de lo que haga `func` con el elemento. `F` debe ser llamable con un argumento de tipo `T&`.

### ex02 — `Array`

| Operacion | Requisitos de T |
|---|---|
| Construccion | Constructor por defecto (para `new T[n]()`) |
| Copia | Operador de asignacion |

---

## 10. Preguntas de defensa con respuestas

### Por que las templates van en el header y no en un .cpp?

El compilador necesita ver la implementacion completa de la template en el momento de instanciarla. Cuando compila `main.cpp` y encuentra `::swap<int>(a, b)`, tiene que generar el codigo especifico para `T=int` en ese momento. Si la implementacion estuviera en un `.cpp` ya compilado, el compilador no tendria acceso al codigo fuente. Poniendola en el header, cada unidad de traduccion que la incluye tiene la implementacion disponible.

### Que hace `::` delante de swap/min/max?

`::` indica "busca en el namespace global". Sin `::`, el ADL podria encontrar `std::swap`, `std::min`, `std::max` y crear conflicto. Con `::swap` llamamos siempre a la version del namespace global (la nuestra).

### Que pasa si T no tiene operador `<`?

El compilador no puede generar el codigo de `min` o `max`. El error ocurre en la instanciacion, no en la declaracion. Si nunca usas `min<MiTipo>()` donde `MiTipo` no tiene `operator<`, no hay error. Aparece solo al intentar generar el codigo concreto.

### Que diferencia hay entre `new T[n]` y `new T[n]()`?

Para tipos primitivos, `new T[n]` deja los valores sin inicializar (basura); `new T[n]()` los inicializa a cero. Para tipos con constructor por defecto, el resultado es identico en ambos casos. Usar `()` es la forma correcta y segura.

### Por que Array necesita deep copy?

Porque gestiona memoria dinamica con `_data`. La shallow copy solo copiaria el puntero, haciendo que dos objetos apunten a la misma memoria: modificar uno afecta al otro, y cuando ambos se destruyan, `delete[]` se llamaria dos veces sobre la misma memoria (comportamiento indefinido). La deep copy asigna nueva memoria y copia los datos.

### Que pasa si accedes fuera de rango en Array?

`operator[]` comprueba `index >= _size` y lanza `std::out_of_range("Index out of bounds")`. El llamador puede capturarla con `catch (const std::exception& e)`.

### Por que `operator[]` devuelve referencia y no valor?

Si devolviera `T` (copia), `arr[0] = 42` modificaria una copia temporal sin efecto sobre el array real. Con `T&`, modifica directamente el elemento en memoria. Ademas evita copias costosas para tipos grandes.

### Tienes dos versiones de operator[]?

Si. La version no-const (`T& operator[]`) se usa para objetos mutables: permite leer y escribir. La version const (`const T& operator[] const`) se usa para objetos const: solo permite leer. Sin la version const, no podrias usar `operator[]` sobre un `const Array<T>`.

### Puede iter recibir un lambda? (no en C++98)

No. Los lambdas son de C++11. La alternativa en C++98 es un **functor**: objeto de una clase que define `operator()`. Es el equivalente C++98 de un lambda.

### Que pasa si n=0 en el constructor de Array?

`new T[0]()` es valido en C++: reserva un bloque de cero elementos y devuelve un puntero valido. `_size` queda a 0. Cualquier acceso lanzara `std::out_of_range`. `delete[]` funciona correctamente. No hay undefined behavior.

---

## 11. Compilacion rapida

```bash
# ex00 - whatever
cd /Users/marta/Documents/PROJECTS/CPP/07/ex00 && make && ./whatever

# ex01 - iter
cd /Users/marta/Documents/PROJECTS/CPP/07/ex01 && make && ./iter

# ex02 - array
cd /Users/marta/Documents/PROJECTS/CPP/07/ex02 && make && ./array
```

Solo se compila `main.cpp` porque toda la logica de los headers (whatever.hpp, iter.hpp, Array.hpp) se incluye directamente. No hay archivos .cpp adicionales.

```bash
# Compilacion manual sin Makefile
c++ -Wall -Wextra -Werror -std=c++98 main.cpp -o whatever
c++ -Wall -Wextra -Werror -std=c++98 main.cpp -o iter
c++ -Wall -Wextra -Werror -std=c++98 main.cpp -o array
```

---

## Resumen de conceptos clave

| Concepto | Descripcion |
|---|---|
| Template | Mecanismo para codigo generico parametrizado por tipo |
| Instanciacion | El compilador genera codigo concreto para cada tipo usado |
| Type deduction | El compilador deduce T de los argumentos automaticamente |
| Header-only | Las templates deben estar completas en el header |
| `::` (global scope) | Fuerza la busqueda en el namespace global, evita ADL |
| `new T[n]()` | Inicializa elementos a valor por defecto / cero |
| Deep copy | Copia de datos, no de puntero; evita aliasing y doble free |
| Functor | Objeto con `operator()`, alternativa C++98 a los lambdas |
| `std::out_of_range` | Excepcion estandar para acceso fuera de rango |
| Rule of Three | Si defines uno de destructor/copy ctor/op=, define los tres |
