/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:09:57 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/17 15:09:59 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.class.hpp"

size_t		Engine::BackwardChaining::State::Get(e_index_type what,
													size_t fact_index)
{
	size_t	i;

	i = 0;
	while (i < this->States.size())
	{
		if (fact_index == this->States[i].Fact)
		{
			if (what == Antecedent)
				return (this->States[i].Antecedent);
			else if (what == Target)
				return (this->States[i].Target);
			else if (what == SubTarget)
				return (this->States[i].Subtarget);
			else
				throw MyException("Unhandled e_index_type value in Engine::BackwardChaining::State::Get!");
		}
		i++;
	}
	this->States.push_back({fact_index, 0, 0, 0});
	return (0);
}

void		Engine::BackwardChaining::State::GoToNext(e_index_type what,
													size_t fact_index)
{
	size_t		i;

	i = 0;
	while (i < this->States.size())
	{
		if (this->States[i].Fact == fact_index)
		{
			if (what == Antecedent)
			{
				this->States[i].Antecedent++;
				this->States[i].Target = 0;
				this->States[i].Subtarget = 0;
			}
			else if (what == Target)
			{
				this->States[i].Target++;
				this->States[i].Subtarget = 0;
			}
			else if (what == SubTarget)
				this->States[i].Subtarget++;
			else
				throw MyException("Unhandled e_index_type value in Engine::BackwardChaining::State::GoToNext!");
			return;
		}
		i++;
	}
	throw MyException("GoToNextTarget: fact_index dosent match any of existing fact indexes!");
}

int			Engine::BackwardChaining::State::Reset(size_t fact_index)
{
	size_t		i;

	i = 0;
	while (i < this->States.size())
	{
		if (this->States[i].Fact == fact_index)
		{
			this->States[i].Antecedent = 0;
			this->States[i].Target = 0;
			this->States[i].Subtarget = 0;
			return (OK);
		}
		i++;
	}
	throw MyException("GoToNextTarget: fact_index dosent match any of existing fact indexes!");
}
