//
// Created by 王少泽 on 2024/11/23.
//

#include <vector>

class solution {
public:
    int minASCII(std::string s1,std::string s2) {
        int m=s1.size();
        int n=s2.size();
        std::vector<std::vector<int>> dp(m+1,std::vector<int>(n+1,0));
        for(int i=1;i<=m;i++) {
            dp[i][0]=dp[i-1][0]+s1[i-1];
        }
        for(int j=1;j<=n;j++) {
            dp[0][j]=dp[0][j-1]+s2[j-1];
        }
        for(int i=1;i<=m;i++) {
            for(int j=1;j<=n;j++) {
                int x=s1[i-1];
                int y=s2[j-1];
                if(s1[i-1]==s2[j-1]) {
                    dp[i-1][j-1]=dp[i][j];
                }else {
                    dp[i][j]=std::min(std::min(dp[i-1][j]+x,dp[i-1][j-1]+x+y),dp[i][j-1]+y);
                }
            }
        }
        return dp[m][n];
    }
};
