/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:43:10 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 17:11:36 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errors.hpp"
#include "Rule.class.hpp"
#include "ReversePolishNotation.class.hpp"

Rule::Rule(std::string const &src)
{
	size_t					sep_pos;
	ReversePolishNotation	Notation;

	sep_pos = src.find("<=>");
	if (sep_pos == std::string::npos)
		sep_pos = src.find("=>");
	if (sep_pos == std::string::npos)
		throw MyException("Rule::Rule(std::string const &src): Rule witout right part!");
	this->left = Notation.Create(src.substr(0, sep_pos));
	if (this->left.empty())
		throw MyException("Rule::Rule(std::string const &src): Error during left part parsing!");
	if (src[sep_pos] == '<')
	{
		this->type = IF_AND_ONLY_IF;
		this->Right = Notation.Create(src.substr(sep_pos + 3));
	}
	else
	{
		this->type = IMPLIES;
		this->Right = Notation.Create(src.substr(sep_pos + 2));
	}
	if (this->Right.empty())
		throw MyException("Rule::Rule(std::string const &src): Error during right part parsing!");
}

std::string						Rule::GetFacts(void) const
{
	std::string		res;
	size_t			i;

	i = 0;
	while (i < this->left.size())
	{
		if (isupper(this->left[i]))
		{
			if (res.size() != 0)
				res.push_back(' ');
			res.push_back(this->left[i]);
		}
		i++;
	}
	if (res.size())
		res.push_back(' ');
	i = 0;
	while (i < this->Right.size())
	{
		if (isupper(this->Right[i]))
		{
			if (res.size() != 0)
				res.push_back(' ');
			res.push_back(this->Right[i]);
		}
		i++;
	}
	return (res);
}
