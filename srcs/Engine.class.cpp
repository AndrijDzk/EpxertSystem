/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:45:30 by imarakho          #+#    #+#             */
/*   Updated: 2018/04/30 15:20:52 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BackwardChaining.class.hpp"
#include "Fact.class.hpp"

int			Engine::Ask(char Name)
{
	int		ret;

	ret = this->Solomon->Ask(Name);
	if (ret == UNDEFINED_FACT)
		std::cout << "I dunno know" << std::endl;
	else if (ret == TRUE_FACT)
		std::cout << "Yes, indeed!" << std::endl;
	else if (ret == FALSE_FACT)
		std::cout << "No, imbecile!" << std::endl;
	else if (ret == UNKNOWN_FACT)
		std::cout << "WTF are you talking about?" << std::endl;
	else
		std::cout << "WTF is going on?" << std::endl;
	return (ret);
}

int			Engine::Tell(std::string const &Facts)
{
	size_t		i;
	size_t		fact_index;

	i = 0;
	while (i < Facts.size())
	{
		fact_index = this->FindFactByName(Facts[i]);
		if (fact_index < this->Facts.size())
			this->Facts[fact_index].SetState(YES);
		i++;
	}
	return (0);
}

int			Engine::Tell(std::vector<char> const &Facts)
{
	size_t		i;
	size_t		fact_index;

	i = 0;
	while (i < Facts.size())
	{
		fact_index = this->FindFactByName(Facts[i]);
		if (fact_index < this->Facts.size())
			this->Facts[fact_index].SetState(YES);
		i++;
	}
	return (0);
}