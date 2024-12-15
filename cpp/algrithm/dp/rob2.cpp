//
// Created by 王少泽 on 2024/12/15.
//

#include "rob2.h"

#include <iostream>

#include "vector"
using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> dp1(nums.size());
        vector<int> dp2(nums.size());
        if(nums.size()==1) return nums[0];
        dp1[0]=std::move(nums[0]);
        dp1[1]=std::max(nums[0],nums[1]);
        for(int i=2;i<nums.size()-1;i++){
            dp1[i]=std::max(dp1[i-2]+nums[i],dp1[i-1]);
        }
        dp2[1]=nums[1];
        for(int i=2;i<nums.size();i++){
            dp2[i]=std::max(dp2[i-2]+nums[i],dp2[i-1]);
        }
        return std::max(dp1[nums.size()-2],dp2[nums.size()-1]);
    }
};

