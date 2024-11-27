#include<vector>
class solution{
public:
    int findNumberOfLIS(std::vector<int>& nums){
        int max=0;
        int ans=0;
        int n=nums.size();
        std::vector<int>dp(n);
        std::vector<int> cnt(n);
        for(int i=0;i<n;i++){
            dp[i]=1;
            cnt[i]=1;
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    if(dp[i]==dp[j]+1){
                        cnt[i]+=cnt[j];
                    }else if(dp[i]<dp[j]+1){
                        cnt[i]=cnt[j];
                        dp[i]=dp[j]+1;
                    }
                }
            }
            if(max<dp[i]){
                max=dp[i];
                ans=cnt[i];
            }else if(max==dp[i]){
                ans+=cnt[i];
            }
        }
        return ans;
    }
};