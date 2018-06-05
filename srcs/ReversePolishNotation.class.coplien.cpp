/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReversePolishNotation.class.coplien.cpp            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 15:53:54 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 15:54:22 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReversePolishNotation.class.hpp"

						ReversePolishNotation::ReversePolishNotation(void) {}

						ReversePolishNotation::ReversePolishNotation(
							ReversePolishNotation const &src
							) :
								Out(src.Out),
								OpStack(src.OpStack) {}

						ReversePolishNotation::~ReversePolishNotation(void) {}

ReversePolishNotation	&ReversePolishNotation::operator=(ReversePolishNotation const &rhs)
{
	this->Out = rhs.Out;
	this->OpStack = rhs.OpStack;
	return (*this);
}
