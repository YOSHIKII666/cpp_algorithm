//
// Created by 王少泽 on 2024/11/12.
//

#include "vector"

class Solution {
public:
    std::vector<std::vector<int>> grid;
    int max=0;
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        this->grid=grid;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1){
                    max=std::max(dfs(i,j,0),max);
                }
            }
        }
        return max;
    }
    int dfs(int i,int j,int sum){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]==0){
            return 0;
        }
        grid[i][j]=0;
        sum=1;
        return sum+=dfs(i+1,j,sum)+dfs(i-1,j,sum)+dfs(i,j+1,sum)+dfs(i,j-1,sum);
    }
};