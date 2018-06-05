/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rule.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:28:28 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 17:09:28 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULE_CLASS_HPP
#define RULE_CLASS_HPP

#include <string>
#include <stack>
#include <ctype.h>
#include <iostream>
#include "Op.class.hpp"
#include "ReturnCodes.hpp"

#define IMPLIES 0
#define IF_AND_ONLY_IF 1

class Rule
{
public:
						Rule(Rule const &src);
						Rule(std::string const &src);
						~Rule(void);
	Rule				&operator=(Rule const &rhs);
	std::string const	&getLeft(void) const;
	char				getType(void) const;
	std::string const	&getRight(void) const;
	std::string const	&GetSrc(void) const;
	std::string			GetFacts(void) const;

private:
	std::string			left;
	char				type;
	std::string			Right;
	std::string			src;
						Rule(void);
};

std::ostream			&operator<<(std::ostream &o, Rule const &rhs);

#endif
