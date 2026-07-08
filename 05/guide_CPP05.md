# CPP05 — Repetition and Exceptions

Guia de estudio y defensa para el modulo CPP05 de la escuela 42.

---

## Indice

1. [Conceptos clave del modulo](#conceptos-clave)
2. [ex00 — Bureaucrat](#ex00--bureaucrat)
3. [ex01 — Form](#ex01--form)
4. [ex02 — AForm y formularios concretos](#ex02--aform-y-formularios-concretos)
5. [ex03 — Intern](#ex03--intern)
6. [Tabla de formularios](#tabla-de-formularios)
7. [Diagramas de herencia](#diagramas-de-herencia)
8. [Preguntas de defensa con respuestas](#preguntas-de-defensa)
9. [Compilacion rapida](#compilacion-rapida)

---

## Conceptos clave

### Que es una excepcion en C++

Una excepcion es un mecanismo que permite interrumpir el flujo normal de ejecucion cuando ocurre un error y transferir el control a un bloque de codigo preparado para manejarlo. El flujo basico es:

```cpp
try {
    // codigo que puede fallar
    throw AlgunaExcepcion();
}
catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

Cuando se lanza una excepcion con `throw`, el programa busca hacia arriba en la pila de llamadas el `catch` mas cercano que pueda capturarla. Si no encuentra ninguno, el programa termina con `std::terminate()`.

### Por que heredar de std::exception

La clase base `std::exception` de la biblioteca estandar define una interfaz comun para todas las excepciones:

```cpp
class exception {
public:
    virtual const char* what() const throw();
};
```

Heredar de ella permite:
- Capturar cualquier excepcion propia con `catch (const std::exception& e)`.
- Acceder al mensaje de error mediante `e.what()`.
- Integrarse con el ecosistema estandar de C++ (otras bibliotecas, herramientas de debug).

### El especificador throw() en what()

```cpp
const char* what() const throw();
```

El `throw()` al final es una especificacion de excepcion dinamica de C++98. Significa que `what()` garantiza que no lanzara ninguna excepcion. Es necesario porque `what()` sobreescribe la funcion virtual de `std::exception`, que tiene esa misma especificacion. En C++11 se reemplaza por `noexcept`.

### La logica invertida de los grados

En este modulo, **grado 1 es el maximo** y **grado 150 es el minimo**. Esto simula la jerarquia burocratica real.

Consecuencias importantes:
- `incrementGrade()` **reduce** el numero (`_grade--`), subiendo de rango.
- `decrementGrade()` **aumenta** el numero (`_grade++`), bajando de rango.
- Para comparar si un burocrata puede firmar/ejecutar: `b.getGrade() <= _gradeToSign` (numericamente menor o igual = rango igual o superior).

---

## ex00 — Bureaucrat

### Archivos

- `Bureaucrat.hpp` / `Bureaucrat.cpp`

### La clase

```cpp
class Bureaucrat
{
public:
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();

    const std::string&  getName() const;
    int                 getGrade() const;

    void    incrementGrade();
    void    decrementGrade();

    class GradeTooHighException : public std::exception
    {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
    public:
        const char* what() const throw();
    };

private:
    const std::string   _name;
    int                 _grade;
};
```

### Por que _name es const

`_name` se declara como `const std::string` porque el nombre de un burocrata es su identidad: no debe cambiar. El `operator=` solo puede copiar el grado:

```cpp
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
    if (this != &other)
        _grade = other._grade;  // solo _grade, nunca _name
    return *this;
}
```

El constructor de copia usa lista de inicializacion para inicializar el miembro `const`:

```cpp
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {}
```

### Validacion en el constructor

```cpp
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}
```

Si el grado es invalido, se lanza la excepcion y el objeto nunca llega a existir en un estado valido.

### incrementGrade y decrementGrade

```cpp
void Bureaucrat::incrementGrade()
{
    if (_grade - 1 < 1)
        throw GradeTooHighException();
    _grade--;
}

void Bureaucrat::decrementGrade()
{
    if (_grade + 1 > 150)
        throw GradeTooLowException();
    _grade++;
}
```

La comprobacion se hace **antes** de modificar `_grade`. Si se comprobara despues, el objeto quedaria en estado invalido aunque se lanzara la excepcion.

### Operador <<

```cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return os;
}
```

Salida de ejemplo: `Alice, bureaucrat grade 1.`

### Excepciones internas (nested classes)

Las excepciones se definen como clases anidadas dentro de `Bureaucrat`. Se accede a ellas como `Bureaucrat::GradeTooHighException`.

- `GradeTooHighException::what()` devuelve `"Grade is too high"`
- `GradeTooLowException::what()` devuelve `"Grade is too low"`

---

## ex01 — Form

### Archivos

- `Form.hpp` / `Form.cpp`
- `Bureaucrat.hpp` / `Bureaucrat.cpp` (actualizado con `signForm`)

### La clase Form

```cpp
class Form
{
public:
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    void    beSigned(const Bureaucrat& b);

    class GradeTooHighException : public std::exception { ... };
    class GradeTooLowException  : public std::exception { ... };

private:
    const std::string   _name;
    bool                _isSigned;
    const int           _gradeToSign;
    const int           _gradeToExecute;
};
```

### Por que _gradeToSign y _gradeToExecute son const

Son requisitos del formulario, no del burocrata. Al ser `const int`, tampoco pueden copiarse en `operator=`:

```cpp
Form& Form::operator=(const Form& other)
{
    if (this != &other)
        _isSigned = other._isSigned;  // solo _isSigned puede cambiar
    return *this;
}
```

### beSigned

```cpp
void Form::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}
```

La condicion `b.getGrade() > _gradeToSign`: si el formulario requiere grado 50 y el burocrata tiene grado 100, `100 > 50` es verdadero, por lo tanto no puede firmarlo.

### signForm en Bureaucrat

```cpp
void Bureaucrat::signForm(Form& form)
{
    try {
        form.beSigned(*this);
        std::cout << _name << " signed " << form.getName() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << _name << " couldn't sign " << form.getName()
            << " because " << e.what() << std::endl;
    }
}
```

`signForm` atrapa la excepcion internamente y muestra un mensaje legible. Nunca propaga la excepcion hacia arriba.

### Diferencia entre signForm y beSigned

| Metodo | Quien lo define | Que hace con el error |
|--------|----------------|----------------------|
| `beSigned(const Bureaucrat&)` | `Form` | Lanza excepcion |
| `signForm(Form&)` | `Bureaucrat` | Captura la excepcion y muestra mensaje |

### Forward declaration para evitar inclusion circular

`Bureaucrat.hpp` en ex01 usa una forward declaration:

```cpp
class Form;  // en lugar de #include "Form.hpp"
```

Si `Bureaucrat.hpp` incluye `Form.hpp` y `Form.hpp` incluye `Bureaucrat.hpp`, el compilador entra en un bucle infinito. La forward declaration dice "esta clase existe" sin necesitar el header completo.

---

## ex02 — AForm y formularios concretos

### La clase abstracta AForm

En ex02 `Form` se convierte en `AForm` (Abstract Form). La diferencia clave es `execute()`:

```cpp
virtual void execute(const Bureaucrat& executor) const = 0;
```

El `= 0` convierte a `execute` en **funcion virtual pura**, lo que hace a `AForm` una clase abstracta. No se puede instanciar directamente un `AForm`; solo se pueden instanciar sus subclases concretas.

### El metodo protegido checkExecution

```cpp
protected:
    void checkExecution(const Bureaucrat& executor) const;
```

```cpp
void AForm::checkExecution(const Bureaucrat& executor) const
{
    if (!_isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
}
```

Este metodo encapsula las dos comprobaciones que todos los formularios deben hacer antes de ejecutarse. Es `protected` porque:
- No debe ser llamado desde fuera de la jerarquia de clases.
- Las subclases concretas deben poder llamarlo desde su `execute()`.

### executeForm en Bureaucrat

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

### Destructor virtual en AForm

```cpp
virtual ~AForm();
```

Cuando se elimina un objeto mediante un puntero a la clase base (`AForm*`), el compilador debe saber que tiene que llamar al destructor de la subclase. Sin el destructor virtual, solo se llamaria al destructor de `AForm`. Esta es una regla fundamental en C++ con herencia polimorfica.

---

## Los tres formularios concretos

### ShrubberyCreationForm

```cpp
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}
```

- `gradeToSign`: 145
- `gradeToExecute`: 137

Al ejecutarse, crea un archivo `<target>_shrubbery` con un arbol ASCII. El `.c_str()` es necesario porque en C++98 `std::ofstream` no acepta `std::string` directamente.

### RobotomyRequestForm

```cpp
RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", 72, 45), _target(target) {}
```

- `gradeToSign`: 72
- `gradeToExecute`: 45

```cpp
std::srand(std::time(NULL));
if (std::rand() % 2)
    std::cout << _target << " has been robotomized successfully!" << std::endl;
else
    std::cout << _target << " robotomization failed." << std::endl;
```

`std::rand() % 2` produce 0 o 1. La probabilidad es 50/50.

### PresidentialPardonForm

```cpp
PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("PresidentialPardonForm", 25, 5), _target(target) {}
```

- `gradeToSign`: 25
- `gradeToExecute`: 5

Imprime que Zaphod Beeblebrox perdona al target.

---

## ex03 — Intern

### Que pide el enunciado

Crear una clase `Intern` que puede fabricar formularios sin que el codigo que la usa necesite saber de que tipo es cada uno. El trabajador interno no tiene nombre ni grado; simplemente hace el trabajo de oficina.

### La clase Intern

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

- No tiene atributos utiles: el constructor de copia y el `operator=` no hacen nada relevante.
- `makeForm` devuelve un puntero a `AForm` creado con `new`. **El que llama es responsable de hacer `delete`.**
- Si `formName` no corresponde a ningun formulario, imprime un error y devuelve `NULL`.

### El metodo makeForm y la tabla de fabricas

La decision de diseno mas importante de ex03: **no usar cadena if/else**.

El sujeto pide expresamente evitar un bosque de `if`/`else if`. La solucion es una tabla (array de structs) que asocia cada nombre con una funcion de fabrica:

```cpp
// Funciones de fabrica estaticas (fuera de la clase)
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
        AForm* (*create)(const std::string&);  // puntero a funcion
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
            return forms[i].create(target);
        }
    }

    std::cerr << "Intern: unknown form \"" << formName << "\"" << std::endl;
    return NULL;
}
```

**Por que este diseno es mejor que if/else:**

| Enfoque | Problema |
|---------|---------|
| `if (name == "x") return new X(t); else if...` | Violare Open/Closed: anadir un formulario implica tocar `makeForm`. |
| Tabla de structs | Para anadir un formulario solo se anade una fila en la tabla. `makeForm` no cambia. |

### Nombres de formulario validos

| String que acepta makeForm | Clase que crea |
|---|---|
| `"shrubbery creation"` | `ShrubberyCreationForm` |
| `"robotomy request"` | `RobotomyRequestForm` |
| `"presidential pardon"` | `PresidentialPardonForm` |

### Gestion de memoria

`makeForm` usa `new` para crear el objeto en el heap. El llamador debe hacer `delete` cuando ya no lo necesite:

```cpp
AForm* f = intern.makeForm("robotomy request", "Bender");
if (f) {
    boss.signForm(*f);
    boss.executeForm(*f);
    delete f;   // <-- obligatorio
}
```

Si `makeForm` devuelve `NULL` (nombre desconocido), el `if (f)` lo protege de un `delete` de puntero nulo.

### Diagrama de flujo de makeForm

```
intern.makeForm("robotomy request", "Bender")
    |
    +--> recorre la tabla de 3 entradas
    |
    +--> "robotomy request" == "robotomy request"  -> MATCH
    |
    +--> imprime: "Intern creates robotomy request"
    |
    +--> llama makeRobotomy("Bender")
    |
    +--> return new RobotomyRequestForm("Bender")
```

---

## Tabla de formularios

| Formulario | gradeToSign | gradeToExecute | Accion |
|---|---|---|---|
| `ShrubberyCreationForm` | 145 | 137 | Crea `<target>_shrubbery` con arboles ASCII |
| `RobotomyRequestForm` | 72 | 45 | 50% de exito, imprime resultado en pantalla |
| `PresidentialPardonForm` | 25 | 5 | Imprime que Zaphod Beeblebrox perdona al target |

Recordatorio: grado 1 es el mas alto, 150 el mas bajo. Un burocrata con grado 140 **puede** firmar `ShrubberyCreationForm` (140 <= 145) pero **no puede** firmar `RobotomyRequestForm` (140 > 72).

---

## Diagramas de herencia

### ex02

```
std::exception
    |
    +-- AForm::GradeTooHighException
    |
    +-- AForm::GradeTooLowException
    |
    +-- AForm::FormNotSignedException
    |
    +-- Bureaucrat::GradeTooHighException
    |
    +-- Bureaucrat::GradeTooLowException


AForm  (clase abstracta -- execute() = 0)
    |
    +-- ShrubberyCreationForm
    |
    +-- RobotomyRequestForm
    |
    +-- PresidentialPardonForm
```

### ex03

```
(mismo diagrama que ex02, mas:)

Intern
    |
    +-- makeForm(formName, target) --> AForm*
            |
            +--> new ShrubberyCreationForm(target)   si formName == "shrubbery creation"
            +--> new RobotomyRequestForm(target)     si formName == "robotomy request"
            +--> new PresidentialPardonForm(target)  si formName == "presidential pardon"
            +--> NULL + mensaje de error             si formName desconocido
```

---

## Preguntas de defensa

### 1. Que es una excepcion en C++ y por que heredar de std::exception?

Una excepcion es un mecanismo de gestion de errores que interrumpe el flujo normal de ejecucion. Se hereda de `std::exception` para:
- Poder capturar con `catch (const std::exception& e)`, el patron estandar.
- Usar la interfaz `what()` para obtener el mensaje de error.
- Integrarse con el ecosistema de C++.

### 2. Por que what() lleva throw() al final?

En C++98, `throw()` garantiza que la funcion no lanzara ninguna excepcion. Es obligatorio porque `std::exception::what()` lo declara con esa especificacion y al sobreescribir una funcion virtual hay que respetar la especificacion de la base.

### 3. Por que el grado 1 es el mas alto?

Es una convencion del enunciado: el grado 1 es el puesto de mayor responsabilidad. `incrementGrade()` hace `_grade--` (el numero baja, el rango sube) y `decrementGrade()` hace `_grade++`.

### 4. Que ocurre si incrementGrade() llega a 0?

El grado 0 es invalido. `incrementGrade()` comprueba antes de modificar:

```cpp
void Bureaucrat::incrementGrade()
{
    if (_grade - 1 < 1)
        throw GradeTooHighException();
    _grade--;
}
```

Si `_grade` es 1, `1 - 1 = 0 < 1` es verdadero y se lanza la excepcion. El valor nunca llega a 0.

### 5. Por que _name es const?

El nombre de un burocrata es su identidad inmutable. Esto impone una restriccion al `operator=`: solo puede copiar `_grade`. El constructor de copia debe usar lista de inicializacion para asignar el miembro `const`.

### 6. Por que AForm tiene checkExecution protegido?

Porque las dos comprobaciones previas (formulario firmado y grado suficiente) son identicas en todos los formularios. Sin `checkExecution`, cada subclase duplicaria ese codigo. Al ser `protected`:
- No es accesible desde fuera de la jerarquia.
- Las subclases pueden llamarlo desde su `execute()`.

### 7. Por que execute() es virtual pura?

No existe un comportamiento generico de "ejecutar un formulario". Cada tipo hace algo distinto. Con `= 0`:
1. `AForm` se convierte en clase abstracta: no se puede instanciar directamente.
2. Se obliga a cada subclase a implementar su version.
3. El polimorfismo permite llamar al `execute()` correcto a traves de `AForm&`.

### 8. Como funciona el 50% de RobotomyRequestForm?

`std::rand() % 2` genera 0 o 1. Estadisticamente 50/50. `std::srand(std::time(NULL))` inicializa la semilla con el tiempo actual en segundos. Si se ejecuta varias veces en el mismo segundo, el resultado puede ser el mismo.

### 9. Que hace ShrubberyCreationForm exactamente?

Crea un archivo `<target>_shrubbery` en el directorio actual con un arbol ASCII. Usa `std::ofstream`. El nombre se construye como `_target + "_shrubbery"` y se convierte con `.c_str()` porque en C++98 el constructor de `std::ofstream` no acepta `std::string`.

### 10. Que hace Intern y por que no tiene atributos?

`Intern` es una clase de utilidad pura: su unico proposito es fabricar formularios. No necesita identidad propia (nombre, grado), solo la capacidad de crear objetos. Sus constructores de copia y `operator=` no hacen nada util porque no hay estado que copiar.

### 11. Por que makeForm usa una tabla en vez de if/else?

Con if/else, cada formulario nuevo obliga a modificar `makeForm`. La tabla separa el registro de tipos (datos) de la logica de busqueda (algoritmo). Anadir un formulario = anadir una fila a la tabla. `makeForm` no cambia. Esto es el principio Open/Closed aplicado en C++98.

### 12. Que es un puntero a funcion y como se usa aqui?

Un puntero a funcion almacena la direccion de una funcion. En la tabla:

```cpp
AForm* (*create)(const std::string&);
```

Esto declara `create` como puntero a una funcion que recibe `const std::string&` y devuelve `AForm*`. Al hacer `forms[i].create(target)` se llama a la funcion apuntada con el argumento `target`.

### 13. Quien es responsable de liberar el AForm* que devuelve makeForm?

El llamador. `makeForm` usa `new` internamente. El codigo que invoca `makeForm` debe hacer `delete` cuando termine de usar el formulario. Si no lo hace, hay memory leak. Siempre hay que protegerse con `if (f)` antes del `delete` por si `makeForm` devolvio `NULL`.

### 14. Que pasa si se pasa un nombre de formulario desconocido a makeForm?

`makeForm` recorre la tabla entera sin encontrar coincidencia, imprime un mensaje de error en `std::cerr` y devuelve `NULL`. El codigo llamador debe comprobar si el puntero devuelto es nulo antes de usarlo.

### 15. Cual es la diferencia entre signForm y beSigned?

`Form::beSigned(const Bureaucrat& b)`:
- Logica pura de firma.
- Lanza excepcion si el grado es insuficiente.

`Bureaucrat::signForm(Form& form)`:
- Accion del burocrata: intenta firmar.
- Llama a `beSigned` en try/catch.
- No propaga la excepcion: muestra un mensaje legible.

---

## Compilacion rapida

```bash
# ex00
cd /Users/marta/Documents/PROJECTS/CPP/05/ex00 && make && ./bureaucrat

# ex01
cd /Users/marta/Documents/PROJECTS/CPP/05/ex01 && make && ./form

# ex02
cd /Users/marta/Documents/PROJECTS/CPP/05/ex02 && make && ./forms
# crea home_shrubbery en el directorio actual

# ex03
cd /Users/marta/Documents/PROJECTS/CPP/05/ex03 && make && ./intern
# crea garden_shrubbery en el directorio actual
```

```makefile
# Targets de Makefile disponibles en todos los ejercicios:
make        # compila
make clean  # elimina .o
make fclean # elimina .o y binario
make re     # fclean + all
```
