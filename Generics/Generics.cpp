// Generics.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Sorry Dr. Rosiene a software developer is ruining your code :)))

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
    std::cout << "\n The result is " << (FactorialSolution*)result; // This is a down cast

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



    std::cout << "\n!--SORT TEST--!\n" << "Select a sorting algorithm, number of times to double N, and number of test iterations.\n";


    auto random_integer = []() {
        std::random_device rd;     // Only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(0, 100); // Guaranteed unbiased
        return uni(rng); };

    //input
    //could probably be command line arguments

    std::cout << "Which algorithm? [D]ivide and conquer, [G]reedy, [L]as Vegas or [M]onte Carlo?: ";
    char mode;
    std::cin >> mode;

    std::cout << "What is the lower bound of N?: ";
    int n;
    std::cin >> n;

    std::cout << "What is the upper bound of N?: ";
    int num_doubles;
    std::cin >> num_doubles;

    std::cout << "How many test iterations?: ";
    int iterations;
    std::cin >> iterations;

    std::cout << "Print lists? [Y/N]: ";
    char print_lists;
    std::cin >> print_lists;


    std::cout << "Time to sort :)" << std::endl;
    std::cout << std::flush;

    Problem* mySortProblem1;
    Problem* mySortProblem2;
    Problem* mySortProblem3;
    Problem* mySortProblem4;
    Sorted* SortedList;
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    std::chrono::microseconds us_int;
    //std::vector<int> averages(iterations);

    for (int i = 0; i < iterations; i++) {
        std::cout << "\nIteration " << i + 1 << std::endl;
        int listSize = n;

        for (int r = 0; r < num_doubles; r++) {
            if (r != 0)
                listSize += 1;
            std::vector<int> v(listSize);

            if (print_lists == 'Y')
                std::cout << "\tList Size (n) is " << listSize << std::endl;
            else
                std::cout << listSize << ',';



            switch (mode) {
            case 'D': //divide and conquer sort
                std::generate(v.begin(), v.end(), random_integer);
                mySortProblem1 = SortIt_Using_Heap(v);

                t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveDivideAndConquer(mySortProblem1);
                t2 = std::chrono::high_resolution_clock::now();
                us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

                if (print_lists == 'Y')
                    std::cout << "\t\tList Sorted (Divide and conquer)" << SortedList << "\t\tTime: " << (long long)us_int.count() << "us";
                else
                    std::cout << (long long)us_int.count();

                break;

            case 'G': //greedy sort
                std::generate(v.begin(), v.end(), random_integer);
                mySortProblem2 = SortIt_Using_Heap(v);

                t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveGreedy(mySortProblem2);
                t2 = std::chrono::high_resolution_clock::now();
                us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

                if (print_lists == 'Y')
                    std::cout << "\t\tList Sorted (Greedy)" << SortedList << "\t\tTime: " << (long long)us_int.count() << "us";
                else
                    std::cout << (long long)us_int.count();

                break;

            case 'L': //las vegas sort
                std::generate(v.begin(), v.end(), random_integer);
                mySortProblem3 = SortIt_Using_Heap(v);

                t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveLasVegas(mySortProblem3);
                t2 = std::chrono::high_resolution_clock::now();
                us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

                if (print_lists == 'Y')
                    std::cout << "\t\tList Sorted (Las Vegas)" << SortedList << "\t\tTime: " << (long long)us_int.count() << "us";
                else
                    std::cout << (long long)us_int.count();

                break;

            case 'M': //monte carlo sort
                std::generate(v.begin(), v.end(), random_integer);
                mySortProblem4 = SortIt_Using_Heap(v);

                t1 = std::chrono::high_resolution_clock::now();
                SortedList = (Sorted*)SortIt::solveMonteCarlo(mySortProblem4);
                t2 = std::chrono::high_resolution_clock::now();
                us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

                if (print_lists == 'Y')
                    std::cout << "\t\tList Sorted (Monte Carlo 1000 Iterations)" << SortedList << "\t\tTime: " << (long long)us_int.count() << "us";
                else
                    std::cout << (long long)us_int.count();
                break;
            }
            std::cout << std::endl;
        }
    }
}