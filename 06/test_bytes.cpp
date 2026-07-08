#include <iostream>
#include <fstream>
#include <cstring>

struct Mensaje {
	int  tipo;
	char texto[20];
};

int main()
{
	// --- ESCRIBIR ---
	Mensaje original;
	original.tipo = 7;
	std::memset(original.texto, 0, sizeof(original.texto));
	std::memcpy(original.texto, "HOLA", 4);

	std::ofstream fichero("mensaje.bin", std::ios::binary);
	char* bytes = reinterpret_cast<char*>(&original);
	fichero.write(bytes, sizeof(Mensaje));
	fichero.close();

	std::cout << "Escrito en disco:" << std::endl;
	std::cout << "  tipo  : " << original.tipo << std::endl;
	std::cout << "  texto : " << original.texto << std::endl;
	std::cout << "  bytes : " << sizeof(Mensaje) << " bytes en disco" << std::endl;

	// --- LEER ---
	char buffer[sizeof(Mensaje)];
	std::ifstream entrada("mensaje.bin", std::ios::binary);
	entrada.read(buffer, sizeof(Mensaje));
	entrada.close();

	Mensaje* recuperado = reinterpret_cast<Mensaje*>(buffer);

	std::cout << "\nLeido del disco:" << std::endl;
	std::cout << "  tipo  : " << recuperado->tipo << std::endl;
	std::cout << "  texto : " << recuperado->texto << std::endl;

	std::cout << "\nSon iguales: "
		<< (recuperado->tipo == original.tipo
			&& std::strcmp(recuperado->texto, original.texto) == 0
			? "si" : "no")
		<< std::endl;

	return 0;
}
