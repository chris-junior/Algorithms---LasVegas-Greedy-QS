#include "Solution.h"

Solution::Solution(const std::vector<int>& solution) : result(solution) {}

const std::vector<int>& Solution::getResult() const {
    return result;
}

void Solution::setResult(const std::vector<int>& solution) {
    result = solution;
}
