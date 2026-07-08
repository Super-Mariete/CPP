#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>  // para std::out_of_range
# include <cstddef>    // para std::size_t

// Clase template: T es el tipo del array (int, string, etc.)
// El tipo se decide cuando se instancia: Array<int>, Array<std::string>
template <typename T>
class Array
{
public:
	// Constructor por defecto: array vacío de tamaño 0
	// El () al final de new T[0]() inicializa los elementos a valor por defecto
	Array() : _data(new T[0]()), _size(0) {}

	// Constructor con tamaño: reserva memoria en el heap para n elementos
	// new T[n]() los inicializa a 0 / valor por defecto según el tipo
	Array(unsigned int n) : _data(new T[n]()), _size(n) {}

	// Constructor copia: DEEP COPY (copia profunda)
	// Reserva su PROPIA memoria nueva — no comparte puntero con other
	// Si fuera shallow (solo copiar _data = other._data), al destruirse other
	// liberaría la memoria y este objeto quedaría con un puntero inválido
	Array(const Array& other) : _data(new T[other._size]()), _size(other._size)
	{
		for (std::size_t i = 0; i < _size; i++)
			_data[i] = other._data[i];
	}

	// Operador de asignación: también DEEP COPY
	// Primero libera la memoria propia, luego reserva nueva y copia
	// if (this != &other) evita el caso a = a (auto-asignado)
	Array& operator=(const Array& other)
	{
		if (this != &other)
		{
			delete[] _data;          // libera memoria antigua
			_size = other._size;
			_data = new T[_size]();  // reserva memoria nueva
			for (std::size_t i = 0; i < _size; i++)
				_data[i] = other._data[i]; // copia elemento a elemento
		}
		return *this;
	}

	// Destructor: libera la memoria del heap reservada con new[]
	// Sin esto habría memory leak
	~Array() { delete[] _data; }

	// operator[] sin const: para arrays NO-const, permite leer Y modificar
	// Devuelve T& (referencia) → puedes hacer arr[i] = 42
	// Lanza excepción si el índice está fuera de rango (seguro vs array de C)
	T& operator[](std::size_t index)
	{
		if (index >= _size)
			throw std::out_of_range("Index out of bounds");
		return _data[index];
	}

	// operator[] con const: para arrays CONST, solo permite leer
	// Devuelve const T& → no puedes modificar el elemento
	// Necesario porque sobre un objeto const solo se pueden llamar métodos const
	// Sin esta versión, no podrías usar [] sobre un const Array<T>
	const T& operator[](std::size_t index) const
	{
		if (index >= _size)
			throw std::out_of_range("Index out of bounds");
		return _data[index];
	}

	// Devuelve el número de elementos
	// Es const porque no modifica el objeto
	unsigned int size() const { return static_cast<unsigned int>(_size); }

private:
	T*          _data;  // puntero al array en el heap
	std::size_t _size;  // número de elementos
};

#endif
