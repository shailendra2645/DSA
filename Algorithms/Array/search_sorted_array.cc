#include <iostream>
#include <vector>

// ANSI escape codes for colored output
// \033 tells terminal it is special command for formatting
// [ start the specific formatting instruction
// 1 means "bold" or "bright" text
// 31 is color for red
// m at end tells that formatting instruction is complete
const std::string RED_TEXT = "\033[1;31m";
const std::string GREEN_TEXT = "\033[1;32m";
const std::string RESET_TEXT = "\033[0m";

int searchRotatedSortedArray(const std::vector<int> &nums, int target);

int main()
{
    std::vector<std::vector<int>> vectors = {
        {4, 5, 6, 7, 0, 1, 2},     // Rotated at index 3
        {10, 11, 12, 15, 1, 2, 3}, // Rotated at index 4
        {30, 40, 50, 5, 10, 20},   // Rotated at index 3
        {7, 9, 11, 12, 5},         // Rotated at index 4
        {5, 6, 7, 8, 1, 2, 3, 4},  // Rotated at index 4
        {4, 5, 6, 7, 0, 1, 2},     // Rotated at index 3
        {10, 11, 12, 15, 1, 2, 3}, // Rotated at index 4
        {30, 40, 50, 5, 10, 20},   // Rotated at index 3
        {7, 9, 11, 12, 5},         // Rotated at index 4
        {5, 6, 7, 8, 1, 2, 3, 4},  // Rotated at index 4
        {5},                       // Single element
        {3, 1},                    // Only two elements, rotated
        {2, 2, 2, 3, 4, 2},        // Repeating elements with rotation
        {1, 1, 1, 1, 1, 1, 2}      // Mostly duplicates, rotated once
    };

    std::vector<int> targets = {0, 15, 20, 5, 8, 3, 14, 25, 0, 9, 5, 1, 4, 2};
    std::vector<int> results = {4, 3, 5, 4, 3, -1, -1, -1, -1, -1, 0, 1, 4, 6};

    bool all_test_passed = true;
    for (size_t i = 0; i < vectors.size(); ++i)
    {
        int result = searchRotatedSortedArray(vectors[i], targets[i]);
        if (result != results[i])
        {
            std::cout << RED_TEXT << "Test failed for vector at " << i << " index\n"
                      << RESET_TEXT;
            all_test_passed = false;
        }
    }
    if (all_test_passed)
    {
        std::cout << GREEN_TEXT << "All test passed.\n"
                  << RESET_TEXT;
    }
}

int searchRotatedSortedArray(const std::vector<int> &nums, int target)
{
    int start = 0;
    int end = nums.size() - 1;

    // Using binary search
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (target == nums[mid])
        {
            return mid;
        }

        bool left_half_sorted = nums[start] <= nums[mid];
        if (left_half_sorted)
        {
            bool in_left_half = nums[start] <= target && target <= nums[mid];
            if (in_left_half)
            {
                end = mid - 1; // search in left half
            }
            else
            {
                start = mid + 1; // otherwise in right half
            }
        }
        else
        {
            bool in_right_half = nums[mid] <= target && target <= nums[end];
            if (in_right_half)
            {
                start = mid + 1; // search in right half
            }
            else
            {
                end = mid - 1; // otherwise in left half
            }
        }
    }

    return -1;
}