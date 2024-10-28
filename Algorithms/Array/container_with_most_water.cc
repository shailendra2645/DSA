#include <iostream>
#include <vector>

long long bruteForce(const std::vector<int> &heights);
long long twoPointer(const std::vector<int> &heights);

int main()
{
    std::vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    std::cout << bruteForce(heights) << std::endl;
    std::cout << twoPointer(heights) << std::endl;
    return 0;
}

long long bruteForce(const std::vector<int> &heights)
{
    long long max_water = 0LL;
    for (size_t left = 0; left < heights.size(); ++left)
    {
        for (size_t right = left + 1; right < heights.size(); ++right)
        {
            long long width = right - left;
            long long height = std::min(heights[left], heights[right]);
            long long current_water = width * height;
            max_water = std::max(current_water, max_water);
        }
    }
    return max_water;
}

long long twoPointer(const std::vector<int> &heights)
{
    long long max_water = 0;
    auto left = heights.begin();
    auto right = heights.end() - 1;

    while (left != right)
    {
        auto width = right - left;
        if (*left < *right)
        {
            auto current_water = width * *left++;
            max_water = std::max(current_water, max_water);
        }
        else
        {
            auto current_water = width * *right--;
            max_water = std::max(current_water, max_water);
        }
    }

    return max_water;
}
