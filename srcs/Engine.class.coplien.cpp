/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.coplien.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:46:40 by adzikovs          #+#    #+#             */
/*   Updated: 2018/03/23 12:46:42 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BackwardChaining.class.hpp"
#include "Rule.class.hpp"
#include "Fact.class.hpp"

Engine::Engine(void) : Solomon(new BackwardChaining(this)) {}

Engine::Engine(Engine const &src) : Rules(src.Rules), Facts(src.Facts), Solomon(new BackwardChaining(this)) {}

Engine::~Engine(void) {}

std::vector<Rule> const				&Engine::GetRules(void) const {return (this->Rules);}

std::vector<Fact> const				&Engine::GetFacts(void) const {return (this->Facts);}

Engine								&Engine::operator=(Engine const &rhs)
{
	this->Rules = rhs.Rules;
	this->Facts = rhs.Facts;
	return (*this);
}

std::ostream						&operator<<(std::ostream &o, Engine const &rhs)
{
	size_t						i;
	std::vector<Rule> const		&Rules_tmp = rhs.GetRules();
	std::vector<Fact> const		&Facts_tmp = rhs.GetFacts();

	i = 0;
	while (i < Rules_tmp.size())
	{
		o << i << ": " << Rules_tmp[i];
		i++;
	}
	i = 0;
	while (i < Facts_tmp.size())
	{
		o << Facts_tmp[i];
		i++;
	}
	return (o);
}
