/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:30:55 by adzikovs          #+#    #+#             */
/*   Updated: 2018/03/13 11:30:56 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_HPP
#define ERRORS_HPP
#include <string>
#include <exception>

class InvalidStateException: public std::exception
{
public:
										InvalidStateException(void) : msg("Trying to set invalid state!") {}
										InvalidStateException(InvalidStateException const &src) : msg(src.msg) {}
										InvalidStateException(char State) : msg("Trying to set invalid state: ") {this->msg.append(std::to_string(static_cast<int>(State)));}
										~InvalidStateException(void) override {}
	InvalidStateException				&operator=(InvalidStateException const &rhs) {this->msg = rhs.msg; return (*this);}
	virtual const char*					what() const throw() override {return (this->msg.c_str());}

private:
	std::string							msg;
};

class InvalidFactException: public std::exception
{
public:
										InvalidFactException(void) : msg("Invalid fact int targets line!") {}
										InvalidFactException(InvalidFactException const &src) : msg(src.msg) {}
										InvalidFactException(std::string const &Target, size_t pos) : msg("Invalid fact int targets line: Target - ") {this->msg.append(Target); this->msg.append(" pos - "); this->msg.append(std::to_string(pos));}
										~InvalidFactException(void) override {}
	InvalidFactException				&operator=(InvalidFactException const &rhs) {this->msg = rhs.msg; return (*this);}
	virtual const char*					what() const throw() override {return (this->msg.c_str());}

private:
	std::string							msg;
};

class MyException: public std::exception
{
public:
										MyException(void) : msg("WTF is going on?!") {}
										MyException(MyException const &src) : msg(src.msg) {}
										MyException(std::string const &msg) : msg(msg) {}
										~MyException(void) override {}
	MyException							&operator=(MyException const &rhs) {this->msg = rhs.msg; return (*this);}
	virtual const char*					what() const throw() override {return (this->msg.c_str());}

private:
	std::string							msg;
};

#endif
