#include <iostream>       // std::cout
#include "Serializer.hpp" // clase Serializer (serialize y deserialize) + Data.hpp incluido dentro

int main()
{
    // --- Crear y rellenar el objeto original ---

    Data data;            // creamos un objeto Data en la pila (stack)
                          // Data es un struct con dos campos: name (string) y value (int)

    data.name  = "Marvin"; // rellenamos el campo name
    data.value = 42;        // rellenamos el campo value

    // --- Mostrar el estado original ---

    std::cout << "Original pointer : " << &data << std::endl;
    // &data → dirección de memoria donde vive el objeto (ej: 0x7fff5fbff5a0)
    // esto es lo que vamos a serializar: la dirección, no el contenido

    std::cout << "name  : " << data.name  << std::endl; // imprimimos "Marvin"
    std::cout << "value : " << data.value << std::endl; // imprimimos 42

    // --- Serializar: puntero → número entero ---

    uintptr_t raw = Serializer::serialize(&data);
    // serialize recibe Data* (un puntero) y lo convierte a uintptr_t (entero sin signo)
    // uintptr_t es un tipo entero garantizado de ser lo suficientemente grande
    // para almacenar cualquier dirección de memoria sin perder información
    // internamente usa: reinterpret_cast<uintptr_t>(ptr)
    // es decir: "coge esos bytes que son una dirección y léelos como número"
    // raw ahora contiene el mismo valor que &data pero en forma de número

    std::cout << "\nSerialized (uintptr_t): " << raw << std::endl;
    // veremos que raw y &data son el mismo valor, solo que uno es puntero y otro entero

    // --- Deserializar: número entero → puntero ---

    Data* recovered = Serializer::deserialize(raw);
    // deserialize recibe el uintptr_t y lo convierte de vuelta a Data*
    // internamente usa: reinterpret_cast<Data*>(raw)
    // es decir: "coge esos bytes que son un número y léelos como dirección de Data"
    // recovered apunta exactamente a la misma dirección que data

    std::cout << "Deserialized pointer : " << recovered << std::endl;
    // debe coincidir con el "Original pointer" de arriba

    std::cout << "name  : " << recovered->name  << std::endl;
    // recovered->name es lo mismo que data.name porque apuntan al mismo objeto
    // -> es el operador de acceso a través de puntero (equivale a (*recovered).name)

    std::cout << "value : " << recovered->value << std::endl;
    // igual: recovered->value == data.value == 42

    // --- Verificar que los punteros son idénticos ---

    std::cout << "\nPointers match: " << (&data == recovered ? "yes" : "no") << std::endl;
    // comparamos las direcciones: &data (la original) y recovered (la deserializada)
    // deben ser iguales porque serialize/deserialize no mueven ni copian el objeto,
    // solo reinterpretan los mismos bytes de dos formas distintas
    // operador ternario: condición ? valor_si_true : valor_si_false

    return 0; // fin del programa, Data se destruye automáticamente al salir del scope
}
