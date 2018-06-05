/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetTargets.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:16:03 by imarakho          #+#    #+#             */
/*   Updated: 2018/04/24 15:34:16 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetTargets.class.hpp"
#include "Errors.hpp"

//std::string*		g_ptr = 0;

std::vector<std::string>		GetTargets::Get(std::string const &left)
{
	std::string				Facts = GetTargets::GetFacts(left);
	std::vector<char>		Fact_values(Facts.size(), 1);
	VVC						Miniterms;
	VVC						PrimeImplicants;
	VVC						PrimeMiniterms;
	size_t 					MinitermsAmount;

	do
	{
		if (GetTargets::SetSatisfiesRule(left, Facts, Fact_values))
			Miniterms.push_back(Fact_values);
		GetTargets::Increment(Fact_values);
	} while (std::find(Fact_values.begin(), Fact_values.end(), 0) != Fact_values.end());
	MinitermsAmount = Miniterms.size();
	PrimeImplicants = Miniterms;
//	g_ptr = &Facts;
	PrimeMiniterms = GetTargets::SimplifyTable(PrimeImplicants);
	GetTargets::PetricksMethod(PrimeImplicants, PrimeMiniterms, MinitermsAmount);
	return GetTargets::CreateTargetsVector(PrimeImplicants, Facts);
}

std::vector<size_t>					GetTargets::GetEssentials(VVC &mini_t)
{
	std::vector<size_t> res;
	size_t m;
	for(size_t i = 0;i < mini_t.size();i++)
	{
		for(size_t j = 0;j < mini_t[i].size();j++)
		{
			for (m = i + 1; m < mini_t.size(); m++)
			{
				if (std::find(mini_t[m].begin(),mini_t[m].end(), mini_t[i][j]) != mini_t[m].end())
					break;
			}
			if(m == mini_t.size())
				res.push_back(i);
		}
	}
	return res;
}

std::vector<size_t>				GetTargets::MiniTermsCoveredByPrimeCombination(VVC const &mini_t, std::vector<size_t> const &prime_index)
{
	std::vector<size_t> res;
	for(size_t i = 0;i < prime_index.size();i++)
	{
		for(size_t j = 0;j < mini_t[prime_index[i]].size();j++)
		{
			if(std::find(res.begin(), res.end(), mini_t[prime_index[i]][j]) == res.end())
				res.push_back(mini_t[prime_index[i]][j]);
		}
	}
	return res;
}

bool							GetTargets::SetCoverAllMiniterms(std::vector<size_t > covBySet,std::vector<size_t > covByEssen,size_t mini_t_ammount)
{
	for(size_t i = 0;i < mini_t_ammount;i++)
	{
		if(std::find(covBySet.begin(),covBySet.end(), i) == covBySet.end()
		   && std::find(covByEssen.begin(),covByEssen.end(), i) == covByEssen.end())
			return false;
	}
	return true;
}

std::vector<size_t>				GetTargets::CreatePrimeSet(size_t Start, size_t Len,
															std::vector<size_t> const &Essen,
															size_t PrimesAmount)
{
	std::vector<size_t>		res;
	size_t					i;

	i = 0;
	while (i < Len)
	{
		while (std::find(Essen.begin(), Essen.end(), Start) != Essen.end())
			Start++;
		if (Start >= PrimesAmount)
			return (std::vector<size_t>());
		res.push_back(Start);
		Start++;
		i++;
	}
	return (res);
}

bool							GetTargets::ChangeSet(VVC const &mini_t,
													  std::vector<size_t> &PrimeSet,
													  std::vector<size_t> const &Essen,
													  size_t PrimesAmount, size_t MinitermAmount)
{
	std::vector<size_t>		CovBySet;
	std::vector<size_t>		CovByEssen = GetTargets::MiniTermsCoveredByPrimeCombination(mini_t, Essen);
	std::vector<size_t>		PrimeSetCopy = PrimeSet;
	std::vector<size_t>		Tmp;

	while (1)
	{
		Tmp = GetTargets::CreatePrimeSet(PrimeSetCopy[0] + 1, PrimeSetCopy.size(), Essen, PrimesAmount);
		if (Tmp.size() == 0)
			Tmp = GetTargets::CreatePrimeSet(0, PrimeSetCopy.size() + 1, Essen, PrimesAmount);
		if (Tmp.size() == 0)
			return (false);
		CovBySet = GetTargets::MiniTermsCoveredByPrimeCombination(mini_t, Tmp);
		if (GetTargets::SetCoverAllMiniterms(CovBySet, CovByEssen, MinitermAmount))
		{
			PrimeSet = Tmp;
			return (true);
		}
		PrimeSetCopy = Tmp;
	}
}

void							GetTargets::PetricksMethod(VVC &Prime, VVC &mini_t, size_t MinitermAmount)
{
	std::vector<size_t>		Esens = GetTargets::GetEssentials(mini_t);
	std::vector<size_t>		PrimeSet = GetTargets::CreatePrimeSet(0, 1, Esens, Prime.size());
	size_t					i;

	if (PrimeSet.empty() == false &&
			GetTargets::ChangeSet(mini_t, PrimeSet, Esens, Prime.size(), MinitermAmount) == true)
	{
		i = Prime.size();
		while (i > 0)
		{
			i--;
			if (std::find(PrimeSet.begin(), PrimeSet.end(), i) == PrimeSet.end() &&
					std::find(Esens.begin(), Esens.end(), i) == Esens.end())
				Prime.erase(Prime.begin() + i);
		}
	}
}

bool							GetTargets::SetSatisfiesRule(
										std::string const &left,
										std::string const &Facts,
										std::vector<char> const &Fact_values)
{
	std::stack<bool>	buff;
	size_t				i;
	size_t				ret;

	i = 0;
	while (i < left.size())
	{
		if(left[i] >= 65 && left[i] <= 90)
		{
			if ((ret = Facts.find(left[i])) == std::string::npos)
				throw std::exception();
			buff.push(Fact_values[ret]);
		}
		else if (Op::validTypes.find(left[i]) != std::string::npos)
			ApplyOp(buff, left[i]);
		i++;
	}
	if (buff.size() != 1)
		throw std::exception();
	return (buff.top());
}

std::string					GetTargets::GetFacts(std::string const &left)
{
	std::string		res;
	size_t			i;
	size_t			j;

	i = 0;
	while (i < left.size())
	{
		if(left[i] >= 65 && left[i] <= 90)
		{
			j = 0;
			while (j < res.size())
			{
				if (res[j] == left[i])
					break;
				j++;
			}
			if (j == res.size())
				res += left[i];
		}
		i++;
	}
	return (res);
}

void							GetTargets::ApplyOp(std::stack<bool> &buff, char Operator)
{
	bool	tm1;
	bool	tm2;

	if ((Operator == Op::validTypes[4] && buff.size() == 0) ||
		(Operator != Op::validTypes[4] && buff.size() < 2))
		throw std::exception();
	tm1 = buff.top();
	buff.pop();
	if (Operator != Op::validTypes[4])
	{
		tm2 = buff.top();
		buff.pop();
	}
	if (Operator == Op::validTypes[1])
		buff.push(tm1 ^ tm2);
	else if (Operator == Op::validTypes[2])
		buff.push(tm1 | tm2);
	else if (Operator == Op::validTypes[3])
		buff.push(tm1 & tm2);
	else if (Operator == Op::validTypes[4])
		buff.push(!tm1);
	else
		throw std::exception();
}


int	        					GetTargets::Increment(std::vector<char> &tbl)
{
    size_t      i;

    i = tbl.size();
    while (i > 0)
	{
		i--;
		if (tbl[i] == 0)
		{
			tbl[i] = 1;
			return (0);
		}
        tbl[i] = 0;
	}
    return (0);
}

VVC							GetTargets::SimplifyTable(VVC &Table)
{
	size_t					i;
	int						ret;
	std::vector<bool>		IsPrime(Table.size(), true);
	VVC						Miniterms = GetTargets::CreateMinitermTable(Table.size());
	VVC						PrimeTable;
	VVC						PrimeMiniterms;

	while (Table.size())
	{
		i = 1;
		while (i < Table.size())
		{
			ret = GetTargets::ImplicantsCanBeCombined(Table[0], Table[i]);
			if (ret >= 0)
			{
				IsPrime[0] = false;
				IsPrime[i] = false;
				Table.push_back(Table[0]);
				Table.back()[ret] = -1;
				IsPrime.push_back(true);
				Miniterms.push_back(CreateMinitermVector(Miniterms[0], Miniterms[i]));
			}
			else if (ret == DUPLICATE)
			{
				IsPrime[0] = false;
				Miniterms[i] = CreateMinitermVector(Miniterms[0], Miniterms[i]);
				break;
			}
//			else if (ret == DUPLICATE)
//				throw MyException("Duplicate in Table!");
			i++;
		}
		if (IsPrime[0] == true)
		{
			PrimeTable.push_back(Table[0]);
			PrimeMiniterms.push_back(Miniterms[0]);
		}
		Table.erase(Table.begin());
		IsPrime.erase(IsPrime.begin());
		Miniterms.erase(Miniterms.begin());
//		std::cout << "Prime Table:" << std::endl;
//		GetTargets::PrintTargetsVector(PrimeTable);
//		std::cout << "Buff Table:" << std::endl;
//		GetTargets::PrintTargetsVector(Table);
	}
	Table = PrimeTable;
	return (PrimeMiniterms);
}

int								GetTargets::ImplicantsCanBeCombined(
									std::vector<char> const &Imp1,
									std::vector<char> const &Imp2)
{
	size_t		i;
	int			ret = -1;
	bool		diff = false;

	if (Imp1.size() != Imp2.size())
		throw std::exception();
	i = 0;
	while (i < Imp1.size())
	{
		if (Imp1[i] != Imp2[i])
		{
			if (diff || Imp1[i] == -1 || Imp2[i] == -1)
				return (CANT_BE_COMBINED);
			else
			{
				diff = true;
				ret = i;
			}
		}
		i++;
	}
	if (diff)
		return (ret);
	else
		return (DUPLICATE);
}

std::vector<std::string>		GetTargets::CreateTargetsVector(VVC const &Table, std::string const &Facts)
{
	std::vector<std::string> res;
	std::string ret;

	for(size_t i = 0;i < Table.size();i++)
	{
		ret = "";
		for(size_t j = 0;j < Table[i].size();j++)
		{
			if(Table[i][j] == 1)
				ret += Facts[j];
			else if(Table[i][j] == 0)
			{
				ret += "!";
				ret += Facts[j];
			}
			if(Table[i][j] != -1)
				ret += " ";
		}
		res.push_back(ret);
	}
	return res;
}

VVC								GetTargets::CreateMinitermTable(
														size_t size)
{
	VVC			res(size, std::vector<char>(1, 0));
	size_t		i;

	i = 0;
	while (i < size)
	{
		res[i][0] = i;
		i++;
	}
	return (res);
}

std::vector<char>				GetTargets::CreateMinitermVector(
									std::vector<char> const &Imp1Mtrs,
									std::vector<char> const &Imp2Mtrs)
{
	std::vector<char>		res;

	GetTargets::AddMinitermsToVector(res, Imp1Mtrs);
	GetTargets::AddMinitermsToVector(res, Imp2Mtrs);
	return (res);
}

void							GetTargets::AddMinitermsToVector(
								std::vector<char> &res,
								std::vector<char> const &NewMiniterms)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < NewMiniterms.size())
	{
		j = 0;
		while (j < res.size())
		{
			if (res[j] == NewMiniterms[i])
				break;
			j++;
		}
		if (j == res.size())
			res.push_back(NewMiniterms[i]);
		i++;
	}
}

/*void 						GetTargets::PrintTargetsVector(VVC const &PrimeImplicants)
{
	size_t							i;
	std::vector<std::string>		Tmp;

	if (g_ptr)
	{
		Tmp = GetTargets::CreateTargetsVector(PrimeImplicants, *g_ptr);
		i = 0;
		while (i < Tmp.size())
		{
			std::cout << Tmp[i] << std::endl;
			i++;
		}
		if (i == 0)
			std::cout << "Empty!" << std::endl;
		else
			std::cout << "-----!" << std::endl;
	}
}*/
