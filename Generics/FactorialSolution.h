#pragma once
#include <iostream>
#include "aSolution.h"

// The FactorialSolution based on the abstract base class aSolution
class FactorialSolution : public aSolution
{
public:
	int answer;
	FactorialSolution(int n) { answer = n; };

};

inline std::ostream& operator<<(std::ostream& os, const FactorialSolution * factres)
{
	os << factres->answer;
	return os;
}