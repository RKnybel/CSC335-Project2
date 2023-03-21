#pragma once
#include <iostream>
#include <stdexcept>
#include "Problem.h"
#include "FactorialSolution.h"

// The FactorialSolution based on the abstract base class aSolution

// The Factorial Problem
class Factorial :
	public Problem
{
	int partial_result = 1; 
	int n;
public: 
	Factorial(int n_in) { n=partial_result = (n_in==0)?1:n=n_in;};
	Factorial(int n_in, int soFar) { partial_result = n_in * soFar;n = n_in; };
	bool trivial() { return n <= 1; };
	bool solved() { return true; };

	void applyRandomAction() {};
	
	// Need to create a solution
	class aSolution* createSolution() {
		return new FactorialSolution(partial_result);
	};

	class Problem* simplifyProblem() { return  new Factorial(n - 1,this->partial_result); };

	// Dummy routines, not used but need to make a stub to the Factorial Problem class concrete.
	// might be able to force the compiler to ignore the undefined virtual functions and create a concrete class
	// but best to provide a stub and throw an error. Since is someone attempts to solve the Factorial using
	// and unsupported design pattern.

	class aSolution* combineSolutions(std::vector<aSolution*> partialSolutions) 
	{	throw std::runtime_error("Not Implemented in the Factorial Problem"); 
		return new FactorialSolution(1); 
	};
	std::vector<Problem*> make_subproblems() 
	{
		throw std::runtime_error("Not Implemented in the Factorial Problem");
		return std::vector < Problem *>{new Factorial(1)}; 
	};
	bool better(class Problem * Reference) {
		throw std::runtime_error("Not Implemented in the Factorial Problem");
		return false;
	};
	void selectBestAction() {
		throw std::runtime_error("Not Implemented in the Factorial Problem");
	};

	int numSorted(){
		throw std::runtime_error("Not Implemented in the Factorial Problem");
	}
	
};
