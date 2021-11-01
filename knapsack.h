#include <vector>

using namespace std;
// weight, price
int knapsack_helper(vector<vector<int>>& memo, const vector<pair<int, int>>& items, int weight, int i) {
    if (i == items.size() || weight < 0) {
        return 0;
    }
    if (memo[weight][i] != -1) {
        return memo[weight][i];
    }
    int better = knapsack_helper(memo, items, weight, i+1);
    
    int new_weight = weight - items[i].first;
    if (new_weight >= 0){
        int select = knapsack_helper(memo, items, new_weight, i+1) + items[i].second;
        if (select > better){
            better = select;
        }
    }

    return memo[weight][i] = better;
}

int knapsack(int weight, vector<pair<int, int>> items) {
    vector<vector<int>> memo(weight+1, vector<int> (items.size(), -1));
    return knapsack_helper(memo, items, weight, 0);
}

int bottomup_knapsack(int weight, const vector<pair<int, int>>& items) {
    vector<vector<int>> dp(weight+1, vector<int> (items.size(), -1));
    for(int w = 0; w <= weight; w++) {
        dp[w][0] = w >= items[0].first ? items[0].second : 0;
    }
    for(int i = 1; i < items.size(); i++) {
        for(int w = 0; w <= weight; w++) {
            int best = dp[w][i-1];
            int new_weight = w - items[i].first;
            if (new_weight >= 0) {
                int alt = dp[new_weight][i-1] + items[i].second;
                if (alt > best) {
                    best = alt;
                }
            }
            dp[w][i] = best;
        }
    }
    return dp[weight][items.size() - 1];
}