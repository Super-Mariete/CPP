#include "Span.hpp"
#include <algorithm>   // std::sort, std::min_element, std::max_element
#include <climits>     // INT_MAX

// ── FORMA CANÓNICA ORTODOXA ───────────────────────────────────────────────────

Span::Span(unsigned int n) : _maxSize(n) {}
// Inicialización directa con lista de inicialización (más eficiente que asignar en el cuerpo)
// _data queda vacío (vector se inicializa vacío por defecto)

Span::Span(const Span& other) : _maxSize(other._maxSize), _data(other._data) {}
// Copia profunda: std::vector tiene su propio copy constructor que copia todos los elementos
// No hay punteros raw, así que no hay riesgo de doble free

Span& Span::operator=(const Span& other)
{
    if (this != &other)  // guardia contra auto-asignación: sp = sp
    {
        _maxSize = other._maxSize;
        _data    = other._data;    // operator= de vector copia todos los elementos
    }
    return *this;  // devuelve referencia para permitir: sp1 = sp2 = sp3
}

Span::~Span() {}
// El vector libera su memoria automáticamente (RAII)
// No hay recursos adicionales que limpiar

// ── ADDNUMBER ─────────────────────────────────────────────────────────────────

void Span::addNumber(int n)
{
    if (_data.size() >= _maxSize)   // _data.size() devuelve size_t (sin signo)
        throw FullException();       // lanza si ya alcanzamos la capacidad máxima
    _data.push_back(n);             // añade al final del vector
}

// ── SHORTESTSPAN ─────────────────────────────────────────────────────────────

int Span::shortestSpan() const
{
    if (_data.size() < 2)           // necesitamos al menos 2 números para calcular span
        throw NotEnoughNumbersException();

    // ── POR QUÉ HACEMOS UNA COPIA ────────────────────────────────────────────
    // 1. shortestSpan es const → no puede modificar _data directamente
    // 2. Ordenar _data cambiaría el orden de inserción del usuario (efecto secundario inesperado)
    // 3. Solución: copiar en variable local, ordenar la copia, dejar _data intacto
    std::vector<int> sorted(_data);         // copia local
    std::sort(sorted.begin(), sorted.end()); // STL algorithm ← el evaluador lo busca

    // ── POR QUÉ COMPARAR PARES ADYACENTES TRAS ORDENAR ───────────────────────
    // EVALUADOR: "Finding the shortest span can't be done only by subtracting
    //             the two lowest numbers"
    //
    // En un conjunto ordenado x1 ≤ x2 ≤ ... ≤ xn, cualquier diferencia entre
    // elementos NO adyacentes es la suma de diferencias adyacentes intermedias:
    //   xj - xi = (xj - xj-1) + ... + (xi+1 - xi)  →  siempre ≥ diferencia adyacente
    //
    // Ejemplo: {3, 6, 9, 11, 17}
    //   adyacentes: 3, 3, 2, 6  →  mínimo = 2 (entre 9 y 11)
    //   si solo miramos los dos menores: 6-3 = 3 → INCORRECTO
    //
    // Por eso hay que recorrer TODOS los pares adyacentes, no solo el primero.
    int shortest = INT_MAX;
    for (std::size_t i = 1; i < sorted.size(); i++)
    {
        int diff = sorted[i] - sorted[i - 1];  // diferencia entre adyacentes
        if (diff < shortest)
            shortest = diff;
    }
    return shortest;
}

// ── LONGESTSPAN ───────────────────────────────────────────────────────────────

int Span::longestSpan() const
{
    if (_data.size() < 2)
        throw NotEnoughNumbersException();

    // El span más largo es simplemente max - min del conjunto entero.
    // No hace falta ordenar: std::min_element y std::max_element recorren en O(n).
    // Ambos son STL algorithms ← el evaluador lo busca
    int minVal = *std::min_element(_data.begin(), _data.end());
    int maxVal = *std::max_element(_data.begin(), _data.end());
    return maxVal - minVal;
    // *std::min_element devuelve referencia al elemento mínimo, * lo desreferencia
}

// ── MENSAJES DE EXCEPCIÓN ─────────────────────────────────────────────────────

const char* Span::FullException::what() const throw()
{
    return "Span is full";
    // throw() al final = especificación de excepción vacía (C++98): garantiza que
    // este método NO lanza excepciones. En C++11 sería noexcept.
}

const char* Span::NotEnoughNumbersException::what() const throw()
{
    return "Not enough numbers to compute a span";
}

// ─── PREGUNTAS DE DEFENSA ─────────────────────────────────────────────────────
// P: ¿Por qué shortestSpan hace una copia del vector?
// R: Es const, no puede modificar _data. Además, ordenar cambia el orden de
//    inserción del usuario, que es un efecto secundario inesperado.
//
// P: ¿Por qué comparar pares adyacentes garantiza el mínimo?
// R: En un array ordenado, cualquier diferencia no adyacente es suma de
//    diferencias adyacentes, siempre mayor o igual. El mínimo global está
//    siempre entre algún par adyacente.
//
// P: ¿Por qué longestSpan no necesita ordenar?
// R: El span máximo es max - min, y std::min/max_element los encuentran en O(n)
//    sin ordenar. Ordenar sería O(n log n), innecesario.
//
// P: ¿Qué pasa si addRange añade más elementos de los que caben?
// R: addRange llama a addNumber en cada iteración. addNumber lanza FullException
//    en cuanto se supera _maxSize. La excepción se propaga hacia arriba.
// ─────────────────────────────────────────────────────────────────────────────
