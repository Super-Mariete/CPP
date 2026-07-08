// Ejemplo didáctico de polimorfismo.
// En ex02 A, B, C están vacías porque el ejercicio trata sobre dynamic_cast,
// no sobre polimorfismo en sí. Aquí vemos cómo serían en un caso real.

#include <iostream>
#include <cstdlib>
#include <ctime>

// ---- Clase base ----
// Define la INTERFAZ común que todos los enemigos comparten.
// virtual = cada subclase puede tener su propia implementación.

class Enemy
{
public:
    virtual void attack() = 0;  // = 0 → método puramente virtual, obliga a implementarlo
    virtual void describe() = 0;
    virtual ~Enemy() {}         // destructor virtual: necesario para delete correcto
};

// ---- Subclases con comportamiento distinto ----

class Warrior : public Enemy
{
public:
    void attack()   { std::cout << "Warrior golpea con espada: -20 hp" << std::endl; }
    void describe() { std::cout << "Soy un Warrior. Cuerpo a cuerpo." << std::endl; }
};

class Mage : public Enemy
{
public:
    void attack()   { std::cout << "Mage lanza bola de fuego: -35 hp" << std::endl; }
    void describe() { std::cout << "Soy un Mage. Magia a distancia." << std::endl; }
};

class Archer : public Enemy
{
public:
    void attack()   { std::cout << "Archer dispara flecha: -15 hp" << std::endl; }
    void describe() { std::cout << "Soy un Archer. Ataque rápido." << std::endl; }
};

// ---- La magia del polimorfismo ----
// Esta función no sabe qué tipo de enemigo recibe.
// Llama a attack() y C++ en tiempo de ejecución decide cuál ejecutar.

void makeAttack(Enemy* e)
{
    e->attack(); // ← mismo código, comportamiento distinto según el tipo real
}

int main()
{
    std::srand(std::time(NULL));

    // Creamos enemigos distintos pero los guardamos como Enemy*
    // Esto es exactamente lo que hace generate() en ex02 con Base*
    Enemy* enemies[3];
    enemies[0] = new Warrior();
    enemies[1] = new Mage();
    enemies[2] = new Archer();

    std::cout << "=== Cada enemigo se describe ===" << std::endl;
    for (int i = 0; i < 3; i++)
        enemies[i]->describe(); // cada uno ejecuta SU describe()

    std::cout << "\n=== Todos atacan (misma llamada, distinto resultado) ===" << std::endl;
    for (int i = 0; i < 3; i++)
        makeAttack(enemies[i]); // makeAttack no sabe qué tipo es, pero funciona

    // ---- dynamic_cast: cuando SÍ necesitas saber el tipo real ----
    std::cout << "\n=== Identificando tipos con dynamic_cast ===" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        if (dynamic_cast<Warrior*>(enemies[i]))
            std::cout << "enemies[" << i << "] es Warrior" << std::endl;
        else if (dynamic_cast<Mage*>(enemies[i]))
            std::cout << "enemies[" << i << "] es Mage" << std::endl;
        else if (dynamic_cast<Archer*>(enemies[i]))
            std::cout << "enemies[" << i << "] es Archer" << std::endl;
    }

    // Limpieza: delete llama al destructor correcto gracias a virtual ~Enemy()
    for (int i = 0; i < 3; i++)
        delete enemies[i];

    return 0;
}

// ---- Resumen ----
//
// SIN polimorfismo necesitarías:
//   attackWarrior(Warrior* w);
//   attackMage(Mage* m);
//   attackArcher(Archer* a);
//   ... una función por tipo, para siempre
//
// CON polimorfismo:
//   makeAttack(Enemy* e);  → una sola función, funciona con cualquier enemigo
//   Añadir DragonEnemy no rompe nada de lo existente.
