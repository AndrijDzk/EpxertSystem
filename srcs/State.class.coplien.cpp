/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.class.coplien.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:12:14 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/17 15:12:16 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.class.hpp"

Engine::BackwardChaining::State::State(void) {}

Engine::BackwardChaining::State::State(Engine::BackwardChaining::State const &src) :
				States(src.States) {}

Engine::BackwardChaining::State::~State(void) {}

Engine::BackwardChaining::State		&Engine::BackwardChaining::State::operator=(Engine::BackwardChaining::State const &rhs)
{
	this->States = rhs.States;
	return (*this);
}
