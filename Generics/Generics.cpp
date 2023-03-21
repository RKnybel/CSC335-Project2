// Generics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
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



    std::cout << "\n!--SORT TEST--!\n";

    auto random_integer = []() {
        std::random_device rd;     // Only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(0, 100); // Guaranteed unbiased
        return uni(rng);};

    std::cout << "Which algorithm? [R]ecursive, [G]reedy, [L]as Vegas or [M]onte Carlo?: ";
    char mode = 'R';
    std::cin >> mode;

    std::cout << "How many items in the vector?: ";
    int list_size = 6;
    std::cin >> list_size;

    std::cout << "How many test iterations?: ";
    int iterations = 8;
    std::cin >> iterations;
    
    std::vector<int> v(list_size);
    auto mySortProblem1 = SortIt_Using_Heap(v);
    auto mySortProblem2 = SortIt_Using_Heap(v);
    auto mySortProblem3 = SortIt_Using_Heap(v);
    auto mySortProblem4 = SortIt_Using_Heap(v);
    auto SortedList = (Sorted*)SortIt::solveRecursive(mySortProblem1); //heheh you didnt see this
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

    for (int i = 0; i < iterations; i++) {
        std::cout << "\nIteration " << i + 1 << std::endl;

        switch (mode) {
        case 'R':
            std::generate(v.begin(), v.end(), random_integer);
            mySortProblem1 = SortIt_Using_Heap(v);

            t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveRecursive(mySortProblem1);
            t2 = std::chrono::high_resolution_clock::now();
            us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

            std::cout << "    List Sorted (recursive)" << SortedList << "    Time: " << (long long)us_int.count() <<"us";
        break;

        case 'G':
            std::generate(v.begin(), v.end(), random_integer);
            mySortProblem2 = SortIt_Using_Heap(v);

            t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveGreedy(mySortProblem2);
            t2 = std::chrono::high_resolution_clock::now();
            us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

            std::cout << "List Sorted (Greedy)" << SortedList << "    Time: " << (long long)us_int.count() << "us";
        break;

        case 'L':
            std::generate(v.begin(), v.end(), random_integer);
            mySortProblem3 = SortIt_Using_Heap(v);

            t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveLasVegas(mySortProblem3);
            t2 = std::chrono::high_resolution_clock::now();
            us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

            std::cout << "List Sorted (Las Vegas)" << SortedList << "    Time: " << (long long)us_int.count() << "us";
        break;

        case 'M':
            std::generate(v.begin(), v.end(), random_integer);
            mySortProblem4 = SortIt_Using_Heap(v);

            t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveMonteCarlo(mySortProblem4);
            t2 = std::chrono::high_resolution_clock::now();
            us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

            std::cout << "List Sorted (Monte Carlo 1000 Iterations)" << SortedList << "    Time: " << (long long)us_int.count() << "us";
        break;
        }
    }
}

