/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReversePolishNotation.class.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 15:46:28 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 16:08:50 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReversePolishNotation.class.hpp"

std::string		ReversePolishNotation::Create(std::string const &src)
{
	size_t				i;
	int					ret;

	this->Out.clear();
	while (this->OpStack.empty() == false)
		this->OpStack.pop();
	i = 0;
	while (i < src.size())
	{
		ret = this->check(src, i);
		if (ret == OUT_OF_STR || ret == LEFT_END)
			break ;
		else if (ret > 0)
		{
			ret--;
			if (static_cast<size_t>(ret) < (Op::validTypes.size() - 1))
				this->PushStack(ret);
			else
				this->closingBracket();
		}
		else if (src[i] != ' ')
			this->Out.push_back(src[i]);
		i++;
	}
	if (ret == OUT_OF_STR)
		return (std::string());
	else
	{
		ret = this->PushRestToOut();
		if (ret != OK)
			return (std::string());
	}
	return (this->Out);
}

int								ReversePolishNotation::check(std::string const &str, size_t i)
{
	size_t		j;

	if (i >= str.size())
		return (OUT_OF_STR);
	else if (str[i] == ' ' || str[i] == '\t')
		return (0);
	else if ((str.size() - i) >= 3 && str.compare(i, 3, "<=>") == 0)
		return (LEFT_END);
	else if ((str.size() - i) >= 2 && str.compare(i, 2, "=>") == 0)
		return (LEFT_END);
	j = 0;
	while (j < Op::validTypes.size())
	{
		if (str[i] == Op::validTypes[j])
			return (j + 1);
		j++;
	}
	return (-3);
}

int								ReversePolishNotation::closingBracket()
{
	while (this->OpStack.size() > 0 && this->OpStack.top().getType() != '(')
	{
		this->Out.push_back(this->OpStack.top().getType());
		this->OpStack.pop();
	}
	if (this->OpStack.size() == 0)
		return (UNMATCHED_BRACKET);
	else
	{
		this->OpStack.pop();
		return (OK);
	}
}

int								ReversePolishNotation::PushStack(size_t i)
{
	Op		tmp(i);

	if (i >= Op::validTypes.size())
		return (WTF);
	while (this->OpStack.size() && this->OpStack.top() >= tmp && tmp.getType() != '(')
	{
		this->Out.push_back(this->OpStack.top().getType());
		this->OpStack.pop();
	}
	this->OpStack.push(tmp);
	return (OK);
}

int								ReversePolishNotation::PushFromStackToOut(void)
{
	if (this->OpStack.size() == 0)
		return (WTF);
	this->Out.push_back(this->OpStack.top().getType());
	this->OpStack.pop();
	return (OK);
}

int						ReversePolishNotation::PushRestToOut()
{
	while (this->OpStack.size())
	{
		if (this->OpStack.top().getType() == '(')
		{
			return (WTF);
		}
		else
		{
			PushFromStackToOut();
		}
	}
	return (OK);
}
