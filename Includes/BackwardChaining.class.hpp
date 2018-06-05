/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BackwardChaining.class.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 10:52:17 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 17:14:49 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <exception>
#include "Engine.class.hpp"
#include "ReturnCodes.hpp"

typedef struct					s_SubTarget
{
	bool						State;
	char						Name;
}								t_SubTarget;

class							Engine::BackwardChaining
{
public:
	int							Ask(char Name);

private:
	int							InitializeBuffers(char Name);
	int							ProceedCurrAntecedent(size_t fact_index, size_t antecedent_index);
	void						HandleUndefinedFact(size_t curr_fact_index, size_t new_fact_index);
	int							HandleCurrSubtarget(std::vector<std::string> const &Targets, size_t curr_fact_index);
	t_SubTarget					GetCurrSubtarget(std::vector<std::string> const &Targets, size_t curr_fact_index);
	t_SubTarget					GetSubtarget(std::string const &Target, size_t subtarget);
	void						CheckAndRemoveFromStack(size_t fact_index, char NewState);
	void						RemoveFromStack(size_t fact_index, char NewState);
	bool						AllPossibleTargetsForRuleProcessed(std::vector<std::string> const &Targets, size_t curr_fact_index);
	bool						AllSubtargetsForTargetProcessed(std::vector<std::string> const &Targets, size_t curr_fact_index);
	char						SubTargetCompleted(t_SubTarget Subtarget, char State);
	void						RuleFires(size_t RuleIndex);
	void						RuleDosentFire(size_t RuleIndex);

private:
	Engine						*Enclosing;
	std::stack<char>			buff;
	class						State;
	State						&States;

public:
								BackwardChaining(Engine* Enclosing);
								~BackwardChaining(void);
	BackwardChaining			&operator=(BackwardChaining const &rhs);

private:
								BackwardChaining(void);
								BackwardChaining(BackwardChaining const &src);
};
