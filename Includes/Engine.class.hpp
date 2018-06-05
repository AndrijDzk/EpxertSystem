/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:22:38 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 15:20:52 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_CLASS_HPP
#define ENGINE_CLASS_HPP
#include <vector>
#include <string>
#include <iostream>
#include <map> 
#include <stack>

class Rule;
class Fact;

using namespace std;

class Engine
{
public:
	int								Ask(char Name);
	int								Tell(std::string const &Facts);
	int								Tell(std::vector<char> const &Facts);
	int								AddRules(std::vector<std::string> const &src);
	int								AddRule(std::string const &src);
	int								AddFactsFromRule(size_t src);
	int								AddRuleAsAntecedent(size_t src);
	size_t							FindFactByName(char Name) const;
	

private:
	std::vector<Rule>				Rules;
	std::vector<Fact>				Facts;
	class							BackwardChaining;
	BackwardChaining				*Solomon;

public:
									Engine(void);
									Engine(Engine const &src);
									~Engine(void);
	Engine							&operator=(Engine const &rhs);
	std::vector<Rule> const			&GetRules(void) const;
	std::vector<Fact> const			&GetFacts(void) const;
};

std::ostream						&operator<<(std::ostream &o, Engine const &rhs);

#endif
