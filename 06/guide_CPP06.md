# CPP06 — C++ Casts

Guia de estudio y defensa para el modulo CPP06 de la escuela 42.

---

## Indice

1. [Los 4 tipos de cast de C++](#1-los-4-tipos-de-cast-de-c)
2. [ex00 — ScalarConverter](#2-ex00--scalarconverter)
3. [ex01 — Serializer](#3-ex01--serializer)
4. [ex02 — Identificacion de tipo real](#4-ex02--identificacion-de-tipo-real)
5. [Preguntas de defensa con respuestas](#5-preguntas-de-defensa-con-respuestas)
6. [Compilacion rapida](#6-compilacion-rapida)

---

## 1. Los 4 tipos de cast de C++

C++ introduce cuatro operadores de conversion explicitos para reemplazar el cast estilo C `(tipo)valor`. Cada uno tiene un proposito especifico y un nivel de seguridad distinto.

### `static_cast`

Conversion estatica, verificada en tiempo de compilacion. Es el cast de proposito general para conversiones bien definidas: entre tipos numericos, entre punteros en una jerarquia de herencia cuando el tipo es conocido en tiempo de compilacion.

```cpp
double d = 3.14;
int i = static_cast<int>(d);       // double -> int
char c = static_cast<char>(65);    // int -> char ('A')

// Upcasting (seguro)
Derived* der = new Derived();
Base* base = static_cast<Base*>(der);

// Downcasting (peligroso sin garantia en tiempo de ejecucion)
Derived* der2 = static_cast<Derived*>(base); // NO comprueba el tipo real
```

### `dynamic_cast`

Conversion dinamica, verificada en tiempo de ejecucion mediante RTTI. Solo funciona con jerarquias polimorficas (la clase base debe tener al menos una funcion virtual).

```cpp
Base* base = new Derived();

// Con puntero: devuelve nullptr si falla
Derived* d = dynamic_cast<Derived*>(base);
if (d)
    d->metodoDerivado();

// Con referencia: lanza std::bad_cast si falla
try {
    Derived& ref = dynamic_cast<Derived&>(*base);
} catch (const std::bad_cast& e) {
    // fallo la conversion
}
```

### `reinterpret_cast`

Reinterpretacion binaria pura. Convierte cualquier tipo de puntero a cualquier otro tipo de puntero, o entre punteros y enteros. No realiza ninguna comprobacion.

```cpp
Data* ptr = new Data();
uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);  // puntero -> entero
Data* recovered = reinterpret_cast<Data*>(raw);     // entero -> puntero
```

Cuando usarlo: serializar/deserializar punteros, interoperabilidad con APIs de bajo nivel. Nunca para conversiones numericas normales.

### `const_cast`

El unico cast que puede anadir o quitar `const`. No cambia el tipo subyacente ni el valor.

```cpp
const char* cstr = "hola";
char* mutable_str = const_cast<char*>(cstr); // quita const
```

Cuando usarlo: para interoperar con funciones C antiguas que no respetan `const`. Modificar un objeto declarado `const` a traves de `const_cast` es comportamiento indefinido.

### Resumen comparativo

| Cast | Comprobacion | Uso principal | Riesgo |
|---|---|---|---|
| `static_cast` | Compilacion | Conversiones numericas, jerarquias conocidas | Bajo |
| `dynamic_cast` | Ejecucion (RTTI) | Downcasting seguro en polimorfismo | Ninguno (controlado) |
| `reinterpret_cast` | Ninguna | Punteros <-> enteros, APIs de bajo nivel | Alto |
| `const_cast` | Ninguna | Anadir/quitar const | Medio |

---

## 2. ex00 — ScalarConverter

### Objetivo

Recibir un literal escalar como cadena de texto y convertirlo a `char`, `int`, `float` y `double`. Gestionar casos imposibles y valores especiales como `nan` e `inf`.

```
./convert 42
./convert 3.14f
./convert 'a'
./convert nan
./convert -inff
```

### Por que no se puede instanciar

`ScalarConverter` es una clase de utilidad pura. Para impedir la instanciacion, el constructor, copia y asignacion son privados:

```cpp
class ScalarConverter
{
public:
    static void convert(const std::string& literal);

private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter&);
    ScalarConverter& operator=(const ScalarConverter&);
    ~ScalarConverter();
};
```

Si alguien escribe `ScalarConverter sc;` el compilador da error porque el constructor es privado. En C++11 se usaria `= delete`.

### Deteccion del tipo de literal

El orden de deteccion importa:

```
1. Char literal   -> 'a' (exactamente 3 caracteres)
2. Special        -> nan, nanf, +inf, -inf, +inff, -inff, inf, inff
3. Float          -> termina en 'f', la parte sin 'f' es un numero valido con '.'
4. Double         -> es un numero valido con '.'
5. Int            -> es un numero entero valido con strtol
6. Invalido       -> ninguno de los anteriores
```

Por que este orden:
- Los especiales deben detectarse antes del parseo general para evitar que `strtod("nan")` los clasifique erroneamente como double.
- Float antes que double: `3.14f` termina en `f`; si primero comprobamos double, `strtod` fallaria en la `f`.
- Double antes que int: `3.14` tiene punto, `strtol` se detendria en el `.`.

Una vez detectado el tipo, el literal se convierte a `double` como tipo interno de trabajo. Desde ese `double` se producen todas las salidas con `static_cast`.

### Impresion de resultados

**char**: imposible si NaN, infinito, o fuera del rango ASCII (0-127). Non displayable si caracter de control (< 32 o == 127).

```cpp
static void printChar(double d)
{
    if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    else if (d < 32 || d == 127)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}
```

**float/double**: se usa `std::floor` para anadir `.0` cuando el valor es entero:

```cpp
if (!std::isnan(f) && !std::isinf(f) && f == std::floor(f))
    std::cout << ".0";
```

Ejemplo de salida:

```
$ ./convert 42
char: '*'
int: 42
float: 42.0f
double: 42.0

$ ./convert nan
char: impossible
int: impossible
float: nanf
double: nan

$ ./convert -inff
char: impossible
int: impossible
float: -inff
double: -inf
```

---

## 3. ex01 — Serializer

### Objetivo

Demostrar `reinterpret_cast` serializando un puntero a `uintptr_t` y recuperandolo de vuelta.

```cpp
// Data.hpp
struct Data
{
    std::string name;
    int         value;
};

// Serializer.cpp
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
```

Uso:

```cpp
Data data;
data.name = "Marvin";
data.value = 42;

uintptr_t raw = Serializer::serialize(&data);
Data* recovered = Serializer::deserialize(raw);

std::cout << (&data == recovered ? "yes" : "no") << std::endl; // yes
```

### Por que `reinterpret_cast` y no `static_cast`

`static_cast` solo funciona entre tipos con una relacion de conversion definida por el estandar. Un puntero a `Data` y un `uintptr_t` no tienen ninguna relacion:

```cpp
// ERROR: static_cast no puede convertir Data* a uintptr_t
uintptr_t raw = static_cast<uintptr_t>(ptr); // fallo de compilacion
```

`reinterpret_cast` reinterpreta el patron de bits. Un puntero es una direccion de memoria; `uintptr_t` es un entero garantizado por el estandar para ser suficientemente grande para contener cualquier puntero.

### Por que `uintptr_t` y no `unsigned long`

`unsigned long` no tiene garantia de tamano consistente entre plataformas. En Windows de 64 bits con MSVC mide 32 bits aunque los punteros sean de 64 bits, causando truncamiento. `uintptr_t` esta definido exactamente del tamano necesario en cada plataforma.

---

## 4. ex02 — Identificacion de tipo real

### Objetivo

Dada la jerarquia `Base -> A, B, C`, identificar el tipo real de un objeto a traves de `Base*` o `Base&` sin usar `typeid`.

```cpp
// Base.hpp
class Base { public: virtual ~Base(); };
class A : public Base {};
class B : public Base {};
class C : public Base {};

Base*  generate();
void   identify(Base* p);
void   identify(Base& p);
```

`generate()` devuelve aleatoriamente un puntero a `A`, `B` o `C`:

```cpp
Base* generate()
{
    switch (std::rand() % 3)
    {
        case 0: return new A();
        case 1: return new B();
        default: return new C();
    }
}
```

### Por que el destructor de Base debe ser virtual

`dynamic_cast` requiere que la clase base sea polimorfica (tenga al menos una funcion virtual). Sin esa condicion, el compilador no genera RTTI y `dynamic_cast` falla:

```
error: 'Base' is not polymorphic
```

Ademas es obligatorio para correcta gestion de memoria: `delete base_ptr` sin destructor virtual solo llama al destructor de `Base`, perdiendo la destruccion de la parte derivada.

### `dynamic_cast` con puntero vs referencia

**Con puntero**: si la conversion falla, devuelve `nullptr`:

```cpp
void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}
```

**Con referencia**: una referencia no puede ser nula. Si falla, lanza `std::bad_cast`:

```cpp
void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (const std::exception&) {}
}
```

El `(void)` descarta el resultado (solo importa si fallo o no). El `return` evita seguir probando tipos una vez identificado.

| Situacion | Comportamiento en fallo |
|---|---|
| `dynamic_cast<X*>(ptr)` | Devuelve `nullptr` |
| `dynamic_cast<X&>(ref)` | Lanza `std::bad_cast` |

---

## 5. Preguntas de defensa con respuestas

### Que diferencia hay entre `static_cast` y `dynamic_cast`?

`static_cast` se resuelve en tiempo de compilacion. Verifica que la conversion sea sintacticamente valida pero no comprueba el tipo real en ejecucion. Un downcast incorrecto con `static_cast` produce comportamiento indefinido.

`dynamic_cast` se resuelve en tiempo de ejecucion consultando RTTI. Si el objeto no es del tipo pedido, devuelve `nullptr` (punteros) o lanza `std::bad_cast` (referencias). Es mas lento pero seguro.

### Por que `dynamic_cast` necesita RTTI?

RTTI es el mecanismo del compilador para almacenar informacion sobre el tipo real de un objeto en ejecucion. Se guarda en la vtable de la clase. Sin RTTI no hay forma de saber en tiempo de ejecucion que tipo real tiene el objeto. Por eso la clase base debe ser polimorfica (tener al menos una funcion virtual).

### Que es `uintptr_t` y por que usarlo en lugar de `unsigned long`?

`uintptr_t` es un tipo entero sin signo garantizado por el estandar para ser exactamente del tamano necesario para almacenar cualquier puntero en la plataforma actual. `unsigned long` no tiene esa garantia en todas las plataformas. `uintptr_t` hace el codigo portable.

### Por que el destructor de `Base` debe ser virtual?

Por dos razones:
1. Para que `dynamic_cast` funcione: requiere una clase polimorfica.
2. Para destruccion correcta: `delete base_ptr` sin destructor virtual solo llama `~Base()`, perdiendo la destruccion de la parte derivada.

### Por que `identify` con referencia usa `try/catch`?

Porque `dynamic_cast` con referencia no puede devolver `nullptr` (las referencias no pueden ser nulas). En su lugar lanza `std::bad_cast`. El `try/catch` es la unica forma de capturar ese fallo y continuar probando con el siguiente tipo.

### Por que `ScalarConverter` usa `static_cast` y no el cast estilo C?

El cast estilo C `(int)d` es implicito y puede hacer cosas inesperadas (descartar `const` sin aviso). `static_cast` es explicito: el programador declara su intencion y el compilador rechaza conversiones invalidas. Ademas, el objetivo del modulo es aprender los casts de C++.

### Que imprime para `"nan"` y `"-inff"`?

Para `"nan"`:
```
char: impossible
int: impossible
float: nanf
double: nan
```

Para `"-inff"`:
```
char: impossible
int: impossible
float: -inff
double: -inf
```

### Como detectas si un literal es float vs double vs int?

- **Float**: el ultimo caracter es `f`, y la cadena sin esa `f` es un numero valido con punto decimal segun `strtod`.
- **Double**: `strtod` parsea toda la cadena y contiene punto decimal.
- **Int**: `strtol` parsea toda la cadena completa.

El orden es float -> double -> int para evitar ambiguedades.

### Por que "Non displayable" en lugar de imprimir el caracter?

Los ASCII del 0 al 31 son caracteres de control y el 127 es DEL. No tienen representacion visual imprimible y enviarlos a `std::cout` puede causar comportamientos inesperados en el terminal. La convencion del ejercicio es imprimir `"Non displayable"`.

---

## 6. Compilacion rapida

```bash
# ex00 - ScalarConverter
cd /Users/marta/Documents/PROJECTS/CPP/06/ex00
make
./convert 42
./convert 3.14f
./convert 'a'
./convert nan
./convert -inff

# ex01 - Serializer
cd /Users/marta/Documents/PROJECTS/CPP/06/ex01
make
./serializer

# ex02 - Identificacion de tipo real
cd /Users/marta/Documents/PROJECTS/CPP/06/ex02
make
./identify
```

Casos de prueba utiles para `ScalarConverter`:

| Entrada | char | int | float | double |
|---|---|---|---|---|
| `42` | `'*'` | `42` | `42.0f` | `42.0` |
| `3.14f` | Non displayable | `3` | `3.14f` | `3.14` |
| `'a'` | `'a'` | `97` | `97.0f` | `97.0` |
| `nan` | impossible | impossible | `nanf` | `nan` |
| `-inff` | impossible | impossible | `-inff` | `-inf` |
| `0` | Non displayable | `0` | `0.0f` | `0.0` |
