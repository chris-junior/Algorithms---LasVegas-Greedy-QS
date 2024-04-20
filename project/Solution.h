#pragma once

#include <vector>

class Solution {
private:
    std::vector<int> result;

public:
    Solution() = default;
    Solution(const std::vector<int>& solution);

    const std::vector<int>& getResult() const;
    void setResult(const std::vector<int>& solution);
};
