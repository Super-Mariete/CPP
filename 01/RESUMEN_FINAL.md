# ✅ CPP MODULE 01 - RESUMEN FINAL

## **ESTADO: COMPLETO Y LISTO PARA EVALUACIÓN**

---

## 📊 **EJERCICIOS COMPLETADOS**

| Ejercicio | Estado | Concepto Clave | Archivos |
|-----------|--------|----------------|----------|
| **ex00** | ✅ | Stack vs Heap | Zombie, newZombie, randomChump |
| **ex01** | ✅ | Array allocation (new[]) | zombieHorde |
| **ex02** | ✅ | References vs Pointers | main.cpp (demo) |
| **ex03** | ✅ | When to use ref vs ptr | Weapon, HumanA, HumanB |
| **ex04** | ✅ | File I/O & string manipulation | replace program |
| **ex05** | ✅ | Pointers to member functions | Harl class |
| **ex06** | ✅ | Switch statement (BONUS) | harlFilter |

---

## 🎓 **CONCEPTOS PRINCIPALES EXPLICADOS**

### **1. Stack vs Heap (ex00)**

```cpp
// STACK - Automático, rápido, scope limitado
void function() {
    Zombie z("Stack");  // Se destruye al salir de la función
}

// HEAP - Manual, persistente, requiere delete
Zombie* z = new Zombie("Heap");  // Vive hasta delete
delete z;
```

**Cuándo usar cada uno:**
- **Stack:** Objetos temporales, pequeños, en scope local
- **Heap:** Objetos que se devuelven, grandes, vida más allá del scope

---

### **2. Arrays Dinámicos (ex01)**

```cpp
// Asignación de array
Zombie* horde = new Zombie[N];  // Llama N veces al constructor por defecto

// CRÍTICO: Usar delete[] para arrays
delete[] horde;  // NO delete horde;
```

**Regla de oro:**
```
new    → delete
new[]  → delete[]
```

---

### **3. Referencias vs Punteros (ex02)**

| Característica | Pointer | Reference |
|----------------|---------|-----------|
| Puede ser NULL | ✅ Sí | ❌ No |
| Reasignable | ✅ Sí | ❌ No |
| Sintaxis | `*ptr` | `ref` |
| Dirección | `&var` | Alias directo |

```cpp
std::string str = "Hello";
std::string* ptr = &str;   // Puntero
std::string& ref = str;    // Referencia

*ptr;  // Acceso con *
ref;   // Acceso directo
```

---

### **4. Referencia vs Puntero en Clases (ex03)**

**HumanA - Referencia:**
```cpp
class HumanA {
    Weapon& weapon;  // SIEMPRE tiene arma
public:
    HumanA(std::string name, Weapon& weapon)
        : weapon(weapon)  // Inicializado en constructor
    { }
};
```

**HumanB - Puntero:**
```cpp
class HumanB {
    Weapon* weapon;  // PUEDE NO tener arma
public:
    HumanB(std::string name)
        : weapon(NULL)  // Puede ser NULL
    { }
    void setWeapon(Weapon& w) { weapon = &w; }
};
```

**Decisión:**
- **Referencia:** Objeto SIEMPRE existe, se pasa en constructor
- **Puntero:** Objeto PUEDE NO existir, puede ser NULL, se setea después

---

### **5. File Streams (ex04)**

```cpp
// Leer archivo
std::ifstream inputFile("file.txt");
if (!inputFile.is_open())
    // Error

std::string line;
while (std::getline(inputFile, line))
    // Procesar línea

inputFile.close();

// Escribir archivo
std::ofstream outputFile("out.txt");
outputFile << "content" << std::endl;
outputFile.close();
```

**Reemplazo de string (SIN std::string::replace):**
```cpp
std::string replaceAll(std::string str, const std::string& s1, const std::string& s2) {
    std::string result;
    size_t pos = 0;
    size_t found;

    while ((found = str.find(s1, pos)) != std::string::npos) {
        result += str.substr(pos, found - pos);  // Parte antes
        result += s2;                             // Reemplazo
        pos = found + s1.length();                // Saltar s1
    }
    result += str.substr(pos);  // Resto
    return result;
}
```

---

### **6. Punteros a Funciones Miembro (ex05)**

```cpp
// Declaración
void (ClassName::*functionPtr)(void);

// Array de punteros a funciones
void (Harl::*functions[4])(void) = {
    &Harl::debug,
    &Harl::info,
    &Harl::warning,
    &Harl::error
};

// Llamada
(this->*functions[i])();
```

**Por qué es mejor que if/else:**
```cpp
// ❌ MAL: Bosque de if/else
if (level == "DEBUG")
    debug();
else if (level == "INFO")
    info();
// ...

// ✅ BIEN: Array lookup
for (int i = 0; i < 4; i++)
    if (levels[i] == level)
        (this->*functions[i])();
```

---

### **7. Switch con Fall-Through (ex06)**

```cpp
switch (levelIndex) {
    case 0:  // DEBUG
        harl.complain("DEBUG");
        // Sin break → cae al siguiente
    case 1:  // INFO
        harl.complain("INFO");
        // Sin break → cae al siguiente
    case 2:  // WARNING
        harl.complain("WARNING");
        // Sin break → cae al siguiente
    case 3:  // ERROR
        harl.complain("ERROR");
        break;  // Aquí para
    default:
        std::cout << "Invalid" << std::endl;
}
```

**Resultado con `./harlFilter "WARNING"`:**
Imprime WARNING y ERROR (fall-through desde case 2).

---

## ✅ **VERIFICACIÓN DE REQUISITOS**

### **Requisitos Generales**

| Requisito | Estado |
|-----------|--------|
| Compila con `-Wall -Wextra -Werror -std=c++98` | ✅ |
| No funciones prohibidas (*printf, *alloc, free) | ✅ |
| No `using namespace` | ✅ |
| No `friend` | ✅ |
| Include guards en todos los .hpp | ✅ |
| Sin memory leaks | ✅ |
| Makefiles correctos (all, clean, fclean, re) | ✅ |
| Sin relinking innecesario | ✅ |

### **Verificación por Ejercicio**

#### **ex00: BraiiiiiiinnnzzzZ**
- ✅ Clase Zombie con nombre privado
- ✅ Función `announce()` imprime formato correcto
- ✅ `newZombie()` crea en heap
- ✅ `randomChump()` crea en stack
- ✅ Destructor imprime mensaje

#### **ex01: Moar brainz!**
- ✅ `zombieHorde()` usa `new[]`
- ✅ Inicializa N zombies
- ✅ Se libera con `delete[]`
- ✅ Sin memory leaks

#### **ex02: HI THIS IS BRAIN**
- ✅ Variable string
- ✅ Puntero a string
- ✅ Referencia a string
- ✅ Imprime direcciones (todas iguales)
- ✅ Imprime valores (todos iguales)

#### **ex03: Unnecessary violence**
- ✅ Clase Weapon con type privado
- ✅ `getType()` devuelve `const std::string&`
- ✅ `setType()` modifica type
- ✅ HumanA usa `Weapon&` (referencia)
- ✅ HumanB usa `Weapon*` (puntero)
- ✅ `attack()` imprime formato correcto
- ✅ Main del subject funciona correctamente

#### **ex04: Sed is for losers**
- ✅ Toma 3 argumentos (filename, s1, s2)
- ✅ Crea archivo `.replace`
- ✅ Reemplaza todas las ocurrencias
- ✅ NO usa `std::string::replace()`
- ✅ NO usa funciones C (fopen, etc.)
- ✅ Maneja errores (archivo no existe, etc.)

#### **ex05: Harl 2.0**
- ✅ Funciones privadas: debug, info, warning, error
- ✅ Función pública: `complain(std::string level)`
- ✅ USA punteros a funciones miembro
- ✅ NO usa bosque de if/else

#### **ex06: Harl filter**
- ✅ Toma 1 argumento (level)
- ✅ Imprime desde level y superiores
- ✅ USA switch statement
- ✅ USA fall-through
- ✅ Ejecutable se llama `harlFilter`

---

## 🧪 **CÓMO PROBAR TODO**

### **Compilación y Ejecución Individual**

```bash
# Ex00
cd 01/ex00 && make && ./zombie

# Ex01
cd 01/ex01 && make && ./zombie

# Ex02
cd 01/ex02 && make && ./brain

# Ex03
cd 01/ex03 && make && ./violence

# Ex04
cd 01/ex04 && make
echo "hello world" > test.txt
./replace test.txt hello hi
cat test.txt.replace

# Ex05
cd 01/ex05 && make && ./harl

# Ex06
cd 01/ex06 && make
./harlFilter "WARNING"
./harlFilter "DEBUG"
./harlFilter "INVALID"
```

### **Script de Verificación Automática**

```bash
cd 01
./verify_all.sh
```

Este script:
- Verifica keywords prohibidas
- Compila todos los ejercicios
- Ejecuta tests básicos
- Muestra output de cada ejercicio

### **Check Memory Leaks (Opcional)**

```bash
# En macOS
leaks -atExit -- ./zombie

# En Linux
valgrind --leak-check=full ./zombie
```

---

## 📋 **OUTPUTS ESPERADOS**

### **ex00: Stack vs Heap**
```
=== Creating zombie on HEAP ===
HeapZombie is born
HeapZombie: BraiiiiiiinnnzzzZ...
HeapZombie still exists here...
HeapZombie is destroyed

=== Creating zombie on STACK ===
StackZombie is born
StackZombie: BraiiiiiiinnnzzzZ...
StackZombie is destroyed
StackZombie is already destroyed here...
```

### **ex01: Zombie Horde**
```
=== Creating a horde of 5 zombies ===

=== Zombies announcing ===
HordeZombie: BraiiiiiiinnnzzzZ...
HordeZombie: BraiiiiiiinnnzzzZ...
HordeZombie: BraiiiiiiinnnzzzZ...
HordeZombie: BraiiiiiiinnnzzzZ...
HordeZombie: BraiiiiiiinnnzzzZ...

=== Deleting horde ===
HordeZombie is destroyed
HordeZombie is destroyed
HordeZombie is destroyed
HordeZombie is destroyed
HordeZombie is destroyed
```

### **ex02: References**
```
=== MEMORY ADDRESSES ===
Address of brain:       0x...
Address in stringPTR:   0x...  (same!)
Address of stringREF:   0x...  (same!)

=== VALUES ===
Value of brain:         HI THIS IS BRAIN
Value pointed by PTR:   HI THIS IS BRAIN
Value pointed by REF:   HI THIS IS BRAIN
```

### **ex03: Weapon**
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

### **ex04: Replace**
Input file:
```
hello world
hello there
goodbye hello
```

After `./replace test.txt hello hi`:
```
hi world
hi there
goodbye hi
```

### **ex05: Harl**
```
[ DEBUG ]
I love having extra bacon...

[ INFO ]
I cannot believe adding extra bacon...

[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

### **ex06: HarlFilter**
`./harlFilter "WARNING"`:
```
[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

---

## ⚠️ **ERRORES COMUNES A EVITAR**

1. ❌ **Usar `delete` en vez de `delete[]` para arrays**
   ```cpp
   Zombie* h = new Zombie[5];
   delete h;     // MAL!
   delete[] h;   // BIEN!
   ```

2. ❌ **No inicializar punteros a NULL**
   ```cpp
   Weapon* w;       // Peligroso!
   Weapon* w = NULL; // Correcto
   ```

3. ❌ **Usar if/else en ex05**
   - Prohibido! Debe usar array de punteros a funciones

4. ❌ **Usar `std::string::replace()` en ex04**
   - Prohibido! Implementar manualmente

5. ❌ **No cerrar archivos**
   ```cpp
   inputFile.close();   // NECESARIO
   outputFile.close();  // NECESARIO
   ```

6. ❌ **No verificar si archivo se abrió**
   ```cpp
   if (!file.is_open())  // CRÍTICO
       return error;
   ```

7. ❌ **Confundir pre y post incremento en punteros**
   ```cpp
   ++ptr;  // Pre: incrementa, luego usa
   ptr++;  // Post: usa, luego incrementa
   ```

---

## 🎯 **PREGUNTAS TÍPICAS DE DEFENSA**

### **ex00:**
**P:** ¿Cuándo usar stack vs heap?
**R:** Stack para objetos temporales locales. Heap para objetos que sobreviven al scope o se devuelven.

### **ex01:**
**P:** ¿Por qué `delete[]` y no `delete`?
**R:** `new[]` asigna array, C++ necesita saber que hay múltiples objetos para llamar destructores de todos.

### **ex02:**
**P:** ¿Cuál es la diferencia real entre puntero y referencia?
**R:** Internamente son lo mismo (direcciones). Sintaxis diferente. Referencias no pueden ser NULL ni reasignadas.

### **ex03:**
**P:** ¿Por qué HumanA usa referencia y HumanB puntero?
**R:** HumanA SIEMPRE tiene arma (pasada en constructor) → referencia. HumanB puede NO tener → puntero (puede ser NULL).

### **ex04:**
**P:** ¿Por qué no usar `std::string::replace()`?
**R:** El ejercicio busca que entiendas cómo funciona internamente: find, substr, concatenación.

### **ex05:**
**P:** ¿Qué es un puntero a función miembro?
**R:** Es una dirección a una función que pertenece a una clase. Necesita objeto para llamarse: `(this->*ptr)()`.

### **ex06:**
**P:** ¿Qué es fall-through en switch?
**R:** Cuando no pones `break`, la ejecución continúa al siguiente case. Útil para ejecutar múltiples casos.

---

## 📚 **ARCHIVOS CREADOS**

```
01/
├── CPP01_CONCEPTS_AND_EVALUATION.md  # Guía completa de conceptos
├── RESUMEN_FINAL.md                   # Este archivo
├── verify_all.sh                      # Script de verificación
├── test_ex04.txt                      # Archivo de prueba ex04
├── ex00/
│   ├── Makefile
│   ├── main.cpp
│   ├── Zombie.hpp
│   ├── Zombie.cpp
│   ├── newZombie.cpp
│   └── randomChump.cpp
├── ex01/
│   ├── Makefile
│   ├── main.cpp
│   ├── Zombie.hpp
│   ├── Zombie.cpp
│   └── zombieHorde.cpp
├── ex02/
│   ├── Makefile
│   └── main.cpp
├── ex03/
│   ├── Makefile
│   ├── main.cpp
│   ├── Weapon.hpp
│   ├── Weapon.cpp
│   ├── HumanA.hpp
│   ├── HumanA.cpp
│   ├── HumanB.hpp
│   └── HumanB.cpp
├── ex04/
│   ├── Makefile
│   └── main.cpp
├── ex05/
│   ├── Makefile
│   ├── main.cpp
│   ├── Harl.hpp
│   └── Harl.cpp
└── ex06/
    ├── Makefile
    ├── main.cpp
    ├── Harl.hpp
    └── Harl.cpp
```

---

## ✅ **CHECKLIST FINAL DE ENTREGA**

- [x] Todos los ejercicios compilan sin warnings
- [x] Sin memory leaks
- [x] Sin funciones prohibidas
- [x] Include guards en todos los .hpp
- [x] Makefiles funcionan correctamente
- [x] Código bien comentado en inglés
- [x] Outputs coinciden con lo esperado
- [x] Entiendo todos los conceptos
- [x] Puedo explicar cada ejercicio

---

## 🎓 **CALIFICACIÓN ESPERADA**

**Ejercicios Obligatorios:** ex00 - ex05 (100%)
**Ejercicio Bonus:** ex06 (+bonus)

**Estado:** ✅ **100% COMPLETO + BONUS**

**Listo para:** ✅ **DEFENSA Y EVALUACIÓN**

---

## 📞 **RECURSOS ADICIONALES**

- **Guía de Conceptos:** `CPP01_CONCEPTS_AND_EVALUATION.md`
- **Script de Verificación:** `./verify_all.sh`
- **Subject Original:** Revisar requisitos específicos

---

**Última actualización:** 17 de octubre de 2025
**Estado:** ✅ VERIFICADO Y LISTO

