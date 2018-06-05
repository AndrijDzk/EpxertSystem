/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:09:37 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/17 15:09:42 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include "BackwardChaining.class.hpp"
#include "Errors.hpp"

enum e_index_type {Antecedent = 0, Target = 1, SubTarget = 2};

typedef struct					s_state
{
	size_t						Fact;
	size_t						Antecedent;
	size_t						Target;
	size_t						Subtarget;
}								t_state;


class							Engine::BackwardChaining::State
{
public:
	size_t 						Get(e_index_type what, size_t fact_index);
	void						GoToNext(e_index_type what, size_t fact_index);
	int							Reset(size_t fact_index);

private:
	std::vector<t_state>		States;

public:
								State(void);
								State(State const &src);
								~State(void);
	State						&operator=(State const &rhs);
};
