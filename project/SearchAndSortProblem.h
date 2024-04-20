#pragma once

#include "Problem.h"
#include <vector>
#include <memory>

class SearchAndSortProblem : public Problem {
private:
    std::vector<int> data;

    static void merge_sort(std::vector<int>& arr);
    static void heap_sort(std::vector<int>& arr);
    static void quick_sort(std::vector<int>& arr);

public:
    SearchAndSortProblem(size_t size);

    bool solved() const override;
    bool trivial() const override;
    Solution createSolution() const override;
    std::vector<std::shared_ptr<Problem>> makeSubproblems() const override;
    Solution combineSolutions(const std::vector<Solution>& partialSolutions) const override;
};
