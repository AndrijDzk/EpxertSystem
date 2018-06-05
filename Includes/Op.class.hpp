/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Op.class.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:49:25 by adzikovs          #+#    #+#             */
/*   Updated: 2018/02/05 14:49:52 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_CLASS_HPP
#define OP_CLASS_HPP
#include <string>
#include <iostream>

class   Op
{
public:
	static std::string		validTypes;
							Op(Op const &src) : type(src.type), priority(src.priority) {}
							Op(char type);
							Op(size_t priority);
							~Op(void) {}
	Op						&operator=(Op const &rhs) {this->type = rhs.type; this->priority = rhs.priority; return (*this);}
	char					getType(void) const {return (this->type);}
	char					getPriority(void) const {return (this->priority);}
	bool					operator<=(Op const &rhs) {return (this->priority <= rhs.getPriority());}
	bool					operator>=(Op const &rhs) {return (this->priority >= rhs.getPriority());}

private:
    char    				type;
	unsigned char			priority;
							Op(void) {}
};

#endif
