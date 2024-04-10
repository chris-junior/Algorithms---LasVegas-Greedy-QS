#include "SearchAndSortProblem.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "Solution.h"

SearchAndSortProblem::SearchAndSortProblem(size_t size) : data(size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    for (size_t i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
}

bool SearchAndSortProblem::solved() const {
    return std::is_sorted(data.begin(), data.end());
}

bool SearchAndSortProblem::trivial() const {
    return data.size() <= 1;
}

Solution SearchAndSortProblem::createSolution() const {
    std::vector<int> sortedData = data;
    merge_sort(sortedData);
    return Solution(sortedData);
}

std::vector<std::shared_ptr<Problem>> SearchAndSortProblem::makeSubproblems() const {
    std::vector<std::shared_ptr<Problem>> subproblems;

    if (data.size() > 1) {
        size_t mid = data.size() / 2;

        std::vector<int> leftData(data.begin(), data.begin() + mid);
        std::vector<int> rightData(data.begin() + mid, data.end());

        subproblems.push_back(std::make_shared<SearchAndSortProblem>(leftData.size()));
        subproblems.push_back(std::make_shared<SearchAndSortProblem>(rightData.size()));
    }

    return subproblems;
}

Solution SearchAndSortProblem::combineSolutions(const std::vector<Solution>& partialSolutions) const {
    std::vector<int> mergedData;
    for (const auto& solution : partialSolutions) {
        mergedData.insert(mergedData.end(), solution.getResult().begin(), solution.getResult().end());
    }

    merge_sort(mergedData);
    return mergedData;
}

void SearchAndSortProblem::merge_sort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    int mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());
    merge_sort(left);
    merge_sort(right);
    std::merge(left.begin(), left.end(), right.begin(), right.end(), arr.begin());
}
