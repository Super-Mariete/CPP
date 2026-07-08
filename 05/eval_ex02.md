# Eval CPP05 — ex02: No, you need form 28B, not 28C...

Cada punto es exactamente lo que el evaluador va a mirar y preguntar.

---

## ✅ Hay un Makefile que compila con los flags correctos

**Dónde:** `ex02/Makefile`, línea 4

Flags obligatorios: `-Wall -Wextra -Werror -std=c++98` con compilador `c++`.

---

## ✅ Existen formularios concretos conformes al subject

El subject especifica tres formularios. Están en:

| Clase | Archivos | gradeToSign | gradeToExecute | Acción |
|---|---|---|---|---|
| `ShrubberyCreationForm` | `ShrubberyCreationForm.hpp/.cpp` | 145 | 137 | Crea `<target>_shrubbery` con árbol ASCII |
| `RobotomyRequestForm` | `RobotomyRequestForm.hpp/.cpp` | 72 | 45 | 50% robotomiza con éxito, imprime resultado |
| `PresidentialPardonForm` | `PresidentialPardonForm.hpp/.cpp` | 25 | 5 | Imprime que Zaphod Beeblebrox perdona al target |

**Recordatorio de la lógica invertida:** Grado 1 = rango más alto. Un burócrata con grado 140 **puede** firmar ShrubberyCreationForm (140 ≤ 145) pero **no puede** ejecutarla (140 > 137).

---

## ✅ Los constructores solo toman un parámetro: el target

**Dónde:** por ejemplo `ex02/ShrubberyCreationForm.cpp`, línea 5

```cpp
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}
```

**Qué pasa aquí:** El constructor de la subclase recibe solo `target`. El nombre del formulario y los grados requeridos están codificados y se pasan al constructor de `AForm` mediante la lista de inicialización (`: AForm(...)`).

**Cómo lo explicas:** *"El constructor solo pide el target porque el nombre y los grados son fijos para cada tipo de formulario. Los paso directamente al constructor de AForm en la lista de inicialización."*

---

## ✅ Existe AForm (la clase abstracta) con execute()

**Dónde:** `ex02/AForm.hpp`, línea 22

```cpp
virtual void execute(const Bureaucrat& executor) const = 0;
```

**Qué es una función virtual pura (`= 0`):**
- Convierte a `AForm` en **clase abstracta**: no se puede instanciar directamente (`AForm f(...)` da error de compilación).
- Obliga a cada subclase a implementar su propia versión de `execute()`.
- Permite el polimorfismo: si tengo un `AForm*`, llamar a `execute()` invoca la versión correcta según el tipo real del objeto.

**Por qué se llama AForm y no Form:** La "A" es de Abstract. Es la convención para indicar que no se puede usar directamente.

**Cómo lo explicas:** *"AForm es una clase abstracta porque execute() es virtual pura (= 0). No puedo crear un AForm directamente, solo subclases concretas. Cada subclase implementa execute() con su lógica específica."*

---

## ✅ Las comprobaciones de grado están en AForm (checkExecution)

El evaluador menciona dos variantes válidas:
1. `execute()` es pura y cada subclase hace sus propias comprobaciones.
2. **La que usamos:** AForm tiene un método protegido que hace las comprobaciones, y cada subclase lo llama.

**Dónde:** `ex02/AForm.hpp`, línea 43 y `ex02/AForm.cpp`, líneas 38-44

```cpp
// En AForm.hpp (declaración)
protected:
    void checkExecution(const Bureaucrat& executor) const;

// En AForm.cpp (implementación)
void AForm::checkExecution(const Bureaucrat& executor) const
{
    if (!_isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
}
```

**Qué comprueba:**
1. ¿Está firmado? Si no → `FormNotSignedException`.
2. ¿El grado del ejecutor es suficiente? Si no → `GradeTooLowException`.

**Por qué `protected` y no `private`:**
- `private`: solo `AForm` podría llamarlo — las subclases no.
- `protected`: `AForm` y todas sus subclases pueden llamarlo, pero nadie de fuera.
- Las subclases necesitan llamarlo desde su `execute()`, así que tiene que ser `protected`.

**Cómo se usa en cada subclase:**

```cpp
// ex02/ShrubberyCreationForm.cpp
void ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
    checkExecution(executor);  // primero valida
    // luego hace la acción específica...
    std::ofstream file((_target + "_shrubbery").c_str());
    ...
}
```

**Cómo lo explicas:** *"checkExecution está en AForm como método protegido. Las tres subclases lo llaman al principio de su execute(). Así no duplico el código de validación en cada formulario. Es protected para que las subclases puedan llamarlo, pero nadie de fuera."*

---

## ✅ El destructor de AForm es virtual

**Dónde:** `ex02/AForm.hpp`, línea 14

```cpp
virtual ~AForm();
```

**Por qué es obligatorio:** Si elimino un objeto a través de un puntero a la clase base:

```cpp
AForm* f = new ShrubberyCreationForm("garden");
delete f;  // ¿qué destructor se llama?
```

- **Sin `virtual`:** solo se llama al destructor de `AForm`. El destructor de `ShrubberyCreationForm` nunca se ejecuta → memoria no liberada.
- **Con `virtual`:** el compilador busca el destructor real del objeto (el de `ShrubberyCreationForm`) y lo llama correctamente.

**Regla general:** Si una clase tiene al menos un método virtual, su destructor también debe serlo.

**Cómo lo explicas:** *"El destructor de AForm es virtual porque si elimino un objeto a través de un puntero AForm*, necesito que se llame al destructor de la subclase real, no solo el de AForm. Sin virtual, habría memory leak."*

---

## ✅ Existe Bureaucrat::executeForm() que funciona como describe el subject

**Dónde:** `ex02/Bureaucrat.cpp`

```cpp
void Bureaucrat::executeForm(const AForm& form) const
{
    try {
        form.execute(*this);
        std::cout << _name << " executed " << form.getName() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << _name << " couldn't execute " << form.getName()
            << " because " << e.what() << std::endl;
    }
}
```

**Qué hace:** Igual que `signForm` pero para ejecutar. El burócrata intenta ejecutar el formulario. Si `execute()` lanza excepción (no firmado, grado insuficiente), la captura y muestra un mensaje.

**La cadena completa de una ejecución:**
```
boss.executeForm(form)
  → form.execute(boss)           [virtual dispatch → subclase correcta]
    → checkExecution(boss)       [comprueba firmado y grado]
    → acción específica          [árbol, robotomía, perdón]
```

---

## ShrubberyCreationForm — detalle

**Dónde:** `ex02/ShrubberyCreationForm.cpp`

```cpp
void ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
    checkExecution(executor);
    std::ofstream file((_target + "_shrubbery").c_str());
    ...árbol ASCII...
}
```

**Por qué `.c_str()`:** En C++98, `std::ofstream` no acepta `std::string` directamente — necesita `const char*`. `.c_str()` convierte el string. (En C++11 ya no hace falta.)

**Qué crea:** Un archivo llamado `<target>_shrubbery` en el directorio actual.

---

## RobotomyRequestForm — detalle

**Dónde:** `ex02/RobotomyRequestForm.cpp`

```cpp
std::srand(std::time(NULL));
if (std::rand() % 2)
    std::cout << _target << " has been robotomized successfully!" << std::endl;
else
    std::cout << _target << " robotomization failed." << std::endl;
```

**Cómo funciona el 50%:** `std::rand() % 2` produce 0 o 1 con igual probabilidad. `std::srand(std::time(NULL))` inicializa la semilla con el tiempo actual. Si ejecutas dos veces en el mismo segundo, puede salir el mismo resultado.

---

## PresidentialPardonForm — detalle

**Dónde:** `ex02/PresidentialPardonForm.cpp`

```cpp
std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
```

Simplemente imprime el mensaje. Es el formulario más fácil de ejecutar pero el más difícil de conseguir (necesita grado 5 para ejecutar).

---

## Resumen para la demo

```bash
cd /Users/marta/Documents/PROJECTS/CPP/05/ex02 && make && ./forms
```

El main demuestra:
1. **ShrubberyCreationForm OK** (Forester, grado 100): firma + ejecuta → árbol ASCII en pantalla
2. **ShrubberyCreationForm FAIL** (Gardener, grado 140): firma, pero no puede ejecutar → mensaje de error
3. **RobotomyRequestForm** (Doctor, grado 45): firma + ejecuta × 2 (para ver el 50%)
4. **PresidentialPardonForm** (President, grado 1): firma + ejecuta
5. **Ejecutar sin firmar** → Form is not signed
6. **Grado insuficiente para ejecutar** → Grade is too low
