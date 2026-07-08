#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main()
{
	MutantStack<int> mstack; // stack de ints con iteradores

	// Operaciones normales de stack (heredadas de std::stack)
	mstack.push(5);
	mstack.push(17);
	std::cout << "Top: " << mstack.top() << std::endl; // top → 17 (LIFO: último en entrar)
	mstack.pop();                                        // elimina 17
	std::cout << "Size: " << mstack.size() << std::endl; // size → 1 (solo queda 5)

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	// Estado del stack (fondo → top): [5, 3, 5, 737, 0]

	std::cout << "Iteration (bottom to top):" << std::endl;
	MutantStack<int>::iterator it  = mstack.begin(); // apunta al fondo (5)
	MutantStack<int>::iterator ite = mstack.end();   // apunta pasado el top (sentinel)

	++it; // avanza al siguiente elemento...
	--it; // ...y vuelve: prueba que el iterador es bidireccional
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}

	// Verifica que MutantStack es compatible con std::stack:
	// el constructor de copia de std::stack acepta un MutantStack porque hereda de él.
	std::stack<int> s(mstack);

	// ---- Mismo test con std::list para verificar output idéntico ----
	// El subject pide que la salida sea la misma al sustituir MutantStack por una lista.
	// push_back en list equivale a push en stack (ambos añaden al "top" conceptual).
	// Nota: en el stack se hizo pop de 17, así que la secuencia es 5, 3, 5, 737, 0.
	std::cout << "\nSame with std::list:" << std::endl;
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator lit  = lst.begin();
	std::list<int>::iterator lite = lst.end();
	while (lit != lite)
	{
		std::cout << *lit << std::endl;
		++lit;
	}

	return 0;
}
