/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReversePolishNotation.class.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 15:46:16 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 16:08:50 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <stack>
#include <ctype.h>
#include <iostream>
#include "Op.class.hpp"
#include "ReturnCodes.hpp"

class						ReversePolishNotation
{
public:
	std::string				Create(std::string const &src);

private:
	std::string				Out;
	std::stack<Op>			OpStack;
	int						check(std::string const &str, size_t i);
	int						closingBracket(void);
	int						PushStack(size_t i);
	int						PushFromStackToOut(void);
	int						PushRestToOut(void);

public:
							ReversePolishNotation(void);
							ReversePolishNotation(ReversePolishNotation const &src);
							~ReversePolishNotation(void);
	ReversePolishNotation	&operator=(ReversePolishNotation const &rhs);
};
