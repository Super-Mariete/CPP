#include "ScalarConverter.hpp" // declaración de la clase ScalarConverter
#include <iostream>            // std::cout
#include <string>              // std::string
#include <climits>             // INT_MAX, INT_MIN
#include <cfloat>              // FLT_MAX, DBL_MAX (no usados directamente pero útiles)
#include <cstdlib>             // strtod, strtol
#include <cerrno>              // errno, ERANGE
#include <cmath>               // std::isnan, std::isinf, std::floor

// ---- Type detection helpers ----
// Funciones internas (static = visibles solo en este .cpp) para detectar
// qué tipo representa el string que pasó el usuario.

// Detecta si el string es un literal de char: 'a', 'z', etc.
static bool isCharLiteral(const std::string& s)
{
    bool correctLength  = s.length() == 3;  // exactamente 3 chars: comilla + char + comilla
    bool hasOpenQuote   = s[0] == '\'';     // empieza con comilla simple
    bool hasCloseQuote  = s[2] == '\'';     // termina con comilla simple
    return correctLength && hasOpenQuote && hasCloseQuote; // las tres condiciones a la vez
}

// Detecta si el string es un valor especial de float o double (nan, inf, etc.)
static bool isSpecial(const std::string& s)
{
    return s == "nan" || s == "nanf"          // not a number (double y float)
        || s == "+inf" || s == "-inf"         // infinito positivo y negativo (double)
        || s == "+inff" || s == "-inff"       // infinito positivo y negativo (float)
        || s == "inf" || s == "inff";         // infinito sin signo (double y float)
}

// Detecta si el string es un literal float: termina en 'f' y tiene punto decimal.
static bool isFloat(const std::string& s)
{
    if (s.empty() || s[s.length() - 1] != 'f') // si está vacío o no termina en 'f', no es float
        return false;
    std::string sub = s.substr(0, s.length() - 1); // quitamos la 'f' final: "4.2f" → "4.2"
    char* end;      // end apuntará al primer char que strtod NO pudo parsear
    errno = 0;      // reseteamos errno antes de llamar para detectar overflow limpiamente
    strtod(sub.c_str(), &end);               // intentamos convertir "4.2" a double
    bool fullyParsed     = *end == '\0';     // si end apunta a '\0', todo el string era número
    bool hasDecimalPoint = sub.find('.') != std::string::npos; // debe tener punto decimal
    return fullyParsed && hasDecimalPoint;   // válido solo si ambas condiciones se cumplen
}

// Detecta si el string es un literal double: número con punto decimal, sin 'f' final.
static bool isDouble(const std::string& s)
{
    char* end;      // end apuntará al primer char que strtod NO pudo parsear
    errno = 0;      // reseteamos errno
    strtod(s.c_str(), &end);                 // intentamos convertir el string entero a double
    bool fullyParsed     = *end == '\0';     // todo el string fue consumido = número válido
    bool hasDecimalPoint = s.find('.') != std::string::npos; // debe tener punto decimal
    return fullyParsed && hasDecimalPoint;   // válido solo si ambas condiciones se cumplen
}

// Detecta si el string es un literal entero: solo dígitos (y signo opcional).
static bool isInt(const std::string& s)
{
    char* end;      // end apuntará al primer char que strtol NO pudo parsear
    errno = 0;      // reseteamos errno
    long val = strtol(s.c_str(), &end, 10); // intentamos convertir en base 10
    (void)val;      // silenciamos el warning de variable no usada; solo nos importa end
    return *end == '\0'; // si end apunta a '\0', todo el string era un entero válido
}

// ---- Print helpers ----
// Todas reciben un double d (tipo puente universal) y muestran la conversión.

// Imprime el valor como char, o un mensaje si no es posible/displayable.
static void printChar(double d)
{
    // imposible: NaN, infinito, o fuera del rango ASCII (0-127)
    if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    // non displayable: caracteres de control ASCII (0-31) y DEL (127)
    else if (d < 32 || d == 127)
        std::cout << "char: Non displayable" << std::endl;
    // displayable: cast explícito de double a char y lo mostramos entre comillas
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

// Imprime el valor como int, o "impossible" si no cabe o es especial.
static void printInt(double d)
{
    // imposible: NaN, infinito, o fuera del rango de int (INT_MIN a INT_MAX)
    if (std::isnan(d) || std::isinf(d)
        || d > static_cast<double>(INT_MAX) || d < static_cast<double>(INT_MIN))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl; // cast explícito a int
}

// Imprime el valor como float, añadiendo ".0" si es un entero exacto (ej: 42.0f).
static void printFloat(double d)
{
    float f = static_cast<float>(d);  // cast explícito de double a float (puede perder precisión)
    std::cout << "float: " << f;      // imprimimos el valor
    // si no es especial Y el valor es entero exacto (sin parte decimal), añadimos ".0"
    if (!std::isnan(f) && !std::isinf(f) && f == std::floor(f))
        std::cout << ".0";
    std::cout << "f" << std::endl;    // siempre termina en 'f' (notación float de C++)
}

// Imprime el valor como double, añadiendo ".0" si es un entero exacto.
static void printDouble(double d)
{
    std::cout << "double: " << d;     // imprimimos el valor
    // si no es especial Y el valor es entero exacto, añadimos ".0"
    if (!std::isnan(d) && !std::isinf(d) && d == std::floor(d))
        std::cout << ".0";
    std::cout << std::endl;
}

// ---- Main convert ----

// Único método público: recibe el string del usuario y orquesta detección + conversión.
void ScalarConverter::convert(const std::string& literal)
{
    double d; // tipo puente: convertimos todo a double primero, luego imprimimos cada tipo

    if (isCharLiteral(literal))
    {
        // literal[1] es el char entre las comillas: 'a' → cogemos 'a'
        // lo casteamos a double para usar el tipo puente
        d = static_cast<double>(literal[1]);
    }
    else if (isSpecial(literal))
    {
        // nan e inf no tienen representación como char ni como int
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;

        // para float y double, imprimimos el literal especial correspondiente
        if (literal == "nan" || literal == "nanf")
        {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        }
        else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff")
        {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        }
        else // "-inf" o "-inff"
        {
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        return; // salimos: ya imprimimos todo, no pasamos por los print helpers
    }
    else if (isFloat(literal))
    {
        // quitamos la 'f' final antes de parsear: "4.2f" → "4.2"
        d = strtod(literal.substr(0, literal.length() - 1).c_str(), NULL);
    }
    else if (isDouble(literal))
    {
        d = strtod(literal.c_str(), NULL); // parseamos el string directamente a double
    }
    else if (isInt(literal))
    {
        // parseamos como long y casteamos a double (tipo puente)
        d = static_cast<double>(strtol(literal.c_str(), NULL, 10));
    }
    else
    {
        // ningún tipo detectado: el input no es válido
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return; // salimos sin imprimir nada más
    }

    // llegamos aquí solo si detectamos un tipo válido y tenemos d con el valor
    printChar(d);   // muestra la conversión a char
    printInt(d);    // muestra la conversión a int
    printFloat(d);  // muestra la conversión a float
    printDouble(d); // muestra la conversión a double
}
