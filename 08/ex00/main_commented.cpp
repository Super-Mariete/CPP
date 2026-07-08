#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

// ─── PUNTO CLAVE DEFENSA ─────────────────────────────────────────────────────
// El evaluador comprueba que el main tiene "enough tests to prove the program
// works as expected". Si no hay tests suficientes, NO gradúa el ejercicio.
// ─────────────────────────────────────────────────────────────────────────────

int main()
{
    // ── TEST 1: std::vector, elemento encontrado ──────────────────────────────
    // Demostramos que funciona con el contenedor más común
    std::vector<int> vec;
    for (int i = 0; i < 10; i++)
        vec.push_back(i * 5);  // {0, 5, 10, 15, 20, 25, 30, 35, 40, 45}

    try {
        std::vector<int>::iterator it = easyfind(vec, 25);
        std::cout << "Found in vector: " << *it << std::endl;  // → 25
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // ── TEST 2: std::vector, elemento NO encontrado → excepción ──────────────
    // Demostramos que la excepción se lanza correctamente
    try {
        easyfind(vec, 99);  // 99 no está en el vector
    }
    catch (const std::exception& e) {
        std::cerr << "Vector: " << e.what() << std::endl;  // → "Value not found..."
    }

    // ── TEST 3: std::list, elemento encontrado ────────────────────────────────
    // Demostramos que la función es GENÉRICA: funciona con cualquier contenedor
    // El evaluador puede pedir que pruebes con otro contenedor
    std::list<int> lst;
    lst.push_back(3);
    lst.push_back(7);
    lst.push_back(42);

    try {
        std::list<int>::iterator it = easyfind(lst, 42);
        std::cout << "Found in list: " << *it << std::endl;  // → 42
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // ── TEST 4: std::list, elemento NO encontrado ─────────────────────────────
    try {
        easyfind(lst, 1);  // 1 no está en la lista
    }
    catch (const std::exception& e) {
        std::cerr << "List: " << e.what() << std::endl;  // → "Value not found..."
    }

    // ── CASOS LÍMITE (para demostrar en defensa si los piden) ─────────────────

    // Contenedor vacío → lanza excepción (std::find devuelve end() inmediatamente)
    std::vector<int> empty;
    try { easyfind(empty, 0); }
    catch (const std::exception& e) {
        std::cerr << "Empty: " << e.what() << std::endl;
    }

    // Primer elemento del contenedor
    std::vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    try {
        std::vector<int>::iterator it = easyfind(v, 1);
        std::cout << "First element: " << *it << std::endl;  // → 1
    }
    catch (...) {}

    // Negativos
    std::vector<int> neg;
    neg.push_back(-5); neg.push_back(-1); neg.push_back(0);
    try {
        std::vector<int>::iterator it = easyfind(neg, -1);
        std::cout << "Negative: " << *it << std::endl;  // → -1
    }
    catch (...) {}

    // ── TEST: contenedor const → usa la sobrecarga con const_iterator ─────────
    // Sin la sobrecarga const, este bloque no compilaría.
    // const T& → el compilador elige la versión que devuelve const_iterator.
    const std::vector<int> cvec(vec);  // copia const de vec
    try {
        std::vector<int>::const_iterator it = easyfind(cvec, 25);
        std::cout << "Const vector: " << *it << std::endl;  // → 25
        // *it = 99;  ← error de compilación: const_iterator no permite escritura
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
