# Templates — Explicado desde cero

---

## El problema que resuelven

Imagina que quieres una función que devuelva el mayor de dos números:

```cpp
int mayor(int a, int b)
{
    return (a > b) ? a : b;
}
```

Funciona para `int`. Pero ¿y si necesitas comparar `double`? ¿O `char`?

```cpp
int    mayor(int a,    int b)    { return (a > b) ? a : b; }
double mayor(double a, double b) { return (a > b) ? a : b; }
char   mayor(char a,   char b)   { return (a > b) ? a : b; }
float  mayor(float a,  float b)  { return (a > b) ? a : b; }
```

El código es **idéntico** en las cuatro. Solo cambia el tipo. Estás
copiando y pegando la misma lógica cuatro veces. Si hay un bug, tienes
que arreglarlo en los cuatro sitios.

**Los templates resuelven exactamente esto:**

```cpp
template <typename T>
T mayor(T a, T b)
{
    return (a > b) ? a : b;
}
```

Una sola función. Funciona con cualquier tipo.

---

## BLOQUE 1 — Qué es un template

Un template es un **molde** que el compilador rellena con el tipo concreto
cuando lo usas.

```cpp
template <typename T>
T mayor(T a, T b)
{
    return (a > b) ? a : b;
}
```

- `template` — le dice al compilador "esto es un molde"
- `<typename T>` — `T` es un nombre de marcador de posición para el tipo.
  Podría llamarse `X`, `Tipo`, `Pato` — da igual. La convención es `T`.
- `T mayor(T a, T b)` — la función devuelve `T` y recibe dos `T`

Cuando lo usas:

```cpp
mayor(3, 7);        // T = int    → compilador genera mayor(int, int)
mayor(3.14, 2.71);  // T = double → compilador genera mayor(double, double)
mayor('a', 'z');    // T = char   → compilador genera mayor(char, char)
```

El compilador mira qué tipo le pasas y genera la versión correcta
automáticamente.

---

## BLOQUE 2 — Templates vs Polimorfismo dinámico

Ya conoces el polimorfismo dinámico de CPP06: `virtual` + `dynamic_cast`.
Los templates son otro tipo de polimorfismo — se resuelve en compilación,
no en ejecución.

```
POLIMORFISMO DINÁMICO (CPP06)       POLIMORFISMO ESTÁTICO (CPP07)
─────────────────────────────       ─────────────────────────────
virtual + herencia                  template <typename T>
Resuelto en EJECUCIÓN               Resuelto en COMPILACIÓN
El programa decide en runtime       El compilador decide antes de ejecutar
Más flexible (tipos desconocidos)   Más rápido (sin vtable, sin overhead)
Necesita herencia                   Funciona con cualquier tipo
```

**Analogía:**

- **Polimorfismo dinámico:** un actor que interpreta distintos personajes
  en escena. En el momento de actuar decide qué personaje es.
- **Templates:** una fotocopiadora con una plantilla. Antes de empezar,
  imprimes una copia específica para cada tipo. Más copias, pero más rápido
  en el momento de usar.

---

## BLOQUE 3 — Cómo funciona por dentro

Cuando el compilador encuentra esto:

```cpp
mayor(3, 7);
mayor(3.14, 2.71);
```

Genera literalmente dos funciones distintas en el binario:

```cpp
// Generado automáticamente para int
int mayor(int a, int b) { return (a > b) ? a : b; }

// Generado automáticamente para double
double mayor(double a, double b) { return (a > b) ? a : b; }
```

Por eso se llama **polimorfismo estático** — el compilador resuelve todo
antes de ejecutar. En tiempo de ejecución no hay ninguna decisión: el
código correcto ya está ahí.

Consecuencia: si llamas a `mayor` con 10 tipos distintos, el compilador
genera 10 funciones. El binario es más grande, pero más rápido.

---

## BLOQUE 4 — Template de función con ejemplo completo

```cpp
#include <iostream>

template <typename T>
T mayor(T a, T b)
{
    return (a > b) ? a : b;
}

int main()
{
    std::cout << mayor(3, 7)        << std::endl;   // 7
    std::cout << mayor(3.14, 2.71)  << std::endl;   // 3.14
    std::cout << mayor('a', 'z')    << std::endl;   // z
    std::cout << mayor(-1, -5)      << std::endl;   // -1
    return 0;
}
```

El compilador deduce el tipo automáticamente mirando los argumentos.
También puedes especificarlo a mano:

```cpp
mayor<int>(3, 7);       // forzar T = int
mayor<double>(3, 7);    // forzar T = double → convierte 3 a 3.0
```

---

## BLOQUE 5 — Template de clase

Los templates no son solo para funciones. Puedes hacer clases enteras
que funcionen con cualquier tipo.

**El ejemplo clásico: una caja que guarda cualquier cosa**

```cpp
template <typename T>
class Caja
{
private:
    T contenido;

public:
    Caja(T valor) : contenido(valor) {}

    T obtener() const { return contenido; }

    void mostrar() const
    {
        std::cout << "Caja contiene: " << contenido << std::endl;
    }
};
```

Uso:

```cpp
Caja<int>         cajaInt(42);
Caja<double>      cajaDouble(3.14);
Caja<std::string> cajaTexto("hola");

cajaInt.mostrar();     // Caja contiene: 42
cajaDouble.mostrar();  // Caja contiene: 3.14
cajaTexto.mostrar();   // Caja contiene: hola
```

Con clase template tienes que especificar el tipo entre `<>` — el
compilador no puede deducirlo solo.

---

## BLOQUE 6 — Varios parámetros de tipo

Un template puede tener más de un tipo:

```cpp
template <typename T, typename U>
void mostrarPar(T primero, U segundo)
{
    std::cout << primero << " y " << segundo << std::endl;
}

mostrarPar(42, 3.14);       // T=int, U=double
mostrarPar("hola", 'A');    // T=const char*, U=char
```

---

## BLOQUE 7 — La restricción: el tipo debe soportar la operación

Los templates no funcionan con cualquier tipo indiscriminadamente. El
tipo `T` tiene que ser capaz de hacer lo que le pides.

```cpp
template <typename T>
T mayor(T a, T b)
{
    return (a > b) ? a : b;   // T debe tener operador >
}
```

Si llamas a `mayor` con un tipo que no tiene `operator>`, el compilador
da error:

```cpp
struct MiStruct { int x; };

mayor(MiStruct{1}, MiStruct{2});   // ERROR: MiStruct no tiene operator>
```

El error aparece en compilación, no en ejecución. El compilador lo detecta
antes de que el programa corra.

---

## BLOQUE 8 — Usos reales

### Contenedores (CPP08)

La STL (Standard Template Library) de C++ está hecha completamente con
templates. En CPP08 vas a usar esto:

```cpp
std::vector<int>         numeros;    // vector de ints
std::vector<std::string> palabras;   // vector de strings
std::vector<Personaje*>  equipo;     // vector de punteros a Personaje
```

`vector` es una clase template. El `<int>` le dice qué tipo guarda.
Sin templates tendrías que implementar `IntVector`, `StringVector`,
`PersonajeVector`... para cada tipo.

### Función de intercambio

```cpp
template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

int x = 1, y = 2;
swap(x, y);   // x=2, y=1

double p = 1.5, q = 2.5;
swap(p, q);   // p=2.5, q=1.5
```

### Función de impresión genérica

```cpp
template <typename T>
void imprimir(T valor)
{
    std::cout << valor << std::endl;
}

imprimir(42);
imprimir(3.14);
imprimir("texto");
imprimir('A');
```

---

## BLOQUE 9 — Dónde va el código de los templates

**Los templates van en el header `.hpp`, no en el `.cpp`.**

Esto parece raro — en 42 te dicen que el código va siempre en `.cpp`.
Los templates son la excepción.

**Por qué:** el compilador necesita ver el código completo del template en
el momento en que lo usa, para poder generar la versión concreta para ese
tipo. Si el código está en un `.cpp` separado, cuando el compilador procesa
otro archivo que usa el template no puede verlo.

```
// Correcto para templates:
// mi_template.hpp
template <typename T>
T mayor(T a, T b)
{
    return (a > b) ? a : b;   // implementación en el header
}
```

En 42 verás esto a partir de CPP07 — los archivos `.tpp` a veces se usan
para separar visualmente la implementación del template, pero se incluyen
desde el `.hpp`.

---

## Resumen

```
Problema: misma lógica, tipos distintos → código duplicado
    ↓
Template: un molde que el compilador rellena con el tipo concreto
    ↓
template <typename T> → T es el marcador de posición del tipo
    ↓
Funciona para funciones y para clases enteras
    ↓
El compilador genera una versión por cada tipo distinto que uses
    ↓
Error si el tipo no soporta la operación → falla en compilación, no en runtime

DIFERENCIA CON POLIMORFISMO DINÁMICO:
  virtual/dynamic_cast  → decisión en RUNTIME  → flexible, con overhead
  templates             → decisión en COMPILACIÓN → rápido, sin overhead
```

---

## Lo que viene en CPP07

En CPP07 implementarás:

- `iter()` — función template que aplica una función a cada elemento de
  un array
- `Array<T>` — clase template que es un array seguro de cualquier tipo
  (acceso con comprobación de rango)

Verás que los templates y el polimorfismo dinámico no se excluyen:
puedes tener un `Array<Personaje*>` — un array template de punteros
polimórficos.
