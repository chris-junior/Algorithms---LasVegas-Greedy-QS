// Generics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include < chrono >
#include "SortIt.h"


int main()
{

    auto random_integer = []() {
        std::random_device rd;     // Only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(0, 100); // Guaranteed unbiased
        return uni(rng);};

   
    for (int itter = 5; itter < 17; itter++) {
        SortIt::N = 1 << itter;
     //   std::cout << "Making Data\n";
        std::vector<int> v(SortIt::N);
        std::generate(v.begin(), v.end(), random_integer);
        auto vals = std::vector<std::any>{ v };
      //  std::cout << "Allocated Data\n";
        auto mySortProblem1 = SortIt_Using_Quick(vals);
      //  std::cout << "Made the problem\n";
        double total_time = 0;
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        Sorted* SortedList;
        SortedList = (Sorted*)SortIt::solveLasVegas(mySortProblem1); // ignore first sort
        for (int trial = 0; trial < 10; trial++) {
            auto mySortProblem1 = SortIt_Using_Quick(vals);
            start_time = std::chrono::high_resolution_clock::now();
            SortedList = (Sorted*)SortIt::solveLasVegas(mySortProblem1);
        //    std::cout << "List Sorted (Las Vegas)";
            end_time = std::chrono::high_resolution_clock::now();
            time = end_time - start_time;
       //     std::cout << "Size  " << SortIt::N << " took " <<
       //         time / std::chrono::milliseconds(1) << " ms to run.\n";
            total_time += time / std::chrono::microseconds(1);
        }
        // This is what you benchmark, but need to do multiple trials(First one is not valid)
     //   std::cout << "Quicksort of " << SortIt::N << " took " << total_time / 10. << "on average ms to run.\n";
        auto QuickTime = total_time / 10.;
        std::generate(v.begin(), v.end(), random_integer);
        auto mySortProblem2 = SortIt_Using_Heap(v);
        // This is what you benchmark 
        start_time = std::chrono::high_resolution_clock::now();
        SortedList = (Sorted*)SortIt::solveGreedy(mySortProblem2);
        // ^^^^^^^
    //    std::cout << "List Sorted (Greedy)";
        end_time = std::chrono::high_resolution_clock::now();
        time = end_time - start_time;
     //   std::cout << "Size  " << SortIt::N << " took " <<
     //       time / std::chrono::microseconds(1) << " us to run.\n";
        auto GreedyTime = time / std::chrono::microseconds(1);
        std::generate(v.begin(), v.end(), random_integer);
        start_time = std::chrono::high_resolution_clock::now();
        auto mySortProblem3 = SortIt_Using_Heap(v);
        // This is what you benchmark 
        SortedList = (Sorted*)SortIt::solveDivideAndConquer(mySortProblem3);
        // ^^^^^^^
     //   std::cout << "List Sorted (Divide and Conquer)";
        end_time = std::chrono::high_resolution_clock::now();
        time = end_time - start_time;
      //  std::cout << "Size  " << SortIt::N << " took " <<
      //      time / std::chrono::microseconds(1) << " us to run.\n";
        auto DivideTime = time / std::chrono::microseconds(1);
        std::cout << SortIt::N << " , " << QuickTime << " , " << GreedyTime << " , " << DivideTime << "\n";
    }
}

