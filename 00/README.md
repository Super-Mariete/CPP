# CPP Module 00 - Complete Guide

## 📚 Contenido del Módulo

Este módulo introduce los conceptos básicos de C++ para estudiantes que vienen de C.

### Ejercicios:

1. **ex00: Megaphone** ⭐ (OBLIGATORIO)
   - Programa simple que convierte texto a mayúsculas
   - Introducción a `std::cout`, `std::string`

2. **ex01: My Awesome PhoneBook** ⭐ (OBLIGATORIO)
   - Agenda telefónica con clases
   - Introducción a clases, métodos, getters/setters
   - Manejo de input con `std::getline()`

3. **ex02: The Job Of Your Dreams** ⚡ (OPCIONAL)
   - Ingeniería inversa de una clase Account
   - Variables y métodos estáticos
   - Constructor/Destructor
   - Formateo avanzado con `<iomanip>`

---

## 🔄 De C a C++: Principales Diferencias

### 1. Input/Output

**C:**
```c
#include <stdio.h>
printf("Hello %s\n", name);
scanf("%s", name);
```

**C++:**
```cpp
#include <iostream>
#include <string>
std::cout << "Hello " << name << std::endl;
std::getline(std::cin, name);
```

### 2. Strings

**C:**
```c
char name[50];
strcpy(name, "John");
strcat(name, " Doe");
```

**C++:**
```cpp
std::string name = "John";
name = name + " Doe";  // O: name += " Doe";
```

### 3. Memoria

**C:**
```c
int *arr = malloc(10 * sizeof(int));
free(arr);
```

**C++:**
```cpp
int *arr = new int[10];
delete[] arr;

// Pero en este módulo NO usamos new/delete
```

### 4. Estructuras vs Clases

**C:**
```c
struct Person {
    char name[50];
    int age;
};

void setName(struct Person *p, const char *name) {
    strcpy(p->name, name);
}
```

**C++:**
```cpp
class Person {
private:
    std::string _name;
    int _age;
public:
    void setName(std::string name) {
        this->_name = name;
    }
    std::string getName(void) const {
        return this->_name;
    }
};
```

---

## 🎯 Conceptos Clave de C++

### 1. Namespaces
```cpp
std::cout   // cout está en el namespace std
std::string // string está en el namespace std

// PROHIBIDO en 42:
using namespace std;  // ❌ Te darán -42 puntos
```

### 2. Clases

```cpp
class MyClass {
private:      // Solo accesible desde dentro de la clase
    int _x;
    
public:       // Accesible desde fuera
    MyClass(void);           // Constructor
    ~MyClass(void);          // Destructor
    void setX(int x);        // Setter
    int getX(void) const;    // Getter
};
```

### 3. Constructor y Destructor

```cpp
MyClass::MyClass(void)  // Se llama al crear: MyClass obj;
{
    this->_x = 0;
    std::cout << "Object created" << std::endl;
}

MyClass::~MyClass(void)  // Se llama al destruir (sale del scope)
{
    std::cout << "Object destroyed" << std::endl;
}
```

### 4. this pointer

```cpp
void MyClass::setX(int x)
{
    this->_x = x;  // this apunta al objeto actual
    // Equivalente a (*this)._x = x;
}
```

### 5. const

```cpp
int getX(void) const;  // Esta función NO modifica el objeto
```

### 6. Variables y Métodos Estáticos

```cpp
class Counter {
private:
    static int _count;  // Compartida por TODAS las instancias
    
public:
    static int getCount(void);  // Método estático
};

// Inicialización (en .cpp):
int Counter::_count = 0;

// Uso:
int total = Counter::getCount();  // Sin crear un objeto Counter
```

---

## 🛠️ Reglas de Compilación

### Compilador y Flags OBLIGATORIOS:
```bash
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program
```

### Makefile Básico:
```makefile
NAME = program
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp MyClass.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## 🚫 Funciones PROHIBIDAS

❌ `printf()`, `scanf()`, y toda la familia `*printf()`
❌ `malloc()`, `calloc()`, `realloc()`, `free()` y `*alloc()`
❌ `using namespace <ns_name>`
❌ `friend` keyword
❌ Containers STL (vector, list, map) - Solo desde Module 08
❌ Algoritmos STL - Solo desde Module 08
❌ C++11 o superior (usar solo C++98)

✅ Usar: `std::cout`, `std::cin`, `std::string`, `new`/`delete`

---

## 📁 Estructura de Archivos

```
CPP/00/
├── ex00/
│   ├── Makefile
│   └── megaphone.cpp
├── ex01/
│   ├── Makefile
│   ├── main.cpp
│   ├── Contact.hpp
│   ├── Contact.cpp
│   ├── PhoneBook.hpp
│   └── PhoneBook.cpp
└── ex02/
    ├── Makefile
    ├── Account.hpp    (dado)
    ├── Account.cpp    (implementar)
    └── tests.cpp      (dado)
```

---

## ✅ Checklist Antes de Entregar

- [ ] Compila con `-Wall -Wextra -Werror -std=c++98`
- [ ] No hay memory leaks (si usas new/delete)
- [ ] No usas funciones prohibidas
- [ ] Headers tienen include guards
- [ ] Nombres de archivos: `ClassName.hpp`, `ClassName.cpp`
- [ ] Nombres de clases en UpperCamelCase
- [ ] Todo en el directorio correcto (ex00, ex01, ex02)
- [ ] Makefile con reglas: all, clean, fclean, re

---

## 🎓 Consejos

1. **Lee el subject completo** antes de empezar
2. **No uses AI** para resolver los ejercicios (está prohibido en esta fase)
3. **Pregunta a tus compañeros** - peer learning es clave en 42
4. **Prueba exhaustivamente** - el evaluador probará casos extremos
5. **Lee los mensajes de error** del compilador - C++ tiene mejores mensajes que C
6. **Usa valgrind** para verificar memory leaks (si usas new/delete)

---

## 📖 Recursos Útiles

- https://cplusplus.com/reference/
- https://cplusplus.com/reference/string/string/
- https://cplusplus.com/reference/iomanip/

---

**¡Buena suerte con el módulo! 🚀**
