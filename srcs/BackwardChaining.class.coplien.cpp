/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BackwardChaining.class.coplien.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 11:01:22 by adzikovs          #+#    #+#             */
/*   Updated: 2018/03/28 11:01:26 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BackwardChaining.class.hpp"
#include "State.class.hpp"

Engine::BackwardChaining::BackwardChaining(Engine* Enclosing) : Enclosing(Enclosing), States(*(new State)) {}

Engine::BackwardChaining::~BackwardChaining(void)
{
	delete(&(this->States));
}

Engine::BackwardChaining	&Engine::BackwardChaining::operator=(Engine::BackwardChaining const &rhs)
{
	this->buff = rhs.buff;
	this->States = rhs.States;
	return (*this);
}
