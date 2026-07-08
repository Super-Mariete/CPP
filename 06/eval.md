# CPP06 — Guía de defensa

---

## PREREQUISITES — Lo que revisan antes de empezar

### "¿Compila con -Wall -Wextra -Werror?"

```bash
make re    # en cada ex00, ex01, ex02
```

Compila limpio, cero warnings. Si el evaluador lo prueba, di:
> "Sí, uso exactamente esos flags en los tres Makefiles."

### "¿No hay funciones en los headers?"

Los tres headers solo tienen declaraciones de clase y firmas de funciones.
Ninguna implementación. La implementación está siempre en los `.cpp`.

### "¿No usas funciones de C prohibidas?"

No hay ningún `printf`, `malloc`, `calloc`, `realloc` ni `free` en el código.
Para convertir strings a números uso `strtod` y `strtol` — están explícitamente
autorizadas en el subject de ex00: *"Any function to convert from a string to an
int, a float, or a double"*.

### "¿No hay using namespace ni friend?"

No están en ningún archivo. Puedes hacer `grep` si quieres comprobarlo.

### "¿Hay memory leaks?"

```bash
valgrind --leak-check=full ./convert 42
valgrind --leak-check=full ./serializer
valgrind --leak-check=full ./identify
```

Los tres dan `All heap blocks were freed -- no leaks are possible`.

En ex02, cada objeto creado con `new` en `generate()` se libera con `delete`
en el loop del `main`.

---

## EX00 — Conversion of scalar types

### "Does the program work as required?"

```bash
./convert 0          # char: Non displayable / int: 0 / float: 0.0f / double: 0.0
./convert nan        # char: impossible / int: impossible / float: nanf / double: nan
./convert 42.0f      # char: '*' / int: 42 / float: 42.0f / double: 42.0
./convert A          # char: 'A' / int: 65 / float: 65.0f / double: 65.0
./convert -inf       # char: impossible / int: impossible / float: -inff / double: -inf
./convert hello      # char: impossible / int: impossible / float: impossible / double: impossible
```

### "Did the student use static_cast to convert values?"

Sí, en todos los puntos de conversión:

```cpp
d = static_cast<double>(literal[1]);       // char literal → double
d = static_cast<double>(literal[0]);       // char sin comillas → double
d = static_cast<double>(strtol(...));      // int → double
static_cast<char>(d)                       // double → char al imprimir
static_cast<int>(d)                        // double → int al imprimir
static_cast<float>(d)                      // double → float al imprimir
static_cast<double>(INT_MAX)               // para comparar rangos
```

Si preguntan por qué static_cast y no el cast de C:
> "El cast de C como `(int)d` funciona pero silencia al compilador — hace lo
> que sea sin avisar. `static_cast` es verificado en tiempo de compilación:
> si la conversión no tiene sentido entre esos tipos, el compilador da error.
> Es más seguro y más legible."

### "¿Por qué la clase no se puede instanciar?"

> "El subject lo exige explícitamente: *'it must not be instantiable by users'*.
> La clase no guarda ningún dato, solo tiene una función estática. Poniendo
> todos los constructores en `private` el compilador rechaza cualquier intento
> de crear un objeto de ella."

### "¿Cómo detectas el tipo del input?"

El programa prueba los tipos en este orden:

1. `isCharLiteral` — ¿tiene el formato `'A'` con comillas?
2. `isSpecial` — ¿es nan, inf, etc.?
3. `isFloat` — ¿termina en `f` y tiene punto decimal?
4. `isDouble` — ¿tiene punto decimal y `strtod` lo convierte entero?
5. `isInt` — ¿`strtol` lo convierte entero?
6. `literal.length() == 1` — ¿es un carácter suelto como `A`?
7. Else → impossible

> "Todo pasa por `double` como tipo intermedio porque es el más grande y
> preciso de los cuatro. Desde `double` puedo llegar a cualquier otro tipo
> con `static_cast`."

### "¿Por qué length == 1 para chars?"

> "Cuando escribes `./convert A` en la shell, la shell entrega `A` al programa
> sin comillas — un string de longitud 1. `isCharLiteral` espera el formato
> `'A'` con las comillas dentro del string, que requeriría escribir
> `./convert \"'A'\"`. La rama `length == 1` maneja el caso habitual."

---

## EX01 — Serialization

### "Does the program work as required?"

```bash
./serializer
# Pointers match: yes
```

El puntero original y el deserializado son idénticos.

### "The reinterpret_cast should be used twice"

```cpp
// Primera vez: Data* → uintptr_t
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

// Segunda vez: uintptr_t → Data*
Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
```

Si preguntan por qué reinterpret_cast y no static_cast:
> "Un puntero `Data*` y un entero `uintptr_t` son tipos incompatibles para
> `static_cast` — el compilador daría error. `reinterpret_cast` reinterpreta
> los bytes sin hacer ninguna conversión: un puntero es simplemente una
> dirección de memoria, un número. Le decimos al compilador que trate ese
> número como otro tipo sin tocar los bits."

### "The final data struct should be usable"

```bash
./serializer
# name  : Marvin      ← datos accesibles después de deserializar
# value : 42
# Pointers match: yes
```

### "¿Por qué uintptr_t y no int o long?"

> "`uintptr_t` es un entero sin signo garantizado de tener el tamaño
> suficiente para guardar cualquier puntero en el sistema. En 64 bits
> un puntero ocupa 8 bytes, un `int` solo tiene 4 — no cabría. `uintptr_t`
> se adapta automáticamente a la arquitectura."

---

## EX02 — Identify real type

### "Does the program work as required?"

```bash
./identify
# Via pointer : A       ← o B o C, es aleatorio
# Via reference: A
```

Cada ejecución da resultados distintos porque usa `std::rand()`.

### "Did the student use dynamic_cast?"

```cpp
// identify(Base* p) — versión puntero
if (dynamic_cast<A*>(p))       // NULL si el cast falla
    std::cout << "A";
else if (dynamic_cast<B*>(p))
    std::cout << "B";
else if (dynamic_cast<C*>(p))
    std::cout << "C";

// identify(Base& p) — versión referencia
try {
    (void)dynamic_cast<A&>(p);  // lanza std::bad_cast si falla
    std::cout << "A";
    return;
} catch (const std::exception&) {}
// ... igual para B y C
```

### "identify(Base* p) should check if the cast return is NULL"

`dynamic_cast<A*>(p)` devuelve `NULL` si `p` no apunta a un objeto de tipo
`A`. El `if` lo comprueba implícitamente: `if (NULL)` es `false`.

> "Con punteros, `dynamic_cast` devuelve `NULL` cuando falla. El `if` directo
> funciona porque `NULL` se evalúa como `false`."

### "identify(Base& p) should use try/catch"

> "Con referencias no se puede devolver `NULL` — una referencia siempre apunta
> a algo. Cuando `dynamic_cast` sobre una referencia falla, lanza
> `std::bad_cast`. Por eso necesito `try/catch`: intento el cast y si lanza,
> capturo la excepción y pruebo con el siguiente tipo."

### "The typeinfo header must not appear"

```bash
grep -r "typeinfo" ex02/    # → sin resultado
```

No está en ningún archivo. `dynamic_cast` no necesita incluir `<typeinfo>`
para funcionar — ese header solo es necesario si usas `typeid()`, que está
prohibido.

### "¿Por qué Base tiene el destructor virtual?"

> "Para que `dynamic_cast` funcione, la clase base necesita al menos un método
> virtual — que la hace polimórfica. Sin eso el compilador rechaza el
> `dynamic_cast` en tiempo de compilación. El destructor virtual es la forma
> más limpia de cumplirlo, y además es buena práctica: garantiza que al hacer
> `delete` sobre un `Base*` se llame al destructor del tipo real."

### "¿Por qué rand() % 3 con srand(time(NULL))?"

> "`srand(time(NULL))` inicializa la semilla con el tiempo actual para que cada
> ejecución sea diferente. `rand() % 3` da 0, 1 o 2 — uno por cada clase.
> El subject dice 'feel free to use anything you like for the random choice'."

---

## Preguntas trampa frecuentes

**"¿Qué diferencia hay entre los 4 casts de C++?"**

| Cast | Cuándo |
|------|--------|
| `static_cast` | Entre tipos compatibles, verificado en compilación |
| `reinterpret_cast` | Reinterpretación de bytes, sin verificación |
| `dynamic_cast` | Jerarquía de clases polimórficas, verificado en runtime |
| `const_cast` | Añadir o quitar `const` |

**"¿Por qué no usaste el cast de C `(tipo)valor`?"**
> "El cast de C hace lo que sea sin avisar — puede comportarse como cualquiera
> de los cuatro casts de C++ dependiendo del contexto. Los casts de C++ son
> explícitos: cada uno tiene un propósito concreto y el compilador verifica que
> tenga sentido. Son más seguros y más fáciles de buscar en el código."

**"¿Qué pasa si modificas el uintptr_t antes de deserializar?"**
> "El puntero resultante apunta a una dirección aleatoria. Al acceder a los
> datos obtendrías un segfault o basura — comportamiento indefinido. El
> compilador no te avisa de nada, por eso reinterpret_cast es peligroso."
