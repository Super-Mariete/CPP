# Eval CPP05 — ex00: Mommy, when I grow up, I want to be a bureaucrat!

Cada punto es exactamente lo que el evaluador va a mirar y preguntar.
Para cada uno: qué es, dónde está en el código, y cómo lo explicas.

---

## ✅ Hay un Makefile que compila con los flags correctos

**Dónde:** `ex00/Makefile`, línea 4

```makefile
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
```

**Qué es:** Los flags de compilación obligatorios.
- `-Wall -Wextra` activan todos los warnings.
- `-Werror` convierte cualquier warning en error (el programa no compila si hay algo sospechoso).
- `-std=c++98` obliga a usar el estándar C++ de 1998, sin características modernas.

**Cómo lo explicas:** *"El Makefile compila con c++ y los cuatro flags requeridos. -Werror hace que cualquier warning rompa la compilación, lo que fuerza a escribir código limpio."*

---

## ✅ Existe la clase Bureaucrat con un nombre constante

**Dónde:** `ex00/Bureaucrat.hpp`, línea 36

```cpp
private:
    const std::string   _name;
    int                 _grade;
```

**Qué es:** `const std::string _name` significa que `_name` no puede modificarse nunca después de crearse el objeto. Es un atributo de solo lectura.

**Por qué es const:** El nombre de un burócrata es su identidad — no cambia. Hacerlo `const` impide un error accidental que lo modifique.

**Consecuencia importante:** Como `_name` es `const`, el `operator=` no puede copiarlo. Solo puede copiar `_grade`:

```cpp
// ex00/Bureaucrat.cpp, línea 14
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
    if (this != &other)
        _grade = other._grade;  // _name no se toca
    return *this;
}
```

**Cómo lo explicas:** *"`_name` es const porque el nombre de un burócrata no debe cambiar nunca. Eso me obliga a inicializarlo en la lista de inicialización del constructor, y en el operator= solo puedo copiar el grado."*

---

## ✅ El grado va de 1 (máximo) a 150 (mínimo)

**Dónde:** `ex00/Bureaucrat.cpp`, líneas 4-9

```cpp
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}
```

**Qué es:** La lógica está invertida respecto a lo intuitivo: el número 1 es el rango más alto (como un general es grado 1, un soldado raso es grado 150).

**Cómo lo explicas:** *"Grado 1 es el más alto, 150 el más bajo. Si alguien intenta crear un burócrata con grado 0 o menor, lanzo GradeTooHighException porque estaría por encima del máximo permitido. Si el grado es 151 o más, lanzo GradeTooLowException."*

---

## ✅ Se lanzan excepciones al crear un Bureaucrat con grado inválido

**Dónde:** `ex00/Bureaucrat.hpp`, líneas 22-30 (definición de las excepciones)

```cpp
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
```

**Qué es:** Son clases definidas dentro de `Bureaucrat` (clases anidadas). Heredan de `std::exception`, que es la clase base de todas las excepciones de C++.

**Por qué heredar de std::exception:** Para que se puedan capturar con `catch (const std::exception& e)`, que es el patrón estándar. Si no heredaran de ella, habría que capturar cada tipo por separado.

**El `throw()` al final de `what()`:** Es una especificación de C++98 que garantiza que `what()` nunca va a lanzar otra excepción. Es obligatorio porque `std::exception::what()` lo tiene.

**Cómo lo explicas:** *"Las excepciones son clases anidadas dentro de Bureaucrat. Heredan de std::exception para que cualquier catch (const std::exception& e) pueda capturarlas. El what() devuelve el mensaje de error."*

**Demo en main:** Intenta crear un `Bureaucrat("test", 0)` dentro de un try/catch y muestra el mensaje.

---

## ✅ Hay accessors para los atributos

**Dónde:** `ex00/Bureaucrat.hpp`, líneas 14-16 y `ex00/Bureaucrat.cpp`, líneas 23-24

```cpp
const std::string&  getName() const;
int                 getGrade() const;
```

**Qué es:** Los atributos son privados, así que la única forma de leerlos desde fuera es a través de estos métodos. Se llaman *getters* o *accessors*.

- `const std::string&` — devuelve una referencia constante (no copia el string, más eficiente).
- El `const` al final del método garantiza que el método no modifica el objeto.

**Cómo lo explicas:** *"Los atributos son privados. Para leerlos desde fuera uso getName() y getGrade(). Los métodos son const porque no modifican el objeto, solo leen."*

---

## ✅ Hay funciones increment/decrement que lanzan excepciones cuando corresponde

**Dónde:** `ex00/Bureaucrat.cpp`, líneas 26-38

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

**Qué es:** Incrementar el grado = subir de rango = el número baja. Decrementar = bajar de rango = el número sube. La comprobación se hace **antes** de modificar `_grade`.

**Por qué antes:** Si se comprobara después de modificar y luego se lanzara la excepción, el objeto habría quedado en estado inválido (grado 0 o 151) aunque el error fuese capturado.

**Cómo lo explicas:** *"incrementGrade hace _grade-- porque subir de rango significa un número menor. La comprobación va antes de la modificación para que si lanzo la excepción, el objeto no quede en estado inválido."*

---

## ✅ Las excepciones heredan de std::exception

Ya cubierto arriba. Punto clave para la demo:

```cpp
try {
    Bureaucrat b("test", 0);
} catch (const std::exception& e) {
    std::cout << e.what() << std::endl;  // "Grade is too high"
}
```

El `catch` usa `std::exception&` — si las excepciones no heredaran de ella, esto no funcionaría.

---

## ✅ Hay un operator<< para ostream

**Dónde:** `ex00/Bureaucrat.cpp`, líneas 73-77

```cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return os;
}
```

**Qué es:** Sobrecarga del operador `<<` para poder usar `std::cout << miburocrata`. No es un método de la clase sino una función libre que recibe el stream y el objeto.

**Por qué devuelve `std::ostream&`:** Para poder encadenar: `std::cout << b1 << b2`. Si devolviera void no se podría.

**Salida esperada:** `Alice, bureaucrat grade 42.`

**Cómo lo explicas:** *"Sobrecargar operator<< me permite usar cout << burocrata directamente. Devuelve la referencia al stream para poder encadenar salidas."*

---

## Resumen para la demo

```bash
cd /Users/marta/Documents/PROJECTS/CPP/05/ex00 && make && ./bureaucrat
```

Cosas que el main debe demostrar:
1. Crear un Bureaucrat válido e imprimir con `<<`
2. Intentar crear uno con grado 0 → GradeTooHighException
3. Intentar crear uno con grado 151 → GradeTooLowException
4. incrementGrade hasta llegar al límite → excepción
5. decrementGrade hasta llegar al límite → excepción
