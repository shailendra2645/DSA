#include <iostream>
#include <vector>
#include <algorithm>

int majorityElement(const std::vector<int> &nums);
int majorityElementBruteForce(const std::vector<int> &nums);
int majorityElementSorting(std::vector<int> nums);

int main()
{
    std::vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    std::cout << majorityElement(nums) << std::endl;
    std::cout << majorityElementBruteForce(nums) << std::endl;
    std::cout << majorityElementSorting(nums) << std::endl;
}

// Boyer-Moore Voting Algorithm
int majorityElement(const std::vector<int> &nums)
{
    if (nums.empty())
        return INT_MIN; // Handle empty array

    int count = 0;
    int candidate = nums[0];

    for (const int &num : nums)
    {
        if (count == 0)
        {
            candidate = num;
        }
        if (num == candidate)
        {
            count++;
        }
        else
        {
            count--;
        }
    }

    count = 0;
    for (const int &num : nums)
    {
        if (num == candidate)
        {
            count++;
        }
    }

    if (count > nums.size() / 2)
    {
        return candidate;
    }

    return INT_MIN;
}

int majorityElementBruteForce(const std::vector<int> &nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        int count = 1;
        for (int j = i + 1; j < nums.size(); ++j)
        {
            if (nums[i] == nums[j])
            {
                ++count;
            }
        }

        if (count > nums.size() / 2)
        {
            return nums[i];
        }
    }

    return INT_MIN;
}

int majorityElementSorting(std::vector<int> nums)
{
    // The majority element will always be in the
    // middle of the sorted array as it occupies more
    // than n / 2 portion of array if it exists

    auto middle = nums.size() / 2;
    std::sort(nums.begin(), nums.end());

    size_t count = 0;
    for (const auto &num : nums)
    {
        if (num == nums[middle])
        {
            ++count;
        }
    }
    if (count > nums.size() / 2)
        return nums[middle];
    return INT_MIN;
}
