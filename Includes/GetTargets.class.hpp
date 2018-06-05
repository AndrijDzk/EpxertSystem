/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetTargets.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:10:03 by imarakho          #+#    #+#             */
/*   Updated: 2018/04/24 15:23:36 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <exception>

#include "ReturnCodes.hpp"

#include "Op.class.hpp"

typedef std::vector<std::vector<char> >	VVC;

class									GetTargets
{
public:
	static std::vector<std::string>		Get(std::string const &left);
	static bool							ChangeSet(VVC const &mini_t, std::vector<size_t> &PrimeSet, std::vector<size_t> const &Essen, size_t PrimesAmount, size_t MinitermsAmount);

private:
	static bool							SetCoverAllMiniterms(std::vector<size_t > covBySet,std::vector<size_t > covByEssen,size_t mini_t_ammount);
	static std::vector<size_t>			MiniTermsCoveredByPrimeCombination(VVC const &mini_t, std::vector<size_t> const &prime_index);
	static std::vector<size_t>			GetMini_terms_covered_by_essentials(VVC &mini_t,std::vector<size_t> es);
	static std::vector<size_t>			GetEssentials(VVC &mini_t);
	static void							PetricksMethod(VVC &Prime, VVC &mini_t,size_t MinitermAmount);
	static std::string					GetFacts(std::string const &left);
	static bool							SetSatisfiesRule(std::string const &left, std::string const &Facts, std::vector<char> const &Fact_values);
	static void							ApplyOp(std::stack<bool> &buff, char Operator);
	static int							Increment(std::vector<char> &values);
	static VVC							SimplifyTable(VVC &Table);
	static int							ImplicantsCanBeCombined(std::vector<char> const &Imp1, std::vector<char> const &Imp2);
	static VVC							CreateMinitermTable(size_t size);
	static std::vector<char>			CreateMinitermVector(std::vector<char> const &Imp1Mtrs, std::vector<char> const &Imp2Mtrs);
	static void							AddMinitermsToVector(std::vector<char> &res, std::vector<char> const &NewMiniterms);
	static std::vector<std::string>		CreateTargetsVector(VVC const &Table, std::string const &Facts);
	static std::vector<size_t>			CreatePrimeSet(size_t Start, size_t Len, std::vector<size_t> const &Essen, size_t PrimesAmount);
	static void							PrintTargetsVector(VVC const &PrimeImplicants);
										GetTargets(void);
										GetTargets(GetTargets const &src);
										~GetTargets(void);
	GetTargets							&operator=(GetTargets const &rhs);
};
