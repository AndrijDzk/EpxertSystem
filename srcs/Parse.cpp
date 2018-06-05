/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:20:51 by imarakho          #+#    #+#             */
/*   Updated: 2018/04/30 19:18:47 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

Parse::Parse()
{

}

Parse::~Parse()
{
	
}

void	Parse::parse_facts(std::string &str, std::vector<char> &facts)
{
	bool space = false;
	for (size_t i = 1; i < str.length();i++)
	{
		if(str[i] == '#')
			break;
		else if(str[i] == ' ')
			space = true;
		else if(str[i] >= 65 && str[i] <= 90 && !space)
		{
			std::cout << str[i] << std::endl;
			facts.push_back(str[i]);
		}
		else
		{
			std::cout << "Wrong facts!" << std::endl;
			exit(1);
		}
	}
}

void	Parse::operand_after_operand(std::string &tmp, size_t &i)
{
	if(tmp[i] >= 65 && tmp[i] <= 90)
	{
		for(size_t j = i + 1; j < tmp.length(); j++)
		{
			if(tmp[j] == Op::validTypes[1] || tmp[j] == Op::validTypes[2]  
			|| tmp[j] == Op::validTypes[3] || (tmp[j] >= 60 && tmp[j] <= 62) 
			|| tmp[j] == '#')
				break ;
			else if (tmp[j] >= 65 && tmp[j] <= 90)
			{
				std::cout << tmp[j] << std::endl;
				std::cout << "Operand after operand!" << std::endl;
				exit(1);
			}
		}
	}
}


void	Parse::check_ammount_operators(std::string tmp)
{
	std::vector<size_t> operands;
	std::vector<size_t> operators;
	for(size_t i = 0;i < tmp.size();i++)
	{
		if(tmp[i] == '#')
			break;
		if(tmp[i] >= 65 && tmp[i] <= 90)
			operands.push_back(i);
		else if(tmp[i] == Op::validTypes[1] || 
			tmp[i] == Op::validTypes[2]  
			|| tmp[i] == Op::validTypes[3])
			operators.push_back(i);
	}
	if(operands.size() != operators.size() + 1)
	{
			std::cout << "Wrong expression!" << std::endl;
			exit(1);
	}
}

void	Parse::operator_after_operator(std::string &tmp, size_t &i)
{
	if(tmp[i] == Op::validTypes[1] || 
	tmp[i] == Op::validTypes[2]  
	|| tmp[i] == Op::validTypes[3])
	{
		for(size_t j = i + 1; j < tmp.length(); j++)
		{
			 if ((tmp[j] >= 65 && tmp[j] <= 90)
			|| tmp[j] == '#')
				break ;
			else if(tmp[j] == Op::validTypes[1] || 
			tmp[j] == Op::validTypes[2]  
			|| tmp[j] == Op::validTypes[3])
			{
				std::cout << tmp[j] << std::endl;
				std::cout << "Operator after operator!" << std::endl;
				exit(1);
			}
			else if(tmp[j] == '=')
			{
				std::cout << tmp[j] << std::endl;
				std::cout << "Wrong operator!" << std::endl;
				exit(1);
			}
		}
	}
}

void		Parse::parse_after_equation(std::string str)
{
	for(size_t i = 0;i < str.length();i++)
	{
		if(str[i] == '#')
			break;
		if (!(str[i] >= 65 && str[i] <= 90) 
		&& str[i] != ' ' && str[i] != '>' &&
		str[i] != Op::validTypes[3] && str[i] != Op::validTypes[4])
		{
			std::cout << "Wrong right part!" << std::endl;
			exit(1);
		}
	}
}

void	Parse::parse_expression(std::string &tmp, std::string &ret, 
	std::vector<char> &true_facts, std::vector<char> &find_facts)
{
	if(tmp[0] == '=')
	{
		if(true_facts.size() != 0)
		{
			std::cout << "Wrong facts!" << std::endl;
			exit(1);
		}
		std::cout << "true facts:" << std::endl;
		parse_facts(tmp, true_facts);
	}
	else if(tmp[0] == '?')
	{
		if(find_facts.size() != 0)
		{
			std::cout << "Wrong facts!" << std::endl;
			exit(1);
		}
		std::cout << "facts to find:" << std::endl;
		parse_facts(tmp, find_facts);
	}
	else
	{ 
		for (size_t i = 0; i < tmp.length(); i++)
			{
				if (tmp[i] == '#')
					break;
				else if ((tmp[i] >= 65 && tmp[i] <= 90)
						 || (tmp[i] >= 60 && tmp[i] <= 62)
						 || tmp[i] == Op::validTypes[0] 
						 || tmp[i] == Op::validTypes[1]  
						|| tmp[i] == Op::validTypes[2]
						|| tmp[i] == Op::validTypes[3]
						|| tmp[i] == Op::validTypes[4]
						|| tmp[i] == Op::validTypes[5])
						ret += tmp[i];
				else if(tmp[i] != ' ')
				{
					std::cout << "Wrong symbol!" << std::endl;
					exit(1);
				}
				operand_after_operand(tmp, i);
				operator_after_operator(tmp, i);
			//	close_bracket(tmp);
			}
	}
}

void		Parse::vector_brackets_validation(std::string &tmp)
{
	std::vector<size_t> open_brackets;
	std::vector<size_t> close_brackets;
	for(size_t i = 0;i < tmp.length();i++)
	{
		if(tmp[i] == Op::validTypes[4] && 
		tmp[i + 1] != Op::validTypes[0] &&
		!(tmp[i + 1] >= 65 && tmp[i + 1] <= 90))
		{
			std::cout << "Wrong negation!" << std::endl;
			exit(1);
		}
		if(tmp[i] == Op::validTypes[0])
		{
			if(tmp[i + 1] == Op::validTypes[1]|| tmp[i + 1] == Op::validTypes[2] 
			|| tmp[i + 1] == Op::validTypes[3])
				{
					std::cout << "Wrong operator!" << std::endl;
					exit(1);
				}
			open_brackets.push_back(i);
		}
		else if(tmp[i] == Op::validTypes[5])
		{
			if(tmp[i - 1] == Op::validTypes[1] 
			|| tmp[i - 1] == Op::validTypes[2]
			|| tmp[i - 1] == Op::validTypes[3]
			|| tmp[i - 1] == Op::validTypes[4])
			{
				std::cout<< "Wrong operator!" << std::endl;
				exit(1);
			}
			close_brackets.push_back(i);
		}
	}
	if(close_brackets.size() != open_brackets.size())
	{
		std::cout << "Wrong number of brackets!" << std::endl;
		exit(1);
	}
	std::sort(close_brackets.begin(), close_brackets.end());
	std::sort(open_brackets.begin(), open_brackets.end());
	for(size_t i = 0;i < open_brackets.size();i++)
	{
		if(open_brackets[i] > close_brackets[i] 
		|| (close_brackets[i] - open_brackets[i] >= 1 
		&& close_brackets[i] - open_brackets[i] <= 3)
		|| tmp[open_brackets[i] + 2] == Op::validTypes[5])
		{
			//std::cout << close_brackets[i] - open_brackets[i] << std::endl;
			std::cout << "Wrong position of brackets!" << std::endl;
			exit(1);
		}

	}
}

void						Parse::vector_validation(std::string &str)
{
	if(str[0] == Op::validTypes[1] || str[0] == Op::validTypes[2] 
	|| str[0] == Op::validTypes[3])
	{
		std::cout << "Wrong operator!" << std::endl;
		exit(1);
	}
}

std::vector<std::string>	Parse::read(char *filename, std::vector<char> &true_facts, 
										std::vector<char> &find_facts)
{
	std::vector<std::string> res;
	std::ifstream in(filename);
	std::string tmp;

	std::string ret;
	if(in.is_open())
	{
		while(std::getline(in,tmp))
		{
			ret = "";
			parse_expression(tmp, ret, true_facts, find_facts);
			if(!ret.empty())
			{
				std::cout << ret << std::endl;
				vector_validation(ret);
				vector_brackets_validation(ret);
				check_ammount_operators(&ret[ret.find("=")]);
				parse_after_equation(&ret[ret.find("=") + 1]);
				//close_bracket(ret);
				res.push_back(ret);
			}

		}	
	}
	in.close();
	return res;
}