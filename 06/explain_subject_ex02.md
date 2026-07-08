# Ex02 — Identify real type, explicado desde cero

---

## ¿Qué pide el subject?

```
Implement a Base class that has a public virtual destructor only.
Create three empty classes A, B, and C, that publicly inherit from Base.

Implement:
  Base* generate(void);
  void identify(Base* p);
  void identify(Base& p);    ← using a pointer inside is forbidden
```

En español: tienes una clase padre (`Base`) y tres clases hijas (`A`, `B`, `C`).
El programa crea objetos de cualquiera de las tres al azar, y tienes que
averiguar cuál es — sin que el subject te deje usar `typeid` ni `<typeinfo>`.

---

## BLOQUE 1 — Herencia: qué es y para qué sirve

**Analogía:** imagina que tienes una categoría "Animal" y dentro de ella
tienes "Perro", "Gato" y "Pájaro". Un perro ES un animal. Un gato ES un
animal. Heredan todo lo que tiene Animal, y además pueden tener sus propias
cosas.

```cpp
class Base          { };   // el "Animal"
class A : public Base { };  // el "Perro" — hereda de Base
class B : public Base { };  // el "Gato"
class C : public Base { };  // el "Pájaro"
```

`public Base` significa: "A hereda de Base de forma pública — todo lo que
Base tiene público, A también lo tiene público".

**¿Para qué sirve en este ejercicio?**

Porque si A, B y C heredan de Base, puedes guardar cualquiera de los tres
en un puntero de tipo `Base*`:

```cpp
Base* p = new A();   // válido — A es un Base
Base* p = new B();   // válido — B es un Base
Base* p = new C();   // válido — C es un Base
```

Esto es **polimorfismo**: un solo tipo de puntero (`Base*`) puede apuntar a
objetos de tipos distintos.

---

## BLOQUE 2 — El destructor virtual: por qué es obligatorio

### ¿Qué es un destructor?

Cuando un objeto muere (al hacer `delete` o al salir de su scope), C++
llama automáticamente a su destructor — una función que limpia la memoria.

```cpp
class Base
{
public:
    virtual ~Base();   // destructor virtual
};
```

### ¿Por qué `virtual`?

Imagina este código:

```cpp
Base* p = new A();
delete p;
```

`p` es de tipo `Base*`, pero apunta a un `A`. Sin `virtual`, el compilador
llama al destructor de `Base` — no al de `A`. Si `A` tuviera memoria
reservada, nunca se liberaría.

Con `virtual`, el compilador llama al destructor del tipo **real** del objeto.
Como `A` hereda de `Base`, primero se destruye `A` y luego `Base`. Correcto.

### La segunda razón: dynamic_cast lo necesita

`dynamic_cast` solo funciona con clases **polimórficas** — clases que tienen
al menos un método `virtual`. Sin el destructor virtual, Base no es
polimórfica y el compilador rechaza el `dynamic_cast` con un error.

> Regla: si una clase va a ser clase padre, ponle siempre el destructor
> virtual.

---

## BLOQUE 3 — generate(): polimorfismo en acción

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

`std::rand() % 3` da un número aleatorio: 0, 1 o 2.

La función devuelve `Base*` — un puntero al tipo padre. Pero dentro crea
un objeto real de tipo `A`, `B` o `C`. El puntero es `Base*`, el objeto
real es uno de los tres hijos.

```
generate() devuelve → Base*
                           └── apunta a → objeto real (A, B o C)
```

Quien recibe el puntero solo sabe que tiene un `Base*`. No sabe cuál de los
tres es. Eso es exactamente lo que hay que descubrir en `identify`.

---

## BLOQUE 4 — dynamic_cast: el cast que mira el tipo real

`dynamic_cast` es el único cast de C++ que funciona en **tiempo de
ejecución**. Pregunta al objeto: "¿eres realmente de tipo X?".

### Con punteros: devuelve NULL si falla

```cpp
Base* p = generate();   // puede ser A, B o C

A* a = dynamic_cast<A*>(p);
```

- Si `p` apunta realmente a un `A` → `a` es un puntero válido
- Si `p` apunta a `B` o `C` → `a` es `NULL`

Así funciona `identify(Base* p)`:

```cpp
void identify(Base* p)
{
    if (dynamic_cast<A*>(p))          // ¿es A? → puntero válido = true
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))     // ¿es B?
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))     // ¿es C?
        std::cout << "C" << std::endl;
}
```

El `if` funciona porque un puntero válido es `true` y `NULL` es `false`.

### Con referencias: lanza excepción si falla

Una referencia no puede ser `NULL` — siempre apunta a algo válido. Entonces
si el cast falla, no puede devolver `NULL`. En su lugar **lanza una
excepción**: `std::bad_cast`.

```cpp
void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);    // intenta castear a A&
        std::cout << "A" << std::endl;
        return;
    } catch (const std::exception&) {}  // si falla, captura y sigue
    // ... mismo para B y C
}
```

`(void)` delante del cast es porque no usamos el resultado — solo nos
importa si lanzó excepción o no. Sin `(void)` el compilador podría dar un
warning de "resultado no usado".

---

## BLOQUE 5 — try/catch: manejar excepciones

Una **excepción** es un error que ocurre durante la ejecución. En vez de
hacer que el programa se cuelgue, C++ te permite capturarla y decidir qué
hacer.

```cpp
try
{
    // código que puede lanzar una excepción
    (void)dynamic_cast<A&>(p);
}
catch (const std::exception& e)
{
    // si lanzó, llegamos aquí
    // si no lanzó, este bloque se salta
}
```

**Flujo cuando `p` apunta a `B`:**

```
1. Entra en try
2. dynamic_cast<A&>(p) → p no es A → lanza std::bad_cast
3. Salta al catch → captura la excepción
4. Continúa después del catch → prueba con B
5. dynamic_cast<B&>(p) → p SÍ es B → no lanza
6. Imprime "B" y hace return
```

---

## BLOQUE 6 — Por qué está prohibido usar punteros en identify(Base& p)

El subject dice:
> "Using a pointer inside this function is forbidden."

Si pudieras usar punteros, la versión con referencia sería trivial:

```cpp
void identify(Base& p)
{
    identify(&p);   // conviertes la referencia a puntero y llamas a la otra función
}
```

Eso no enseña nada nuevo. El subject te obliga a aprender que las referencias
y los punteros se comportan diferente con `dynamic_cast` — y por tanto el
código tiene que ser distinto.

---

## BLOQUE 7 — Por qué no puedes usar typeinfo

El subject lo prohíbe explícitamente. `typeid` devuelve información del tipo
en runtime, pero es una solución directa que no te enseña cómo funciona
`dynamic_cast`. El objetivo del ejercicio es que aprendas a usar
`dynamic_cast`, no `typeid`.

Comprobación:
```bash
grep -r "typeinfo" ex02/   # debe dar sin resultado
```

---

## BLOQUE 8 — La vtable: por qué funciona todo esto

Cuando una clase tiene métodos `virtual`, el compilador crea una tabla
oculta llamada **vtable** (virtual table). Cada objeto guarda un puntero
a la vtable de su tipo real.

```
Objeto A en memoria:
┌─────────────────┐
│ puntero vtable  │ → vtable de A
│ datos de A      │
└─────────────────┘

vtable de A:
┌──────────────────────────┐
│ ~A (destructor)          │
│ tipo: "A"                │  ← dynamic_cast lee esto
└──────────────────────────┘
```

`dynamic_cast` consulta esa vtable para saber el tipo real del objeto.
Por eso necesita que la clase sea polimórfica (tenga al menos un `virtual`)
— sin vtable no hay información de tipo en runtime.

---

## BLOQUE 9 — El flujo completo

```cpp
int main()
{
    std::srand(std::time(NULL));   // semilla aleatoria distinta cada vez

    for (int i = 0; i < 6; i++)
    {
        Base* obj = generate();        // crea A, B o C al azar
        std::cout << "Via pointer : ";
        identify(obj);                 // dynamic_cast con puntero
        std::cout << "Via reference: ";
        identify(*obj);                // dynamic_cast con referencia
        std::cout << std::endl;
        delete obj;                    // destructor virtual llama al correcto
    }
}
```

`*obj` convierte el puntero a referencia. Es el operador de desreferencia —
el mismo `*` que en `*ptr = 5`. Aquí lo usas para pasar la referencia a
`identify(Base& p)`.

---

## Resumen visual

```
generate()
    │
    ▼
Base* obj  →  apunta a objeto real (A, B o C)
    │
    ├── identify(obj)           → dynamic_cast<X*>(obj)
    │                              ✓ devuelve puntero válido → imprime tipo
    │                              ✗ devuelve NULL           → prueba siguiente
    │
    └── identify(*obj)          → dynamic_cast<X&>(*obj)
                                   ✓ no lanza               → imprime tipo + return
                                   ✗ lanza std::bad_cast    → catch → prueba siguiente
```

---

## Lo que el ejercicio enseña en una frase

> Cuando tienes un puntero al tipo padre (`Base*`) y necesitas saber qué tipo
> hijo real tiene, usas `dynamic_cast`. Con punteros compruebas si es `NULL`,
> con referencias usas `try/catch`. Esto solo es posible porque la clase es
> polimórfica — tiene un destructor `virtual` que activa la vtable.
