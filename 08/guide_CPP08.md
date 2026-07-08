# CPP08 — Templated Containers, Iterators and Algorithms

Guia de estudio y defensa para el modulo CPP08 de la escuela 42.

---

## Indice

1. [Iteradores en la STL](#1-iteradores-en-la-stl)
2. [Como funciona std::find internamente](#2-como-funciona-stdfind-internamente)
3. [ex00 — easyfind](#3-ex00--easyfind)
4. [ex01 — Span](#4-ex01--span)
5. [ex02 — MutantStack](#5-ex02--mutantstack)
6. [Metodos template dentro de una clase](#6-metodos-template-dentro-de-una-clase)
7. [Preguntas de defensa con respuestas](#7-preguntas-de-defensa-con-respuestas)
8. [Compilacion rapida](#8-compilacion-rapida)

---

## 1. Iteradores en la STL

Un iterador es un objeto que actua como puntero a un elemento dentro de un contenedor. Permite recorrer el contenedor sin conocer su implementacion interna.

La STL define cinco categorias de iteradores:

### 1.1 Input iterator

Solo permite leer hacia adelante, un paso a la vez.

```cpp
*it;   // leer
++it;  // avanzar
```

### 1.2 Output iterator

Solo permite escribir hacia adelante. No permite lectura.

```cpp
*it = valor;  // escribir
++it;         // avanzar
```

### 1.3 Forward iterator

Combina lectura y escritura hacia adelante. Permite pasar multiples veces por los mismos elementos. `std::forward_list` usa este tipo.

```cpp
*it;          // leer
*it = valor;  // escribir
++it;         // avanzar (solo hacia adelante)
```

### 1.4 Bidirectional iterator

Como el forward, pero tambien puede retroceder. `std::list`, `std::set`, `std::map` usan este tipo.

```cpp
++it;  // avanzar
--it;  // retroceder
```

### 1.5 Random access iterator

El mas potente. Permite saltar a cualquier posicion en tiempo constante. `std::vector`, `std::deque` y los punteros raw usan este tipo.

```cpp
it + n;    // saltar n posiciones
it - n;    // retroceder n posiciones
it[n];     // acceso por indice
it1 < it2; // comparacion de orden
```

### Tabla resumen

| Categoria | Leer | Escribir | Avanzar | Retroceder | Salto aleatorio |
|---|---|---|---|---|---|
| Input | si | no | si | no | no |
| Output | no | si | si | no | no |
| Forward | si | si | si | no | no |
| Bidirectional | si | si | si | si | no |
| Random access | si | si | si | si | si |

Contenedores y sus tipos de iterador:

| Contenedor | Tipo de iterador |
|---|---|
| `std::vector` | Random access |
| `std::deque` | Random access |
| `std::list` | Bidirectional |
| `std::set` | Bidirectional |
| `std::map` | Bidirectional |
| `std::stack` | Ninguno (adaptador) |

---

## 2. Como funciona std::find internamente

`std::find` es un algoritmo declarado en `<algorithm>`. Implementacion conceptual:

```cpp
template <typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T& value)
{
    while (first != last)
    {
        if (*first == value)
            return first;
        ++first;
    }
    return last;
}
```

Recorre el rango `[first, last)` usando iteradores. Si encuentra el valor, devuelve el iterador que apunta a el. Si llega al final, devuelve `last`.

Contrato: si `find` devuelve `end()`, el elemento no esta en el contenedor.

---

## 3. ex00 — easyfind

### Implementacion

```cpp
// easyfind.hpp
#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <stdexcept>

template <typename T>
typename T::iterator easyfind(T& container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}

#endif
```

### Como funciona

Recibe cualquier contenedor `T` que tenga metodos `begin()` y `end()` que devuelvan iteradores. Delega la busqueda en `std::find`. Si no encuentra el valor, lanza una excepcion en lugar de devolver `end()`.

El tipo de retorno `typename T::iterator` es necesario porque el compilador no puede saber de antemano si `T::iterator` es un tipo. La palabra clave `typename` le dice explicitamente que es un tipo.

### Uso con distintos contenedores

```cpp
// Con vector
std::vector<int> vec;
vec.push_back(10);
vec.push_back(25);
vec.push_back(42);

std::vector<int>::iterator it = easyfind(vec, 25);
// *it == 25

// Con list
std::list<int> lst;
lst.push_back(3);
lst.push_back(7);
lst.push_back(42);

std::list<int>::iterator it2 = easyfind(lst, 42);
// *it2 == 42

// Valor no encontrado: lanza std::runtime_error
try {
    easyfind(vec, 99);
} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

### Por que no funciona con std::map

`std::map<K, V>` almacena pares `std::pair<const K, V>`. La comparacion `*it == value` donde `value` es un `int` fallaria porque se estaria comparando un `std::pair` con un `int`.

Ademas, el proposito de `std::map` es buscar por clave con `find()` propio en O(log n), no recorrer linealmente.

---

## 4. ex01 — Span

### Concepto

`Span` es una clase que almacena hasta `N` enteros y puede calcular la distancia minima y maxima entre cualquier par de ellos.

- **shortestSpan**: diferencia minima entre cualquier par de numeros.
- **longestSpan**: diferencia maxima entre cualquier par de numeros.

### Archivos

**Span.hpp**

```cpp
#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <stdexcept>

class Span
{
public:
    Span(unsigned int n);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int n);

    template <typename Iterator>
    void addRange(Iterator begin, Iterator end)
    {
        while (begin != end)
        {
            addNumber(*begin);
            ++begin;
        }
    }

    int shortestSpan() const;
    int longestSpan() const;

    class FullException : public std::exception
    {
    public:
        const char* what() const throw();
    };

    class NotEnoughNumbersException : public std::exception
    {
    public:
        const char* what() const throw();
    };

private:
    unsigned int      _maxSize;
    std::vector<int>  _data;
};

#endif
```

### Por que shortestSpan ordena una copia y no el original

`shortestSpan` es `const`: no puede modificar los miembros del objeto. Ordenar `_data` directamente seria una modificacion.

Ademas, ordenar el contenedor interno cambiaria el orden de insercion de los datos del usuario, lo que seria un efecto secundario inesperado.

Por eso se crea una copia local `sorted`, se ordena esa copia y se trabaja sobre ella. El original `_data` permanece intacto.

```cpp
int Span::shortestSpan() const
{
    if (_data.size() < 2)
        throw NotEnoughNumbersException();

    std::vector<int> sorted(_data);
    std::sort(sorted.begin(), sorted.end());

    int shortest = INT_MAX;
    for (std::size_t i = 1; i < sorted.size(); i++)
    {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < shortest)
            shortest = diff;
    }
    return shortest;
}
```

### Por que pares adyacentes tras ordenar dan el span minimo

Dado un conjunto de numeros ordenados `x1 <= x2 <= ... <= xn`, la diferencia entre cualquier par no adyacente `xj - xi` (con `j > i+1`) es mayor o igual que la diferencia entre sus vecinos inmediatos, porque es la suma de diferencias adyacentes intermedias. Por tanto, la diferencia minima global siempre se encuentra entre algun par adyacente.

```
Ejemplo: {3, 9, 6, 17, 11}
Ordenado: {3, 6, 9, 11, 17}
Diferencias adyacentes: 3, 3, 2, 6
Menor diferencia: 2 (entre 9 y 11)
```

### Por que longestSpan usa min_element y max_element

El span mas largo es simplemente `max - min` del conjunto entero. No hace falta ordenar:

```cpp
int Span::longestSpan() const
{
    if (_data.size() < 2)
        throw NotEnoughNumbersException();

    int minVal = *std::min_element(_data.begin(), _data.end());
    int maxVal = *std::max_element(_data.begin(), _data.end());
    return maxVal - minVal;
}
```

`std::min_element` y `std::max_element` recorren el contenedor en O(n).

### Uso de addRange

`addRange` permite insertar un rango de iteradores de golpe:

```cpp
std::vector<int> nums;
for (int i = 0; i < 10000; i++)
    nums.push_back(std::rand());

Span large(10000);
large.addRange(nums.begin(), nums.end());  // inserta 10000 numeros de una vez
```

Funciona con listas, deques, o cualquier contenedor con iteradores:

```cpp
std::list<int> lst;
lst.push_back(1);
lst.push_back(2);
lst.push_back(3);

Span sp(10);
sp.addRange(lst.begin(), lst.end());
```

---

## 5. ex02 — MutantStack

### El problema con std::stack

`std::stack` es un adaptador de contenedor. Envuelve internamente otro contenedor (por defecto `std::deque<T>`) y solo expone la interfaz LIFO: `push`, `pop`, `top`, `size`, `empty`.

`std::stack` **no tiene iteradores** por diseno. Exponer iteradores romperia esa abstraccion.

Sin embargo, el estandar especifica que el contenedor interno se almacena en un miembro protegido llamado `c`. Esto permite acceder a el desde clases derivadas.

### Implementacion

```cpp
// MutantStack.hpp
#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
    MutantStack() {}
    MutantStack(const MutantStack& other) : std::stack<T>(other) {}
    MutantStack& operator=(const MutantStack& other)
    {
        std::stack<T>::operator=(other);
        return *this;
    }
    ~MutantStack() {}

    typedef typename std::stack<T>::container_type::iterator         iterator;
    typedef typename std::stack<T>::container_type::const_iterator   const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;

    iterator       begin() { return this->c.begin(); }
    iterator       end()   { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end()   const { return this->c.end(); }
};

#endif
```

### Que es this->c

`this->c` es el miembro protegido que `std::stack` usa para almacenar el contenedor interno:

```cpp
// Dentro de std::stack (simplificado)
template <typename T, typename Container = std::deque<T> >
class stack {
protected:
    Container c;  // accesible desde clases derivadas
};
```

Al heredar de `std::stack<T>`, `MutantStack` puede acceder a `c` directamente. Ese `c` es un `std::deque<int>` (por defecto), y un deque si tiene iteradores.

La notacion `this->` fuerza al compilador a buscarlo en la clase base (necesario dentro de templates).

### Uso

```cpp
MutantStack<int> mstack;

mstack.push(5);
mstack.push(17);
mstack.push(3);
mstack.push(737);
mstack.push(0);

// Comportamiento de pila normal
std::cout << mstack.top() << std::endl;  // 0
mstack.pop();

// Iteracion de fondo a tope (orden de insercion)
MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
while (it != ite)
{
    std::cout << *it << std::endl;
    ++it;
}
// Imprime: 5, 17, 3, 737
```

---

## 6. Metodos template dentro de una clase

En C++98, es posible declarar un metodo template dentro de una clase no-template. **La definicion del metodo template debe estar en el header**.

Esto ocurre porque los templates no generan codigo hasta que se instancian. Si la definicion estuviera en el .cpp, el compilador no la veria al compilar otros archivos.

### Caso de Span::addRange

`Span` no es una clase template, pero `addRange` si es un metodo template:

```cpp
// En Span.hpp — definicion completa en el header
class Span
{
public:
    template <typename Iterator>
    void addRange(Iterator begin, Iterator end)
    {
        while (begin != end)
        {
            addNumber(*begin);
            ++begin;
        }
    }
};
```

Cuando el compilador ve `sp.addRange(nums.begin(), nums.end())`, deduce que `Iterator` es `std::vector<int>::iterator` y genera el codigo especifico para ese tipo.

### Por que addRange llama a addNumber

`addNumber` contiene la logica de validacion (comprueba si el Span esta lleno y lanza `FullException`). Si `addRange` insertara directamente en `_data`, saltaria esa proteccion. Al llamar a `addNumber` en bucle, cada insercion pasa por la validacion.

---

## 7. Preguntas de defensa con respuestas

### Por que easyfind lanza una excepcion en lugar de devolver end()?

El enunciado pide que la funcion indique el fallo mediante excepciones. Lanzar una excepcion hace el fallo explicito e imposible de ignorar. El iterador `end()` es valido como valor de retorno de error solo cuando el cliente conoce el contenedor, pero `easyfind` es generica.

### Por que easyfind no funciona con std::map?

Los iteradores de `std::map<K, V>` apuntan a `std::pair<const K, V>`, no a valores sueltos. `std::find` intenta comparar `*it == value` donde `value` es un `int`. Comparar un `std::pair` con un `int` es un error de tipos.

Ademas, buscar en un map por valor (no por clave) tiene poco sentido semantico. El map esta indexado por clave.

### Como calculas el shortestSpan sin modificar el array original?

Se crea una copia del vector `_data` en una variable local `sorted`:

```cpp
std::vector<int> sorted(_data);
std::sort(sorted.begin(), sorted.end());
```

Esta copia se ordena. El original `_data` no se toca.

### Por que ordenar y comparar adyacentes garantiza el span minimo?

En un conjunto ordenado, la diferencia entre cualquier par no adyacente es la suma de diferencias adyacentes intermedias, por lo que siempre es mayor o igual. Por tanto, la diferencia minima global siempre se encuentra entre algun par adyacente. No hace falta comparar todos los pares posibles (O(n^2)); basta con un recorrido lineal sobre el array ordenado.

### Por que no ordenas el array original en shortestSpan?

Porque `shortestSpan` es un metodo `const`: no puede modificar el estado del objeto. Ademas, ordenar el contenedor interno cambiaria el orden de los datos del usuario, lo que seria un efecto secundario inesperado. La copia local respeta el principio de minima sorpresa.

### Que es this->c en MutantStack?

`c` es el miembro protegido de `std::stack` que almacena el contenedor interno (por defecto `std::deque<T>`). Al heredar de `std::stack`, `MutantStack` tiene acceso a ese miembro. Se usa `this->c` porque dentro de una clase template el compilador no resuelve automaticamente los nombres de miembros heredados; el prefijo `this->` fuerza esa resolucion.

### Por que std::stack no expone iteradores por defecto?

Porque `std::stack` es un adaptador cuyo proposito es modelar una pila (LIFO). Una pila semanticamente solo permite acceder al elemento del tope. Exponer iteradores romperia esa abstraccion. El contenedor interno `c` es `protected` para permitir que clases derivadas extiendan el comportamiento si lo necesitan, pero el uso normal queda restringido.

### Que contenedor usa std::stack internamente?

Por defecto, `std::deque<T>`. Se puede cambiar al instanciar:

```cpp
std::stack<int, std::vector<int> > s;  // usa vector
std::stack<int, std::list<int> >   s;  // usa list
```

El contenedor debe soportar `back()`, `push_back()` y `pop_back()`.

### Podria MutantStack usar std::list como contenedor interno?

Si. `std::list` cumple los requisitos:

```cpp
MutantStack<int, std::list<int> > ms;
```

Como `MutantStack` hereda de `std::stack<T, Container>`, el miembro `c` seria un `std::list<int>`. Los typedef de iteradores apuntarian a `std::list<int>::iterator`, que es bidireccional. La iteracion funcionaria igual.

### Que diferencia hay entre MutantStack e iterar directamente sobre un std::deque?

Funcionalmente, si se usa `std::deque`, el resultado de la iteracion es el mismo. La diferencia es **semantica**:
- `std::deque` no tiene semantica de pila: permite insertar por ambos extremos.
- `MutantStack` tiene la interfaz completa de `std::stack` (push, pop, top, size, empty) mas iteracion. Comunica que es una pila LIFO con capacidad adicional de iteracion.

### Por que addRange es un metodo template dentro de una clase?

Porque queremos que `addRange` acepte cualquier tipo de iterador sin restringir el contenedor origen. Al hacerlo template:

```cpp
template <typename Iterator>
void addRange(Iterator begin, Iterator end);
```

Funciona con iteradores de `std::vector`, `std::list`, `std::deque`, arrays en bruto, o cualquier otra secuencia. El compilador instancia la funcion para cada tipo de iterador que se use.

La clase `Span` en si no necesita ser template porque el tipo de dato (int) esta fijo. Solo el metodo `addRange` necesita ser generico.

---

## 8. Compilacion rapida

```bash
# ex00 - easyfind
cd /Users/marta/Documents/PROJECTS/CPP/08/ex00 && make && ./easyfind

# ex01 - Span
cd /Users/marta/Documents/PROJECTS/CPP/08/ex01 && make && ./span

# ex02 - MutantStack
cd /Users/marta/Documents/PROJECTS/CPP/08/ex02 && make && ./mutantstack
```

Compilacion manual rapida (sin Makefile):

```bash
c++ -Wall -Wextra -Werror -std=c++98 main.cpp -o easyfind
c++ -Wall -Wextra -Werror -std=c++98 main.cpp Span.cpp -o span
c++ -Wall -Wextra -Werror -std=c++98 main.cpp -o mutantstack
```

---

## Resumen de conceptos clave

| Concepto | Donde aparece | Idea central |
|---|---|---|
| Template de funcion | easyfind | Funcion generica para cualquier contenedor con iteradores |
| typename en tipo de retorno | easyfind | Necesario cuando el tipo depende de un parametro template |
| Copia para no modificar | Span::shortestSpan | Respetar const y no alterar datos del usuario |
| Pares adyacentes tras ordenar | Span::shortestSpan | El span minimo siempre esta entre elementos contiguos en orden |
| min/max_element | Span::longestSpan | Algoritmo STL en O(n) sin necesidad de ordenar |
| Miembro protegido heredado | MutantStack::this->c | Acceso al contenedor interno de std::stack desde clase derivada |
| Adaptador de contenedor | std::stack | Oculta el contenedor real, expone solo la interfaz LIFO |
| Template en metodo de clase | Span::addRange | Acepta cualquier tipo de iterador sin hacer template toda la clase |
