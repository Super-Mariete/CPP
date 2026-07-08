/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by marta             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"
# include <iostream>

class HumanA
{
private:
	std::string	name;
	Weapon&		weapon;  // Reference: ALWAYS has a weapon

public:
	HumanA(std::string name, Weapon& weapon);
	~HumanA(void);

	void	attack(void) const;
};

#endif
