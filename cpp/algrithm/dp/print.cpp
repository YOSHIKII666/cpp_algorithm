//
// Created by 王少泽 on 2024/11/27.
//

#include<vector>
class print {
public:
    int mincost(std::vector<std::vector<int>>& costs) {
        std::vector<std::vector<int>> dp(costs.size(),std::vector<int>(3));
        dp[0][0]=costs[0][0];
        dp[0][0]=costs[0][1];
        dp[0][0]=costs[0][2];
        for(int i=1;i<costs.size();i++) {
            dp[i][0]=std::min(dp[i-1][1],dp[i-1][2])+costs[i][0];
            dp[i][1]=std::min(dp[i-1][0],dp[i-1][2])+costs[i][1];
            dp[i][2]=std::min(dp[i-1][1],dp[i-1][0])+costs[i][2];
        }
        return std::min(std::min(dp[costs.size()-1][0],dp[costs.size()-1][1]),dp[costs.size()-1][2]);
    }
};
