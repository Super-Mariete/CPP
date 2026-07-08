#include <iostream>
#include "Serializer.hpp"

int main()
{
	Data data;
	data.name = "Marvin";
	data.value = 42;

	std::cout << "Original pointer : " << &data << std::endl;
	std::cout << "name  : " << data.name << std::endl;
	std::cout << "value : " << data.value << std::endl;

	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "\nSerialized (uintptr_t): " << raw << std::endl;

	Data* recovered = Serializer::deserialize(raw);
	std::cout << "Deserialized pointer : " << recovered << std::endl;
	std::cout << "name  : " << recovered->name << std::endl;
	std::cout << "value : " << recovered->value << std::endl;

	std::cout << "\nPointers match: " << (&data == recovered ? "yes" : "no") << std::endl;

	return 0;
}
