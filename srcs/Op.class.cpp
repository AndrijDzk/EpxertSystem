/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Op.class.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <imarakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:59:47 by adzikovs          #+#    #+#             */
/*   Updated: 2018/03/22 14:47:13 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Op.class.hpp"

std::string     Op::validTypes = "(^|+!)";

Op::Op(char type)
{
    size_t      i;

    if (Op::validTypes.size() == 0)
    {
        std::cerr << "ERROR: Op::validTypes uninitialized!" << std::endl;
        return ;
    }
    i = 0;
    while (i < Op::validTypes.size())
    {
        if (type == Op::validTypes[i])
        {
            this->type = type;
            this->priority = i;
            break ;
        }
        i++;
    }
    if (i >= Op::validTypes.size())
    {
        std::cerr << "WARNING: invalid type for Op class construction. Setting to default - " << Op::validTypes[1] << std::endl;
        this->type = Op::validTypes[1];
        this->priority = 1;
    }
}

Op::Op(size_t priority)
{
    if (Op::validTypes.size() == 0)
    {
        std::cerr << "ERROR: Op::validTypes uninitialized!" << std::endl;
        return ;
    }
    if (priority >= Op::validTypes.size())
    {
        std::cerr << "WARNING: invalid priority for Op class construction. Setting to minimum" << std::endl;
        this->type = Op::validTypes[1];
        this->priority = 1;
    }
    else
    {
        this->type = Op::validTypes[priority];
        this->priority = priority;
    }
}
