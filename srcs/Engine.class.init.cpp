/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.class.init.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:43:49 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 15:43:19 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.class.hpp"
#include "Rule.class.hpp"
#include "Fact.class.hpp"

int								Engine::AddRules(std::vector<std::string> const &src)
{
	size_t		i;
	int			ret;

	i = 0;
	while (i < src.size())
	{
		ret = this->AddRule(src[i]);
		if (ret != OK)
			return (ret);
		i++;
	}
	return (OK);
}

int								Engine::AddRule(std::string const &src)
{
	int									ret;

	this->Rules.push_back(Rule(src));
	if (this->Rules.size() == 0)
		return (WTF);
	if ((ret = this->AddFactsFromRule(this->Rules.size() - 1)) != OK)
		return (ret);
	if ((ret = this->AddRuleAsAntecedent(this->Rules.size() - 1)) != OK)
		return (ret);
	return (OK);
}

int								Engine::AddFactsFromRule(size_t src)
{
	std::string		Facts_tmp;
	size_t			i;

	if (src >= this->Rules.size())
		return (WTF);
	Facts_tmp = this->Rules[src].GetFacts();
	i = 0;
	while (i < Facts_tmp.size())
	{
		if (Facts_tmp[i] != ' ' &&
				this->FindFactByName(Facts_tmp[i]) >= this->Facts.size())
			this->Facts.push_back(Fact(Facts_tmp[i]));
		i++;
	}
	return (OK);
}

int								Engine::AddRuleAsAntecedent(size_t src)
{
	size_t			i;
	size_t			j;
	std::string		Right;
	bool			Added = false;

	if (src >= this->Rules.size())
		return (WTF);
	Right = this->Rules[src].getRight();
	i = 0;
	while (i < Right.size())
	{
		j = this->FindFactByName(this->Rules[src].getRight()[i]);
		if (j < this->Facts.size())
		{
			this->Facts[j].AddAntecedent(src);
			Added = true;
		}
		i++;
	}
	if (Added)
		return (OK);
	else
		return (RULE_CONSEQ_NOT_FOUND);
}
