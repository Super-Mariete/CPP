# Eval CPP05 — ex01: Form up, maggots!

Cada punto es exactamente lo que el evaluador va a mirar y preguntar.

---

## ✅ Hay un Makefile que compila con los flags correctos

**Dónde:** `ex01/Makefile`, línea 4

Igual que ex00. Flags: `-Wall -Wextra -Werror -std=c++98` con compilador `c++`.

---

## ✅ Existe la clase Form

**Dónde:** `ex01/Form.hpp`

La clase tiene exactamente estos cuatro atributos privados:

```cpp
private:
    const std::string   _name;        // nombre del formulario
    bool                _isSigned;    // si está firmado o no
    const int           _gradeToSign;    // grado mínimo para firmar
    const int           _gradeToExecute; // grado mínimo para ejecutar
```

**Qué es cada uno:**
- `_name`: el tipo de formulario (ej. "ShrubberyCreationForm"). Const porque no cambia.
- `_isSigned`: empieza en `false`. Pasa a `true` cuando un burócrata con suficiente rango lo firma.
- `_gradeToSign`: el rango mínimo que se necesita para firmar. Const porque es un requisito fijo del formulario.
- `_gradeToExecute`: el rango mínimo para ejecutarlo. También const.

---

## ✅ Los nombres y grados son constantes

**Dónde:** `ex01/Form.hpp`, en la sección `private`

```cpp
const std::string   _name;
const int           _gradeToSign;
const int           _gradeToExecute;
```

**Qué implica que sean const:**
1. Solo se pueden asignar en la lista de inicialización del constructor, nunca después.
2. El `operator=` no puede copiarlos — solo puede copiar `_isSigned`:

```cpp
// ex01/Form.cpp
Form& Form::operator=(const Form& other)
{
    if (this != &other)
        _isSigned = other._isSigned;  // único campo no-const
    return *this;
}
```

**Cómo lo explicas:** *"El nombre y los grados requeridos son constantes porque son características propias del tipo de formulario, no del burócrata que lo usa. No tiene sentido que cambien. Por eso el operator= solo puede copiar si está firmado o no."*

---

## ✅ Todos los atributos son privados (no protected)

**Dónde:** `ex01/Form.hpp`, bajo la palabra clave `private:`

Todos están en `private`, no en `protected`. La diferencia:
- `private`: solo la propia clase puede acceder.
- `protected`: la clase y sus subclases pueden acceder.

En ex01 Form no tiene subclases, así que todo es `private`. (En ex02 esto cambia con AForm.)

---

## ✅ Los grados siguen las mismas restricciones que Bureaucrat

**Dónde:** `ex01/Form.cpp`, constructor

```cpp
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}
```

**Qué comprueba:** Si cualquiera de los dos grados está fuera del rango 1-150, se lanza excepción. Igual que con Bureaucrat. La Form también tiene sus propias excepciones anidadas que heredan de `std::exception`.

**Cómo lo explicas:** *"El formulario valida los grados en el constructor, igual que Bureaucrat. Si intento crear un Form con gradeToSign = 0, lanza GradeTooHighException."*

---

## ✅ Hay accessors y operator<< que muestra el estado completo

**Dónde:** `ex01/Form.hpp` (declaraciones) y `ex01/Form.cpp` (implementaciones)

Getters:
```cpp
getName()         // devuelve const std::string&
getIsSigned()     // devuelve bool
getGradeToSign()  // devuelve int
getGradeToExecute() // devuelve int
```

Operator<<:
```cpp
std::ostream& operator<<(std::ostream& os, const Form& f)
{
    os << "Form " << f.getName()
       << " | signed: " << (f.getIsSigned() ? "yes" : "no")
       << " | grade to sign: " << f.getGradeToSign()
       << " | grade to execute: " << f.getGradeToExecute() << ".";
    return os;
}
```

**Cómo lo explicas:** *"El operator<< imprime toda la información del formulario: nombre, si está firmado, y los grados requeridos."*

---

## ✅ Existe Form::beSigned() que funciona como describe el subject

**Dónde:** `ex01/Form.cpp`

```cpp
void Form::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}
```

**Qué hace:** Compara el grado del burócrata con el grado necesario para firmar.
- Si `b.getGrade() > _gradeToSign`: el número del burócrata es mayor, lo que significa que su rango es inferior. No puede firmar → excepción.
- Si puede firmar: `_isSigned = true`.

**Ejemplo concreto:** El formulario necesita grado 50 para firmar. El burócrata tiene grado 100.
`100 > 50` es verdadero → el burócrata no tiene rango suficiente → GradeTooLowException.

**Qué NO hace beSigned:** No imprime nada. Solo lanza excepción o firma. El mensaje lo maneja `signForm`.

**Cómo lo explicas:** *"beSigned es la lógica pura de firma. Si el grado del burócrata (número mayor = rango inferior) es mayor que el grado requerido, no puede firmar y lanza excepción. Si puede, pone _isSigned a true."*

---

## ✅ Existe Bureaucrat::signForm() que funciona como describe el subject

**Dónde:** `ex01/Bureaucrat.cpp`

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

**Qué hace:** El burócrata intenta firmar el formulario. Llama a `beSigned` dentro de un try/catch.
- Si `beSigned` funciona: imprime "[nombre] signed [formulario]".
- Si `beSigned` lanza excepción: la captura e imprime "[nombre] couldn't sign [formulario] because [motivo]".

**Diferencia clave entre signForm y beSigned:**

| | `beSigned` | `signForm` |
|---|---|---|
| **Quién lo define** | `Form` | `Bureaucrat` |
| **Qué hace con el error** | Lanza excepción | Captura la excepción y muestra mensaje |
| **Propaga la excepción** | Sí | No |

**Cómo lo explicas:** *"signForm es la acción del burócrata: intenta firmar. Llama a beSigned en un try/catch. Si beSigned lanza excepción, signForm la captura y muestra un mensaje legible. La excepción no sube más arriba."*

---

## ¿Por qué hay forward declaration en Bureaucrat.hpp?

**Dónde:** `ex01/Bureaucrat.hpp`, línea 6

```cpp
class Form;  // en lugar de #include "Form.hpp"
```

**Qué es:** Una declaración anticipada. Le dice al compilador "existe una clase llamada Form" sin necesitar el archivo completo.

**Por qué no hacer #include "Form.hpp" directamente:** Si `Bureaucrat.hpp` incluye `Form.hpp` y `Form.hpp` incluye `Bureaucrat.hpp`, el compilador entra en bucle infinito (inclusión circular). La forward declaration rompe ese ciclo.

**Cuándo funciona:** Solo cuando usas la clase como referencia (`Form&`) o puntero (`Form*`), nunca cuando accedes a sus miembros.

---

## Resumen para la demo

```bash
cd /Users/marta/Documents/PROJECTS/CPP/05/ex01 && make && ./form
```

Cosas que el main debe demostrar:
1. Crear un Form e imprimir su estado con `<<` (sin firmar)
2. Un burócrata con grado suficiente firma → éxito
3. Un burócrata con grado insuficiente intenta firmar → mensaje de error
4. Intentar crear un Form con grado inválido → excepción
