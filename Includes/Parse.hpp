/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:20:19 by imarakho          #+#    #+#             */
/*   Updated: 2018/04/30 18:33:44 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Op.class.hpp"

class	Parse
{
	public:
	Parse();
	Parse(Parse const &p);
	void	operator=(Parse const &p);
	~Parse();
	std::vector<std::string>	read(char *filename, std::vector<char> &true_facts, 
									std::vector<char> &find_facts);
	private:
	void					parse_expression(std::string &tmp, std::string &ret, 
	std::vector<char> &true_facts, std::vector<char> &find_facts);
	//std::vector<string>		parse_find(std::string &str);
	void		operand_after_operand(std::string &tmp, size_t &i);
	void		operator_after_operator(std::string &tmp, size_t &i);
	void		close_bracket(std::string &tmp);
	void		parse_facts(std::string &str, std::vector<char> &facts);
	void		vector_validation(std::string &str);
	void		check_ammount_operators(std::string str);
	void		vector_brackets_validation(std::string &str);
	void		parse_after_equation(std::string str);
};