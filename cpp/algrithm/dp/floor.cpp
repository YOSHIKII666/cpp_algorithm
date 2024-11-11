//
// Created by 王少泽 on 2024/11/11.
//

#include "floor.h"
#include<vector>
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size()+1);
        for(int i=2;i<=cost.size();i++){
            dp[i]=std::min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2]);
        }
        return dp[cost.size()];
    }
};