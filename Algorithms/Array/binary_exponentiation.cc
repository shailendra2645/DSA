#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <string>

double power(double base, int exponent);
const double TOLERANCE = 1e-9;

// ANSI escape codes for colored output
// \033 tells terminal it is special command for formatting
// [ start the specific formatting instruction
// 1 means "bold" or "bright" text
// 31 is color for red
// m at end tells that formatting instruction is complete
const std::string RED_TEXT = "\033[1;31m";
const std::string GREEN_TEXT = "\033[1;32m";
const std::string RESET_TEXT = "\033[0m";

int main()
{
    // Test cases
    struct TestCase
    {
        double base;
        int exponent;
    };

    TestCase test_caes[] = {
        {2.0, 3},   // 2^3 = 8
        {2.0, -3},  // 2^-3 = 0.125
        {5.0, 0},   // 5^0 = 1
        {1.0, 100}, // 1^100 = 1
        {0.0, 5},   // 0^5 = 0
        {2.5, 2},   // 2.5^2 = 6.25
        {-2.0, 3},  // (-2)^3 = -8
        {-2.0, 4},  // (-2)^4 = 16
        {2.0, -1},  // 2^-1 = 0.5
        {0.0, -1},  // Edge case: 0^-1, should throw an error or handle gracefully: return infinity
        {1.0, -1000},
    };
    bool all_test_passed = true;

    std::cerr << std::fixed << std::setprecision(10);
    for (const auto &test : test_caes)
    {
        double my_result = power(test.base, test.exponent);
        double expected_result = std::pow(test.base, test.exponent);

        if (std::abs(my_result - expected_result) > TOLERANCE)
        {
            all_test_passed = false;
            std::cerr << RED_TEXT << "Test failed for base = " << test.base
                      << ", exponent = " << test.exponent << RESET_TEXT << std::endl;
            std::cerr << "Expected: " << expected_result
                      << ", Got: " << my_result << std::endl;
        }
    }

    if (all_test_passed)
    {
        std::cout << GREEN_TEXT << "All Test cases passed sucessfully.\n"
                  << RESET_TEXT;
    }
}

double power(double base, int exponent)
{
    if (exponent == 0)
        return 1.0;
    if (base == 1)
        return base;
    if (base == -1)
        return exponent % 2 == 0 ? 1.0 : base;

    unsigned long long abs_exponent = static_cast<unsigned long long>(std::abs(exponent));
    double result = 1.0;

    if (exponent < 0)
    {
        base = 1.0 / base;
    }

    // binary exponentiation
    while (abs_exponent != 0)
    {
        if (abs_exponent % 2 == 1)
        {
            result *= base;
        }

        base *= base;
        abs_exponent /= 2;
    }

    return result;
}
