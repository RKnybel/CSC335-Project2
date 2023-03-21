// Generics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include "Factorial.h"
#include "SortIt.h"

int main()
{
    // Since Factorial is a concrete implementation of the ABC Problem, we can apply solveRecursive to it.

    auto result = Factorial::solveRecursive(new Factorial(3));
    // What follows is a downcast, since we are going from a abstract base class to a concrete derived class.
    // generally not a good practice, but since every concrete solution class may have different answers this is
    // and example of the Dependency Inversion Principle, of S.O.L.I.D. the algorithm to solve the problem doesn't need to 
    // know what the solution looks like.

    std::cout << "!--FACTORIAL TEST--!\n";
    std::cout << "\n The result is "<< (FactorialSolution *) result; // This is a down cast

    // but to adhere to the Liskov Substitution Principle  we can have our solution overload the
    // ostream& operator<< and use the abstraction so the person using the Factorial Problem doesn't need to 
    // know about the result class variable.

    result = Factorial::solveRecursive(new Factorial(6));
    std::cout << "\n The result is " << (FactorialSolution*)result; // This is a down cast
    try {
        auto result2 = Factorial::solveDivideAndConquer(new Factorial(5));
    }
    catch (const std::exception& e) {
        std::cout << "\n Caught exception \"" << e.what() << "\"\n";
    }



    std::cout << "!--SORT TEST--!\n";

    auto random_integer = []() {
        std::random_device rd;     // Only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(0, 100); // Guaranteed unbiased
        return uni(rng);};

    
    
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), random_integer);
    auto mySortProblem1 = SortIt_Using_Heap(v);
    auto SortedList = (Sorted *) SortIt::solveRecursive(mySortProblem1);
    std::cout << "List Sorted (recursive)" << SortedList;

    std::generate(v.begin(), v.end(), random_integer);
    auto mySortProblem2 = SortIt_Using_Heap(v);
    SortedList = (Sorted*)SortIt::solveGreedy(mySortProblem2);
    std::cout << "List Sorted (Greedy)" << SortedList;

    std::generate(v.begin(), v.end(), random_integer);
    auto mySortProblem3 = SortIt_Using_Heap(v);
    SortedList = (Sorted*)SortIt::solveLasVegas(mySortProblem2);
    std::cout << "List Sorted (Las Vegas)" << SortedList;
}

