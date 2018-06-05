/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.base.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:47:38 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/17 12:24:32 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.class.hpp"
#include "Rule.class.hpp"
#include "Fact.class.hpp"

size_t							Engine::FindFactByName(char Name) const
{
	size_t		i;

	i = 0;
	while (i < this->Facts.size())
	{
		if (this->Facts[i].GetName() == Name)
			return (i);
		i++;
	}
	return (i);
}
