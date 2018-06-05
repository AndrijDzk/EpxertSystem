/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.class.coplien.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:51:55 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 16:51:55 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rule.class.hpp"

					Rule::Rule(Rule const &src) :
							left(src.left),
							type(src.type),
							Right(src.Right),
							src(src.src) {}

					Rule::~Rule(void) {}

Rule				&Rule::operator=(Rule const &rhs)
{
	this->left = rhs.getLeft();
	this->type = rhs.getType();
	this->Right = rhs.getRight();
	this->src = rhs.src;
	return (*this);
}

std::string const	&Rule::getLeft(void) const
{
	return (this->left);
}

char				Rule::getType(void) const
{
	return (this->type);
}

std::string const	&Rule::getRight(void) const
{
	return (this->Right);
}

std::string const	&Rule::GetSrc(void) const
{
	return (this->src);
}

std::ostream		&operator<<(std::ostream &o, Rule const &rhs)
{
	std::cout << rhs.GetSrc() << std::endl;
	std::cout << rhs.getLeft() << ' ' << static_cast<int>(rhs.getType());
	std::cout << ' ' << rhs.getRight() << std::endl;
	return (o);
}
