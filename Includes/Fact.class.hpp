/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fact.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:32:23 by adzikovs          #+#    #+#             */
/*   Updated: 2018/03/20 10:32:24 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACT_CLASS_HPP
#define FACT_CLASS_HPP
#include <vector>
#include <iostream>
#include "Errors.hpp"

#define UNDEFINED -1
#define NO 0
#define YES 1
#define CYCLED 2

class Rule;

class Fact
{
public:
	void								AddAntecedent(size_t Antecedent);

private:
	char								Name;
	char								State;
	bool								Visited;
	std::vector<size_t>					Antecedents;
										Fact(void);

public:
										Fact(char name);
										Fact(Fact const &src);
										~Fact(void);
	Fact								&operator=(Fact const &rhs);
	char								GetName(void) const;
	void								SetState(char State);
	char								GetState(void) const;
	void								SetVisited(bool Visited);
	bool								GetVisited(void) const;
	std::vector<size_t> const			&GetAntecedents(void) const;
};

std::ostream							&operator<<(std::ostream &o, Fact const &rhs);

#endif
