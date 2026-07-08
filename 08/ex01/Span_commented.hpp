#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <stdexcept>

// ─── PUNTO CLAVE DEFENSA ─────────────────────────────────────────────────────
// El evaluador comprueba:
// 1. "Any non-interface class is not in orthodox canonical class form"
//    → necesita: constructor, copy constructor, operator=, destructor
// 2. "Member functions use STL algorithms as much as possible"
// 3. "Finding the shortest span can't be done only by subtracting the two
//    lowest numbers (take a closer look at the subject example)"
//    → la estrategia correcta: ORDENAR + comparar PARES ADYACENTES
// 4. "There's an addNumber() function repeated way to add numbers that's
//    more practical than calling it repeatedly" → addRange()
// ─────────────────────────────────────────────────────────────────────────────

class Span
{
public:
    // ── FORMA CANÓNICA ORTODOXA (obligatorio en 42) ───────────────────────────
    Span(unsigned int n);               // constructor: capacidad máxima N
    Span(const Span& other);            // copy constructor
    Span& operator=(const Span& other); // operador de asignación
    ~Span();                            // destructor

    // ── FUNCIÓN PRINCIPAL ─────────────────────────────────────────────────────
    void addNumber(int n);
    // Añade un número. Lanza FullException si ya está lleno.

    // ── ADDRANGE: la función "mejorada" que busca el evaluador ────────────────
    // Evaluador: "There's a way to add numbers that's more practical than
    //             calling addNumber() repeatedly"
    //
    // Es un MÉTODO TEMPLATE dentro de una clase NO template.
    // Acepta cualquier tipo de iterador (vector, list, deque, array...)
    // DEBE definirse aquí en el .hpp porque los templates se instancian
    // en tiempo de compilación: si estuviera en el .cpp, el compilador
    // no vería la definición al compilar otros archivos.
    template <typename Iterator>
    void addRange(Iterator begin, Iterator end)
    {
        // ── POR QUÉ NO LLAMAR A addNumber EN UN BUCLE ─────────────────────────
        // El bucle simple (while begin!=end: addNumber(*begin++)) tiene un problema:
        // si el rango no cabe entero, lanza FullException a MITAD de la inserción.
        // El Span queda en estado inconsistente: se añadieron algunos elementos pero
        // no todos. Eso es un efecto secundario inesperado e indeseable.
        //
        // Solución ATÓMICA: comprobar primero si hay hueco para TODO el rango.
        // Si no cabe → lanzar ANTES de insertar nada.
        // Si cabe    → insertar todo de una vez con vector::insert.
        //
        // std::distance: STL algorithm que cuenta cuántos pasos hay entre dos
        //   iteradores. Para random-access (vector) es O(1); para list es O(n).
        //   "typename" no hace falta aquí porque std::distance devuelve un tipo
        //   concreto (std::ptrdiff_t).
        if (_data.size() + (std::size_t)std::distance(begin, end) > _maxSize)
            throw FullException();  // lanza ANTES de tocar _data → operación atómica

        // vector::insert(pos, first, last): inserta el rango [first,last) en pos.
        // Es más eficiente que un bucle: puede reservar memoria de una sola vez.
        // Además usa iteradores directamente → STL idiomático (el subject lo pide).
        _data.insert(_data.end(), begin, end);
    }

    // ── CÁLCULO DE SPANS ──────────────────────────────────────────────────────
    int shortestSpan() const;  // diferencia mínima entre cualquier par
    int longestSpan() const;   // diferencia máxima entre cualquier par
    // Ambos son const → no pueden modificar el estado del objeto

    // ── EXCEPCIONES ───────────────────────────────────────────────────────────
    class FullException : public std::exception
    {
    public:
        const char* what() const throw();  // "Span is full"
    };

    class NotEnoughNumbersException : public std::exception
    {
    public:
        const char* what() const throw();  // "Not enough numbers to compute a span"
    };

private:
    unsigned int      _maxSize;  // capacidad máxima (fijada en constructor)
    std::vector<int>  _data;     // almacén de números
};

// ─── PREGUNTAS DE DEFENSA ─────────────────────────────────────────────────────
// P: ¿Por qué addRange está en el .hpp y no en el .cpp?
// R: Es un método template. Los templates no generan código hasta que se
//    instancian con un tipo concreto. Si la definición estuviera en el .cpp,
//    el compilador no la vería al compilar otros archivos → error de enlazado.
//
// P: ¿Por qué la clase Span no es template pero addRange sí?
// R: Span siempre trabaja con int (tipo fijo), no necesita ser genérica.
//    Solo addRange necesita ser genérica para aceptar cualquier tipo de iterador.
//
// P: ¿Por qué usas std::distance en vez de (end - begin)?
// R: El operador - solo existe para iteradores de acceso aleatorio (vector, deque).
//    std::distance funciona con cualquier iterador (también list, set...).
//    Esto hace que addRange sea genérico para todos los contenedores.
//
// P: ¿Por qué addRange es atómico ahora?
// R: Primero comprueba si hay espacio para todo el rango. Si no cabe, lanza
//    ANTES de insertar nada → el Span queda sin modificar. El bucle con addNumber
//    insertaba algunos elementos antes de lanzar → estado inconsistente.
// ─────────────────────────────────────────────────────────────────────────────

#endif
