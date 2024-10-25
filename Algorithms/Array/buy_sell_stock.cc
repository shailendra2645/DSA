#include <iostream>
#include <vector>

int maxProfit(const std::vector<int> &prices);

int main()
{
    std::vector<int> prices = {7, 1, 5, 3, 6, 4};
    std::cout << maxProfit(prices) << std::endl;
    return 0;
}

int maxProfit(const std::vector<int> &prices)
{
    if (prices.empty())
        return 0;

    int min_buy_price = prices[0];
    int max_profit = 0;

    // Iterate over the prices starting from the second day
    for (auto price = prices.cbegin() + 1; price != prices.cend(); ++price)
    {

        int current_price = *price;
        int current_profit = current_price - min_buy_price;

        // Update max_profit if the current profit is higher
        max_profit = std::max(max_profit, current_profit);

        // Update min_buy_price if a new lower price is found
        min_buy_price = std::min(min_buy_price, current_price);
    }

    return max_profit;
}