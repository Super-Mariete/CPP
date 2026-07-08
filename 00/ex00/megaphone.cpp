/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-ped <made-ped@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:03:57 by made-ped          #+#    #+#             */
/*   Updated: 2026/07/08 21:04:13 by made-ped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	// Si no hay argumentos, imprime el mensaje especial
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}

	// Recorre todos los argumentos (empezando desde 1, no 0)
	i = 1;
	while (i < argc)
	{
		j = 0;
		// Recorre cada carácter del argumento
		while (argv[i][j])
		{
			// Convierte a mayúscula (similar a toupper en C)
			std::cout << (char)std::toupper(argv[i][j]);
			j++;
		}
		i++;
	}
	std::cout << std::endl;
	
	return (0);
}
