# Eval CPP05 — ex03: At least this beats coffee-making

Cada punto es exactamente lo que el evaluador va a mirar y preguntar.
**Este ejercicio tiene un punto extra de diseño que el evaluador mira específicamente.**

---

## ✅ Hay un Makefile que compila con los flags correctos

**Dónde:** `ex03/Makefile`, línea 4

Flags: `-Wall -Wextra -Werror -std=c++98` con compilador `c++`.

---

## ✅ Existe la clase Intern

**Dónde:** `ex03/Intern.hpp`

```cpp
class Intern
{
public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    AForm* makeForm(const std::string& formName, const std::string& target) const;
};
```

**Qué es Intern:** Una clase que representa a un trabajador sin nombre ni grado. Su único propósito es fabricar formularios. No tiene atributos útiles.

**Por qué no tiene atributos:** Un `Intern` no tiene identidad propia (sin nombre, sin grado). Es una herramienta. El constructor de copia y el `operator=` no hacen nada relevante porque no hay estado que copiar.

**Forma canónica ortodoxa:** Aunque no tenga atributos útiles, el subject exige la forma canónica: constructor por defecto, constructor de copia, operator=, destructor. Los cuatro están definidos.

**Cómo lo explicas:** *"Intern tiene la forma canónica completa aunque no tenga atributos. Su único método útil es makeForm, que crea el formulario correcto según el nombre que le pases."*

---

## ✅ Existe makeForm() que funciona como describe el subject

**Dónde:** `ex03/Intern.cpp`

```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
```

**Qué hace:**
- Recibe el nombre del formulario como string y el target.
- Devuelve un puntero `AForm*` al formulario creado con `new`.
- Si el nombre no existe, imprime un error en `std::cerr` y devuelve `NULL`.
- Si existe, imprime `"Intern creates <formName>"` y devuelve el puntero.

**Nombres válidos:**

| String | Formulario creado |
|---|---|
| `"shrubbery creation"` | `new ShrubberyCreationForm(target)` |
| `"robotomy request"` | `new RobotomyRequestForm(target)` |
| `"presidential pardon"` | `new PresidentialPardonForm(target)` |

**Gestión de memoria — IMPORTANTE:** `makeForm` usa `new`. El código que llama a `makeForm` es responsable de hacer `delete`. Si no se hace, hay memory leak. En el main siempre protegemos con `if (f)` antes de usar el puntero:

```cpp
AForm* f = intern.makeForm("robotomy request", "Bender");
if (f) {
    boss.signForm(*f);
    boss.executeForm(*f);
    delete f;  // obligatorio
}
```

---

## ✅⭐ makeForm usa un array de punteros a función — NO if/else

**Este es el punto estrella del ejercicio. El evaluador lo comprueba explícitamente.**

La hoja de eval dice literalmente: *"If it's using an ugly approach like if/elseif/elseif/else branchings, please count this as wrong."*

**Dónde:** `ex03/Intern.cpp`

### La solución: tabla de structs con punteros a función

```cpp
// Funciones de fábrica (una por formulario)
static AForm* makeShrubbery(const std::string& target)
{
    return new ShrubberyCreationForm(target);
}
static AForm* makeRobotomy(const std::string& target)
{
    return new RobotomyRequestForm(target);
}
static AForm* makePardon(const std::string& target)
{
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
    struct FormEntry {
        const char* name;
        AForm*      (*create)(const std::string&);  // puntero a función
    };

    static const FormEntry forms[] = {
        { "shrubbery creation",  makeShrubbery },
        { "robotomy request",    makeRobotomy  },
        { "presidential pardon", makePardon    }
    };

    for (int i = 0; i < 3; ++i)
    {
        if (formName == forms[i].name)
        {
            std::cout << "Intern creates " << formName << std::endl;
            return forms[i].create(target);  // llama a la función apuntada
        }
    }

    std::cerr << "Intern: unknown form \"" << formName << "\"" << std::endl;
    return NULL;
}
```

---

### ¿Qué es un puntero a función?

Un puntero a función es una variable que almacena la dirección de una función. En lugar de llamar a la función directamente, la llamas a través del puntero.

```cpp
// Tipo: "puntero a función que recibe const std::string& y devuelve AForm*"
AForm* (*create)(const std::string&);

// Asignar:
create = makeShrubbery;   // guarda la dirección de makeShrubbery

// Llamar:
AForm* f = create("garden");  // equivale a makeShrubbery("garden")
```

**Cómo lo explicas:** *"create es un puntero a función. Le asigno la dirección de makeShrubbery, makeRobotomy o makePardon. Luego llamo a forms[i].create(target) y se ejecuta la función correcta."*

---

### ¿Por qué es mejor que if/else?

**Con if/else** (MAL — no hagas esto):
```cpp
if (formName == "shrubbery creation")
    return new ShrubberyCreationForm(target);
else if (formName == "robotomy request")
    return new RobotomyRequestForm(target);
else if (formName == "presidential pardon")
    return new PresidentialPardonForm(target);
else
    return NULL;
```

Problema: Si mañana hay un cuarto formulario, hay que entrar en `makeForm` y añadir otro `else if`. La función crece sin control.

**Con la tabla** (BIEN — lo que tenemos):
- Para añadir un formulario nuevo: añadir una función de fábrica + una línea en la tabla.
- `makeForm` no cambia nunca.
- El código de búsqueda está separado del registro de tipos.

**Cómo lo explicas:** *"La tabla separa los datos (qué formularios existen) de la lógica (cómo buscar). Si añado un formulario nuevo, solo añado una fila a la tabla. makeForm no cambia. Con if/else tendría que modificar makeForm cada vez."*

---

## Flujo completo de una llamada a makeForm

```
intern.makeForm("robotomy request", "Bender")
    │
    ├─ recorre la tabla: forms[0].name = "shrubbery creation" → no coincide
    ├─ recorre la tabla: forms[1].name = "robotomy request"  → COINCIDE
    │
    ├─ imprime: "Intern creates robotomy request"
    ├─ llama forms[1].create("Bender") → llama makeRobotomy("Bender")
    └─ return new RobotomyRequestForm("Bender")
```

```
intern.makeForm("coffee request", "Bob")
    │
    ├─ recorre toda la tabla: ninguna coincidencia
    ├─ imprime en cerr: "Intern: unknown form "coffee request""
    └─ return NULL
```

---

## Resumen para la demo

```bash
cd /Users/marta/Documents/PROJECTS/CPP/05/ex03 && make && ./intern
```

El main demuestra los cuatro casos:
1. `"shrubbery creation"` → crea el formulario + firma + ejecuta → árbol ASCII visible
2. `"robotomy request"` → crea + firma + ejecuta → 50% robotomía
3. `"presidential pardon"` → crea + firma + ejecuta → mensaje de perdón
4. `"coffee request"` → nombre inválido → mensaje de error, devuelve NULL

**Si el evaluador pregunta por el diseño, señala:**
- La struct `FormEntry` con el puntero a función `(*create)`.
- El array `forms[]` con las tres entradas.
- El bucle `for` que recorre y llama a `forms[i].create(target)`.
- Que añadir un formulario = añadir una función + una línea en el array. `makeForm` no cambia.
