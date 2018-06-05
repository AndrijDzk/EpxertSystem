/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fact.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:40:56 by adzikovs          #+#    #+#             */
/*   Updated: 2018/03/20 10:40:58 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fact.class.hpp"
#include "Rule.class.hpp"

void							Fact::AddAntecedent(size_t Antecedent)
{
	this->Antecedents.push_back(Antecedent);
}

Fact							&Fact::operator=(Fact const &rhs)
{
	this->Name = rhs.Name;
	this->SetState(rhs.State);
	this->SetVisited(rhs.Visited);
	this->Antecedents = rhs.Antecedents;
	return (*this);
}

char							Fact::GetName(void) const
{
	return (this->Name);
}

void							Fact::SetState(char State)
{
	if (State == UNDEFINED || State == NO || State == YES || State == CYCLED)
		this->State = State;
	else
		throw InvalidStateException(State);
}

char							Fact::GetState(void) const
{
	return (this->State);
}

void							Fact::SetVisited(bool Visited)
{
	this->Visited = Visited;
}

bool							Fact::GetVisited(void) const
{
	return (this->Visited);
}

std::vector<size_t> const		&Fact::GetAntecedents(void) const
{
	return (this->Antecedents);
}

std::ostream					&operator<<(std::ostream &o, Fact const &rhs)
{
	std::vector<size_t> const		&tmp = rhs.GetAntecedents();
	size_t							i;

	std::cout << "Fact: " << rhs.GetName() << std::endl;
	if (tmp.size() == 0)
		std::cout << "No antecedents!" << std::endl;
	else
	{
		i = 0;
		while (i < tmp.size())
		{
			std::cout << tmp[i] << std::endl;
			i++;
		}
	}
	return (o);
}

Fact::Fact(char name) : Name(name), State(UNDEFINED), Visited(false) {}

Fact::Fact(Fact const &src) : Name(src.Name), State(src.State),	Visited(false), Antecedents(src.Antecedents) {}

Fact::~Fact(void) {}
