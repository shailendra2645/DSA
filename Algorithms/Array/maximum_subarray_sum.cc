#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

void printAllSubarrays(const std::vector<int> &nums);
int maxSubarraySumBruteForce(const std::vector<int> &nums);
int maxSubarraySumOptimized(const std::vector<int> &nums);
int maxSubarraySumKadane(const std::vector<int> &nums);

int main()
{
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    printAllSubarrays(nums);

    std::cout << "The max subarray sum is:\n";
    std::cout << maxSubarraySumBruteForce(nums) << std::endl;
    std::cout << maxSubarraySumOptimized(nums) << std::endl;
    std::cout << maxSubarraySumKadane(nums) << std::endl;
}

int maxSubarraySumKadane(const std::vector<int> &nums)
{
    if (nums.empty())
    {
        throw std::invalid_argument("The input array is empty.");
    }
    int max_sum = INT_MIN;
    int current_sum = 0;

    for (const int &num : nums)
    {
        current_sum += num;
        max_sum = std::max(max_sum, current_sum);
        if (current_sum < 0)
        {
            current_sum = 0;
        }
    }

    return max_sum;
}

// Prints all subarrays for the given array
// with some formatting
void printAllSubarrays(const std::vector<int> &nums)
{
    // Define the start for each subarray
    for (size_t start = 0; start < nums.size(); ++start)
    {
        // Define the end for each subarray
        for (size_t end = start; end < nums.size(); ++end)
        {
            std::string subarray = "[";

            // Prints the element of each subarray
            for (size_t i = start; i <= end; ++i)
            {
                subarray += std::to_string(nums[i]);

                if (i < end)
                {
                    subarray += ", ";
                }
            }
            std::cout << subarray << "]\n";
        }
        std::cout << std::endl;
    }
}

int maxSubarraySumBruteForce(const std::vector<int> &nums)
{
    decltype(nums.size()) n = nums.size();
    int max_sum = INT_MIN;

    // Define the start for each subarray
    for (size_t start = 0; start < n; ++start)
    {
        // Define the end for each subarray
        for (size_t end = start; end < n; ++end)
        {
            int current_sum = 0;

            // Accumulate the sum for each subarray
            for (size_t i = start; i <= end; ++i)
                current_sum += nums[i];

            max_sum = std::max(max_sum, current_sum);
        }
    }

    return max_sum;
}

int maxSubarraySumOptimized(const std::vector<int> &nums)
{
    if (nums.empty())
    {
        throw std::invalid_argument("The input array is empty.");
    }

    decltype(nums.size()) n = nums.size();
    int max_sum = INT_MIN;

    // Define the start for each subarray
    for (size_t start = 0; start < n; ++start)
    {
        int current_sum = 0;

        // Expand the subarray ending at each index
        for (size_t end = start; end < n; ++end)
        {
            current_sum += nums[end];

            max_sum = std::max(max_sum, current_sum);
        }
    }

    return max_sum;
}
