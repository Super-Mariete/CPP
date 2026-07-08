# CPP09 — STL Guide

## Índice

1. [Reglas del módulo](#reglas-del-módulo)
2. [Ex00 — Bitcoin Exchange](#ex00--bitcoin-exchange)
3. [Ex01 — Reverse Polish Notation](#ex01--reverse-polish-notation)
4. [Ex02 — PmergeMe](#ex02--pmergeme)

---

## Reglas del módulo

La restricción más importante de CPP09 es que **cada contenedor solo puede usarse en un ejercicio**. Una vez que validas un ejercicio con un contenedor, ese contenedor queda prohibido para el resto del módulo.

| Ejercicio | Contenedor principal | Prohibido en |
|-----------|----------------------|--------------|
| ex00      | `std::map`           | ex01, ex02   |
| ex01      | `std::stack`         | ex02         |
| ex02      | `std::vector`, `std::deque` | —     |

---

## Ex00 — Bitcoin Exchange

**Binario:** `btc`
**Uso:** `./btc input.txt`
**Contenedor:** `std::map<std::string, float>`

### Qué hace

Lee una base de datos de precios históricos de Bitcoin (`data.csv`) y un archivo de entrada con pares `fecha | valor`. Para cada línea válida, busca el tipo de cambio de esa fecha (o la más cercana anterior) y muestra el resultado de multiplicar el valor por el tipo de cambio.

### Estructura

```
data.csv          →  base de datos de precios (date,exchange_rate)
input.txt         →  archivo de entrada (date | value)
BitcoinExchange   →  clase que gestiona todo
```

### Por qué std::map

`std::map` mantiene las claves ordenadas. Las fechas en formato `YYYY-MM-DD` se ordenan correctamente de forma lexicográfica, por lo que podemos usar `upper_bound` para encontrar la fecha más cercana:

```cpp
// upper_bound devuelve el primer elemento MAYOR que la clave
std::map<std::string, float>::const_iterator it = _rates.upper_bound(date);
if (it == _rates.begin())
    // fecha anterior a todos los registros → error
--it;
// it apunta ahora al mayor elemento <= date
```

### Formato y validaciones

**data.csv** — separador: coma
```
date,exchange_rate
2011-01-03,0.3
2012-01-11,7.1
```

**input.txt** — separador: ` | ` (espacio-barra-espacio)
```
date | value
2011-01-03 | 3
2011-01-03 | 1.2
```

| Condición de error              | Mensaje                              |
|---------------------------------|--------------------------------------|
| Fecha con formato inválido      | `Error: bad input => <date>`         |
| Valor negativo                  | `Error: not a positive number.`      |
| Valor > 1000                    | `Error: too large a number.`         |
| Sin separador ` \| ` en la línea | `Error: bad input => <line>`         |
| Fecha anterior a todos los registros | `Error: bad input => <date>`    |

### Flujo de ejecución

```
main(argv[1])
  └── BitcoinExchange("data.csv")     → carga _rates en std::map
        └── evaluate(argv[1])
              └── por cada línea:
                    1. separar por " | "
                    2. validar fecha (YYYY-MM-DD, mes 1-12, día 1-31)
                    3. validar valor (0 ≤ v ≤ 1000)
                    4. upper_bound(date) → --it → tipo de cambio
                    5. imprimir: date => value = value * rate
```

---

## Ex01 — Reverse Polish Notation

**Binario:** `RPN`
**Uso:** `./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"`
**Contenedor:** `std::stack<int>`

### Qué es la notación polaca inversa (RPN)

En RPN los operadores van **después** de sus operandos:

| Infix         | RPN           | Resultado |
|---------------|---------------|-----------|
| `8*9-9-9-9-4+1` | `8 9 * 9 - 9 - 9 - 4 - 1 +` | 42 |
| `7*7-7`       | `7 7 * 7 -`   | 42        |

### Algoritmo

Para cada token en la expresión:
- Si es un **dígito** (0–9): push a la pila
- Si es un **operador** (`+ - * /`): pop dos valores, operar, push resultado
- Cualquier otra cosa → `Error`

Al final, la pila debe tener exactamente un elemento: el resultado.

```
Expresión: "7 7 * 7 -"

Token "7" → stack: [7]
Token "7" → stack: [7, 7]
Token "*" → pop 7, pop 7 → 7*7=49 → stack: [49]
Token "7" → stack: [49, 7]
Token "-" → pop 7, pop 49 → 49-7=42 → stack: [42]

Resultado: 42
```

### Restricciones del subject

- Los **números del input** son siempre < 10 (un solo dígito)
- El resultado sí puede superar 9
- No se manejan paréntesis ni decimales

### Por qué std::stack

`std::stack` es la estructura ideal para RPN: LIFO (último en entrar, primero en salir). Operaciones usadas:
- `push(val)` — añadir un número
- `top()` — leer el tope
- `pop()` — extraer el tope
- `size()` — verificar que hay ≥ 2 elementos antes de operar

---

## Ex02 — PmergeMe

**Binario:** `PmergeMe`
**Uso:** `./PmergeMe 3 5 9 7 4`
**Contenedores:** `std::vector<int>` y `std::deque<int>`

### Qué hace

Ordena una secuencia de enteros positivos usando el algoritmo **Ford-Johnson (merge-insert sort)**, y muestra el tiempo que tarda con cada contenedor.

```
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 36 us
Time to process a range of 5 elements with std::deque  : 49 us
```

### El algoritmo Ford-Johnson

Ford-Johnson minimiza el número de comparaciones necesarias para ordenar una secuencia. Es el algoritmo óptimo en comparaciones para n pequeño.

#### Pasos

**1. Formar pares y ordenar cada par**
```
[3, 5, 9, 7, 4]
Pares: (5,3) (9,7) | straggler: 4
       ↑ganador ↑perdedor
```

**2. Ordenar recursivamente los ganadores**
```
Ganadores: [5, 9] → sorted: [5, 9]
Pares reordenados: [(5,3), (9,7)]
```

**3. Construir la cadena principal**

Insertar el perdedor del par mínimo al principio (es ≤ que el mínimo ganador):
```
result = [3, 5, 9]   ← b1=3 va primero, luego todos los ganadores
```

**4. Insertar los perdedores restantes en orden de Jacobsthal**

La secuencia de Jacobsthal determina el orden de inserción para minimizar comparaciones:
```
t1=1, t2=3, t3=5, t4=11, t5=21, t6=43 ...
Recurrencia: t(k) = t(k-1) + 2 * t(k-2)
```

Para cada perdedor `b_i`, se sabe que `b_i ≤ a_i` (su ganador). La búsqueda binaria se acota a `[begin, posición_de_a_i)`, reduciendo el rango máximo.

**5. Insertar el straggler (si n era impar)**

Búsqueda binaria en toda la cadena.

#### Por qué el orden de Jacobsthal

Insertar en orden normal (b2, b3, b4...) desaprovecha el conocimiento de las cotas superiores. El orden de Jacobsthal garantiza que cada grupo de inserciones usa exactamente `floor(log2(t_k))` comparaciones como máximo, que es el óptimo teórico.

#### Ejemplo completo con [3, 5, 9, 7, 4]

```
n=5, pairCount=2, straggler=4

Pares: [(9,7), (5,3)] → después de sort por ganador: [(5,3), (9,7)]
Ganadores recursivos: sort([5,9]) → [5,9]  (ya ordenados, n=2 → par=(5,3) primer lugar)

result = [3, 5, 9]   (b1=3, luego a1=5, a2=9)

Jacobsthal para pairCount=2: [3]
  g=0: curr=min(3,2)=2, insertar idx=2 down to 2:
    b2=7, partner=9, buscar 7 en [begin, pos(9)) = [3,5,_)
    lower_bound([3,5], 7) → inserta después de 5
    result = [3, 5, 7, 9]

Straggler=4:
  lower_bound([3,5,7,9], 4) → inserta entre 3 y 5
  result = [3, 4, 5, 7, 9] ✓
```

### Implementación

El algoritmo se implementa **dos veces por separado**, una para `std::vector` y otra para `std::deque`:

```cpp
void PmergeMe::sortVector(std::vector<int>& arr);
void PmergeMe::sortDeque(std::deque<int>& arr);
```

Operaciones clave usadas:
- `std::sort` — para reordenar los pares según el ganador
- `std::find` — para localizar el ganador (cota superior de búsqueda)
- `std::lower_bound` — búsqueda binaria para inserción
- `insert(pos, val)` — inserción en posición

### Medición de tiempo

Se usa `gettimeofday` (C++98, microsegundos):

```cpp
struct timeval tv;
gettimeofday(&tv, NULL);
double t = tv.tv_sec * 1e6 + tv.tv_usec;  // microsegundos
```

### Validación de entrada

```cpp
long n = std::strtol(argv[i], &end, 10);
if (*end != '\0' || n < 1 || n > INT_MAX)
    // Error: no numérico, negativo, cero, o demasiado grande
```

- Se rechazan: negativos, cero, no-numéricos, demasiado grandes
- El programa debe manejar al menos **3000 enteros** sin problemas

### Vector vs Deque — diferencias de rendimiento

| Operación        | `std::vector`              | `std::deque`               |
|------------------|----------------------------|----------------------------|
| Acceso aleatorio | O(1), contiguo en memoria  | O(1), bloques              |
| `insert` al medio| O(n) shift de elementos    | O(n) pero más costoso      |
| Memoria          | Un bloque continuo         | Bloques separados          |

Para Ford-Johnson con muchas inserciones en el medio, `std::vector` suele ser más rápido gracias a la localidad de caché.

---

---

## Preguntas de defensa

### Ex00 — Bitcoin Exchange

**¿Por qué usas `std::map` y no otro contenedor?**
> `std::map` mantiene las claves ordenadas automáticamente. Esto me permite usar `upper_bound(date)` para encontrar en O(log n) la fecha más cercana. Con un `vector` no ordenado necesitaría ordenarlo primero o hacer una búsqueda lineal.

**¿Cómo encuentras la fecha más cercana inferior?**
> Con `upper_bound(date)` obtengo un iterador al primer elemento **estrictamente mayor** que la fecha buscada. Retrocedo un paso con `--it` y llego al mayor elemento **≤ date**. Si `upper_bound` devuelve `begin()`, la fecha es anterior a todos los registros → error.

**¿Qué pasa si la fecha exacta existe en el mapa?**
> `upper_bound` devuelve el elemento siguiente al exacto. Al decrementar, apuntamos al exacto. Funciona igual.

**¿Qué formatos de fecha rechazas?**
> Cualquier cosa que no sea exactamente `YYYY-MM-DD`: longitud ≠ 10, guiones en posición incorrecta, caracteres no numéricos, mes fuera de [1,12], día fuera de [1,31].

**¿Por qué no validas si el día es válido para el mes (febrero tiene 28...)?**
> El subject no lo exige. La fecha "2011-02-30" se buscaría en el mapa y si no existe, se usaría la más cercana. En la base de datos oficial no hay fechas inválidas, solo en el input del usuario.

---

### Ex01 — RPN

**¿Qué pasa si la expresión tiene solo un número?**
> Al final la pila tiene exactamente 1 elemento → se devuelve ese número. Ej: `./RPN "5"` → `5`.

**¿Qué pasa si la expresión está vacía?**
> La pila queda vacía, `stack.size() != 1` → `InvalidExpressionException` → `Error`.

**¿Por qué los números deben ser < 10?**
> El subject lo exige para simplificar el parsing. Solo acepto tokens de un carácter que sean dígitos. El resultado puede ser cualquier valor entero.

**¿Qué pasa con la división entera? ¿5 / 2 = 2 o 2.5?**
> División entera de C++: `5 / 2 = 2`. El subject no pide manejar decimales.

**¿Qué pasa si divido por cero?**
> Lanzo `InvalidExpressionException` → se imprime `Error` por stderr y el programa termina con código 1.

**Explica el orden de los operandos en la resta y división.**
> El primero en ser popeado es `b` (el más reciente), el segundo es `a`. La operación es `a OP b`. Ejemplo con `"5 3 -"`:
> push 5, push 3 → pop b=3, pop a=5 → `5-3=2`. Correcto.

---

### Ex02 — PmergeMe

**¿Qué es el algoritmo Ford-Johnson?**
> Es un algoritmo de ordenación que minimiza el número de comparaciones. Funciona en tres fases: formar pares y ordenarlos, ordenar recursivamente los "ganadores" (elementos mayores de cada par), e insertar los "perdedores" usando la secuencia de Jacobsthal para minimizar las comparaciones en la búsqueda binaria.

**¿Qué es la secuencia de Jacobsthal y para qué sirve?**
> Es una secuencia definida por `t(k) = t(k-1) + 2*t(k-2)` con t1=1, t2=3: **1, 3, 5, 11, 21, 43...**
> Determina el orden en que se insertan los "perdedores". Al insertar en este orden, cada búsqueda binaria puede acotarse a un rango que no supera 2^k elementos, garantizando el mínimo teórico de comparaciones.

**¿Por qué insertas `b1` (el primer perdedor) primero?**
> Porque `b1 ≤ a1` (fueron emparejados y a1 ganó). Como `a1` es el mínimo de todos los ganadores (tras ordenarlos), `b1` es ≤ a todos los ganadores. Por tanto, va directamente al principio de la cadena sin necesitar búsqueda.

**¿Por qué implementas el algoritmo dos veces en vez de usar una función genérica?**
> El subject lo recomienda explícitamente: *"It is strongly advised to implement your algorithm for each container"*. Aunque la lógica es la misma, `std::vector` y `std::deque` tienen características de rendimiento distintas (memoria contigua vs. bloques), y implementarlos por separado permite observar esa diferencia.

**¿Por qué `std::vector` suele ser más rápido que `std::deque`?**
> `std::vector` almacena los datos en memoria contigua, lo que aprovecha mejor la caché del procesador. `std::deque` usa bloques separados con punteros intermedios, añadiendo indirecciones. Para accesos secuenciales y búsquedas binarias, `vector` es más eficiente.

**¿Cómo mides el tiempo?**
> Con `gettimeofday()` (disponible en C++98). Devuelve segundos y microsegundos. Convierto todo a microsegundos: `tv_sec * 1e6 + tv_usec`. Mido antes y después de cada `sort` por separado.

**¿Tu algoritmo es correcto con números repetidos?**
> Para encontrar la posición del ganador uso `std::find`, que devuelve la primera ocurrencia. Con duplicados esto puede fallar al identificar el ganador correcto. En la práctica, el test estándar usa `shuf -i 1-100000 -n 3000`, que genera valores únicos, por lo que no hay duplicados.

**¿Qué complejidad tiene tu implementación?**
> Las fases de emparejamiento y recursión son O(n log n). La inserción con Jacobsthal es O(n log n) en comparaciones. Sin embargo, la inserción en el medio de un `vector` o `deque` es O(n), haciendo que la complejidad global sea O(n²) en tiempo de ejecución. Para 3000 elementos (~9M operaciones) es perfectamente manejable.

**¿Qué pasa si pasas un solo número?**
> `n=1`, la función retorna inmediatamente. El output muestra ese número como "Before" y "After".

**¿Qué errores detectas en la entrada?**
> Números negativos, cero, no numéricos (letras, símbolos), y números demasiado grandes (> INT_MAX). Cualquiera imprime `Error` por stderr y termina con código 1.

---

## Compilación rápida

```bash
# ex00
cd 09/ex00 && make && ./btc input.txt

# ex01
cd 09/ex01 && make && ./RPN "7 7 * 7 -"

# ex02
cd 09/ex02 && make && ./PmergeMe 3 5 9 7 4
# con 3000 elementos:
./PmergeMe $(jot -r 3000 1 100000 | tr '\n' ' ')
```
