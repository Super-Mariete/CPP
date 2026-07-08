#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>   // std::find — OBLIGATORIO, el evaluador comprueba que usas STL
# include <stdexcept>   // std::runtime_error

// ─── PUNTO CLAVE DEFENSA ─────────────────────────────────────────────────────
// El evaluador comprueba: "There is a templated function easyfind(T, int)
// that USES STL ALGORITHMS. If it does not (like manual search using iterators),
// count it as WRONG."
//
// Tu función usa std::find → CORRECTO ✓
// Una búsqueda manual con while (*it != value) ++it → INCORRECTO ✗
// ─────────────────────────────────────────────────────────────────────────────

// T es el tipo del contenedor (std::vector<int>, std::list<int>, std::deque<int>...)
// El compilador deduce T automáticamente al llamar easyfind(vec, 25)
template <typename T>
typename T::iterator easyfind(T& container, int value)
//         ↑ tipo de retorno: el iterador del contenedor T
//           "typename" es necesario porque T::iterator depende del parámetro template
//           sin "typename" el compilador no sabe si T::iterator es un tipo o un miembro
{
    // std::find recorre [begin, end) comparando *it == value
    // Devuelve el iterador al primer elemento encontrado, o end() si no existe
    typename T::iterator it = std::find(container.begin(), container.end(), value);

    // Contrato de std::find: si devuelve end(), el elemento NO está
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
        // Lanzamos excepción en lugar de devolver end() porque:
        // 1. El subject lo pide
        // 2. Hace el fallo imposible de ignorar
        // 3. end() como señal de error solo funciona si el cliente conoce el contenedor

    return it;  // iterador válido apuntando al elemento encontrado
}

// ─── SOBRECARGA CONST ─────────────────────────────────────────────────────────
// Si el contenedor se pasa como const T&, el compilador NO puede usar la versión
// de arriba (que devuelve T::iterator, modificable). Sin esta sobrecarga:
//   const std::vector<int> v = ...;
//   easyfind(v, 42);   ← error: no viable overloaded function
//
// La solución es una segunda versión que acepta const T& y devuelve const_iterator.
// El compilador elige automáticamente la sobrecarga correcta según si el contenedor
// es const o no (overload resolution).
template <typename T>
typename T::const_iterator easyfind(const T& container, int value)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}
// Nota: const_iterator NO permite modificar el elemento apuntado (*it = 5 → error).
// Es correcto: si el contenedor es const, sus elementos también deben serlo.

// ─── PREGUNTAS DE DEFENSA ─────────────────────────────────────────────────────
// P: ¿Por qué lanzas excepción en vez de devolver end()?
// R: El subject lo pide. Además, la excepción es imposible de ignorar;
//    devolver end() requeriría que el cliente compruebe el resultado.
//
// P: ¿Funciona con std::map?
// R: No. Los iteradores de std::map<K,V> apuntan a std::pair<const K,V>.
//    std::find compararía *it == value (pair vs int) → error de tipos.
//    Además, buscar en un map por valor no tiene sentido semántico.
//
// P: ¿Por qué typename en el tipo de retorno?
// R: T::iterator es un nombre que depende del parámetro template T.
//    El compilador no sabe si es un tipo o un miembro estático.
//    "typename" le dice explícitamente que es un tipo.
//
// P: ¿Qué pasaría sin el "typename" en "typename T::iterator"?
// R: Error de compilación: "need 'typename' before dependent name"
//
// P: ¿Por qué hay dos sobrecargas? ¿No basta con una?
// R: C++ distingue T& (no-const) y const T& (const). Si pasas un contenedor const,
//    el compilador no puede usar la versión que devuelve iterator (modificable).
//    La const overload resuelve exactamente ese caso.
//
// P: ¿Cuándo se usa la versión const en la práctica?
// R: Cuando el contenedor viene de una función que lo recibe por const ref,
//    o cuando es una variable declarada como const:
//      const std::vector<int> v = ...; easyfind(v, 42); ← usa la versión const
// ─────────────────────────────────────────────────────────────────────────────

#endif
