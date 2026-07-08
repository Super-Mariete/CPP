#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

// MutantStack hereda públicamente de std::stack<T>.
// std::stack NO es iterable por defecto: no expone begin()/end().
// Al heredar, obtenemos todos sus métodos (push, pop, top, size, empty...)
// y añadimos los iteradores accediendo al miembro protegido 'c',
// que es el contenedor subyacente (std::deque<T> por defecto).
template <typename T>
class MutantStack : public std::stack<T>
{
public:
	// Forma ortodoxa canónica
	MutantStack() {}
	MutantStack(const MutantStack& other) : std::stack<T>(other) {} // delega al copy ctor del padre
	MutantStack& operator=(const MutantStack& other)
	{
		std::stack<T>::operator=(other); // delega al operator= del padre
		return *this;
	}
	~MutantStack() {}

	// container_type es el typedef que std::stack expone para su contenedor interno.
	// Por defecto es std::deque<T>, pero así el código funciona aunque se cambie.
	// Sacamos los 4 tipos de iterador del contenedor interno:
	typedef typename std::stack<T>::container_type::iterator				iterator;
	typedef typename std::stack<T>::container_type::const_iterator			const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator		reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;

	// 'this->c' es el contenedor protegido de std::stack (el deque interno).
	// begin()/end() recorren de abajo (fondo del stack) hacia arriba (top).
	iterator				begin()  { return this->c.begin(); }
	iterator				end()    { return this->c.end(); }
	const_iterator			begin()  const { return this->c.begin(); }  // versión para objetos const
	const_iterator			end()    const { return this->c.end(); }

	// rbegin()/rend() recorren en sentido inverso: de top hacia el fondo.
	reverse_iterator		rbegin() { return this->c.rbegin(); }
	reverse_iterator		rend()   { return this->c.rend(); }
	const_reverse_iterator	rbegin() const { return this->c.rbegin(); }
	const_reverse_iterator	rend()   const { return this->c.rend(); }
};

#endif
