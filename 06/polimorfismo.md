# Polimorfismo — De cero hasta dynamic_cast

---

## El problema que viene antes del polimorfismo

Imagina que estás haciendo un juego. Tienes tres tipos de personaje:
guerrero, mago y arquero. Sin polimorfismo, el código para que cada uno
ataque sería así:

```cpp
void atacar(int tipo)
{
    if (tipo == 0)
        std::cout << "Guerrero golpea con espada" << std::endl;
    else if (tipo == 1)
        std::cout << "Mago lanza un hechizo" << std::endl;
    else if (tipo == 2)
        std::cout << "Arquero dispara una flecha" << std::endl;
}
```

Cada vez que añades un personaje nuevo tienes que buscar todos los
`if/else` del código y añadir un caso más. En un juego real hay decenas
de funciones así. Es un desastre.

**El polimorfismo resuelve exactamente esto.**

---

## PASO 1 — Herencia: compartir código entre clases

La herencia permite que una clase hija **tome todo lo que tiene la clase
padre** y añada o cambie lo que necesite.

```cpp
class Personaje          // clase padre (base)
{
public:
    std::string nombre;
    int         vida;

    void morir()
    {
        std::cout << nombre << " ha muerto" << std::endl;
    }
};

class Guerrero : public Personaje   // hereda de Personaje
{
public:
    int fuerza;
};

class Mago : public Personaje       // también hereda de Personaje
{
public:
    int mana;
};
```

`Guerrero` tiene `nombre`, `vida`, `morir()` **y además** `fuerza`.
`Mago` tiene `nombre`, `vida`, `morir()` **y además** `mana`.

No has repetido el código común — vive una sola vez en `Personaje`.

**Analogía real:** un contrato de trabajo tiene cláusulas comunes para
todos los empleados (vacaciones, horario). Cada departamento añade sus
cláusulas específicas. No imprimes el contrato entero para cada
departamento — heredas las comunes y añades las tuyas.

---

## PASO 2 — El problema de atacar diferente

Cada personaje ataca distinto. Si pones `atacar()` en la clase padre:

```cpp
class Personaje
{
public:
    void atacar()
    {
        std::cout << "ataque genérico" << std::endl;   // ← ¿qué pones aquí?
    }
};
```

No sabes qué poner — cada hijo ataca diferente. Y si lo pones en cada
hijo por separado:

```cpp
class Guerrero : public Personaje {
public:
    void atacar() { std::cout << "espada" << std::endl; }
};

class Mago : public Personaje {
public:
    void atacar() { std::cout << "hechizo" << std::endl; }
};
```

Funciona, pero si tienes un `Personaje*` apuntando a un `Guerrero`, el
compilador llama al `atacar()` de `Personaje`, no al de `Guerrero`:

```cpp
Personaje* p = new Guerrero();
p->atacar();   // imprime "ataque genérico" ← INCORRECTO
```

El compilador ve el tipo del puntero (`Personaje*`) y llama al método de
ese tipo. No mira el objeto real.

---

## PASO 3 — virtual: la palabra que lo cambia todo

```cpp
class Personaje
{
public:
    virtual void atacar()
    {
        std::cout << "ataque genérico" << std::endl;
    }
};
```

Con `virtual`, el compilador ya no mira el tipo del puntero. Mira el
**objeto real** en tiempo de ejecución y llama al método correcto:

```cpp
Personaje* p = new Guerrero();
p->atacar();   // imprime "espada" ← CORRECTO
```

Esto es **polimorfismo**: el mismo código (`p->atacar()`) se comporta
diferente según el tipo real del objeto.

```
Sin virtual:
  Personaje* p = new Guerrero()
  p->atacar()  →  mira tipo del puntero (Personaje)  →  "ataque genérico"

Con virtual:
  Personaje* p = new Guerrero()
  p->atacar()  →  mira tipo del objeto real (Guerrero) →  "espada"
```

---

## PASO 4 — La vtable: cómo funciona por dentro

Cuando una clase tiene métodos `virtual`, el compilador crea una tabla
oculta por clase llamada **vtable**. Cada objeto guarda un puntero a la
vtable de su tipo real.

```
Objeto Guerrero en memoria:
┌──────────────────┐
│ ptr → vtable     │ ──→  vtable de Guerrero
│ nombre           │        [ atacar → Guerrero::atacar ]
│ vida             │        [ morir  → Personaje::morir ]
│ fuerza           │        [ ~Guerrero               ]
└──────────────────┘
```

Cuando llamas a `p->atacar()`, el programa:
1. Sigue el puntero del objeto hasta su vtable
2. Busca `atacar` en la tabla
3. Llama a la función que encuentre ahí

Por eso funciona en tiempo de ejecución: la vtable del objeto real siempre
apunta al método correcto, sin importar el tipo del puntero.

---

## PASO 5 — El destructor virtual: por qué es obligatorio

```cpp
class Personaje
{
public:
    virtual ~Personaje() {}   // destructor virtual
};
```

Sin `virtual` en el destructor:

```cpp
Personaje* p = new Guerrero();
delete p;   // llama a ~Personaje(), NO a ~Guerrero()
            // si Guerrero reservó memoria, se pierde → leak
```

Con `virtual`:

```cpp
delete p;   // mira la vtable → llama a ~Guerrero() primero,
            // luego a ~Personaje()  → correcto, sin leaks
```

**Regla de oro:** si una clase va a ser padre, su destructor debe ser
`virtual`. Siempre.

---

## PASO 6 — Polimorfismo en práctica: el poder real

Con herencia + virtual puedes guardar tipos distintos en una misma
colección y tratarlos todos igual:

```cpp
Personaje* equipo[3];
equipo[0] = new Guerrero();
equipo[1] = new Mago();
equipo[2] = new Arquero();

for (int i = 0; i < 3; i++)
    equipo[i]->atacar();   // cada uno ataca a su manera
```

Output:
```
espada
hechizo
flecha
```

**Un solo bucle, tres comportamientos distintos.** Esto es imposible sin
polimorfismo. Con el código del principio tendrías tres `if` anidados.

**Uso real — motor de videojuego:**

```cpp
// Unity/Unreal hacen exactamente esto
Entidad* escena[1000];
// mezcla de enemigos, jugadores, objetos, efectos...

for (int i = 0; i < 1000; i++)
{
    escena[i]->actualizar();   // cada entidad sabe actualizarse
    escena[i]->dibujar();      // cada entidad sabe dibujarse
}
```

Sin polimorfismo necesitarías un bucle separado para cada tipo de entidad.
Con 50 tipos de entidades, sería 50 bucles.

---

## PASO 7 — El límite del polimorfismo básico

El polimorfismo con `virtual` es potente pero tiene un límite: **no sabes
qué tipo real tiene el objeto**.

```cpp
Personaje* p = equipo[0];
p->atacar();   // funciona — polimorfismo
p->fuerza;     // ERROR — Personaje* no sabe que es un Guerrero
```

La variable `fuerza` solo existe en `Guerrero`. Desde un `Personaje*` no
puedes acceder a ella, aunque el objeto real sea un `Guerrero`.

**Caso real donde esto importa:**

En un juego tienes personajes que pueden volar y otros que no. Solo
`Arquero` puede volar. Necesitas saber si el personaje actual es un
`Arquero` para activar el modo vuelo.

Aquí entra `dynamic_cast`.

---

## PASO 8 — dynamic_cast: identificar el tipo real

`dynamic_cast` pregunta al objeto en tiempo de ejecución: "¿eres
realmente de tipo X?".

```cpp
Personaje* p = equipo[0];   // puede ser cualquier tipo

Guerrero* g = dynamic_cast<Guerrero*>(p);

if (g)   // si el cast tuvo éxito (no es NULL)
{
    std::cout << "Fuerza: " << g->fuerza << std::endl;
}
else
{
    std::cout << "No es un guerrero" << std::endl;
}
```

`dynamic_cast<Guerrero*>(p)`:
- Si `p` apunta realmente a un `Guerrero` → devuelve el puntero válido
- Si `p` apunta a `Mago` o `Arquero` → devuelve `NULL`

**Con referencias — lanza excepción si falla:**

```cpp
void procesar(Personaje& p)
{
    try {
        Guerrero& g = dynamic_cast<Guerrero&>(p);
        // si llegamos aquí, es un Guerrero
        std::cout << g.fuerza << std::endl;
    }
    catch (const std::exception&) {
        // no era un Guerrero
    }
}
```

Las referencias no pueden ser `NULL`, así que el fallo se señala con una
excepción en lugar de con `NULL`.

---

## Aplicado a ex02

```cpp
class Base { public: virtual ~Base(); };
class A : public Base {};
class B : public Base {};
class C : public Base {};
```

`generate()` devuelve un `Base*` que en realidad apunta a `A`, `B` o `C`.
`identify()` tiene que descubrir cuál:

```cpp
void identify(Base* p)
{
    if (dynamic_cast<A*>(p))        // ¿es A?
        std::cout << "A";
    else if (dynamic_cast<B*>(p))   // ¿es B?
        std::cout << "B";
    else if (dynamic_cast<C*>(p))   // ¿es C?
        std::cout << "C";
}

void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A"; return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B"; return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C"; return;
    } catch (const std::exception&) {}
}
```

Sin `virtual ~Base()` no habría vtable → `dynamic_cast` no funcionaría.

---

## ¿Hay más polimorfismo después de esto?

Sí. Lo que has visto hasta aquí es **polimorfismo dinámico** — ocurre en
tiempo de ejecución usando vtables. Hay otro tipo que viene en CPP07:

```
┌─────────────────────────────────────────────────────────┐
│                    POLIMORFISMO                          │
├────────────────────────┬────────────────────────────────┤
│   DINÁMICO (runtime)   │   ESTÁTICO (compile time)      │
├────────────────────────┼────────────────────────────────┤
│ virtual + herencia     │ Templates (CPP07)               │
│ dynamic_cast           │                                 │
│ Funciona en ejecución  │ Funciona en compilación         │
│ Más flexible           │ Más rápido (sin vtable)         │
│ Lo de ex02             │ Lo que viene                    │
└────────────────────────┴────────────────────────────────┘
```

**Templates (CPP07):** una función o clase que funciona con cualquier tipo
sin repetir código. Misma idea — un código, múltiples comportamientos —
pero el compilador lo resuelve antes de ejecutar el programa.

```cpp
// Una sola función que suma cualquier tipo
template <typename T>
T suma(T a, T b) { return a + b; }

suma(1, 2);       // int
suma(1.5, 2.3);   // double
suma('a', 'b');   // char
```

También en CPP04 (si no lo has visto ya) hay **clases abstractas** —
clases con métodos `virtual` sin implementar que obligan a los hijos a
implementarlos:

```cpp
class Personaje
{
public:
    virtual void atacar() = 0;   // = 0 → método puro virtual
                                  // obliga a Guerrero, Mago etc. a implementarlo
};
```

---

## Resumen del camino

```
Problema: código duplicado para cada tipo
    ↓
Herencia: clases hijas toman el código del padre
    ↓
virtual: el método correcto se llama según el objeto real (en runtime)
    ↓
Destructor virtual: delete llama al destructor correcto, sin leaks
    ↓
dynamic_cast: cuando necesitas saber el tipo real concreto
    ↓  (puntero → NULL si falla / referencia → excepción si falla)
Templates (CPP07): polimorfismo resuelto en compilación, sin vtable
```
