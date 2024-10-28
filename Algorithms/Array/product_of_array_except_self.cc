#include <iostream>
#include <vector>

std::vector<int> productExceptSelf(const std::vector<int> &nums);

int main()
{
    std::vector<int> nums = {1, 2, 3, 4};
    auto answer = productExceptSelf(nums);
    for (auto a : answer)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

std::vector<int> productExceptSelf(const std::vector<int> &nums)
{
    std::vector<int> result(nums.size(), 1);

    // Calculate prefix products
    for (int i = 1; i < nums.size(); ++i)
    {
        result[i] = result[i - 1] * nums[i - 1];
    }

    // Calculate suffix products and combine them with prefix products
    int suffix = 1;
    for (int i = nums.size() - 2; i >= 0; --i)
    {
        suffix *= nums[i + 1];
        result[i] *= suffix;
    }

    return result;
}
