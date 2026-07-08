/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:05:30 by marta             #+#    #+#             */
/*   Updated: 2025/10/21 21:01:52 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// Creates a zombie on the HEAP (dynamic allocation)
// Must be deleted manually with 'delete'
// Use when: zombie needs to exist beyond function scope
Zombie* newZombie(std::string name)
{
	return new Zombie(name);
}
