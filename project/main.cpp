#include <iostream>
#include <random>
#include <memory>
#include "SearchAndSortProblem.h"
#include "Solution.h"

int main() {
    constexpr size_t dataSize = 10;
    SearchAndSortProblem problem(dataSize);

    Solution mergeSortSolution = problem.createSolution();
    std::cout << "Merge Sort Result: ";
    for (const auto& num : mergeSortSolution.getResult()) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    Solution bestActionSolution = problem.createSolution();
    std::cout << "Best Action (Merge Sort) Result: ";
    for (const auto& num : bestActionSolution.getResult()) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
    int choice = dis(gen);

    switch (choice) {
    case 0:
        std::cout << "Random Action Result (Merge Sort): ";
        break;
    case 1:
        std::cout << "Random Action Result (Heap Sort): ";
        break;
    case 2:
        std::cout << "Random Action Result (Quick Sort): ";
        break;
    default:
        std::cout << "Random Action Result: ";
        break;
    }

    Solution randomActionSolution = problem.createSolution();
    for (const auto& num : randomActionSolution.getResult()) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
