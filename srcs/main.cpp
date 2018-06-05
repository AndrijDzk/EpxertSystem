/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:19:36 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 18:40:23 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errors.hpp"
#include "GetTargets.class.hpp"
#include "Engine.class.hpp"
#include "Rule.class.hpp"
#include <vector>
#include <fstream>
#include "Parse.hpp"

int     main(int argc, char **argv)
{
	try
	{
	std::vector<std::string>	ret;
	size_t						i;

    if (argc == 2)
	{
		Parse						_parser;
		std::vector<char>			True;
		std::vector<char>			Find;
		std::vector<std::string>	Rules;
		std::string					buff;
		Engine						eng;

		Rules = _parser.read(argv[1], True, Find);
		if (Rules.empty() || Find.empty())
			throw MyException("Invalid file!");
		i = 0;
		while (i < Rules.size())
		{
			eng.AddRule(Rules[i]);
			i++;
		}
		eng.Tell(True);
		i = 0;
		while (i < Find.size())
		{
			eng.Ask(Find[i]);
			i++;
		}
    }
	}
	catch (std::exception &e) {std::cout << e.what() << std::endl;}

    return (0);
}
