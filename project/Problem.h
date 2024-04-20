#pragma once

#include <vector>
#include <memory>

class Solution;

class Problem {
public:
    virtual bool solved() const = 0;
    virtual bool trivial() const = 0;
    virtual Solution createSolution() const = 0;
    virtual std::vector<std::shared_ptr<Problem>> makeSubproblems() const = 0;
    virtual Solution combineSolutions(const std::vector<Solution>& partialSolutions) const = 0;

    virtual ~Problem() {}
};
