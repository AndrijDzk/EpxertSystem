/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BackwardChaining.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:44:18 by adzikovs          #+#    #+#             */
/*   Updated: 2018/04/30 17:41:31 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BackwardChaining.class.hpp"
#include "Rule.class.hpp"
#include "Fact.class.hpp"
#include "State.class.hpp"
#include "GetTargets.class.hpp"

int			Engine::BackwardChaining::Ask(char Name)
{
	int								ret;
	size_t							fact_index;
	size_t							antecedent_index;

	ret = this->InitializeBuffers(Name);
	if (ret != OK)
		return (ret);
	while (this->buff.size())
	{
		fact_index = this->Enclosing->FindFactByName(buff.top());
		if (fact_index >= this->Enclosing->Facts.size())
			return (UNKNOWN_FACT);
		if (this->Enclosing->Facts[fact_index].GetState() == UNDEFINED ||
			this->Enclosing->Facts[fact_index].GetState() == CYCLED)
		{
			if (fact_index >= this->Enclosing->Facts.size())
				return (WTF);
			antecedent_index = this->States.Get(Antecedent, fact_index);
			if (antecedent_index >= this->Enclosing->Facts[fact_index].GetAntecedents().size())
				this->CheckAndRemoveFromStack(fact_index, NO);
			else
			{
				ret = this->ProceedCurrAntecedent(fact_index, antecedent_index);
				if (ret != OK)
					return (ret);
			}
		}
		else
			this->RemoveFromStack(fact_index, this->Enclosing->Facts[fact_index].GetState());
	}
	fact_index = this->Enclosing->FindFactByName(Name);
	if (fact_index >= this->Enclosing->Facts.size())
		return (UNKNOWN_FACT);
	else if (this->Enclosing->Facts[fact_index].GetState() == YES)
		return (TRUE_FACT);
	else if (this->Enclosing->Facts[fact_index].GetState() == NO)
		return (FALSE_FACT);
	else
		return (FALSE_FACT);
}

int			Engine::BackwardChaining::ProceedCurrAntecedent(size_t fact_index, size_t antecedent_index)
{
	std::vector<Fact>				&Facts_tmp = this->Enclosing->Facts;
	std::vector<size_t> const		&Antecedents_tmp = (Facts_tmp[fact_index]).GetAntecedents();
	size_t							curr_rule_index = Antecedents_tmp[antecedent_index];
	std::vector<std::string>		CurrRuleTargets;
	int								ret;

	if (curr_rule_index >= this->Enclosing->Rules.size())
		return (WTF);
	CurrRuleTargets = GetTargets::Get(this->Enclosing->Rules[curr_rule_index].getLeft());
	if (this->AllPossibleTargetsForRuleProcessed(CurrRuleTargets, fact_index))
	{
		if (this->Enclosing->Rules[curr_rule_index].getType() == IF_AND_ONLY_IF)
		{
			this->RuleDosentFire(curr_rule_index);
			while (antecedent_index < Antecedents_tmp.size())
			{
				this->States.GoToNext(Antecedent, fact_index);
				antecedent_index++;
			}
		}
		else
			this->States.GoToNext(Antecedent, fact_index);
	}
	else if (this->AllSubtargetsForTargetProcessed(CurrRuleTargets, fact_index))
	{
		this->RuleFires(curr_rule_index);
		this->buff.pop();
	}
	else
	{
		ret = HandleCurrSubtarget(CurrRuleTargets, fact_index);
		if (ret != OK)
			return (ret);
	}
	return (OK);
}

int			Engine::BackwardChaining::HandleCurrSubtarget(
										std::vector<std::string> const &Targets,
										size_t curr_fact_index)
{
	size_t		subtarget_index;
	t_SubTarget	Subtarget;
	char		Completed;
	char		State;

	Subtarget = this->GetCurrSubtarget(Targets, curr_fact_index);
	if (Subtarget.Name == 0)
		return (WTF);
	subtarget_index = this->Enclosing->FindFactByName(Subtarget.Name);
	if (subtarget_index >= this->Enclosing->Facts.size())
		return (UNKNOWN_FACT);
	State = this->Enclosing->Facts[subtarget_index].GetState();
	Completed = this->SubTargetCompleted(Subtarget, State);
	if (Completed == YES)
		this->States.GoToNext(SubTarget, curr_fact_index);
	else if (Completed == NO)
		this->States.GoToNext(Target, curr_fact_index);
	else
		this->HandleUndefinedFact(curr_fact_index, subtarget_index);
	return (OK);
}

void		Engine::BackwardChaining::HandleUndefinedFact(size_t curr_fact_index,
															size_t new_fact_index)
{
	if (new_fact_index >= this->Enclosing->Facts.size() ||
			curr_fact_index >= this->Enclosing->Facts.size())
		throw MyException("Engine::BackwardChaining::HandleUndefinedFact: curr_fact_index or new_fact_index exceeds Facts vector size!");
	if (this->Enclosing->Facts[new_fact_index].GetState() != UNDEFINED &&
		this->Enclosing->Facts[new_fact_index].GetState() != CYCLED)
		throw MyException("Engine::BackwardChaining::HandleUndefinedFact: attempt to handle defined fact as undefined!");
	if (this->Enclosing->Facts[new_fact_index].GetVisited() == true)
	{
		this->Enclosing->Facts[curr_fact_index].SetState(CYCLED);
		this->States.GoToNext(Target, curr_fact_index);
	}
	else if (this->Enclosing->Facts[new_fact_index].GetState() == CYCLED)
	{
		this->Enclosing->Facts[curr_fact_index].SetState(CYCLED);
		this->States.Reset(new_fact_index);
		this->Enclosing->Facts[new_fact_index].SetState(UNDEFINED);
		this->States.GoToNext(Target, curr_fact_index);
	}
	else
	{
		this->buff.push(this->Enclosing->Facts[new_fact_index].GetName());
		this->Enclosing->Facts[new_fact_index].SetVisited(true);
	}
}

int			Engine::BackwardChaining::InitializeBuffers(char Name)
{
	size_t		j;

	if ((j = this->Enclosing->FindFactByName(Name)) >= this->Enclosing->Facts.size())
		return (UNKNOWN_FACT);
	else
	{
		this->Enclosing->Facts[j].SetVisited(true);
		buff.push(Name);
	}
	return (OK);
}

void		Engine::BackwardChaining::CheckAndRemoveFromStack(size_t fact_index,
																char NewState)
{
	if (fact_index >= this->Enclosing->Facts.size() ||
		this->Enclosing->Facts[fact_index].GetName() != this->buff.top())
		throw MyException("Engine::BackwardChaining::CheckAndRemoveFromStack: fact_index exceeds Facts vector size or name of fact with index fact_index dosent match name of fact on top of stack!");
	if (this->Enclosing->Facts[fact_index].GetState() != CYCLED)
		this->RemoveFromStack(fact_index, NewState);
	else
	{
		this->RemoveFromStack(fact_index, CYCLED);
		this->Enclosing->Facts[fact_index].SetVisited(false);
	}
}

void		Engine::BackwardChaining::RemoveFromStack(size_t fact_index,
														char NewState)
{
	if (fact_index >= this->Enclosing->Facts.size() ||
		this->Enclosing->Facts[fact_index].GetName() != this->buff.top())
		throw MyException("Engine::BackwardChaining::RemoveFromStack: fact_index exceeds Facts vector size or name of fact with index fact_index dosent match name of fact on top of stack!");
	else
	{
		this->Enclosing->Facts[fact_index].SetState(NewState);
		this->buff.pop();
	}
}

t_SubTarget	Engine::BackwardChaining::GetCurrSubtarget(
										std::vector<std::string> const &Targets,
										size_t curr_fact_index)
{
	t_SubTarget	Subtarget;
	size_t		IndexOfTargetToBeProcessed;
	size_t		IndexOfSubtargetToBeProcessed;

	if (curr_fact_index >= this->Enclosing->Facts.size())
		throw MyException("Engine::BackwardChaining::GetCurrSubtarget: curr_fact_index >= this->Enclosing->Facts.size()");
	IndexOfTargetToBeProcessed = this->States.Get(Target, curr_fact_index);
	IndexOfSubtargetToBeProcessed = this->States.Get(SubTarget, curr_fact_index);
	if (IndexOfTargetToBeProcessed >= Targets.size())
		throw MyException("Engine::BackwardChaining::GetCurrSubtarget: IndexOfTargetToBeProcessed >= Targets.size()");
		
	std::string const	&TargetToBeProcessed = Targets[IndexOfTargetToBeProcessed];

	Subtarget = this->GetSubtarget(TargetToBeProcessed, IndexOfSubtargetToBeProcessed);
	return (Subtarget);
}

t_SubTarget	Engine::BackwardChaining::GetSubtarget(std::string const &Target,
														size_t subtarget)
{
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	while (i < Target.size())
	{
		if (j == subtarget)
		{
			while (i < Target.size() && Target[i] == ' ')
				i++;
			if (i >= Target.size())
				return (t_SubTarget{false, 0});
			if (Target[i] != '!')
				return (t_SubTarget{true, Target[i]});
			if ((i + 1) < Target.size() && std::isupper(Target[i + 1]))
				return (t_SubTarget{false, Target[i + 1]});
			else
				throw InvalidFactException(Target, i);
		}
		else if (Target[i] != ' ')
		{
			j++;
			while (i < Target.size() && Target[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (t_SubTarget{false, 0});
}

bool		Engine::BackwardChaining::AllPossibleTargetsForRuleProcessed(
										std::vector<std::string> const &Targets,
										size_t curr_fact_index)
{
	size_t		current_target_for_this_rule;
	size_t		total_amount_of_tagets_for_this_rule;

	if (curr_fact_index >= this->Enclosing->Facts.size())
		throw MyException("Engine::BackwardChaining::AllPossibleTargetsForRuleProcessed: curr_fact_index out of range of Facts vector!");
	current_target_for_this_rule = this->States.Get(Target, curr_fact_index);
	total_amount_of_tagets_for_this_rule = Targets.size();
	if (current_target_for_this_rule >= total_amount_of_tagets_for_this_rule)
		return (true);
	else
		return (false);
}

bool		Engine::BackwardChaining::AllSubtargetsForTargetProcessed(
										std::vector<std::string> const &Targets,
										size_t curr_fact_index)
{
	t_SubTarget		Subtarget;

	Subtarget = this->GetCurrSubtarget(Targets, curr_fact_index);
	if (Subtarget.Name == 0)
		return (true);
	else
		return (false);
}

char		Engine::BackwardChaining::SubTargetCompleted(
				t_SubTarget Subtarget,
				char State)
{
	if (State != YES && State != NO)
		return (UNDEFINED);
	else if ((Subtarget.State == true && State == YES) ||
			(Subtarget.State == false && State == NO))
			return (YES);
	else
			return (NO);
}

void		Engine::BackwardChaining::RuleFires(size_t RuleIndex)
{
	std::string		Right;
	size_t			i;
	size_t			FactTmp;

	if (RuleIndex >= this->Enclosing->Rules.size())
		throw MyException("Engine::BackwardChaining::RuleFires: RuleIndex exceeds Rules vector size!");
	Right = this->Enclosing->Rules[RuleIndex].getRight();
	i = 0;
	while (i < Right.size())
	{
		if (isupper(Right[i]))
		{
			FactTmp = this->Enclosing->FindFactByName(Right[i]);
			if (FactTmp < this->Enclosing->Facts.size())
			{
				if ((i + 1) < Right.size() && Right[i + 1] == Op::validTypes[4])
					this->Enclosing->Facts[FactTmp].SetState(NO);
				else
					this->Enclosing->Facts[FactTmp].SetState(YES);
			}
		}
		i++;
	}
}

void		Engine::BackwardChaining::RuleDosentFire(size_t RuleIndex)
{
	std::string		Right;
	size_t			i;
	size_t			FactTmp;

	if (RuleIndex >= this->Enclosing->Rules.size())
		throw MyException("Engine::BackwardChaining::RuleFires: RuleIndex exceeds Rules vector size!");
	Right = this->Enclosing->Rules[RuleIndex].getRight();
	i = 0;
	while (i < Right.size())
	{
		if (isupper(Right[i]))
		{
			FactTmp = this->Enclosing->FindFactByName(Right[i]);
			if (FactTmp < this->Enclosing->Facts.size())
			{
				if ((i + 1) < Right.size() && Right[i + 1] == Op::validTypes[4])
					this->Enclosing->Facts[FactTmp].SetState(YES);
				else
					this->Enclosing->Facts[FactTmp].SetState(NO);
			}
		}
		i++;
	}
}
