//
// Created by 王少泽 on 2024/11/22.
//

#include<vector>

class solution {
    public:
    int longestArith(std::vector<int>& vec) {
        int n=vec.size();
        int ans=2;
        std::vector<std::vector<int>> dp(n,std::vector<int>(n,1001));
        for(int i=1;i<n;i++) {
            for(int j=0;j<i;j++) {
                int distance=vec[i]-vec[j]+500;
                dp[i][distance]=std::max(dp[i][distance],dp[j][distance]+1);
                ans=std::max(ans,dp[i][distance]);
            }
        }
        return ans;
    }
};
