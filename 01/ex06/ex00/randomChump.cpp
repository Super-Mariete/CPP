/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:23:11 by marta             #+#    #+#             */
/*   Updated: 2025/10/21 21:03:24 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// Creates a zombie on the STACK (automatic allocation)
// Automatically destroyed when function ends
// Use when: zombie only needed within function scope
void randomChump(std::string name)
{
	Zombie zombie(name);
	zombie.announce();
}
